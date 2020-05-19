/* 
 * Structs to be used in custom-actions implementation
 */

#ifndef INCLUDE_STRUCT_H_
#define INCLUDE_STRUCT_H_

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"

/* An enumeration type for an AST block */
typedef enum {
    CONTROL, 
    BRANCH, 
    ACTION, 
    CONDITIONAL
} block_type;

/* An enumeration type for a control block */
typedef enum {
    IF-ELSE;
    WHILE-ENDWHILE;
    FOR-ENDFOR;
} control_type;

/* An enumeration type for a conditional block */
typedef enum {
    EQ;
    LT-GT;
    LTE-GTE;
    IN;
} conditional_type;

/* An enumeration type for an action block */
typedef enum {
    SET;
    SAY;
    MOVE;
    ADD-SUB-MULT-DIV;
    GEN;
    EXEC;
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
    AST_block* next;
} action_block_t;

/* Struct to contain a control block, which introduces an action */
typedef struct control_block {
    enum control_type control_type;
    AST_block* next;
} control_block_t;

/* A block that holds pointers to both a control and a conditional block */
typedef struct branch_block {
    int num_conditionals;
    conditional_block_t** conditionals;
    enum conditional_type conditional_type;
    int num_controls;
    control_block_t** controls;
} branch_block_t;

/* 
 * Allocates an AST block in the heap. 
 * 
 * Parameters: 
 * - block: either a control, branch, action or conditional block 
 * - enum representing the type of block
 * 
 * Returns: 
 * - A block. 
 */
AST_block_t* AST_block_new(block_t block, enum block_type block_type);

/* 
 * Initializes an AST block. 
 * 
 * Parameters: 
 * - AST block. Must point to already allocated memory. 
 * - block, block_type: parameters that define the block
 * 
 * Returns: 
 * - SUCCESS if success, FAILURE if error occurs
 */
int AST_block_init(AST_block_t *ast, block_t block, enum block_type block_type);

/* 
 * Frees an AST block. 
 * 
 * Parameters: 
 * - AST block. Must point to an AST block allocated with AST_block_new. 
 * 
 * Returns: 
 * - Always returns 0. 
 */
int AST_block_free(AST_block_t *ast);

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
control_block_t* control_block_new(enum control_type control_type, AST_block *next);

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
AST_block *next);

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

/* 
 * Allocates a branch block in the heap. 
 * 
 * Parameters: 
 * - integer containing the number of conditional blocks
 * - pointer to a list of conditional blocks
 * - integer for the number of control blocks
 * - pointer to a list of control blocks 
 * - enum representing the conditional type 
 * 
 * Returns: 
 * - A branch block. 
 */  
branch_block_t* branch_block_new(int num_conditionals, conditional_block_t** 
conditionals, enum conditional_type conditional_type, int num_controls, 
control_block_t** controls);

/* 
 * Initializes a branch block. 
 * 
 * Parameters: 
 * - branch block. Must point to already allocated memory.  
 * - integer containing the number of conditional blocks
 * - pointer to a list of conditional blocks
 * - integer for the number of control blocks
 * - pointer to a list of control blocks 
 * - enum representing the conditional type   
 * 
 * Returns: 
 * - SUCCESS if success, FAILURE if error occurs
 */  
int branch_block_init(branch_block_t *branch, int num_conditionals, conditional_block_t**
conditionals, enum conditional_type conditional_type, int num_controls,
control_block_t** controls);

/* 
 * Frees a branch block. 
 * 
 * Parameters: 
 * - branch block. Must point to a branch block allocated with branch_block_new. 
 * 
 * Returns: 
 * - Always returns 0. 
 */  
int branch_block_free(branch_block_t *branch);

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
attribute_t** args, AST_block *next);

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
attribute_t** args, AST_block *next);

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

/* 
 * Allocates a conditional block in the heap. 
 * 
 * Parameters: 
 * - pointer to a "left" attribute
 * - pointer to a "right" attribute 
 * - enum representing the conditional type 
 * 
 * Returns: 
 * - A conditional block. 
 */
conditional_block_t* conditional_block_new(enum conditional_type conditional_type, 
attribute_t* left, attribute_t* right);

/* 
 * Initializes a conditional block. 
 * 
 * Parameters: 
 * - conditional block. Must point to already allocated memory.  
 * - pointer to a "left" attribute 
 * - pointer to a "right" attribute  
 * - enum representing the conditional type    
 * 
 * Returns: 
 * - SUCCESS if success, FAILURE if error occurs
 */
int conditional_block_init(conditional_block_t *conditional, enum conditional_type 
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

/* 
 * Allocates an attribute in the heap. 
 * 
 * Parameters: 
 * - an attribute value 
 * - a string with the attribute name 
 * - enum representing the attribute type 
 * 
 * Returns: 
 * - An attribute. 
 */
attribute_t* attribute_new(attribute_value_t value, enum attribute_type 
attribute_type, char *name);

/* 
 * Initializes attribute. 
 * 
 * Parameters: 
 * - attribute. Must point to already allocated memory.  
 * - an attribute value 
 * - a string with the attribute name  
 * - enum representing the attribute type    
 * 
 * Returns: 
 * - SUCCESS if success, FAILURE if error occurs
 */
int attribute_init(attribute_t *attribute, attribute_value_t value, enum                  
attribute_type attribute_type, char *name);

#endif /* INCLUDE_STRUCT_H_ */
