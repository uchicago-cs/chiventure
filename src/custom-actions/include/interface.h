#ifndef INCLUDE_INTERFACE_H_
#define INCLUDE_INTERFACE_H_

#include "custom-actions-cond.h"
#include "custom-actions-common.h"
#include <stdlib.h>
#include <stdio.h>
#include "ast_block.h"
#include "action_block.h"
#include "branch_block.h"
#include "conditional_block.h"
#include "control_block.h"
#include "common/uthash.h"
#include "custom_action.h"
#include "libobj/obj.h"

/* 
 * Given a custom action and its corresponding arguments, 
 * attempt to execute the given action.
 * 
 * Parameters: 
 * - action: A pointer to the custom action to be executed (most likely
 *   acquired from search_for_custom_action)
 * 
 * Returns:
 * - SUCCESS on successful execution
 * - FAILURE if any one of the blocks fails to execute
 */
int do_custom_action(custom_action_t *action);


/* 
 * Search for a custom action by name
 * 
 * Parameters: 
 * - action_name: The name of the custom action to be searched for
 * - all_actions: Comprehensive list of all previously defined custom actions
 * 
 * Returns:
 * - custom_action_t* Pointer to the custom action with the same name as
 *   action_name if it exists
 * - NULL if no such action_name custom action exists in game
 * 
 */
custom_action_t *search_for_custom_action(char *action_name);

/*
 * Build a custom action object and add it to the game’s list of custom
 * actions. Also associates custom actions with objects and attributes
 * if necessary.
 * 
 * NOTE: Any objects or attributes the action is associated with need to be
 * initialized before the action is compiled.
 * 
 * NOTE 2: The list of custom actions is currently represented as a private
 * hash table inside interface.c; in the future, it should be integrated
 * into game-state/game.h.
 * 
 * Parameters:
 * - action: object_t representing information about a custom action and
 *           its attributes (created when a custom action is parsed from
 *           a json file)
 * 
 * Returns:
 * - custom_action_t* A pointer to the compiled custom action if successful
 * - NULL if there was an error working with the object_t struct or an error
 *        adding the resulting custom action to the list
 */
custom_action_t *compile_custom_action(obj_t *action);

/*
 * Adds a custom action object to the game's list of custom actions
 * (currently represented as a private hash table inside interface.c).
 * 
 * Parameters:
 * - action: The custom action to be added
 * 
 * Returns:
 * - SUCCESS if the custom action was successfully added to the list
 * - FAILURE if otherwise
 */
int add_custom_action_to_game(custom_action_t *action);

/* 
 * Translates information about a custom action and its attributes (an
 * object_t, having just been parsed from a json file) into an actual
 * custom_action_t.
 * 
 * Parameters:
 * - action: object_t representing information about a custom action and
 *           its attributes (created when a custom action is parsed from
 *           a json file)
 * 
 * Returns:
 * - custom_action_t* A pointer to the created custom action if successful
 * - NULL if there was an error working with the object_t struct
 * 
 * To be implemented in the future - see backlog issue #796.
 */
custom_action_t *translate_custom_action(obj_t *action);

#endif
