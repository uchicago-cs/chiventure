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



roomspec_t* random_first_room(game_t* game, gencontext_t* context);


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