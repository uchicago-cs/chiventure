/* Team RPG-Openworld
*
* Sample-Game-Generation header file
*
* sample_generation.h: This file: function prototypes and purposes from
* the functions defined in chiventure/src/openworld/src/game_autogenerate.c
*
*/

#ifndef INCLUDE_GAME_AUTOGENERATE_H
#define INCLUDE_GAME_AUTOGENERATE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "common/uthash.h"
#include "game-state/room.h"
#include "game-state/game.h"
#include "gen_structs.h"
#include "default_rooms.h"
#include "autogenerate.h"
#include "game_autogenerate.h"

#define MAX_RAND_ITEMS (100)

/* random_first_room
* given a specgraph struct, and a game struct, updates the 
* game struct to include a random first room based on the specgraph
*
* parameters:
* - specgraph: A pointer to a specgraph_t. Should not be NULL.
* - game_t* game: a pointer to the game struct that needs to be updated. Should not contain any rooms.
*
* returns:
* SUCCESS - if the game was successfully updated
* FAILURE - if the function failed to update the game struct
*/
int random_first_room(game_t* game, specgraph_t *specgraph);

/* random_room_from_game
* given a game struct, randomly picks a new room from the game 
* parameters:
* - game_t* game: a pointer to the game struct. Must contain at least one room.
*
* returns:
* random_room: A pointer to the randomly chosen room
*/
room_t* random_room_from_game(game_t* game);

/* autogenerate_room_in_game
* given a game struct and specgraph struct, generates a random room in the game by 
* choosing a random room with random_room_in_game and generating a room from that room
* using the adjacency matrix. ALso generates any new associated paths using 
* path_autogenerate
*
* parameters:
* - game_t* game: a pointer to the game struct. Must contain at least one room.
* - specgraph: A pointer to a specgraph_t. Should not be NULL.
* returns:
* 1 - if a random room was successfully generated
* 0 - if a random room could not be generated due to having no empty directions
* -1 - if a random room could not be generate due to invalid inputs 
* (e.g. if game is null, if game contains no rooms, etc.)
*/
int autogenerate_room_in_game(game_t* game, specgraph_t *specgraph);

/*
* game_autogenerate_static
* Given a game_t and specgraph_t pointer and number of rooms, statically autogenerates 
* a new game
*
* Parameters:
* - game_t* game: a pointer to the game struct. Must contain at least one room.
* - specgraph: A pointer to a specgraph_t. Should not be NULL.
* - num_rooms: The number of rooms in the newly generate game
* - first_room: The name of the roomspec of the first room. Enter "pickrandomly" if you would like 
*               the roomspec to be chosen randomly.
* returns:
* Integer to indicate if the generation was successful.
*/
int game_autogenerate_static(game_t* g, specgraph_t *specgraph, int num_rooms, char* first_room);

/*
* game_autogenerate_dynamic
* Given a game_t and specgraph_t pointer and a string indicating the first room, 
* dynamically autogenerates a new game
*
* returns:
* Integer to indicate if the generation was successful.
*/
int game_autogenerate_dynamic(game_t* g, specgraph_t *specgraph, char* first_room);

#endif /* INCLUDE_GAME_AUTOGENERATE_H */