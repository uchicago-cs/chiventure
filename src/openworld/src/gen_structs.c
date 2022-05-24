/*Team RPG-Openworld 
*
* autogenerate.c: This file. Function definitions of the functions
* specified in chiventure/include/autogenerate.h
*
* Room module that autogenerates string of rooms connected via paths when
* a "dead-end" room is entered
*
* See chiventure/include/autogenerate.h header file to see function
* prototypes and purposes
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "openworld/gen_structs.h"
#include "common/utlist.h"
#include "common/uthash.h"

/* See gen_structs.h */
int init_itemspec(itemspec_t *itemspec, char *item_name, double spawn_chance, 
                                        unsigned int min_num, unsigned int max_num)
{
    if (itemspec == NULL) {
        return FAILURE;
    } else if (spawn_chance < 0 || 1 < spawn_chance) {
        return FAILURE;
    } else if (min_num > max_num) {
        return FAILURE;
    }

    strcpy(itemspec->item_name, item_name);
    itemspec->spawn_chance = spawn_chance;
    itemspec->min_num = min_num;
    itemspec->max_num = max_num;

    return SUCCESS;
}

/* See gen_structs.h */
itemspec_t *itemspec_new(char *item_name, double spawn_chance, 
                         unsigned int min_num, unsigned int max_num)
{
    itemspec_t *rv = calloc(1, sizeof(itemspec_t));
    if (rv == NULL) {
        fprintf(stderr, "calloc failed to allocate space for itemspec_new\n");
        return NULL;
    }

    rv->item_name = malloc((MAX_SDESC_LEN + 1) * sizeof(char));
    if (rv->item_name == NULL) {
        fprintf(stderr, "calloc failed to allocate space for itemspec->item_name\n");
        itemspec_free(rv);
        return NULL;
    }

    int rc = init_itemspec(rv, item_name, spawn_chance, min_num, max_num);
    if (rc == FAILURE) {
        itemspec_free(rv);
        return NULL;
    }
    return rv;
}

/* See gen_structs.h */
int itemspec_free(itemspec_t *itemspec)
{
    if (itemspec == NULL) 
        return FAILURE;

    if (itemspec->item_name)
        free(itemspec->item_name);
    
    free(itemspec);
    return SUCCESS;
}

/* see gen_structs.h */
int init_gencontext(gencontext_t *context, path_t *open_paths, int level, int num_open_paths, specgraph_t *specgraph)
{

    if (context == NULL)
        return FAILURE;

    context->level = level;
    context->open_paths = open_paths;
    context->num_open_paths = num_open_paths;
    context->specgraph = specgraph;
    return SUCCESS;
}


/* see gen_structs.h */
gencontext_t* gencontext_new(path_t *open_paths, int level, int num_open_paths, specgraph_t *specgraph)
{

    gencontext_t *contextnew = calloc(1, sizeof(gencontext_t));

    if (contextnew == NULL) {
        fprintf(stderr, "calloc failed to allocate space for contextnew. \n");
        return NULL;
    }

    init_gencontext(contextnew, open_paths, level, num_open_paths, specgraph);
    return contextnew;
}

/* see gen_structs.h */
int gencontext_free(gencontext_t *context)
{

    if (context == NULL)
        return FAILURE;

    free(context);
    return SUCCESS;
}

/* see gen_structs.h */
int roomspec_free(roomspec_t *spec)
{

    if (spec == NULL)
        return FAILURE;

    if (spec->short_desc) {
        free(spec->short_desc);
    }

    if (spec->long_desc) {
        free(spec->long_desc);
    }

    free(spec);
    return SUCCESS;
}

