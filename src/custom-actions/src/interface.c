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

/* PRIVATE HELPER FUNCTIONS */

/* Note to those writing helper functions - these functions could also take
 * AST_block_t blocks as parameters, if you find that's better suited. - Annabelle*/

/* Given an action block and its corresponding arguments, 
 * attempt to execute the given block.
 * 
 * Parameters: 
 * - block: A pointer to the action block to be executed
 * 
 * Returns:
 * - SUCCESS on successful execution
 * - FAILURE/TBD on specific types of failure
 */
int do_action_block(action_block_t *block)
{
    return 0;
}

/* Given an branch block and its corresponding arguments, 
 * attempt to execute the given block.
 * 
 * Parameters: 
 * - block: A pointer to the branch block to be executed
 * 
 * Returns:
 * - SUCCESS on successful execution
 * - FAILURE/TBD on specific types of failure
 */
int do_branch_block(branch_block_t *block)
{
    return 0;
}

/* Given an conditiional block and its corresponding arguments, 
 * attempt to execute the given block.
 * 
 * Parameters: 
 * - block: A pointer to the conditional block to be evaluated
 * 
 * Returns:
 * - SUCCESS on successful execution
 * - FAILURE/TBD on specific types of failure
 */
int do_conditional_block(conditional_block_t *block)
{
    return 0;
}

/* Given an control block and its corresponding arguments, 
 * attempt to execute the given block.
 * 
 * Parameters: 
 * - block: A pointer to the control block to be executed
 * 
 * Returns:
 * - SUCCESS on successful execution
 * - FAILURE/TBD on specific types of failure
 */
int do_control_block(control_block_t *block)
{
    return 0;
}