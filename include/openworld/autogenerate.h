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
#include "default_rooms.h"


/*
 * path_exists_in_dir
 * Is there any path in the given room that exists in the given direction?
 * Return a boolean.
 * 
 * parameters:
 * - r: A room pointer for the input room. Should not be NULL.
 * - direction: A string specifying the direction to check for 
 *              ("NORTH", "EAST", SOUTH", or "WEST")
 *
 * side effects:
 * - None. Does not alter room/game states. Just determines if the input 
 *   room has any paths in the given direction.
 *
 * returns:
 * - true if the room has a path with in the given direction
 * - false if the room has no paths in the give direction
 */
bool path_exists_in_dir(room_t *r, char *direction);


/*
 * roomspec_to_room
 * Given a roomspec_t pointer (type roomspec_t*), returns 
 * a room_t pointer generated from its specifications, with a room_id that 
 * is uniquely generated from the given game (different from the game's rooms).
 * 
 * Increments the num_built field of the given roomspec by 1
 * 
 * parameters:
 * - roomspec: A pointer to a roomspec_t (type gencontext_t*). Not NULL.
 * - room_id: A unique room_id string for the to-be-generated room.
 *
 * side effects:
 * - Creates a new room_t pointer on the heap.
 *
 * returns:
 * The generated room_t struct pointer.
 */
room_t* roomspec_to_room(roomspec_t *roomspec, char *room_id);


/*
 * room_generate
 * Generates a room based on the given speclist and adds it to the game.
 * 
 * Checks to see if path direction is available.
 * 
 * parameters:
 * - game: A pointer to a game struct. Should not be NULL.
 * - context: A pointer to a gencontext_t (type speclist_t*). Not NULL.
 * - room_id: A unique room_id string for the to-be-generated room.
 *
 * side effects:
 * - Changes input game to hold the newly generated room. Allocated on the heap
 *
 * returns:
 * - SUCCESS if the new room was generated and added (SUCCESS)
 * - FAILURE if the new room was not generated/added (FAILURE)
 */
int room_generate(game_t *game, gencontext_t *gencontext, char *room_id);


/*
 * multi_room_generate
 * Iterate through all the rooms of the speclist field of the given context 
 * (gencontext_t pointer) and create a "domain" of rooms around the current 
 * room. Only succeeds when the current room has no outward paths, i.e. is 
 * a "dead end".
 * 
 * Connects the newly-generated room to the old room via paths.
 * 
 * parameters:
 * - game: A pointer to a game struct. Should not be NULL.
 * - context: A pointer to a gencontext_t (type gencontext_t*). Not NULL.
 * - room_id: A unique room_id string for the to-be-generated room.
 *
 * side effects:
 * - Changes input game to hold the newly generated room(s). Allocated on the heap
 *
 * returns:
 * - SUCCESS if the new rooms were generated and added (SUCCESS)
 * - FAILURE if the new rooms were not generated/added (FAILURE)
 */
int multi_room_generate(game_t *game, gencontext_t *context, char *room_id);


#endif /* INCLUDE_AUTOGENERATE_H */
