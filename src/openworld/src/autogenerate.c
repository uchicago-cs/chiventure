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
bool path_exists_in_dir(room_t *r, char *direction)
{
    // No paths case
    if (r->paths == NULL)
    {
        return false;
    }

    path_hash_t *current, *tmp;
    HASH_ITER(hh, r->paths, current, tmp) {
        // If the path has the given direction, return true
        if (strcmp(current->direction, direction) == 0)
        {
            return true;
        }
    }
    return false;
}

/* See autogenerate.h */
room_t* roomspec_to_room(roomspec_t *roomspec, char *room_id)
{
    room_t *res = room_new(room_id, roomspec->short_desc, roomspec->long_desc);

    item_hash_t *current, *tmp;
    HASH_ITER(hh, roomspec->items, current, tmp) {
        assert(SUCCESS == copy_item_to_hash(&res->items, roomspec->items, current->item_id));
    }

    roomspec->num_built++;
    res->paths = NULL;

    return res;
}

/* See autogenerate.h */
int room_generate(game_t *game, gencontext_t *context, char *room_id)
{
    // 2D array of possible directions
    char directions[4][6];
    strncpy(directions[0], "NORTH", 6);
    strncpy(directions[1], "EAST", 5);
    strncpy(directions[2], "SOUTH", 6);
    strncpy(directions[3], "WEST", 5);

    // Random initial direction
    unsigned int first_direction = rand() % 4;

    // Bump directions index by 1 if a path with that direction already exists
    unsigned int bump;
    for (bump = 0; bump < 4; bump++)
    {
        // Forwards direction + bump
        int forwards = (first_direction + bump) % 4;

        // If path in that direction exists in game->curr_room, bump. Else, create the path
        if (path_exists_in_dir(game->curr_room, directions[forwards]))
        {
            // Bump if the room already has a path in the given direction
            continue;
        }
        
        // Adds one generated room from the head of context->speclist only
        room_t *new_room = roomspec_to_room(context->speclist->spec, room_id);
        assert(SUCCESS == add_room_to_game(game, new_room));

        // Path to the generated room
        path_t* path_to_room = path_new(new_room, directions[forwards]);
        assert(SUCCESS == add_path_to_room(game->curr_room, path_to_room));

        // Path for the opposite direction
        unsigned int backwards = (forwards + 2) % 4;
        path_t* path_to_room2 = path_new(game->curr_room, directions[backwards]);
        assert(SUCCESS == add_path_to_room(new_room, path_to_room));

        return SUCCESS; // Room was generated
    }

    return FAILURE; // Room was not generated
}

/* See autogenerate.h */
int multi_room_generate(game_t *game, gencontext_t *context, char *room_id)
{
    /* If game->curr_room is not a dead end or there are no roomspec_t elements 
     * in context->speclist, then do not autogenerate */
    if (context->speclist == NULL)
    {
        return FAILURE;
    }

    // Iterate through the speclist field, generating and adding rooms for each
    speclist_t *tmp;
    char buff[MAX_SDESC_LEN + 1] = {0}; // Will hold unique room_id
    DL_FOREACH(context->speclist, tmp)
    {
        // Append num_built value to the roomspec's room_name
        snprintf(buff, MAX_SDESC_LEN, "%s%d", tmp->spec->room_name, tmp->spec->num_built);

        // Increments tmp->spec->num_built
        room_generate(game, context, buff);
    }

    return SUCCESS;
}