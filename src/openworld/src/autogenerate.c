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
#include "common/utlist.h"
#include "common/uthash.h"
#include "game-state/room.h"
#include "openworld/autogenerate.h"
#include "openworld/gen_structs.h"
#include "openworld/default_rooms.h"
#include "openworld/default_npcs.h"

/* See autogenerate.h */
bool path_exists_in_dir(room_t *r, char *direction)
{
    // No paths case
    if (r->paths == NULL) {
        return false;
    }

    path_hash_t *current, *tmp;
    HASH_ITER(hh, r->paths, current, tmp) {
        // If the path has the given direction, return true
        if (strcmp(current->direction, direction) == 0) {
            return true;
        }
    }
    return false;
}

/* See autogenerate.h */
room_t* roomspec_to_room(roomspec_t *roomspec)
{
    // moved- generate the unique room id here and pass it to the room; don't mess with the roomspec
    char buff[MAX_SDESC_LEN + 1] = { 0 }; // Will hold unique room_id
    snprintf(buff, MAX_SDESC_LEN, "%s%d", roomspec->room_name, roomspec->num_built);

    roomspec->num_built++;

    // we use buff for the room name instead
    room_t *res = room_new(buff, roomspec->short_desc, roomspec->long_desc);
    // instead of taking all the items, just take a few of them
    res->items = random_items(roomspec);
    //res->npcs = random_npcs(roomspec);
    res->paths = NULL;
    return res;
}

/* See autogenerate.h */
int room_generate(game_t *game, gencontext_t *context, roomspec_t *rspec)
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
    for (bump = 0; bump < 4; bump++) {
        // Forwards direction + bump
        int forwards = (first_direction + bump) % 4;
        // If path in that direction exists in game->curr_room, bump. Else, create the path
        if (path_exists_in_dir(game->curr_room, directions[forwards])) {
            // Bump if the room already has a path in the given direction
            continue;
        }

        //create new combination of rooms/items from randomly picked roomspec
        // Adds one generated room from the head of context->speclist only
        room_t *new_room = roomspec_to_room(rspec);
        assert(SUCCESS == add_room_to_game(game, new_room));

        // Path to the generated room
        path_t* path_to_room = path_new(new_room, directions[forwards]);
        assert(SUCCESS == add_path_to_room(game->curr_room, path_to_room));

        // Path for the opposite direction
        unsigned int backwards = (forwards + 2) % 4;
        path_t* path_to_room2 = path_new(game->curr_room, directions[backwards]);
        assert(SUCCESS == add_path_to_room(new_room, path_to_room2));

        return SUCCESS; // Room was generated
    }

    return FAILURE; // Room was not generated
}

int multi_room_generate(game_t *game, gencontext_t *context, char *room_id, int num_rooms)
{
    /* If game->curr_room is not a dead end or there are no roomspec_t elements
    * in context->speclist, then do not autogenerate */
    if (context->speclist == NULL) {
        return FAILURE;
    }
    // Iterate through the speclist field, generating and adding rooms for each
    speclist_t *tmp;
    for (int i = 0; i < num_rooms; i++) {
        roomspec_t *rspec = random_room_lookup(context->speclist);
        // Increments tmp->spec->num_built
        room_generate(game, context, rspec);
    }
    return SUCCESS;
}

/* See autogenerate.h */
int speclist_from_hash(speclist_t **orig, roomspec_t *hash)
{
    roomspec_t *current_room = NULL;
    roomspec_t *tmp = NULL;

    HASH_ITER(hh, hash, current_room, tmp) {
        speclist_t *s = speclist_new(current_room);
        DL_APPEND(*orig, s);
    }
    return SUCCESS;
}

/* See autogenerate.h */
roomspec_t *random_room_lookup(speclist_t *spec)
{
    int count;
    speclist_t *tmp = NULL;
    speclist_t *random = NULL;

    DL_COUNT(spec, tmp, count);
    int idx = rand() % count, i = 0;

    DL_FOREACH(spec, tmp) {
        if (i == idx) {
            return tmp->spec;
        }
        i++;
    }
    return NULL;
}

/* See autogenerate.h */
item_hash_t *random_items(roomspec_t *room)
{
    if (room == NULL) {
        return NULL;
    }

    int count = HASH_COUNT(room->items);
    int num_items = rand() % MAX_RAND_ITEMS;
    int num_iters = rand() % count;

    item_hash_t *items = NULL;
    for (int i = 0; i < num_items; i++) {
        int rc = random_item_lookup(&items, room->items, num_iters);
    }
    if (items == NULL) return NULL;
    return items;
}

/* See autogenerate.h */
int random_item_lookup(item_hash_t **dst, item_hash_t *src, int num_iters)
{
    item_hash_t *current = NULL;
    item_hash_t *tmp = NULL;

    int i = 0;

    HASH_ITER(hh, src, current, tmp) {
        if (i == num_iters) {
            copy_item_to_hash(dst, src, current->item_id);
            return SUCCESS;
        }
        i++;
    }

}

/* See autogenerate.h */
npc_t *random_npcs(roomspec_t *room)
{
    if (room == NULL) {
        return NULL;
    }

    int num_npcs = rand() % MAX_NPCS;

    //assuming that npcs are not automatically assigned to rooms
    npc_t *hostiles = get_hostile_npcs();
    npc_t *friendlies = get_friendly_npcs();
    npc_t *generic = get_generic_npcs();


    npc_t *combo = NULL;
    npc_t *current = NULL;
    npc_t *tmp = NULL;

    strcat(room->long_desc, "These npcs are in the room: ");
    for (int i = 0; i < num_npcs; i++) {
        int random_num = rand() % 3;
        if(random_num == 1)
        {
            random_npc_lookup(&current, hostiles, rand() % MAX_NPCS);
        }
        else if(random_num  == 2)
        {
            random_npc_lookup(&current, friendlies, rand() % MAX_NPCS);
        }
        else
        {
            random_npc_lookup(&current, generic, rand() % MAX_NPCS);
        }
        HASH_ADD_STR(combo,npc_name,current);
    }
    HASH_ITER(hh, combo, current, tmp) {
        strncat(room->long_desc, current->npc_name, MAX_NAME_LEN);
        if (tmp != NULL)
            strncat(room->long_desc, ", ", MAX_NAME_LEN);
    }
    strcat(room->long_desc, ".\n");

    if (combo == NULL)
        return NULL;

    return combo;
}

/* See autogenerate.h */
int random_npc_lookup(npc_t **dst, npc_t *src, int num_iters)
{
    npc_t *current = NULL;
    npc_t *tmp = NULL;

    int i = 0;
    HASH_ITER(hh, src, current, tmp) {
    if (i == num_iters) {
       npc_t *new_npc = calloc(1, sizeof(npc_t));
      
       new_npc->npc_name = calloc(MAX_NAME_LEN + 1, sizeof(char));
       strncpy(new_npc->npc_name, current->npc_name, MAX_NAME_LEN); 
       new_npc->level = current->level;
       new_npc->inventory = current->inventory;
       new_npc->classification = current->classification;
       HASH_ADD_STR(*dst, npc_name, new_npc);
       return SUCCESS;
    }
      i++;
}

   return FAILURE;
}
