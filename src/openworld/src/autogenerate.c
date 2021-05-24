#define NUM_COMPASS_DIRECTIONS 4
#define NUM_DIRECTIONS 6
#define MAX_DIRECTION_STRLEN 6


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


/* See autogenerate.h */
bool path_exists_in_direction(room_t *r, char *direction)
{
    /* No paths case */
    if (r->paths == NULL) {
        return false;
    }

    path_hash_t *current, *tmp;
    HASH_ITER(hh, r->paths, current, tmp) {
        /* If the path has the given direction, return true */
        if (strcmp(current->direction, direction) == 0) {
            return true;
        }
    }
    return false;
}

/* See autogenerate.h */
room_t* roomspec_to_room(roomspec_t *roomspec)
{
    /* moved- generate the unique room id here and pass it to the room; don't mess with the roomspec */
    char buff[MAX_SDESC_LEN + 1] = { 0 }; // Will hold unique room_id
    snprintf(buff, MAX_SDESC_LEN, "%s%d", roomspec->room_name, roomspec->num_built);
    roomspec->num_built++;

    /* we use buff for the room name instead */
    room_t *res = room_new(buff, roomspec->short_desc, roomspec->long_desc);
    /* instead of taking all the items, just take a few of them */
    res->items = random_items(roomspec);

    res->paths = NULL;
    return res;
}


/* See autogenerate.h */ 
int pick_random_direction(room_t *curr, char *out_direction_to_curr, char *out_direction_to_new)
{
    /* 2D array of possible directions */
    char directions[NUM_COMPASS_DIRECTIONS][MAX_DIRECTION_STRLEN];
    strncpy(directions[0], "NORTH", 6);
    strncpy(directions[1], "EAST", 5);
    strncpy(directions[2], "SOUTH", 6);
    strncpy(directions[3], "WEST", 5);

    /* Random initial direction */
    unsigned int initial_direction = rand() % NUM_COMPASS_DIRECTIONS;

    /* Bump directions index by 1 if a path with that direction already exists */
    unsigned int bump;
    for (bump = 0; bump < NUM_COMPASS_DIRECTIONS; bump++) {
        /* Forwards direction + bump */
        unsigned int forwards = (initial_direction + bump) % NUM_COMPASS_DIRECTIONS;
        /* If path in that direction exists in curr, bump. Else, create the path */
        if (path_exists_in_direction(curr, directions[forwards])) {
            /* Bump if the room already has a path in the given direction */
            continue;
        }
        unsigned int backwards = (forwards + 2) % NUM_COMPASS_DIRECTIONS;
        strcpy(out_direction_to_curr, directions[backwards]);
        strcpy(out_direction_to_new, directions[forwards]);
        return SUCCESS; // direction was picked
    }

    return FAILURE; // no open direction
}

/* See autogenerate.h */
int room_generate(game_t *game, room_t *curr, roomspec_t *rspec_new,
                  char *direction_to_curr, char *direction_to_new)
{
    /* create new combination of rooms/items from randomly picked roomspec
    Adds one generated room from the head of context->speclist only */
    room_t *new_room = roomspec_to_room(rspec_new);
    assert(add_room_to_game(game, new_room) == SUCCESS);

    /* Path to the generated room */
    path_t* path_to_new = path_new(new_room, direction_to_new);
    assert(add_path_to_room(curr, path_to_new) == SUCCESS);

    /* Path for the opposite direction */
    path_t* path_to_curr = path_new(curr, direction_to_curr);
    assert(add_path_to_room(new_room, path_to_curr) == SUCCESS);
    
    return SUCCESS;
}

/* See autogenerate.h */
int multi_room_generate(game_t *game, gencontext_t *context, char *room_id, int num_rooms)
{
    /* If game->curr_room is not a dead end or there are no roomspec_t elements
    * in context->speclist, then do not autogenerate */
    if (context->speclist == NULL) {
        return FAILURE;
    }

    /* Iterate through the speclist field, generating and adding rooms for each */
    for (int i = 0; i < num_rooms; i++) {
        roomspec_t *rspec = random_room_lookup(context->speclist);
        /* Increments tmp->spec->num_built */

        char direction_to_curr[MAX_DIRECTION_STRLEN], direction_to_new[MAX_DIRECTION_STRLEN];

        if (pick_random_direction(game->curr_room, direction_to_curr, direction_to_new) == FAILURE) 
            return FAILURE; // failed to generate at least one room
        
        room_generate(game, game->curr_room, rspec, direction_to_curr, direction_to_new);
    }
    return SUCCESS;
}


/* See autogenerate.h */
int speclist_from_hash(speclist_t **orig, rspec_hash_t *hash)
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
    if (count == 0) {
        return NULL; // otherwise we have a zero division error
    }

    int num_items = rand() % MAX_RAND_ITEMS;
    int num_iters = rand() % count;

    item_hash_t *items = NULL;
    for (int i = 0; i < num_items; i++) {
        int rc = random_item_lookup(&items, room->items, num_iters);
    }
    /* note that items could be NULL */
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

    return FAILURE;
}


