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
#include "../../../include/openworld/gen_structs.h"

/* see gen_structs.h */
int init_gencontext(gencontext_t *context, path_t *path, int level, int openpaths, speclist_t *speclist)
{

    if (context == NULL)
        return FAILURE;

    context->path = path;
    context->level = level;
    context->openpaths = openpaths;
    context->speclist = speclist;

    return SUCCESS;
}


/* see gen_structs.h */
gencontext_t* gencontext_new(path_t *path, int level, int openpaths, speclist_t *speclist)
{

    gencontext_t *contextnew = calloc(1, sizeof(gencontext_t));
    contextnew->path = path;
    contextnew->level = level;
    contextnew->openpaths = openpaths;
    contextnew->speclist = speclist;
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
int init_roomspec(roomspec_t *spec,char *short_desc, char *long_desc,
                  item_list_t *allowed, item_hash_t *items, path_hash_t *paths)
{

    if (spec == NULL)
        return FAILURE;

    spec->short_desc = short_desc;
    spec->long_desc = long_desc;
    spec->allowed_items = allowed;
    spec->items = items;
    spec->paths = paths;
    return SUCCESS;
}

/* see gen_structs.h */
roomspec_t* roomspec_new(char *room_name, char *short_desc, char *long_desc,
                         item_list_t *allowed, item_hash_t *items, path_hash_t *paths)
{

    roomspec_t *roomspecnew = calloc(1, sizeof(roomspec_t));
    roomspecnew->room_name = room_name;
    roomspecnew->short_desc = short_desc;
    roomspecnew->long_desc = long_desc;
    roomspecnew->allowed_items = allowed;
    roomspecnew->items = items;
    roomspecnew->paths = paths;
    return roomspecnew;
}

/* see gen_structs.h */
int roomspec_free(roomspec_t *spec)
{

    if (spec == NULL)
        return FAILURE;

    free(spec);
    return SUCCESS;
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
    listnew->spec = spec;
    listnew->prev = NULL;
    listnew->next = NULL;
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
