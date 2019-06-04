/*
 * Header file for loading rooms into game_state structs
 */

#ifndef INCLUDE_LOAD_ROOMS_H
#define INCLUDE_LOAD_ROOMS_H

#define FILE_PATH "../examples/sample_yaml/connected_rooms.yaml"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parser.h"
#include "room.h"
#include "game.h"
#include "path.h"
#include "validate.h"

/* Helper function for creating doc object from defined FILE_PATH */
obj_t *get_doc_obj();

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
 * - 0 for successful parse
 * - 1 for unsuccessful parse
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
 * - 0 for successful parse
 * - 1 for unsuccessful parse
 */
int add_connections_to_rooms(obj_t *obj, game_t *g);

#endif
