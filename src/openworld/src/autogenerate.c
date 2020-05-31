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

    item_hash_t *current, *tmp;
    HASH_ITER(hh, roomspec->items, current, tmp) {
        assert(SUCCESS == copy_item_to_hash(&res->items, roomspec->items, current->item_id));
    }

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

        char directions[3][6];
        strncpy(directions[0], "NORTH", 6);
        strncpy(directions[1], "SOUTH", 6);
        strncpy(directions[2], "EAST", 5);
        strncpy(directions[3], "WEST", 5);
        
        // Add path from the current room to addRoom
        unsigned int random_index = rand() % 4;

        // Random direction for the path
        path_t* path_to_room = path_new(new_room, directions[random_index]);
        assert(SUCCESS == add_path_to_room(game->curr_room, path_to_room));

        // Opposite direction
        if (random_index == 0 || random_index == 2)
        {
            random_index++;
        }
        else
        {
            random_index--;
        }

        // Add the opposite path to the game
        path_t* path_to_room2 = path_new(game->curr_room, directions[random_index]);
        assert(SUCCESS == add_path_to_room(new_room, path_to_room));

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