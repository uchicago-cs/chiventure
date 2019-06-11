#ifndef _ACTIONS_H_
#define _ACTIONS_H_

#include "action_structs.h"
#include "item.h"
#include "room.h"
#include "game.h"
#include "ctx.h"

// forward declaration
typedef struct chiventure_ctx chiventure_ctx_t;

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
 * - a: a pointer to an empty action_type_t allocated by action_type_new
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
 * - a: An action type struct. Must point to action type struct allocated by action_type_new
 *
 * Returns:
 * - 0 if success, 1 if an error occurs
 */
int action_type_free(action_type_t *a);


// =============================================================================

/*
 * Note: this function is in the src file get_actions.c, a separate module
 * from the rest of the functions, which are in actionmanagement.c.
 * A function that returns all supported actions.
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
 * - a: An action type struct
 * - i: An item struct
 * - ret_string: A pointer to a string describing the result of the function
 *   - NOTE: THIS STRING IS MALLOCED AND MUST BE FREED BY USERS OF THIS FUNCTION
 *
 * Returns:
 * - 0 upon success, success string as an out parameter
 * - 1 if the action type has the wrong kind, failure string as an out parameter
 * - 2 if the action can't be used on the item, failure string as an out parameter
 */
int do_item_action(action_type_t *a, item_t *i, char **ret_string);


/* A function that executes KIND 2 actions (ACTION <path>)
 *
 * Parameters:
 * - c: A context struct encapsulating the shared state in chiventure
 * - a: An action type struct
 * - p: A path struct
 * - ret_string: A pointer to a string describing the result of the function
 *   - NOTE: THIS STRING IS MALLOCED AND MUST BE FREED BY USERS OF THIS FUNCTION
 *
 * Returns:
 * - 0 upon success, success string as an out parameter
 * - 1 if the action type has the wrong kind, failure string as an out parameter
 */
int do_path_action(chiventure_ctx_t *c, action_type_t *a, path_t *p, char **ret_string);


/* A function that executes KIND 3 actions (ACTION <item> <item>)
 *
 * Parameters:
 * - a: An action type struct
 * - direct: An item struct containing the direct object (the "actor")
 * - indirect: An item struct containing the indirect object (the "actee")
 * - ret_string: A pointer to a string describing the result of the function
 *   - NOTE: THIS STRING IS MALLOCED AND MUST BE FREED BY USERS OF THIS FUNCTION
 *
 * Returns:
 * - 0 upon success, success string as an out parameter
 * - 1 if the action type has the wrong kind, failure string as an out parameter
 * - 2 if the action can't be used on the item, failure string as an out parameter
 */
int do_item_item_action(action_type_t *a, item_t *direct,
                        item_t *indirect, char **ret_string);


#endif
