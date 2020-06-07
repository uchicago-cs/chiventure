/* 
 * Basic functions for custom-actions interface. 
 * 
 * Please see "interface.h" for function documentation. 
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "interface.h"
#include "libobj/obj.h"
/*
 * A list of all custom actions. This is a placeholder which will eventually
 * be replaced by a list inside of game-state/game.h.
 */
custom_action_t *actions = NULL;

/* See interface.h */
custom_action_t *search_for_custom_action(char *action_name)
{
    custom_action_t *result = NULL;
    HASH_FIND_STR(actions, action_name, result);
    return result;
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
custom_action_t *compile_custom_action(obj_t *action)
{
    custom_action_t *translated = translate_custom_action(action);

    if (translated == NULL)
    {
        return NULL;
    }

    int rc = add_custom_action_to_game(translated);
    if (rc == FAILURE)
    {
        return NULL;
    }

    return translated;
}

/* 
 * See interface.h.
 * 
 * NOTE: This would normally be a private helper function for 
 * compile_custom_action, but it is currently public for sandbox code use.
 */
int *add_custom_action_to_game(custom_action_t *action)
{
    if (action == NULL || action->name == NULL)
    {
        return FAILURE;
    }

    HASH_ADD_KEYPTR(hh, actions, action->action_name, strlen(action->action_name), action);

    return SUCCESS;
}

/* 
 * See interface.h.
 * 
 * NOTE: This would normally be a private helper function for 
 * compile_custom_action, but it is currently public for sandbox code use.
 */
custom_action_t *translate_custom_action(obj_t *action)
{
    // to be implemented
    // to see obj_t documentation, refer to libobj/obj.h
    return NULL;
}
