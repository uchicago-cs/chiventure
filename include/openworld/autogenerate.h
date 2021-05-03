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
#include "default_rooms.h"
#include "default_npcs.h"

#define MAX_RAND_ITEMS (6)
#define MAX_NPCS (3)

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
*
* returns:
* The generated room_t struct pointer.
*/
room_t* roomspec_to_room(roomspec_t *roomspec);


/*
* room_generate
* Generates a room based on the given speclist and adds it to the game.
*
* Checks to see if path direction is available.
*
* parameters:
* - game: A pointer to a game struct. Should not be NULL.
* - context: A pointer to a gencontext_t (type speclist_t*). Not NULL.
* - rspec: A unique roomspec for the to-be-generated room.
*
* side effects:
* - Changes input game to hold the newly generated room. Allocated on the heap
*
* returns:
* - SUCCESS if the new room was generated and added (SUCCESS)
* - FAILURE if the new room was not generated/added (FAILURE)
*/
int room_generate(game_t *game, gencontext_t *gencontext, roomspec_t *rspec);

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
* - room_id: A unique room_id string for the to-be-generated room.i
* - num_rooms: specifies how many new rooms will be generated
*
* side effects:
* - Changes input game to hold the newly generated room(s). Allocated on the heap
*
* returns:
* - SUCCESS if the new rooms were generated and added (SUCCESS)
* - FAILURE if the new rooms were not generated/added (FAILURE)
*/
int multi_room_generate(game_t *game, gencontext_t *context, char *room_id, int num_rooms);

/*
* speclist_from_hash
* Iterate through all the rooms in a roomspec hash and append them to
* original speclist in a doubly linked list.
*
* parameters:
* - hash: a roomspec hash that has multiple roomspecs
*
* returns:
* - NULL if hash is NULL
* - speclist_t* a new speclist with all the roomspecs stored in hash copied
*/
int speclist_from_hash(speclist_t **orig, roomspec_t *hash);

/*
* random_room_lookup
* Iterate through all the rooms of the speclist a "random" number of times
* and returns one of these roomspecs.
*
* parameters:
* - speclist_t *spec: the speclist from which to pull a roomspec
*
* returns:
* - NULL if failure
* - roomspec_t* new roomspec from the speclist
*/
roomspec_t *random_room_lookup(speclist_t *spec);

/*
* random_items
* Adds 0-6 "random" items to the roomspec given. Uses the roomspec's
* allowed items hash to pull the acceptable items.
*
* parameters:
* - room: A single roomspec with a item_hash of ALL allowed items.
*
* returns:
* - NULL if failure
* - item_hash_t* new item hash
*/
item_hash_t *random_items(roomspec_t *room);

/*
* random_item_lookup
* Iterate through the src item hash table num_iters times and copy that
* item to the dst item hash. This is a helper function for random_items.
*
* parameters:
* - item_hash_t *dst is where you want to store the item you just found
* - item_hash_t *src is where you're looking up the item
* - num_iters is how many times you'll iterate through src to settle on an item.
*
* returns:
* - SUCCESS if items allowed in a room could be found (SUCCESS)
* - FAILURE if items allowed in a room could not be found (FAILURE)
*/
int random_item_lookup(item_hash_t **dst, item_hash_t *src, int num_iters);

/*
* random_npcs
* randomly selects a number of npcs in a room where the max NPCs in a room is 3
* Assumes that npcs are not automatically assigned to rooms
* Includes a NPC room description and then randomly generates
* a certain amount of generic, friendly, and hostile per room.
*
* parameters:
*  - a roomspe_t that icnludes the type npc_t struct 
* returns: type npc_t and a room npc description
*/
npc_t *random_npcs(roomspec_t *room);

/*
* random_npc_lookup
* Iterates through num_iters times to and copies the source item at most 3 times
* Helper function for random_npcs
*
* parameters:
* -  item_hash_t *dst is where you want to store the npc you just found
* -  item_hash_t *src is where you're looking up the npc
* -  num_iters is how many times you'll iterate through src to settle on an npc 
*
* returns:
*  - Failure if the NPC is NULL or if the num_iters is 0
*  - Success if NPC is not NULL and there's at least 1 num_iters.
*/
int random_npc_lookup(npc_t **dst, npc_t *src, int num_iters);

#endif /* INCLUDE_AUTOGENERATE_H */
