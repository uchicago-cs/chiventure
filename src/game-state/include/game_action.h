
#include "game_state_common.h"
#include "action_structs.h"
#include "item.h"

/* game_action_new() allocates a space for an action struct in memory and
* assigns given values to struct fields
*  Parameters:
*    action name and an action type struct
*  Returns:
*    A pointer to a new action struct.
*/
game_action_t *game_action_new(char *act_name, char* success_str, char* fail_str);


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


/* possible_action() checks if an item permits a specific action
 * Parameters:
 *  a pointer to the item
 *  the action name
 * Returns:
 *  true if item contains action, false if it does not
 */
bool possible_action(item_t* item, char* action_name);

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

//write header (fix params)
int add_action_condition(item_t* item, char* action_name);


/* check_conditionn() checks if the actual attribute of an item is equal to the desired attribute
 * Parameters:
 *  a pointer to the item to check
 *  the desired attribute 
 * Returns:
 *  true if desired attribute matches the actual, false if not
 */
bool check_condition(item_t *item, game_action_condition_t *condition);



/* all_conditions_met() checks if all of the conditions of an action are met
 * Parameters:
 *  a pointer to the item to check
 *  the action
 * Returns:
 *  SUCCESS if all conditions are met, FAILURE if not
 *  2 if action not possible
 */
int all_conditions_met(item_t* item, char* action_name);


//------------------------- EFFECT FUNCTIONS ------------------------------

/* add_action_effect creates an effect_t struct and adds it to the action pointed to
* Parameters:
* - ptr to action
* - ptr to item being modified
* - ptr to attribute to modify
* - new attribute_value_t (takes tag from attribute above)
* 
* Returns:
* int SUCCESS FAILURE
* error 2 if action NULL
* error 3 if item to modify is null
*/
int add_action_effect(game_action_t *action, item_t *item_to_modify, attribute_t *attribute, attribute_value_t *new_value);


//alt version 
//int add_effect(game_t *game, char* room_id, char* action, char* item_id, attribute_t *attribute, attribute_value_t *new_value);

//UNWRITTEN HEADER
//creates condition_t
condition_t *create_condition(item_t *item_to_modify, attribute_t *attribute, attribute_value_t *new_value);

//troll name find a better one
bool affect_effect(game_action_effect_t *effect);



 