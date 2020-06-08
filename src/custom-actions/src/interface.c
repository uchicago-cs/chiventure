/* 
 * Basic functions for custom-actions interface. 
 * 
 * Please see "interface.h" for function documentation. 
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "interface.h"

/* PRIVATE HELPER FUNCTIONS */

/* Given an conditiional block and its corresponding arguments, 
 * attempt to execute the given block.
 * 
 * Parameters: 
 * - block: A pointer to the conditional block to be evaluated
 * 
 * Returns:
 * - TRUE if condition true
 * - FALSE if condition false
 */
int do_conditional_block(conditional_block_t *block)
{
    switch(block->conditional_type) {
        case EQ:
            return check_eq(block->left,block->right);
            break;
        case LTGT: // functioning like case LT
            return check_lt(block->left,block->right);
            break;
        /* 
        case GT // once conditional_block struct changed
            return check_gt(block->left,block->right);
            break;
        */
        case LTEGTE: // functioning like case LTE at the moment
            return check_lte(block->left,block->right);
            break;
        /*
        case GTE // once conditional_block struct changed
            return check_gte(block->left,block->right);
            break;
        */
        case IN:
            return FAILURE;
            // return check_in(block->left,block->right); but check_in not yet implemented
            break;
    }
}

/* Given an branch block and its corresponding arguments, 
 * attempt to execute the given block.
 * 
 * Parameters: 
 * - block: A pointer to the branch block to be executed
 * 
 * Returns:
 * - Integer of what block to execute next
 */
int do_branch_block(branch_block_t *block)
{
    if(block->conditionals[0] == NULL) return -1;
    if(do_conditional_block(block->conditionals[0]) == TRUE) return 1;
    else return 0;
    
    /* Deprecated for future readers - we made last minute to ast_block that made branch blocks useless, hopefully one day they'll be reverted
    if(block->num_controls != block->num_conditionals) return -1;
    // goes through each of the control blocks
    int i;
    for(i = 0; i < block->num_controls; i++) 
    {
        // will perform the appropriate type of action
        switch(block->controls[i]->control_type) {
            case IFELSE:
                if(do_conditional_block(block->conditionals[i]) == TRUE) return i;
                break;
            case WHILEENDWHILE:
                // not implemented yet
                break;
            case FORENDFOR:
                // not implemented yet
                break;
        }
    }
    return i;
    */
}

/* Executes a given AST block (the essential element
 * of a custom action)
 * 
 * Parameters: 
 * - block: A pointer to the AST block to be executed
 * 
 * Returns:
 * - Integer value of SUCCESS or FAILURE
 */
int run_ast_block(AST_block_t *block) 
{
    int returnV;
    if(block == NULL) return SUCCESS;
    switch(block->block_type) 
    {
        case(CONTROL):
            return FAILURE;
            break;
        case(BRANCH):
            returnV = do_branch_block(block->block->branch_block);
            if(returnV == 0) return run_ast_block(block->prev);
            return run_ast_block(block->next);
            break;
        case(ACTION):
            if(exec_action_block(block->block->action_block) == FAILURE) 
                return FAILURE;
            return run_ast_block(block->next);
            break;
        case(CONDITIONAL):
            return FAILURE;
            break;   
    }
}

// Interface-showing functions

/* See interface.h */
int do_custom_action(custom_action_t *action)
{
    if(action == NULL) return FAILURE;
    return run_ast_block(action->head);
}



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

/*
 * See interface.h.
 * 
 * This depends on translate_custom_action having been written
 * (see backlog issue #796). Also needs tests.
 */
custom_action_t *compile_custom_action(object_t *action)
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
int add_custom_action_to_game(custom_action_t *action)
{
    if (action == NULL || action->action_name == NULL)
    {
        return FAILURE;
    }

    HASH_ADD_KEYPTR(hh, actions, action->action_name,
                    strlen(action->action_name), action);

    return SUCCESS;
}

/* 
 * See interface.h.
 * 
 * To be implemented in the future - see backlog issue #796.
 * Also needs tests.
 * 
 * NOTE: This would normally be a private helper function for 
 * compile_custom_action, but it is currently public for sandbox code use.
 */
custom_action_t *translate_custom_action(object_t *action)
{
    // to be implemented
    // to see object_t documentation, refer to wdl/object.h
    return NULL;
}
