/* 
 * Functions and structs to be used in action_block_t implementation
 */

#ifndef INCLUDE_ACTION_BLOCK_H
#define INCLUDE_ACTION_BLOCK_H

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "ast_block.h"

/* An enumeration type for an action block */
typedef enum action_type {
    SET,
    SAY,
    MOVE, 
    ADDSUBMULTDIV, 
    GEN, 
    EXEC
} action_enum_t;

/* A block that holds an action, as well as corresponding attributes and actions */
typedef struct action_block {
    action_enum_t action_type;
    int num_args;
    attribute_t** args;
} action_block_t;

/* 
 * Allocates an action block in the heap. 
 * 
 * Parameters: 
 * - integer containing the number of arguments 
 * - pointer to a list of attributes 
 * - enum representing the action type 
 * 
 * Returns: 
 * - An action block. 
 */
action_block_t* action_block_new(action_enum_t action_type, int num_args, 
attribute_t** args);

/* 
 * Allocates an AST type action block in the heap. 
 * 
 * Parameters: 
 * - integer containing the number of arguments 
 * - pointer to a list of attributes 
 * - enum representing the action type 
 * 
 * Returns: 
 * - An action block. 
 */
AST_block_t* AST_action_block_new(action_enum_t action_type, int num_args, 
attribute_t** args);

/* 
 * Initializes an action block. 
 * 
 * Parameters: 
 * - action block. Must point to already allocated memory.  
 * - integer containing the number of arguments 
 * - pointer to a list of attributes 
 * - enum representing the action type    
 * 
 * Returns: 
 * - SUCCESS if success, FAILURE if error occurs
 */
int action_block_init(block_t *action, action_enum_t action_type, int num_args, 
attribute_t** args);

/* 
 * Frees an action block. 
 * 
 * Parameters: 
 * - action block. Must point to an action block allocated with action_block_new. 
 * 
 * Returns: 
 * - Always returns 0. 
 */
int action_block_free(action_block_t *action);  

#endif /* INCLUDE_ACTION_BLOCK_H */
