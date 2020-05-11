/* 
 * Basic functions for custom-actions interface. 
 * 
 * Please see "interface.h" for function documentation. 
 */

#include <stdlib.h>
#include <stdio.h>
#include "interface.h"
#include "struct.h"

/* See interface.h */
custom_action_t *search_for_custom_action(char *action_name, game *game)
{
    return NULL;
}

/* See interface.h */
int do_custom_action(custom_action_t *action, char **args, int num_args)
{
    return 0;
}

/* See interface.h */
custom_action_t *compile_custom_action(json_dict_obj *json, game *game)
{
    return NULL;
}

/* See interface.h */
int free_custom_action(custom_action_t *action)
{
    return 0;
}

/* See interface.h */
char *get_custom_action_name(custom_action_t *action)
{
    return ' ';
}
