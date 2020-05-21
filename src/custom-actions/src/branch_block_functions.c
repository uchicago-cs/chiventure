/* 
 * Basic functions for branch blocks to be used in custom-actions implementation. 
 * 
 * Please see "branch_block_functions.h" for function documentation. 
 */

#include <stdlib.h>
#include <stdio.h>
#include "custom-actions/branch_block_structs.h"
#include "game-state/item.h"
#include "custom-actions/branch_block_functions.h"

/* See branch_block_functions.h */
branch_block_t* branch_block_new(int num_conditionals, conditional_block_t** 
conditionals, enum conditional_type conditional_type, int num_controls, 
control_block_t** controls)
{
    branch_block_t *branch;
    int new_branch;

    branch = malloc(sizeof(branch_block_t));

    if (branch == NULL)
    {
        error("Could not allocate memory");
        return NULL;
    }

    new_branch = branch_block_init(branch, num_conditionals, conditionals, 
    conditional_type, num_controls, controls);
    if (new_branch != SUCCESS)
    {
        error("Could not initialize branch_block_t");
        return NULL;
    }

    return branch;
}
    
/* See branch_block_functions.h */
int branch_block_init(branch_block_t *branch, int num_conditionals, conditional_block_t**
conditionals, enum conditional_type conditional_type, int num_controls,
control_block_t** controls)
{
    assert(branch != NULL);
    assert(num_conditionals != NULL);
    assert(conditionals != NULL);
    assert(conditional_type != NULL);
    assert(num_controls != NULL);
    assert(controls != NULL);

    branch->num_conditionals = num_conditionals;
    branch->conditionals = conditionals;
    branch->conditional_type = conditional_type;
    branch->num_controls = num_controls;
    branch->controls = controls;

    return SUCCESS; 
}

/* See branch_block_functions.h */
int branch_block_free(branch_block_t *branch)
{
    assert(branch != NULL);

    free(branch);
    
    return SUCCESS; 
} 
