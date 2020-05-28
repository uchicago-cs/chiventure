
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
* - context: A pointer to a gencontext_t (type gencontext_t*). Not NULL.
*
* side effects:
* - Changes input game to hold the newly generated room. Allocated on the heap
*
* returns:
* - SUCCESS if the new room was generated and added (SUCCESS)
* - FAILURE if the new room was not generated/added (FAILURE)
*/
int room_generate(game_t *game, gencontext_t *context, char *bucket);


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
*
* side effects:
* - Changes input game to hold the newly generated room(s). Allocated on the heap
*
* returns:
* - SUCCESS if the new rooms were generated and added (SUCCESS)
* - FAILURE if the new rooms were not generated/added (FAILURE)
*/

roomspec_t *random_room_content(speclist_t *spec);

int multi_room_generate(game_t *game, gencontext_t *context, char *bucket);

roomspec_t *random_room_lookup(speclist_t *spec);

item_hash_t *random_items(roomspec_t *room);

int random_item_lookup(item_hash_t *dst, item_hash_t *src, int num_iters);

speclist_t *speclist_from_hash(roomspec_t *hash);

#endif /* INCLUDE_AUTOGENERATE_H */
