/* 
 * Functions and structs to be used in control_block_t implementation
 */

#ifndef INCLUDE_CONTROL_BLOCK_FUNCTIONS_H
#define INCLUDE_CONTROL_BLOCK_FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "custom-actions/ast_block_functions.h"

/* An enumeration type for a control block */
typedef enum control_type control_type;

/* Struct to contain a control block, which introduces an action */
typedef struct control_block control_block_t;

/* 
 * Allocates a control block in the heap. 
 * 
 * Parameters: 
 * - pointer to the first AST block in the sequence 
 * - enum representing the control type 
 * 
 * Returns: 
 * - A control block. 
 */  
control_block_t* control_block_new(enum control_type control_type, AST_block_t *next);

/* 
 * Initializes a control block. 
 * 
 * Parameters: 
 * - Control block. Must point to already allocated memory. 
 * - Control type, first AST block in sequence: parameters that define the control block
 * 
 * Returns: 
 * - SUCCESS if success, FAILURE if error occurs
 */  
int control_block_init(control_block_t *control, enum control_type control_type,
AST_block_t *next);

/* 
 * Frees a control block. 
 * 
 * Parameters: 
 * - Control block. Must point to a control block allocated with control_block_new. 
 * 
 * Returns: 
 * - Always returns 0. 
 */  
int control_block_free(control_block_t *control);

#endif /* INCLUDE_CONTROL_BLOCK_FUNCTIONS_H */
