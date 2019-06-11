#ifndef _COMMON_GAME_ACTION_H
#define _COMMON_GAME_ACTION_H

#include "game_action.h"

/* action_init() initializes an action struct with given values
   arguments are taken from action management
 Parameters:
    a memory allocated new action pointer
    an action name
    an action type struct
 Returns:
    FAILURE for failure, SUCCESS for success
*/
int game_action_init(game_action_t *new_action, char *act_name, char* success_str, char* fail_str);

/* game_action_new() allocates a space for an action struct in memory and
* assigns given values to struct fields
*  Parameters:
*    action name and an action type struct
*  Returns:
*    A pointer to a new action struct.
*/
game_action_t *game_action_new(char *action_name, char* success_str, char* fail_str);

/* condition_new() creates a new condition in an item with given inputs
 * Parameters:
 *  a pointer to the item to be modified
 *  a pointer to the attribute
 *  the desired value of the attribute
 * Returns:
 *  NULL if item or attribute are NULL, the new condition if succcessful
 */
game_action_condition_t *condition_new(item_t *item_to_modify, attribute_t *attribute,
				       attribute_value_t new_value);

/* create_effect creates an effect_t struct with the given inputs
 * Parameters:
 *  item to modify
 *  attribute_t
 *  attribute_value_t
 * Returns:
 * NULL or game_action_effect_t
 */
game_action_effect_t *effect_new(item_t *item_to_modify, attribute_t *attribute, attribute_value_t new_value);

/* check_condition() checks if the actual attribute of an item is equal
 * to the desired attribute
 * Parameters:
 *  a pointer to the item to check
 *  the desired attribute
 * Returns:
 *  true if desired attribute matches the actual, false if not
 */
bool check_condition(game_action_condition_t *condition);

/* do_effects() sets an effect
 * Parameters:
 *  pointer to effect
 * Returns:
 *  SUCCESS if effect is set, FAILURE if not
 */
int do_effect(game_action_effect_t *effect);

#endif