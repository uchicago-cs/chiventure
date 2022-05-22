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


/*
* game_autogenerate_static
* Given a game_t and gencontext_t pointer and number of rooms, statically autogenerates 
* a new game
*
* returns:
* Integer to indicate if the generation was successful.
*/
int game_autogenerate_static(game_t* g, gencontext_t context, int num_rooms, char* first_room);

/*
* game_autogenerate_dynamic
* Given a game_t and gencontext_t pointer and a string indicating the first room, 
* dynamically autogenerates a new game
*
* returns:
* Integer to indicate if the generation was successful.
*/
int game_autogenerate_dynamic(game_t* g, gencontext_t context, char* first_room);

#endif /* INCLUDE_GAME_AUTOGENERATE_H */