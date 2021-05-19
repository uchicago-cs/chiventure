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


room_t *helper(game_t *game, speclist_t *speclist, room_t *pivot, char *forwards, char *backwards)
{
    room_t *next_room;
    
    roomspec_t *rspec = random_room_lookup(speclist);
    next_room = roomspec_to_room(rspec);
    assert(SUCCESS == add_room_to_game(game, next_room));

    /* Path to the generated room */
    path_t* path_to_next_room = path_new(next_room, forwards);
    assert(SUCCESS == add_path_to_room(pivot, path_to_next_room));

    /* Path for the opposite direction */
    path_t* path_to_pivot = path_new(pivot, backwards);
    assert(SUCCESS == add_path_to_room(next_room, path_to_pivot));

    return next_room;
}



/* See autogenerate.h */
bool path_exists_in_dir(room_t *r, char *direction)
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
int room_generate(game_t *game, gencontext_t *context, room_t *pivot, roomspec_t *rspec)
{
    /* 2D array of possible directions */
    char directions[4][6];
    strncpy(directions[0], "NORTH", 6);
    strncpy(directions[1], "EAST", 5);
    strncpy(directions[2], "SOUTH", 6);
    strncpy(directions[3], "WEST", 5);

    /* Random initial direction */
    unsigned int first_direction = rand() % 4;

    /* Bump directions index by 1 if a path with that direction already exists */
    unsigned int bump;
    for (bump = 0; bump < 4; bump++) {
        /* Forwards direction + bump */
        int forwards = (first_direction + bump) % 4;
        /* If path in that direction exists in pivot, bump. Else, create the path */
        if (path_exists_in_dir(pivot, directions[forwards])) {
            /* Bump if the room already has a path in the given direction */
            continue;
        }

        /* create new combination of rooms/items from randomly picked roomspec
        Adds one generated room from the head of context->speclist only */
        room_t *new_room = roomspec_to_room(rspec);
        assert(SUCCESS == add_room_to_game(game, new_room));

        /* Path to the generated room */
        path_t* path_to_room = path_new(new_room, directions[forwards]);
        assert(SUCCESS == add_path_to_room(pivot, path_to_room));

        /* Path for the opposite direction */
        unsigned int backwards = (forwards + 2) % 4;
        path_t* path_to_room2 = path_new(pivot, directions[backwards]);
        assert(SUCCESS == add_path_to_room(new_room, path_to_room2));

        return SUCCESS; // Room was generated
    }

    return FAILURE; // Room was not generated
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
        room_generate(game, context, game->curr_room, rspec);
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

    return FAILURE;
}


/* See autogenerate.h */
int map_level_to_difficulty(difficulty_level_scale_t *level_scale, 
                            int player_level)
{   
    /* Iterate from start (lowest point) of threshold array... */
    for (int i = 0; i < level_scale->num_thresholds; i++) {
        /* ...to find the first or minimum threshold which exceeds the given player level: */
        if (player_level < level_scale->thresholds[i]) {
            /* Player lvl must be in difficulty level directly below it (-1)... */
            return (i - 1);
        }
    }
    /* ...OR equal/exceeding the max threshold, in which case print max difficulty: */
    return level_scale->num_thresholds - 1; // -1 to convert array len -> max index
}


/* See autogenerate.h */
int roomspec_is_given_difficulty(room_level_t **room_levels, 
                                  roomspec_t *roomspec, 
                                  int difficulty_level)
{
    room_level_t *elt;

    HASH_FIND_STR(*room_levels, roomspec->room_name, elt); 
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
                                            room_level_t **room_levels, 
                                            int difficulty_level)
{
    speclist_t *tmp;
    speclist_t *filtered_speclist = NULL;

    DL_FOREACH(speclist, tmp) { 
        if (roomspec_is_given_difficulty(room_levels, tmp->spec, difficulty_level) == SUCCESS) 
        { 
               DL_APPEND(filtered_speclist, tmp);    
        }
    }

    return filtered_speclist;
}


