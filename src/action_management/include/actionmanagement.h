#ifndef _ACTIONS_H_
#define _ACTIONS_H_

#include "action_structs.h"
#include "game.h"


/* File consisting of all functions created by action management
   =========================================================================== */

/*
 * Allocates a new action type on the heap, calling action_init
 *
 * Parameters:
 * - c_name: a string containing an actions canonical name
 * - kind: an enumeration of the kind of action
 *
 * Returns:
 * - a pointer to a new action type struct
 */
action_type_t *action_type_new(char *c_name, enum action_kind kind);


/*
 * A function that initializes an action type struct, filling its parameters.
 *
 * Parameters:
 * - a: a pointer to an empty action_type_t allocated by action_new
 * - c_name: a string containing an actions canonical name
 * - kind: an enumeration of the kind of action
 *
 * Returns:
 * - 0 if success, 1 if an error occurs
 * - an error message in stderr if the action type struct is not initialized
 */
int action_type_init(action_type_t *a, char *c_name, enum action_kind kind);


/*
 * A function that frees the resources associated with an action type struct
 *
 * Parameters:
 * - a: An action struct. Must point to action struct allocated by action_new
 *
 * Returns:
 * - Returns void.
 */
void action_type_free(action_type_t *a);


// =============================================================================

/*
 * A function that returns all supported actions
 *
 * Parameters:
 * - none
 *
 * Returns:
 * - a linked list of action_type_t structs
 */
list_action_type_t *get_supported_actions();


// =============================================================================

/* A function that executes KIND 1 actions (ACTION <item>)
 *
 * Parameters:
 * - g: A game struct consisting of the game state
 * - a: An action type struct
 * - i: An item struct
 *
 * Returns
 * - 0 on success
 * - 1 on failure
 */
int do_item_action(game_t *g, action_type_t *a, item_t *i);


/* A function that executes KIND 2 actions (ACTION <path>)
 *
 * Parameters:
 * - g: A game struct consisting of the game state
 * - a: An action type struct
 * - p: A path struct
 *
 * Returns
 * - 0 on success
 * - 1 on failure
 */
int do_path_action(game_t *g, action_type_t *a, path_t *p);


/* A function that executes KIND 5 actions (ACTION <item> <item>)
 *
 * Parameters:
 * - g: A game struct containing a field for the current player
 * - a: An action type struct
 * - direct: An item struct containing the direct object (the "actor")
 * - indirect: An item struct containing the indirect object (the "actee")
 *
 * Returns
 * - 0 on success
 * - 1 on failure
 */
int do_item_item_action(game_t *g, action_type_t *a, item_t *direct, item_t *indirect);


#endif
