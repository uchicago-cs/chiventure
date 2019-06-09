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

int do_effect(game_action_effect_t *effect);

#endif