/* See autogenerate.h */
int multi_room_level_generate(game_t *game, gencontext_t *context, 
                              char *room_id, int num_rooms,
                              room_level_t **room_levels, 
                              difficulty_level_scale_t *level_scale)
{
    /* If there are no roomspec_t elements in context->speclist, then do not autogenerate */
    if (context->speclist == NULL) {
        return FAILURE;
    }

    /* compute the difficulty corresponding to player level */
    int difficulty_level = map_level_to_difficulty(level_scale, context->level);

    /* filter the given speclist according to difficulty */
    speclist_t *filtered_speclist = filter_speclist_with_difficulty(context->speclist, 
                                                                    room_levels, 
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
int recursive_generate(game_t *game, room_t *curr_room, speclist_t *speclist, 
                       int radius, char **directions, int num_of_dir, char *dir_to_parent) 
{
    /* base case */
    if (radius <= 0) 
    {
        return SUCCESS;
    }

    /* 2D array of possible directions */
    char all_directions[6][6];
    strncpy(all_directions[0], "NORTH", 6);
    strncpy(all_directions[1], "EAST", 5);
    strncpy(all_directions[2], "UP", 3);
    strncpy(all_directions[3], "SOUTH", 6);
    strncpy(all_directions[4], "WEST", 5);
    strncpy(all_directions[5], "DOWN", 5);

    /* map directions to index */
    int dir_index[num_of_dir];
    for (int i = 0; i < num_of_dir; i++) 
    {
        for (int j = 0; j < 6; j++)
        {
            if (strcmp(all_directions[j], directions[i]) == 0)
            {
                dir_index[i] = j;
            }
        }
    } 

    /* map dir_to_parent to index */
    int dir_to_parent_index = -1;
    for (int i = 0; i < num_of_dir; i++) 
    {
        if(strcmp(directions[i], dir_to_parent) == 0) {
            dir_to_parent_index = dir_index[i];
        }
    } 

    /* A large portion of the following code can be replaced with a call to room_generate.
    BUT there is one caveat:
    room_generate must be modified so that it generates around ANY given room, not just the 
    'curr_room' specified in the game struct as it does currently.

    The easiest way to do this is probably adding a 'room_t *curr_room' parameter. Expect lots
    of tedious function call modifications. */
    int rc; // return code
    for (int i = 0; i < num_of_dir; i++) 
    {
        /* if direction is to parent, skip */
        if (dir_index[i] == dir_to_parent_index) {
            continue;
        }

        room_t *next_room;
        /* opposite direction */
        int forwards = dir_index[i];
        int backwards = (forwards + 3) % 6;


        if (path_exists_in_dir(curr_room, all_directions[forwards])) {
            next_room = find_room_from_dir(curr_room, all_directions[forwards]);
        
        /* create room in path if it doesn't exist yet */
        } else { // make everything inside this 'else' bracket a helper (likewise for in room_generate())
                 // helper(speclist_t *speclist, room_t *pivot, char *direction)

            next_room = helper(game, speclist, curr_room, all_directions[forwards], all_directions[backwards]);
            // roomspec_t *rspec = random_room_lookup(speclist);
            // next_room = roomspec_to_room(rspec);
            // assert(SUCCESS == add_room_to_game(game, next_room));

            // /* Path to the generated room */
            // path_t* path_to_next_room = path_new(next_room, all_directions[forwards]);
            // assert(SUCCESS == add_path_to_room(curr_room, path_to_next_room));

            // /* Path for the opposite direction */
            // path_t* path_to_curr_room = path_new(curr_room, all_directions[backwards]);
            // assert(SUCCESS == add_path_to_room(next_room, path_to_curr_room));
        }

        /* recursive case, decrement radius by 1 */
        rc = recursive_generate(game, next_room, speclist, 
                                radius - 1, directions, num_of_dir,
                                all_directions[backwards]);
    }
    return rc; 
}

