/* 
 * Structs to be used in custom-actions implementation
 */

#ifndef INCLUDE_STRUCT_H_
#define INCLUDE_STRUCT_H_

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"

/* An enumeration type for an AST block */
typedef enum block_type {
    CONTROL, 
    BRANCH, 
    ACTION, 
    CONDITIONAL
} block_type;

/* An enumeration type for a control block */
typedef enum control_type {
    IFELSE,
    WHILEENDWHILE,
    FORENDFOR
} control_type;

/* An enumeration type for a conditional block */
typedef enum conditional_type {
    EQ,
    LTGT,
    LTEGTE,
    IN
} conditional_type;

/* An enumeration type for an action block */
typedef enum action_type {
    SET,
    SAY,
    MOVE, 
    ADDSUBMULTDIV, 
    GEN, 
    EXEC
} action_type;

/* A block that returns true or false, and contains an operator and two attributes */
typedef struct conditional_block {
    enum conditional_type conditional_type;
    attribute_t* left;
    attribute_t* right;
} conditional_block_t;

/* Struct to represent the type of a block */
typedef union block {
    control_block_t control_block;
    branch_block_t branch_block;
    action_block_t action_block;
    conditional_block_t conditional_block;
} block_t;

/* Struct to contain a block, as well as its type */
typedef struct AST_block {
    block_t block;
    enum block_type block_type;
} AST_block_t;

/* A block that holds an action, as well as corresponding attributes and actions */
typedef struct action_block {
    enum action_type action_type;
    int num_args;
    attribute_t** args;
    AST_block_t* next;
} action_block_t;

/* Struct to contain a control block, which introduces an action */
typedef struct control_block {
    enum control_type control_type;
    AST_block_t* next;
} control_block_t;

/* A block that holds pointers to both a control and a conditional block */
typedef struct branch_block {
    int num_conditionals;
    conditional_block_t** conditionals;
    enum conditional_type conditional_type;
    int num_controls;
    control_block_t** controls;
} branch_block_t;
  
#endif /* INCLUDE_STRUCT_H_ */
