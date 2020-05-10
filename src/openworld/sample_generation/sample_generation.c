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
#include "../../../include/openworld/sample_generation.h"
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

        // HASH_ADD_TO_TABLE(addRoom->hh, gameNew->all_rooms, addRoom->hh.key, 
        // addRoom->hh.keylen, addRoom->hh.hashval, addRoom, oomed); 

        // oomed is "out of memory error"??
        // HASH_ADD_TO_TABLE(hh,head,keyptr,keylen_in,hashval,add,oomed);
        // (HASH_ADD_TO_TABLE) I have no idea what these "add" and "oomed" parameters are

        // For now:
        /* Here, implement a way to add addRoom to the list of all rooms in gameNew */
        
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

    /* Ideas: We should find a "random" library that pulls randomly from a 
     * given list of items (or structs). We can pull from a hard-coded list 
     * of structs randomly, only when desired. Should have a function that 
     * uses this random library to randomly pull from a given list/database/
     * hashtable (up for discussion) when the user chooses to. Does nothing 
     * when a new room is not desired */

    return 1; // Depends algorithm module to be created
}