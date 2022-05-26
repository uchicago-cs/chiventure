#ifndef _GAME_ACTION_H
#define _GAME_ACTION_H

#include "item.h"
#include "game_state_common.h"
#include "action_management/action_structs.h"
#include "condition.h"
#include "npc/npc.h"


// ------------------------- ACTION FUNCTIONS -------------------------
// the following functions are to do with searching for allowed actions
// and conducting actions

/* get_action() returns the game_action_t associated with an action
 * Parameters:
 *  a pointer to the agent
 *  the action name
 * Returns:
 *  the action struct associated or NULL if not associated
 */
game_action_t *get_action(agent_t *agent, char *action_name);

/* add_action() adds a (presumed legal) action to an agent
 * Parameters:
 *  a pointer to the agent
 *  the action name
 *  the action struct
 *  the action type (as specified by action management)
 *  the string to print should the action be performed successfully
 *  the string to print shoulf the action fail to be performed
 * Returns:
 *  SUCCESS if added correctly, FAILURE if failed to add
 */
int add_action(agent_t *agent, char *action_name, char *success_str, char *fail_str);


/* possible_action() checks if an item permits a specific action
 * Parameters:
 *  a pointer to the agent
 *  the action name
 * Returns:
 *  SUCCESS if item contains action, FAILURE if it does not
 */
int possible_action(agent_t *agent, char *action_name);

/*
 * Function to get a linked list (utlist) of all the actions in the item
 *
 * Parameters:
 *  item
 *
 * Returns:
 *  linked list of pointers to actions (the head element)
 */
game_action_hash_t *get_all_actions(item_t *item);


/* game_action_free() frees allocated space for an action struct in memory
 *  Parameters:
 *    a pointer to the action
 *  Returns:
 *    SUCCESS if successful, FAILURE if not
 */
int game_action_free(game_action_t *action_tofree);



// ------------------------- CONDITION FUNCTIONS -------------------------

/* add_action_attribute_condition() creates a new attribute condition for an item's action and
 * adds to the action's condition list
 * Parameters:
 *  a pointer to the action to which the condition is being added
 *  a pointer to the item specified in the action condition
 *  a pointer to the attribute of the item specified in action condition that needs to be validated
 *  the value of the above attribute that needs to be validated
 * Returns:
 *  SUCCESS upon SUCCESS
 *  ACTION_NULL if specified action does not exist in first item
 *  ITEM_MODIFY_NULL if the item ID does not exist
 */
int add_action_attribute_condition(game_action_t *action, item_t *cond_item, 
			 attribute_t *cond_attribute, attribute_value_t *cond_value);

/* add_action_inventory_condition() creates a new inventory condition for an item's action and
 * adds to the action's condition list
 * Parameters:
 *  a pointer to the action to which the condition is being added
 *  a pointer to the player whose inventory to check
 *  a pointer to the item to check in the inventory
 * Returns:
 *  SUCCESS upon SUCCESS
 *  ACTION_NULL if specified action does not exist in first item
 *  PLAYER_NULL if the player does not exist
 *  ITEM_MODIFY_NULL if the item ID does not exist
 */
int add_action_inventory_condition(game_action_t *action, player_t *player,
                                    item_t *item);


/* add_action_condition() adds the given condition to the action's linkedlist of
 * conditions
 * Parameters:
 *   a pointer to the action to add to
 *   the condition
 * Returns:
 *   SUCCESS upon SUCCESS
 *   ACTION_NULL if action does not exist
 */
int add_action_condition(game_action_t *action, condition_t *condition);

/*
 * Function that returns the node with the right action_type_t
 *
 * Parameters:
 * - list_action_type_t: list containing actions
 * - action_type_t: action that we want
 *
 * Returns:
 * pointer to correct list_action_type_t node
 */
list_action_type_t *find_act(list_action_type_t *head, action_type_t *a);

/*
 * Function that deletes a node in list_action_type_t
 * 
 * Parameters:
 * - action_type_t: action to be deleted
 * - list_action_type_t: list to remove action from
 *
 * Returns:
 * - int SUCCESS when node is removed
 */
int delete_action(list_action_type_t **head, list_action_type_t *act);


// ------------------------- EFFECT FUNCTIONS ------------------------------


/* add_action_effect creates an effect_t struct and adds it to the action pointed to
 * Parameters:
 *  pointer to action
 *  pointer to item being modified
 *  pointer to attribute to modify
 *  new attribute_value_t (takes tag from attribute above)
 *
 * Returns:
 * SUCCESS upon success, FAILURE upon failure
 * ACTION_NULL if action NULL
 * ITEM_MODIFY_NULL if item to modify is null
 */
int add_action_effect(game_action_t *action, item_t *item_to_add, 
		      attribute_t *attribute, attribute_value_t *new_value);

/* delete_action_effect_llist frees a linked list of action effects
 * Parameters:
 *  linked list of effects
 *
 * Returns:
 *  always returns SUCCESS
 */
int delete_action_effect_llist(action_effect_list_t *effects);

//alt version

/* do_effects() sets an effect
 * Parameters:
 *  pointer to effect
 * Returns:
 *  SUCCESS if effect is set, FAILURE if not
 */
int do_effect(game_action_effect_t *effect);

/* do_all_effects() sets all effects of an action
 * Parameters:
 *  pointer to the agent to check
 *  the action_name
 * Returns:
 *  SUCCESS if all effects are set, FAILURE if not
 */
int do_all_effects(agent_t *agent, char *action_name);

/* action_init() initializes an action struct with given values
   arguments are taken from action management
 Parameters:
    a memory allocated new action pointer
    an action name
    an action type struct
 Returns:
    FAILURE for failure, SUCCESS for success
*/
int game_action_init(game_action_t *new_action, char *act_name, 
		     char* success_str, char* fail_str);

/* game_action_new() allocates a space for an action struct in memory and
* assigns given values to struct fields
*  Parameters:
*    action name
*    a success string
*    a failure string
*  Returns:
*    A pointer to a new action struct.
*/
game_action_t *game_action_new(char *action_name, char* success_str, char* fail_str);

/* do_effect() performs given effect
 *
 * Parameters:
 *   pointer to an action effect
 * Returns:
 *   SUCCESS upon success, FAILURE upon failure
 */
int do_effect(game_action_effect_t *effect);

/* create_effect creates an effect_t struct with the given inputs
 * Parameters:
 *  pointer to item to modify
 *  pointer to attribute_t
 *  attribute_value_t
 * Returns:
 * NULL or game_action_effect_t
 */
game_action_effect_t *effect_new(item_t *item_to_modify, 
				 attribute_t *attribute, attribute_value_t *new_value);

#endif
