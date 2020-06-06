#include "npc_action.h"
#include "game-state/game_state_common.h"
#include "game-state/item.h"
#include "game-state/game_action.h"

/*
 * Returns the game_action_t associated with an action
 * Parameters:
 *  - npc: a pointer to the npc
 *  - action_name: the action name
 * Returns:
 *  - the npc action struct associated or NULL if not associated
 */
npc_action_t *get_npc_action(npc_t *npc, char* action_name);

/* Checks if an npc permits a specific action
 * Parameters:
 *  - npc: a pointer to the npc
 *  - action_name: the action name
 * Returns:
 *  - SUCCESS if npc contains action, FAILURE if it does not
 */
int possible_npc_action(npc_t *npc, char* action_name);

/*
 * Function to get a linked list (utlist) of all the actions for the npc
 *
 * Parameters:
 *  - npc: a pointer to the npc
 *
 * Returns:
 *  - linked list of pointers to actions (the head element)
 */
game_action_hash_t *get_all_actions(npc_t *npc);

/* 
 * Creates a new condition for an npc's action and adds to the action's condition list
 * Parameters:
 *  - npc: a pointer to the npc the action is being performed on
 *  - action: a pointer to the action to which the condition is being added
 *  - cond_item: a pointer to the item specified in the action condition
 *  - attribute_t: a pointer to the attribute of the item specified in action condition that needs to be validated
 *  - attribute_value_t: the value of the above attribute that needs to be validated
 * Returns:
 *  - SUCCESS upon SUCCESS
 *  - ITEM_SRC_NULL if npc ID does not exist
 *  - ACTION_NULL if specified action does not exist in first npc
 *  - ITEM_MODIFY_NULL if item ID does not exist
 */
int add_npc_action_condition(npc_t *npc, game_action_t *action, item_t *cond_item, attribute_t *cond_attribute, attribute_value_t cond_value);

/* 
 * Creates a new condition in an npc with given inputs
 * Parameters:
 *  - npc: a pointer to the npc to be modified
 *  - attribute: a pointer to the attribute
 *  - new_value: the desired value of the attribute
 * Returns:
 *  - NULL if npc or attribute are NULL, the new condition if succcessful
 */
game_action_condition_t *npc_condition_new(npc_t *npc, attribute_t *attribute, attribute_value_t new_value);

/* 
 * Checks if all of the conditions of an action are met
 * Parameters:
 *  - npc: a pointer to the npc to check
 *  - action_name: the action name
 * Returns:
 *  SUCCESS if all conditions are met, FAILURE if not
 *  2 if action not possible
 */
int all_npc_conditions_met(npc_t *npc, char* action_name);

/* 
 * Creates an effect_t struct and adds it to the action pointed to
 * Parameters:
 *  - action: pointer to action
 *  - npc: pointer to npx being modified
 *  - attribute: pointer to attribute to modify
 *  - new_value: new attribute_value_t (takes tag from attribute above)
 *
 * Returns:
 *  - SUCCESS upon success, FAILURE upon failure
 *  - ACTION_NULL if action NULL
 *  - ITEM_MODIFY_NULL if npc to modify is null
 */
int add_action_effect(game_action_t *action, npc_t *npc, attribute_t *attribute, attribute_value_t new_value);

/* 
 * Sets all effects of an action
 * Parameters:
 *  - npc: pointer to the npc to check
 *  - action_name: the action_name
 * Returns:
 *  - SUCCESS if all effects are set, FAILURE if not
 */
int do_all_effects(npc_t *npc, char* action_name);