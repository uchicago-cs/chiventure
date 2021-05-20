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

/* see gen_structs.h */
int init_gencontext(gencontext_t *context, path_t *open_paths, int level, int num_open_paths, speclist_t *speclist)
{

    if (context == NULL)
        return FAILURE;

    context->level = level;
    context->open_paths = open_paths;
    context->num_open_paths = num_open_paths;
    context->speclist = speclist;
    return SUCCESS;
}


/* see gen_structs.h */
gencontext_t* gencontext_new(path_t *open_paths, int level, int num_open_paths, speclist_t *speclist)
{

    gencontext_t *contextnew = calloc(1, sizeof(gencontext_t));

    if (contextnew == NULL) {
        fprintf(stderr, "calloc failed to allocate space for contextnew. \n");
        return NULL;
    }

    init_gencontext(contextnew, open_paths, level, num_open_paths, speclist);
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
    return roomspecnew;
}

/* see gen_structs.h */
int init_speclist(speclist_t *list, roomspec_t *spec)
{

    if (list == NULL)
        return FAILURE;

    list->spec = spec;
    list->prev = NULL;
    list->next = NULL;
    return SUCCESS;
}

/* see gen_structs.h */
speclist_t* speclist_new(roomspec_t *spec)
{

    speclist_t *listnew = calloc(1, sizeof(speclist_t));

    if (listnew == NULL) {
        fprintf(stderr, "calloc failed to allocate space for listnew. \n");
        return NULL;
    }

    init_speclist(listnew, spec);
    return listnew;
}

/* see gen_structs.h */
int speclist_free(speclist_t *list)
{

    if (list == NULL)
        return FAILURE;

    free(list);
    return SUCCESS;
}

/* see gen_structs.h */
int speclist_free_all(speclist_t *list)
{

    if (list == NULL)
        return FAILURE;

    speclist_t *elt, *tmp;
    DL_FOREACH_SAFE(list, elt, tmp) {
        DL_DELETE(list, elt);
        speclist_free(elt);
    }
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
int add_roomlevel_to_hash(roomlevel_t **roomlevels, char *name, int difficulty_level) 
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
}