/* 
 * Functions and structs to be used in action_block_t implementation
 */

#ifndef INCLUDE_ACTION_BLOCK_H
#define INCLUDE_ACTION_BLOCK_H

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"

/* Forward delcaration */
typedef struct AST_block  AST_block_t;

/* An enumeration type for an action block */
typedef enum action_type {
    SET,
    SAY,
    MOVE, 
    ADDSUBMULTDIV, 
    GEN, 
    EXEC
} action_type;

/* A block that holds an action, as well as corresponding attributes and actions */
typedef struct action_block {
    enum action_type action_type;
    int num_args;
    attribute_t** args;
    AST_block_t* next;
} action_block_t;


/* 
 * Allocates an action block in the heap. 
 * 
 * Parameters: 
 * - integer containing the number of arguments 
 * - pointer to a list of attributes 
 * - pointer to the first AST block in the sequence 
 * - enum representing the action type 
 * 
 * Returns: 
 * - An action block. 
 */
action_block_t* action_block_new(enum action_type action_type, int num_args, 
attribute_t** args, AST_block_t *next);

/* 
 * Initializes an action block. 
 * 
 * Parameters: 
 * - action block. Must point to already allocated memory.  
 * - integer containing the number of arguments 
 * - pointer to a list of attributes 
 * - pointer to the first AST block in the sequence 
 * - enum representing the action type    
 * 
 * Returns: 
 * - SUCCESS if success, FAILURE if error occurs
 */
int action_block_init(action_block_t *action, enum action_type action_type, int num_args, 
attribute_t** args, AST_block_t *next);

/* 
 * Frees an action block. 
 * 
 * Parameters: 
 * - action block. Must point to an action block allocated with action_block_new. 
 * 
 * Returns: 
 * - Always returns 0. 
 */
int action_block_free(action_block_t *branch);  

#endif /* INCLUDE_ACTION_BLOCK_H */
