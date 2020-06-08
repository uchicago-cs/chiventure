/* 
 * Basic functions for custom-actions interface. 
 * 
 * Please see "interface.h" for function documentation. 
 */

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
            if(returnV == 0) return block->previous;
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
