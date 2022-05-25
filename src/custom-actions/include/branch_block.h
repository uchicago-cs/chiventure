/* 
 * Functions and structs to be used in branch_block_t implementation
 */

#ifndef INCLUDE_BRANCH_BLOCK_H
#define INCLUDE_BRANCH_BLOCK_H

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "conditional_block.h"
#include "control_block.h"

/* Forward declaration */
typedef struct AST_block AST_block_t;

/* A block that holds pointers to both a control and a conditional block */
typedef struct branch_block {
    int num_conditionals;
    conditional_block_t** conditionals;
    control_type_t control_type;
    int num_actions;
    AST_block_t** actions;
} branch_block_t;

/* 
 * Allocates a branch block in the heap. 
 * 
 * Parameters: 
 * - integer containing the number of conditional blocks
 * - pointer to a list of conditional blocks
 * - enum representing the conditional type 
 * - integer for the number of control blocks
 * - pointer to a list of control blocks 
 * 
 * Returns: 
 * - A branch block. 
 */  
branch_block_t* branch_block_new(int num_conditionals, conditional_block_t** conditionals, 
                                 control_type_t control_type, int num_actions,
				 AST_block_t** actions);

/* 
 * Allocates an AST type branch block in the heap. 
 * 
 * Parameters: 
 * - integer containing the number of conditional blocks
 * - pointer to a list of conditional blocks
 * - enum representing the conditional type 
 * - integer for the number of control blocks
 * - pointer to a list of control blocks 
 * 
 * Returns: 
 * - An AST block. 
 */  
AST_block_t* AST_branch_block_new(int num_conditionals, conditional_block_t** conditionals, 
                                  control_type_t control_type, int num_actions, 
                                  AST_block_t** actions);

/* 
 * Initializes a branch block. 
 * 
 * Parameters: 
 * - branch block. Must point to already allocated memory.  
 * - integer containing the number of conditional blocks
 * - pointer to a list of conditional blocks
 * - enum representing the conditional type  
 * - integer for the number of control blocks
 * - pointer to a list of control blocks  
 * 
 * Returns: 
 * - SUCCESS if success, FAILURE if error occurs
 */  
int branch_block_init(branch_block_t *branch, int num_conditionals, conditional_block_t** conditionals, 
                      control_type_t control_type, int num_actions,
                      AST_block_t** actions);

/* 
 * Frees a branch block, as well as the conditional and control blocks nested within it. 
 * 
 * Parameters: 
 * - branch block. Must point to a branch block allocated with branch_block_new. 
 * 
 * Returns: 
 * - Always returns 0. 
 */  
int branch_block_free(branch_block_t *branch);

/* Given an branch block and its corresponding arguments,
 * attempt to execute the given block.
 *
 * Parameters:
 * - block: A pointer to the branch block to be executed
 *
 * Returns:
 * - SUCCESS if successful
 * - FAILURE if unsuccessful
 */
int do_branch_block(branch_block_t *block);

#endif /* INCLUDE_BRANCH_BLOCK_H */
