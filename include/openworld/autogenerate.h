/* Team RPG-Openworld
 * 
 * Sample-Generation header file
 * 
 * sample_generation.h: This file: function prototypes and purposes from 
 * the functions defined in chiventure/src/openworld/src/autogenerate.c
 * 
 * Room module that autogenerates and adds room to a game when a "dead end" 
 * is reached (i.e. no outward paths from the current room)
 * 
 * See sample_generation.c source code file to see function definitions
 */

#ifndef INCLUDE_AUTOGENERATE_H
#define INCLUDE_AUTOGENERATE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "game-state/game.h"
#include "gen_structs.h"


/*
 * any_paths
 * Are there any outward paths in the given room? Returns a boolean.
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
 * room_generate
 * Given a game pointer and a context struct (gencontext_t*), generates a room 
 * based on the head node only of the context struct and adds it to the game. Only 
 * does so if the current room has no outward paths (dead end).
 * 
 * Connects the newly-generated room to the old room via paths.
 * 
 * parameters:
 * - game: A pointer to a game struct. Should not be NULL.
 * - roomspec: A pointer to a roomspec_t (type gencontext_t*). Not NULL.
 *
 * side effects:
 * - Changes input game to hold the newly generated room. Allocated on the heap
 *
 * returns:
 * - SUCCESS if the new room was added (SUCCESS)
 * - FAILURE if the new room was not added (FAILURE)
 */
int room_generate(game_t *game, gencontext_t *context);


#endif /* INCLUDE_AUTOGENERATE_H */
