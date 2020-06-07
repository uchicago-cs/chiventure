/* 
 * Basic functions for custom-actions interface. 
 * 
 * Please see "interface.h" for function documentation. 
 */

#include <stdlib.h>
#include <stdio.h>
#include "custom-actions/interface.h"
#include "ast_block.h"
#include "custom_action.h"

/* See interface.h */
custom_action_t *search_for_custom_action(char *action_name, game_t *game)
{
    return NULL;
}

/* See interface.h */
int do_custom_action(custom_action_t *action, char **args, int num_args)
{
    AST_block_t *current = action->head;
    int rc = 0;
    while (current != NULL)
    {
        switch (current->block_type)
        {
        case CONTROL:
            rc = exec_control_block(current->block);
            break;
        case BRANCH:
            rc = exec_branch_block(current->block);
            break;
        case ACTION:
            rc = exec_action_block(current->block);
            break;
        case CONDITIONAL:
            rc = exec_conditional_block(current->block);
            break;
        }
        if (rc == FAILURE)
        {
            return FAILURE;
        }
        current = current->next;
    }
    return SUCCESS;
}

/* See interface.h */
custom_action_t *compile_custom_action(json_dict_obj *json, game_t *game)
{
    return NULL;
}

/* See interface.h */
int free_custom_action(custom_action_t *action)
{
    assert(action);
    free(action);
    return SUCCESS;
}

/* See interface.h */
char *get_custom_action_name(custom_action_t *action)
{
    return action->action_name;
}
