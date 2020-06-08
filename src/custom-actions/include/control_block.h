/* 
 * Functions and structs to be used in control_block_t implementation
 */

#ifndef INCLUDE_CONTROL_BLOCK_H
#define INCLUDE_CONTROL_BLOCK_H

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"

/* Forward declaration */
typedef struct AST_block AST_block_t;

/* An enumeration type for a control block */
typedef enum control_type {
    IFELSE,
    WHILEENDWHILE,
    FORENDFOR
} control_type_t;

/* Struct to contain a control block, which introduces an action */
typedef struct control_block {
    control_type_t control_type;
} control_block_t;

/* 
 * Allocates a control block in the heap. 
 * 
 * Parameters: 
 * - enum representing the control type 
 * 
 * Returns: 
 * - A control block. 
 */  
control_block_t* control_block_new(control_type_t control_type);

/* 
 * Allocates an AST type control block in the heap. 
 * 
 * Parameters: 
 * - enum representing the control type 
 * 
 * Returns: 
 * - An AST block. 
 */ 
AST_block_t* AST_control_block_new(control_type_t control_type);

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
int control_block_init(control_block_t *control, control_type_t control_type);

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

#endif /* INCLUDE_CONTROL_BLOCK_H */
