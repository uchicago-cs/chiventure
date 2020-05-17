/* Team RPG-Openworld
 * 
 * Sample-Generation header file
 * 
 * sample_generation.h: This file: function prototypes and purposes from 
 * the functions defined in chiventure/src/sample_generation.c
 * 
 * Create a high level room generation module that pulls the lower-level 
 * room generation modules together
 * 
 * See chiventure/include/sample_generation.c source code file to see function 
 * prototypes and purposes
 */

#ifndef INCLUDE_SAMPLE_GENERATION_H
#define INCLUDE_SAMPLE_GENERATION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// INCLUDE HARD-CODE ROOMS AND AUTOGENERATION MODULE

#include "sample_items.h"
#include "sample_rooms.h"

/* gencontext_t struct
 * This struct will carry the info for the generation algorithm
 * The struct contains: 
 * - int level: this is the players current level
 */
typedef struct {
 int level;
} gencontext_t;



// #include "../game-state/game_state_common.h"
// #include "../game-state/game_action.h"
// #include "../game-state/game.h"
// #include "../game-state/room.h"
// #include "../game-state/item.h"

// ASSUME HARD-CODED ROOMS AVAILABLE FROM ANOTHER MODULE

/*
 * enter_new_room
 * Did the player move from one room to another in the same game?
 * Compares two rooms based on UT_hash_handle to see if they are different
 * Assume that the input rooms are from the same game in different states
 * 
 * parameters:
 * - r1: a room pointer for input room 1 (old game state)
 * - g2: a room pointer for input room 2 (new game state, after entering room)
 *
 * side effects:
 * - None. Does not alter room/game states. Just compares them to determine if 
 * a new room was entered. Assume old room state is saved on the heap before a 
 * path action is taken, so that they can be compared after a path action.
 *
 * returns:
 * - true if a new room was entered
 * - false if a new room was not entered
 */
bool enter_new_room(room_t *r1, room_t *r2);

/*
 * room_generate
 * Given two room states and a room to add, add the room to the game holding 
 * the new room state (connected to the current room) if and only if the 
 * curr_room field is different between the two games
 * 
 * Freeing roomOld from the old game state is to be handled outside 
 * of this function
 * 
 * parameters:
 * - roomOld: a room pointer for the old room state
 * - roomNew: a room pointer for the old room state
 * - addRoom: a room pointer for the room to add if a new room was entered
 *
 * side effects:
 * - Changes roomNew game to add a room to the list of all_rooms and edits the 
 *   current_room struct to have a path to the newly-added room
 *
 * returns:
 * - SUCCESS if the new room (addRoom) was added
 * - FAILURE if the new room (addRoom) was not added
 */
int room_generate(room_t* roomOld, room_t* roomNew, room_t* addRoom);

/*
 * autogen_algorithm
 * A wrapper function for the autogeneration algorithm design and 
 * implementation in a separate module - TODO
 * 
 * parameters:
 * - TODO
 *
 * side effects:
 * - TODO
 *
 * returns:
 * - TODO
 * - todo
 */
int autogen_algorithm(void);

#endif /* INCLUDE_SAMPLE_GENERATION_H */
