/* 
 * Basic functions for custom-actions interface. 
 * 
 * Please see "interface.h" for function documentation. 
 */

#include <stdlib.h>
#include <stdio.h>
#include "custom-actions/interface.h"

/* See interface.h */
custom_action_t *search_for_custom_action(char *action_name, game_t *game)
{
    return NULL;
}

/* See interface.h */
int do_custom_action(custom_action_t *action, char **args, int num_args)
{
    // need to check if item is there
    // then need to just execute first AST_block in struct, everything will follow from there
    return 0;
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

<<<<<<< HEAD
void run_ast_block(AST_block_t *block) 
{
    if(block == NULL) return;
    switch(block->block_type) 
    {
        case(CONTROL):
            do_control_block(block->block);
            break;
        case(BRANCH):
            int i = do_branch_block(block->block);
            run_ast_block(block->next[i]);
            break;
        case(ACTION):
            do_action_block(block->block);
            break;
        case(CONDITIONAL):
            do_conditional_block(block->block);
            break;   
    }
}


=======
>>>>>>> 41fa530b3bd07ce55e3831b8d19ce2ff1c024f7d
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
<<<<<<< HEAD
    // goes through each of the control blocks
    for(int i = 0; i < block->numcontrols; i++) 
    {
        // will perform the appropriate 
        switch(block->controls[i]->control_type) {
            case IFELSE:
                if(do_conditional_block(block->conditionals[i]) == SUCCESS) return i;
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
=======
    return 0;
>>>>>>> 41fa530b3bd07ce55e3831b8d19ce2ff1c024f7d
}

/* Given an conditiional block and its corresponding arguments, 
 * attempt to execute the given block.
 * 
 * Parameters: 
 * - block: A pointer to the conditional block to be evaluated
 * 
 * Returns:
<<<<<<< HEAD
 * - TRUE if condition true
 * - FALSE if condition false
 */
bool do_conditional_block(conditional_block_t *block)
=======
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
>>>>>>> 41fa530b3bd07ce55e3831b8d19ce2ff1c024f7d
{
    return 0;
}