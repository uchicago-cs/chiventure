/* Team RPG-Openworld
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

/* see gen_structs.h */
int init_gencontext(gencontext_t *context, path_t *path, int level, int open_paths, int num_npcs, speclist_t *speclist)
{
    
    if (context == NULL)
    {
        return FAILURE;
    }

    context->path = path;
    context->level = level;
    context->open_paths = open_paths;
    context->num_npcs = num_npcs;
    context->speclist = speclist;
    return SUCCESS;
}


/* see gen_structs.h */
gencontext_t *gencontext_new(path_t *path, int level, int open_paths, int num_npcs, speclist_t *speclist)
{

    gencontext_t *context_new = calloc(1, sizeof(gencontext_t));
    assert(context_new != NULL);
    context_new->path = path;
    context_new->level = level;
    context_new->open_paths = open_paths;
    context_new->num_npcs = num_npcs;
    context_new->speclist = speclist;
    return context_new;
}


/* see gen_structs.h */
int gencontext_free(gencontext_t *context)
{

    if (context == NULL)
    {
	    return FAILURE;
    }

    free(context);
    return SUCCESS;
}

/* see gen_structs.h */
int init_roomspec(roomspec_t *spec, char *short_desc, char *long_desc, item_hash_t *items, path_hash_t *paths)
{
    
    if (spec == NULL)
    {
	    return FAILURE;
    }

    spec->short_desc = short_desc;
    spec->long_desc = long_desc;
    spec->items = items;
    spec->paths = paths;
    return SUCCESS;
}

/* see gen_structs.h */
roomspec_t *roomspec_new(char *short_desc, char *long_desc, item_hash_t *items, path_hash_t *paths)
{

    roomspec_t *roomspec_new = calloc(1, sizeof(roomspec_t));
    assert(roomspec_new != NULL);

    init_roomspec(roomspec_new, short_desc, long_desc, items, paths);
    
    return roomspec_new;
}

/* see gen_structs.h */
int roomspec_free(roomspec_t *spec)
{

    if (spec == NULL)
    {
        return FAILURE;
    }

    free(spec);
    return SUCCESS;
}

/* see gen_structs.h */
int init_speclist(speclist_t *list, roomspec_t *spec)
{

    if (list == NULL)
    {
	    return FAILURE;
    }

    list->spec = spec;
    speclist_t *head = NULL;

    DL_APPEND(head, list);
    assert(list == head);

    return SUCCESS;
}

/* see gen_structs.h */
speclist_t *speclist_new(roomspec_t *spec)
{

    speclist_t *list_new = calloc(1, sizeof(speclist_t));
    assert(list_new != NULL);
    
    init_speclist(list_new, spec);

    return list_new;
}

/* see gen_structs.h */
int speclist_free(speclist_t *list)
{
    
    if (list == NULL)
    {
	    return FAILURE;
    }

    free(list);
    return SUCCESS;	
}