/* see gen_structs.h */
int init_roomspec(roomspec_t *spec, char *room_name, char *short_desc, char *long_desc, item_hash_t *items)
{

    if (spec == NULL)
        return FAILURE;

    spec->room_name = calloc(MAX_SDESC_LEN + 1, sizeof(char));
    if (spec->room_name == NULL) {
        roomspec_free(spec);
        fprintf(stderr, "calloc failed to allocate space for spec's room name.\n");
        return FAILURE;
    }

    spec->short_desc = calloc(MAX_SDESC_LEN + 1, sizeof(char));
    if (spec->short_desc == NULL) {
        roomspec_free(spec);
        fprintf(stderr, "calloc failed to allocate space for spec's short_desc. \n");
        return FAILURE;
    }

    spec->long_desc = calloc(MAX_LDESC_LEN + 1, sizeof(char));
    if (spec->long_desc == NULL) {
        free(spec->short_desc);
        roomspec_free(spec);
        fprintf(stderr, "calloc failed to allocate space for spec's short_desc. \n");
        return FAILURE;
    }

    strncpy(spec->room_name, room_name, MAX_SDESC_LEN);
    strncpy(spec->short_desc, short_desc, MAX_SDESC_LEN);
    strncpy(spec->long_desc, long_desc, MAX_LDESC_LEN);
    spec->items = items;
    spec->num_built = 0;
    return SUCCESS;
}

/* see gen_structs.h */
roomspec_t* roomspec_new(char *room_name, char *short_desc, char *long_desc, item_hash_t *items)
{

    roomspec_t *roomspecnew = calloc(1, sizeof(roomspec_t));

    if (roomspecnew == NULL) {
        fprintf(stderr, "calloc failed to allocate space for roomspecnew. \n");
        return NULL;
    }

    int check = init_roomspec(roomspecnew, room_name, short_desc, long_desc, items);
    if (check == FAILURE) {
        return NULL;
    }
    roomspecnew->itemspecs = NULL;
    return roomspecnew;
}

/* See gen_structs.h */
int edges_init(int** edges, int* inp_array, int num_rows, int num_cols) 
{
    if (edges == NULL)
        return FAILURE;
    
    for (unsigned int i = 0; i < num_rows; i++) 
    {
        for (unsigned int j = 0; j < num_cols; j++) 
        {
            edges[i][j] = inp_array[i * num_cols + j];
        }
    }

    return SUCCESS;
}

/* See gen_structs.h */
int** edges_new(int* inp, int num_rows, int num_cols)
{
    int** edges = (int**)malloc(sizeof(int*) * num_rows);

    if (edges == NULL) {
        fprintf(stderr, "malloc failed to allocate space for edges. \n");
        return NULL;
    }

    for (unsigned int i = 0; i < num_rows; i++) 
    {
        edges[i] = (int*)malloc(sizeof(int) * num_cols);
    }

    for (unsigned int i = 0; i < num_rows; i++)
    {
        if (edges[i] == NULL)
        {
            fprintf(stderr, "malloc failed to allocate space for edges. \n");
            return NULL;
        }
    }
    edges_init(edges, inp, num_rows, num_cols);
    return edges;
}

/* See gen_structs.h */
int edges_free(int** edges, int num_rows) {
     for(int i=0; i<num_rows; i++)
        free(edges[i]);   
    free(edges);
}



/* see gen_structs.h */
int specgraph_init(specgraph_t *specgraph, int num_roomspecs, roomspec_t **roomspecs, int **edges)
{
    if (specgraph == NULL)
        return FAILURE;

    specgraph->num_roomspecs = num_roomspecs;
    specgraph->roomspecs = roomspecs;
    specgraph->edges = edges;
    return SUCCESS;
}

/* see gen_structs.h */
specgraph_t* specgraph_new(int num_roomspecs, roomspec_t **roomspecs, int **edges)
{
    specgraph_t *specnew = (specgraph_t*)malloc(sizeof(specgraph_t));

    if (specnew == NULL) {
        fprintf(stderr, "calloc failed to allocate space for specnew. \n");
        return NULL;
    }

    specgraph_init(specnew, num_roomspecs, roomspecs, edges);
    return specnew;
}

