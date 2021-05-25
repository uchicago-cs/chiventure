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
