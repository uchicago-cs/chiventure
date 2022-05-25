/* 
 * Functions and structs to be used in conditional_block_t implementation
 */

#ifndef INCLUDE_CONDITIONAL_BLOCK_H
#define INCLUDE_CONDITIONAL_BLOCK_H

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"

/* Forward declaration */
typedef struct AST_block AST_block_t;

/* An enumeration type for a conditional block */
typedef enum conditional_type {
    EQ,
    LTB,
    GTB,
    LTEB,
    GTEB,
    IN
} conditional_type_t;

/* A block that returns true or false, and contains an operator and two attributes */
typedef struct conditional_block {
    conditional_type_t conditional_type;
    attribute_t* left;
    attribute_t* right;
} conditional_block_t;

/* 
 * Allocates a conditional block in the heap. 
 * 
 * Parameters: 
 * - enum representing the conditional type 
 * - pointer to a "left" attribute
 * - pointer to a "right" attribute 
 * 
 * Returns: 
 * - A conditional block. 
 */
conditional_block_t* conditional_block_new(conditional_type_t conditional_type, 
                                           attribute_t* left, attribute_t* right);

/* 
 * Allocates an AST type conditional block in the heap. 
 * 
 * Parameters: 
 * - enum representing the conditional type 
 * - pointer to a "left" attribute
 * - pointer to a "right" attribute 
 * 
 * Returns: 
 * - An AST block. 
 */
AST_block_t* AST_conditional_block_new(conditional_type_t conditional_type, 
                                       attribute_t* left, attribute_t* right);

/* 
 * Initializes a conditional block. 
 * 
 * Parameters: 
 * - conditional block. Must point to already allocated memory.  
 * - enum representing the conditional type  
 * - pointer to a "left" attribute 
 * - pointer to a "right" attribute    
 * 
 * Returns: 
 * - SUCCESS if success, FAILURE if error occurs
 */
int conditional_block_init(conditional_block_t *conditional, conditional_type_t 
                           conditional_type, attribute_t* left, attribute_t* right);

/* 
 * Frees a conditional block. 
 * 
 * Parameters: 
 * - conditional block. Must point to a conditional block allocated with conditional_block_new. 
 * 
 * Returns: 
 * - Always returns 0. 
 */
int conditional_block_free(conditional_block_t *conditional);

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
int eval_conditional_block(conditional_block_t *block);

#endif /* INCLUDE_CONDITIONAL_BLOCK_H */
