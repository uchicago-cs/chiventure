/*
 * Header file for loading item object into game struct
 */

#ifndef INCLUDE_LOAD_ITEM_H
#define INCLUDE_LOAD_ITEM_H

#include "parse.h"
#include "load_room.h"
#include "wdl_common.h"

#define FILE_PATH "../examples/sample_yaml/simplified_wdl.yaml"

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
 * - 0 for successful parse
 * - 1 for unsuccessful parse
 */
int load_items(obj_t *doc, game_t *g );

/* load_actions
 * loads actions into the given item
 */
int load_actions(obj_t *doc, item_t *i);

/* add_cond_and_eff_to_actions
 * Iterates through a parsed WDL file a second time after successfully
 * loading items and item actions
 *
 * Parameters:
 * - doc: the parsed WDL document object
 * - g : a game pointer
 *
 * Side effects:
 * - adds conditions and effects for all the actions of all items
 * - prints accompanying error messages and success messages to stderr
 *   and stdout respectfully 
 *
 * Returns:
 * - 0 for SUCCESS
 * - 1 otherwise
 */
int add_cond_and_eff_to_actions(obj_t *doc, game_t *g);

#endif /* INCLUDE_LOAD_ITEM_H */
