/* Team RPG-Openworld
 * 
 * sample_generation.c: This file. Function definitions of the functions 
 * specified in chiventure/include/sample_generation.h
 * 
 * Sprint 2: 
 * Create a high level room generation module that pulls the lower-level 
 * room generation modules together
 * 
 * See chiventure/include/sample_generation.h header file to see function 
 * prototypes and purposes
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../../include/openworld/sample_generation.h" // Need to fix: cannot open common/uthash.h for some reason
#include "../../../include/openworld/sample_rooms.h" 
#include "../../../include/openworld/sample_items.h"

/* See sample_generation.h */
bool enter_new_room(room_t *r1, room_t *r2) {
    // Check if they have the same hash handle pointer
    return (bool) (r1->hh.key == r2->hh.key)
}

/* See sample_generation.h */
int room_generate(game_t* gameOld, game_t* gameNew, room_t* addRoom) {
    /* BELOW: implement algo from autogenerate algorithm module */
    if (enter_new_room(gameOld->curr_room, gameNew->curr_room)) {
        /* BELOW: TO BE EDITED */

        // Add addRoom to gameNew
        HASH_ADD_TO_TABLE(addRoom->hh, gameNew->all_rooms, addRoom->hh.key, 
        addRoom->hh.keylen, addRoom->hh.hashval, add, oomed); 
        // (HASH_ADD_TO_TABLE) I have no idea what these "add" and "oomed" parameters are
        
        // Add path from the current room to addRoom
        path_t* path_to_room = path_new(addRoom, "to new room");
        assert (0 == add_path_to_room(gameNew->curr_room, path_to_room));

        /* ABOVE: TO BE EDITED */

        return 0; /* SUCCESS - room added */
    }

    return 1; /* room not added */
}

int autogen_algorithm(void) {
    /* TODO */

    return 1; // Depends algorithm module to be created
}