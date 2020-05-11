/* 
 * Structs to be used in custom-actions implementation
 */

#ifndef INCLUDE_STRUCT_H_
#define INCLUDE_STRUCT_H_

#include <stdlib.h>
#include <stdio.h>

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

/* Sruct to conatin a control block, which introduces an action */
typedef struct control_block {
    enum control_type control_type;
    AST_block* next
} control_block_t;

/* A block that holds pointers to both a control and a conditional block */
typedef struct branch_block {
    int num_conditionals;
    conditional_block_t** conditionals;
    enum conditional_union_type conditional_union_type;
    int num_controls;
    control_block_t** controls;
} branch_block_t;

/* A block that holds an action, as well as corresponding attributes and actions */
typedef struct action_block {
    enum action_type action_type;
    int num_args;
    attribute_t** args;
    AST_block* next;
} action_block_t;

/* A block that returns true or false, and contains an operator and two attributes */
typedef struct conditional_block {
    enum conditional_type conditional_type;
    attribute_t* left;
    attribute_t* right;
} conditional_block_t;

/* A block that serves as a wrapper for a single primitive value */
typedef union attribute_value {
    double double_val;
    char char_val;
    bool bool_val;
    char* str_val;
    int int_val;
} attribute_value_t;

/* A block that contains a single primitive value, as well as the type 
belonging to that value */
typedef struct attribute {
    attribute_value_t value;
    attribute_type attribute_type;
    char* name;
} attribute_t;

  
