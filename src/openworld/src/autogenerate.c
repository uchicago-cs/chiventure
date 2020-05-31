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
#include "openworld/autogenerate.h"

/* See autogenerate.h */
bool any_paths(room_t *r)
{
    assert(r != NULL && "any_paths: Given room is NULL");
    return (r->paths != NULL);
}

/* See autogenerate.h */
room_t* roomspec_to_room(game_t *game, roomspec_t *roomspec, char *room_id)
{
    room_t *res = room_new(room_id, roomspec->short_desc, roomspec->long_desc);

    item_hash_t *current = NULL, *tmp = NULL;
    // attribute_list_t *item_attributes; // ???
    UT_hash_handle hh;
    HASH_ITER(hh, roomspec->items, current, tmp) {
        assert(SUCCESS == copy_item_to_hash(&res->items, roomspec->items, roomspec->room_name));
    }
    // res->items = roomspec->items;
    res->paths = NULL;

    return res;
}

/* See autogenerate.h */
int room_generate(game_t *game, gencontext_t *context, char *room_id)
{
    /* Implement simple single-room autogeneration */
    if (!any_paths(game->curr_room)) 
    {
        // Adds one generated room from the head of the speclist only
        room_t *new_room = roomspec_to_room(game, context->speclist->spec, room_id);

        // Add addRoom to gameNew
        assert(SUCCESS == add_room_to_game(game, new_room));
        
        // Add path from the current room to addRoom
        path_t* path_to_room = path_new(new_room, context->speclist->spec->room_name);
        assert(SUCCESS == add_path_to_room(game->curr_room, path_to_room));

        return SUCCESS; /* room added */
    }

    return FAILURE; /* room not added */
}

/* See autogenerate.h */
int multi_room_generate(game_t *game, gencontext_t *context, char *room_id)
{
    /* If game->curr_room is not a dead end or there are no roomspec_t elements 
     * in context->speclist, then do not autogenerate */
    if (any_paths(game->curr_room) || context->speclist == NULL)
    {
        return FAILURE;
    }

    // Iterate through the speclist field, generating and adding rooms for each
    speclist_t *tmp;
    DL_FOREACH(context->speclist, tmp)
    {
        room_generate(game, context, room_id);
    }

    return SUCCESS;
}