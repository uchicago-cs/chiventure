/* Team RPG-Openworld
 * 
 * Sample-Generation header file
 * 
 * sample_generation.h: This file: function prototypes and purposes from 
 * the functions defined in chiventure/src/openworld/src/autogenerate.c
 * 
 * Room module that autogenerates string of rooms connected via paths when 
 * a "dead-end" room is entered
 * 
 * See sample_generation.c source code file to see function definitions
 */

#ifndef INCLUDE_AUTOGENERATE_H
#define INCLUDE_AUTOGENERATE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// #include "sample_items.h"
// #include "sample_rooms.h"

#include "../game-state/game_state_common.h"
#include "../game-state/game_action.h"
#include "../game-state/game.h"
#include "../game-state/room.h"
#include "../game-state/item.h"
#include "../openworld/gen_structs.h"

// ASSUME HARD-CODED ROOMS AVAILABLE FROM ANOTHER MODULE

/*
 * any_paths
 * Are there any paths in the given room? Returns a boolean.
 * 
 * parameters:
 * - r: A room pointer for the input room. Should not be NULL.
 *
 * side effects:
 * - None. Does not alter room/game states. Just determines if the input 
 *   rooms have any paths.
 *
 * returns:
 * - true if the room has one or more paths
 * - false if the room has no paths
 */
bool any_paths(room_t *r);


/*
 * context_to_room
 * Given a roomspec_t pointer (type roomspec_t*), returns 
 * a room_t pointer generated from its specifications, with a room_id that 
 * is uniquely generated from the given game (different from the game's rooms).
 * 
 * parameters:
 * - game: A pointer to a game struct. Should not be NULL.
 * - roomspec: A pointer to a roomspec_t (type gencontext_t*). Not NULL.
 *
 * side effects:
 * - Creates a new room_t pointer on the heap.
 *
 * returns:
 * The generated room_t struct pointer.
 */
room_t* roomspec_to_room(game_t *game, roomspec_t *roomspec);


/*
 * pop_speclist
 * Given a context struct pointer (type speclist_t*), sets the head of the 
 * speclist field, pops the old head and frees it from the heap.
 * 
 * parameters:
 * - context: A pointer to a context struct (type speclist_t*). Not NULL.
 *
 * side effects:
 * - Frees a speclist pointer (and its contents) from the heap 
 *   (the list's head node).
 *
 * returns:
 * - 0 if successful
 * - 1 if unsuccessful (error)
 */
int pop_speclist(speclist_t *context);


/*
 * room_generate
 * Given a game pointer and a context struct (speclist_t*), generates a room 
 * based on the head node of the context struct and adds it to the game. Only 
 * does so if the current room has no paths (dead ends).
 * 
 * Connects the newly-generated room to the old room via paths.
 * 
 * parameters:
 * * - game: A pointer to a game struct. Should not be NULL.
 * - roomspec: A pointer to a roomspec_t (type gencontext_t*). Not NULL.
 *
 * side effects:
 * - Changes input game to hold the newly generated room. Allocated on the heap
 *
 * returns:
 * - 0 if the new room was added (SUCCESS)
 * - 1 if the new room was not added (FAILURE)
 */
int room_generate(game_t *game, speclist_t *context);

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

#endif /* INCLUDE_AUTOGENERATE_H */
