/*
 * Header file for loading rooms into game_state structs
 */

#ifndef INCLUDE_LOAD_ROOMS_H
#define INCLUDE_LOAD_ROOMS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parser.h"
#include "room.h"
#include "game.h"
#include "validate.h"
#include "parse.h"
#include "common.h"

#define PATH_FAILURE (1)
#define ID_FAILURE (2)
#define CONNECTIONS_FAILURE (3)

#define ROOM_PATH "../examples/sample_yaml/connected_rooms.yaml"

/*
 * add_rooms_to_game
 * accesses the document object and obtain list of rooms to parse into game_state
 * structs and add to the inputted game pointer
 *
 * parameters:
 * - obj: the document object
 * - g: a game pointer as a return parameter
 *
 * side effects:
 * - adds rooms into the inputted game pointer
 *
 * returns:
 * - SUCCESS for successful parse
 * - FAILURE for unsuccessful parse
 */
int add_rooms_to_game(obj_t *obj, game_t *g);

/*
 * add_connections_to_rooms
 * accesses the document object and obtains connections for each room to parse intro
 * game_state structs and add to the inputted game pointer
 * parameters:
 * - obj: the document object
 * - g: a game pointer as a return parameter
 *
 * side effects:
 * - adds connections into the inputted game parameter
 *
 * returns;
 * - SUCCESS for successful parse
 * - FAILURE for unsuccessful parse
 */
int add_connections_to_rooms(obj_t *obj, game_t *g);

#endif
