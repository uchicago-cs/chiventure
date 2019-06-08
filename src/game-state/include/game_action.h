
#include "game_state_common.h"
#include "action_structs.h"
#include "item.h"

/* item_free() frees allocated space for an action struct in memory
*  Parameters:
*    a pointer to the action
*  Returns:
*    SUCCESS if successful, FAILURE if not
*/
int game_action_free(game_action_t *action_tofree);

//ACTION FUNCTIONS
// the following functions are to do with searching for allowed actions
//and conducting actions

/* get_action() returns the game_action_t associated with an action
 * Parameters:
 *  a pointer to the item
 *  the action name
 * Returns:
 *  the action struct associated or NULL if not associated
 */
game_action_t *get_action(item_t *item, char* action_name);

/* add_action() adds a (presumed legal) action to an item
 * Parameters:
 *  a pointer to the item
 *  the action name
 *  the action struct
 *  the action type (as specified by action management)
 *  the string to print should the action be performed successfully
 *  the string to print shoulf the action fail to be performed
 * Returns:
 *  SUCCESS if added correctly, FAILURE if failed to add
 */
int add_action(item_t* item, char *action_name, char* success_str, char* fail_str);


/* REDO THIS possible_action() (formerly allowed_action())checks if an item permits a specific action
 * Parameters:
 *  a pointer to the item
 *  the action name
 * Returns:
 *  true if item contains action, false if it does not
 */
bool possible_action(item_t* item, char* action_name);

//ACTION LIST FUNCTIONS
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


/* check_conditionn() checks if the actual attribute of an item is equal to the desired attribute
 * Parameters:
 *  a pointer to the item to check
 *  the desired attribute 
 * Returns:
 *  true if desired attribute matches the actual, false if not
 */
bool check_condition(item_t *item, attribute_t* desired_attribute);



/* all_conditions_met() checks if all of the conditions of an action are met
 * Parameters:
 *  a pointer to the item to check
 *  the action
 * Returns:
 *  true if all conditions are met, false if not
 */
bool all_conditions_met(item_t* item, char* action_name);
