/* 
 * Basic functions for branch blocks to be used in custom-actions implementation. 
 * 
 * Please see "branch_block_functions.h" for function documentation. 
 */

#include <stdlib.h>
#include <stdio.h>
#include "custom-actions/struct.h"
#include "game-state/item.h"
#include "custom-actions/branch_block_functions.h"

/* See branch_block_functions.h */
branch_block_t* branch_block_new(int num_conditionals, conditional_block_t** 
conditionals, enum conditional_type conditional_type, int num_controls, 
control_block_t** controls)
{
    return NULL;
}

/* See branch_block_functions.h */
int branch_block_init(branch_block_t *branch, int num_conditionals, conditional_block_t**
conditionals, enum conditional_type conditional_type, int num_controls,
control_block_t** controls)
{
    return 0;
}

/* See branch_block_functions.h */
int branch_block_free(branch_block_t *branch)
{
    return 0;
} 