/* see gen_structs.h */
int specgraph_free(specgraph_t *specgraph)
{
    if (specgraph == NULL)
        return FAILURE;
    //Free the roomspecs
    int num_roomspecs=specgraph->num_roomspecs;
    for(int i=0; i<num_roomspecs; i++)
        free((specgraph->roomspecs)[i]);
    
    //Free the adjacency matrix
    for(int i=0; i<num_roomspecs; i++)
        free((specgraph->edges)[i]);   
    free(specgraph->edges);
    free(specgraph);

    return SUCCESS;
}

/* See gen_structs.h */
int init_roomlevel(roomlevel_t *roomlevel, char *room_name, int difficulty_level)
{
    if (roomlevel == NULL)
        return FAILURE;

    strcpy(roomlevel->room_name, room_name);
    roomlevel->difficulty_level = difficulty_level;
    return SUCCESS;
}


/* See gen_structs.h */
roomlevel_t* roomlevel_new(char *room_name, int difficulty_level)
{
    roomlevel_t *roomlevel = calloc(1, sizeof(roomlevel_t));
    if (roomlevel == NULL) {
        fprintf(stderr, "calloc failed to allocate space for roomlevel_new\n");
        return NULL;
    }

    roomlevel->room_name = calloc(1, sizeof(MAX_SDESC_LEN + 1));
    if (roomlevel->room_name == NULL) {
        fprintf(stderr, "calloc failed to allocate space for roomlevel->room_name\n");
        return NULL;
    }

    init_roomlevel(roomlevel, room_name, difficulty_level);
    return roomlevel;
}



/* See gen_structs.h */
int roomlevel_free(roomlevel_t *roomlevel)
{
    if (roomlevel == NULL) 
        return FAILURE;

    free(roomlevel->room_name);
    free(roomlevel);
    return SUCCESS;
}


/* See gen_structs.h */  
int add_roomlevel_to_hash(roomlevel_hash_t **roomlevels, char *name, int difficulty_level) 
{
    roomlevel_t *elt = NULL;
    roomlevel_t *out_tmp = NULL;

    HASH_FIND_STR(*roomlevels, name, out_tmp);
    if (out_tmp == NULL) {
        elt = roomlevel_new(name, difficulty_level);
        HASH_ADD_KEYPTR(hh, *roomlevels, elt->room_name, strlen(elt->room_name), elt);
        return SUCCESS;
    }
    return FAILURE;
}




/* See gen_structs.h */
int init_levelspec(levelspec_t *levelspec, int num_thresholds, int *thresholds)
{
    if (!levelspec)
        return FAILURE;

    levelspec->num_thresholds = num_thresholds;
    for (int i = 0; i < num_thresholds; i++) {
        levelspec->thresholds[i] = thresholds[i];
    } 
    
    return SUCCESS;
}

/* See gen_structs.h */
levelspec_t *levelspec_new(int num_thresholds, int *thresholds)
{
    levelspec_t *levelspec = calloc(1, sizeof(levelspec_t));
    if (levelspec == NULL) {
        fprintf(stderr, "calloc failed to allocate space for levelspec\n");
        return NULL;
    }

    levelspec->thresholds = calloc(1, sizeof(int) * num_thresholds);
    if (levelspec->thresholds == NULL) {
        fprintf(stderr, "calloc failed to allocate space for levelspec->thresholds\n");
        return NULL;
    }

    init_levelspec(levelspec, num_thresholds, thresholds);
    levelspec->roomlevels = NULL;
    return levelspec;
}

/* See gen_structs.h */
int levelspec_free(levelspec_t *levelspec)
{
    if (!levelspec)
        return FAILURE;

    free(levelspec->thresholds);
    /* frees roomlevels hash and sets it to NULL */
    HASH_CLEAR(hh, levelspec->roomlevels);
    free(levelspec);

    return SUCCESS;
}
