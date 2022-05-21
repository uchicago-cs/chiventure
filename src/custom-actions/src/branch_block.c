/* 
 * Basic functions and structs for branch blocks to be 
 * used in custom-actions implementation. 
 * 
 * Please see "branch_blocks.h" for function documentation. 
 */

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "branch_block.h"
#include "ast_block.h"

/* See branch_block.h */
branch_block_t* branch_block_new(int num_conditionals, conditional_block_t** conditionals, 
                                 control_type_t control_type, int num_actions, 
                                 AST_block_t** actions)
{
    branch_block_t *branch;
    int new_branch;
    block_type_t block_type = BRANCH;

    branch = malloc(sizeof(branch_block_t));

    if (branch == NULL)
    {
        fprintf(stderr,"Could not allocate memory");
        return NULL;
    }

    new_branch = branch_block_init(branch, num_conditionals, conditionals, 
                                   control_type, num_actions, actions);
    if (new_branch != SUCCESS)
    {
        fprintf(stderr,"Could not initialize branch_block_t");
        return NULL;
    }

    return branch;
}

/* See branch_block.h */
AST_block_t* AST_branch_block_new(int num_conditionals, conditional_block_t** conditionals, 
                                  control_type_t control_type, int num_actions, 
                                  AST_block_t** actions)
{
    AST_block_t *ast;
    branch_block_t *branch;
    int new_branch;
    block_type_t block_type = BRANCH;

    branch = malloc(sizeof(branch_block_t));
    ast = malloc(sizeof(AST_block_t));

    if (branch == NULL)
    {
        fprintf(stderr,"Could not allocate memory");
        return NULL;
    }

    new_branch = branch_block_init(branch, num_conditionals, conditionals, 
                                   control_type, num_actions, actions);
    if (new_branch != SUCCESS)
    {
        fprintf(stderr,"Could not initialize branch_block_t");
        return NULL;
    }

    block_t *block = malloc(sizeof(block));
    block->branch_block = branch;
    ast = AST_block_new(block, block_type);
    return ast;
}
    
/* See branch_block.h */
int branch_block_init(branch_block_t *branch, int num_conditionals, conditional_block_t** conditionals, 
                      control_type_t control_type, int num_actions,
                      AST_block_t** actions)
{
    assert(branch != NULL);
    assert(num_conditionals > 0);
    assert(conditionals != NULL); 
    assert(num_actions > 0);
    assert(actions != NULL);

    branch->num_conditionals = num_conditionals;
    branch->conditionals = conditionals;
    branch->control_type = control_type;
    branch->num_actions = num_actions;
    branch->actions = actions;

    return SUCCESS; 
}

/* See branch_block.h */
int branch_block_free(branch_block_t *branch)
{
    assert(branch != NULL);
    
    if (branch->num_conditionals > 0)
    {
       assert(branch->conditionals != NULL);
       for (int n = 0; n < branch->num_conditionals; n++)
       {
           conditional_block_free(branch->conditionals[n]);
       }
    }
    if (branch->num_actions > 0)
    {
        assert(branch->actions != NULL);
        for (int n = 0; n < branch->num_actions; n++)
        {
            AST_block_free(branch->actions[n]);
        }
    }
    free(branch);
    
    return SUCCESS; 
} 

/* See branch_block.h */
int do_branch_block(branch_block_t *block)
{
    if (block == NULL)
    {
        return FAILURE;
    }
    if (block->num_conditionals <= 0 || block->num_actions <= 0)
    {
        return FAILURE; //Not valid branch
    }
    switch (block->control_type)
    {
        case IFELSE:
            if (block->num_conditionals > block->num_actions || block->num_conditionals + 1 < block->num_actions)
            {
                return FAILURE; //All conditions must have actions
            }
            for (int i = 0; i < block->num_conditionals; i++)
            {
            /*
             * Loops over all the conditionals in the list of conditionals
             * If any conditional evalutes to True (0)
             *     Run the action associated with that conditional
             * First conditional represents the if statement,
             *    the rest of the conditionals represent elif statements
             */
                if (eval_conditional_block(block->conditionals[i]))
                {
                    return run_ast_block(block->actions[i]);
                }
            }
            /*
             * None of the if or elif statements were true
             * If there is still an unassociated action, then
             *     that action is run as an else clause of the if.
             */
            if (block->num_actions > block->num_conditionals)
            {
                return run_ast_block(block->actions[block->num_actions - 1]);
            }
            return SUCCESS;
        case FORENDFOR:
        case WHILEENDWHILE:
	    if(block->num_conditionals > 2 || block->num_actions != 1)
	    {
	        return FAILURE; //Invalid while syntax
	    }
	    conditional_block_t *loop = block->conditionals[0];
	    if (block->num_conditionals == 2)
	    {
	      /*
	       * Checks if a loop is a while loop or an end while loop
	       * While loop, num_conditionals = 1
	       * End while loop, different end condition num_conditionals = 2
	       */
	        loop = block->conditionals[1];
	    }
	    if (eval_conditional_block(block->conditionals[0]))
	    {
	      /*
	       * As with normal while loops, this can infinite loop
	       * There is no built in method for checking that this will terminate.
	       *     Also will not terminate after a set amount of time.
	       */
	        do
		{
		  int rc = run_ast_block(block->actions[0]);
		  if (rc == FAILURE)
		  {
		      return FAILURE;
		  }
		} while(eval_conditional_block(loop));
		return SUCCESS;
	    }
    } 
    return FAILURE;
}
