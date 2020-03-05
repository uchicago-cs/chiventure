#ifndef _COMMON_GAME_ACTION_H
#define _COMMON_GAME_ACTION_H

#include "game-state/game_action.h"

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
				 attribute_t *attribute, attribute_value_t new_value);

#endif
