/*
 * Header file for loading item object into game struct
 */

#ifndef INCLUDE_LOAD_ITEM_H
#define INCLUDE_LOAD_ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game-state/game.h"
#include "load_room.h"
#include "wdl_common.h"

/* load_items
 * accesses the document object and obtain list of items to parse into the
 * game_state structs and adds to the inputted game pointer
 * 
 * parameters:
 * - obj: the document object
 * - g: a game pointer as a return parameter
 *
 * side effects:
 * - adds items into the inputted game pointer and 
 *   their respective rooms
 *
 * returns:
 * - SUCCESS for successful parse
 * - FAILURE for unsuccessful parse
 */
int load_items(obj_t *doc, game_t *g );

/* load_actions
 * loads actions into the given item
 *
 * parameters:
 * - item_obj: the item object
 * - agent: an agent pointer
 *
 * returns;
 * - SUCCESS for successful parse
 * - FAILURE for unsuccessful parse
 */
int load_actions(obj_t *item_obj, agent_t *agent);

#endif /* INCLUDE_LOAD_ITEM_H */