/* See autogenerate.h */
int map_level_to_difficulty(int num_thresholds, int *thresholds, int player_level)
{   
    /* Iterate from start (lowest point) of threshold array... */
    for (int i = 0; i < num_thresholds; i++) {
        /* ...to find the first or minimum threshold which exceeds the given player level: */
        if (player_level < thresholds[i]) {
            /* Player lvl must be in difficulty level directly below it (-1)... */
            return (i - 1);
        }
    }
    /* ...OR equal/exceeding the max threshold, in which case print max difficulty: */
    return num_thresholds - 1; // -1 to convert array len -> max index
}


/* See autogenerate.h */
int roomspec_is_given_difficulty(roomlevel_hash_t **roomlevels, 
                                 roomspec_t *roomspec, 
                                 int difficulty_level)
{
    roomlevel_t *elt;

    HASH_FIND_STR(*roomlevels, roomspec->room_name, elt); 
    if (elt) {
        if (elt->difficulty_level == difficulty_level) {
            return SUCCESS;
        } else {
            return 1; // roomspec found but not of given difficulty level
        }
    }
    return 2; // roomspec not found
}


/* See autogenerate.h */
speclist_t* filter_speclist_with_difficulty(speclist_t *speclist, 
                                            roomlevel_hash_t **roomlevels, 
                                            int difficulty_level)
{    
    speclist_t *curr, *tmp;
    speclist_t *filtered_speclist = NULL;

    DL_FOREACH_SAFE(speclist, curr, tmp) { 
        int is_given_difficulty = roomspec_is_given_difficulty(roomlevels, 
                                                               curr->spec, 
                                                               difficulty_level);
        if (is_given_difficulty == SUCCESS) { 
            DL_APPEND(filtered_speclist, curr);    
        }
    }

    return filtered_speclist;
}


/* See autogenerate.h */
int multi_room_level_generate(game_t *game, gencontext_t *context, 
                              char *room_id, int num_rooms,
                              levelspec_t *levelspec)
{
    /* If there are no roomspec_t elements in context->speclist, then do not autogenerate */
    if (context->speclist == NULL) {
        return FAILURE;
    }

    /* compute the difficulty corresponding to player level */
    int difficulty_level = map_level_to_difficulty(levelspec->num_thresholds,
                                                   levelspec->thresholds,
                                                   context->level);

    /* filter the given speclist according to difficulty */
    speclist_t *filtered_speclist = filter_speclist_with_difficulty(context->speclist,
                                                                    &(levelspec->roomlevels), 
                                                                    difficulty_level);

    /* filtered gencontext */
    gencontext_t* filtered_context = gencontext_new(context->open_paths,
                                                    context->level,
                                                    context->num_open_paths,
                                                    filtered_speclist);

    int result = multi_room_generate(game, filtered_context, room_id, num_rooms); 

    return result;
}


/* See autogenerate.h */
int recursive_generate(game_t *game, gencontext_t *context, room_t *curr_room, 
                       int radius, char **directions, int num_directions, char *direction_to_parent) 
{
    /* base case */
    if (radius <= 0) 
    {
        return SUCCESS;
    }

    /* 2D array of possible directions */
    char all_directions[NUM_DIRECTIONS][MAX_DIRECTION_STRLEN];
    strncpy(all_directions[0], "NORTH", 6);
    strncpy(all_directions[1], "EAST", 5);
    strncpy(all_directions[2], "UP", 3);
    strncpy(all_directions[3], "SOUTH", 6);
    strncpy(all_directions[4], "WEST", 5);
    strncpy(all_directions[5], "DOWN", 5);

    /* map directions to index */
    int direction_index[num_directions];
    for (int i = 0; i < num_directions; i++) 
    {
        for (int j = 0; j < NUM_DIRECTIONS; j++)
        {
            if (strcmp(all_directions[j], directions[i]) == 0)
            {
                direction_index[i] = j;
            }
        }
    } 

    /* map direction_to_parent to index */
    int direction_to_parent_index = -1;
    for (int i = 0; i < num_directions; i++) 
    {
        if(strcmp(directions[i], direction_to_parent) == 0) {
            direction_to_parent_index = direction_index[i];
        }
    } 

    int rc; // return code
    for (int i = 0; i < num_directions; i++) 
    {
        /* if direction is to parent, skip */
        if (direction_index[i] == direction_to_parent_index) {
            continue;
        }

        room_t *next_room;
        /* opposite direction */
        int forwards = direction_index[i];
        int backwards = (forwards + 3) % NUM_DIRECTIONS;

        /* create room in direction if it doesn't exist yet */
        if (!path_exists_in_direction(curr_room, all_directions[forwards])) {        
            roomspec_t *rspec = random_room_lookup(context->speclist);
            int rc_callback = room_generate(game, curr_room, rspec,
                                            all_directions[backwards], all_directions[forwards]);

            assert(rc_callback == SUCCESS);
        }
        /* note that next_room is either a preexisting room, or a room that was newly generated
           by room_generate in the if statement above */
        next_room = find_room_from_dir(curr_room, all_directions[forwards]);

        /* recursive case, decrement radius by 1 */
        rc = recursive_generate(game, context, next_room, 
                                radius - 1, directions, 
                                num_directions, all_directions[backwards]);
    }
    return rc; 
}
