/* 
 * Functions and structs to be used in AST_block_t implementation
 */

#ifndef INCLUDE_AST_BLOCK_H
#define INCLUDE_AST_BLOCK_H

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "action_block.h"
#include "branch_block.h"
#include "conditional_block.h"
#include "control_block.h"

/* An enumeration type for an AST block */
typedef enum block_type {
    CONTROL, 
    BRANCH, 
    ACTION, 
    CONDITIONAL
} block_type_t;

/* Struct to represent the type of a block */
typedef union block {
    control_block_t *control_block;
    branch_block_t *branch_block;
    action_block_t *action_block;
    conditional_block_t *conditional_block;
} block_t;

/* Struct to contain a block, as well as its type */
typedef struct AST_block {
    block_t *block;
    block_type_t block_type;
    struct AST_block *next;
} AST_block_t;

/* 
 * Allocates an AST block in the heap. 
 * 
 * Parameters: 
 * - block: pointer to either a control, branch, action or conditional block 
 * - enum representing the type of block
 * 
 * Returns: 
 * - An AST block. 
 */
AST_block_t* AST_block_new(block_t *block, block_type_t block_type);

/* 
 * Initializes an AST block. 
 * 
 * Parameters: 
 * - AST block. Must point to already allocated memory. 
 * - block: pointer to either a control, branch, action or conditional block 
 * - enum representing the type of block
 * 
 * Returns: 
 * - SUCCESS if success, FAILURE if error occurs
 */
int AST_block_init(AST_block_t *ast, block_t *block, block_type_t block_type);

/* AST_free: Free an individual AST_block_t (NOT the entire list)
 *
 * Input:
 *      - ast: The AST_block_t to free
 * 
 * Returns:
 *      - Always returns SUCCESS
 */
int AST_free(AST_block_t* ast);

/* 
 * Frees an all of the AST blocks found in the sequence. 
 * 
 * Parameters: 
 * - AST block. Must point to an AST block allocated with AST_block_new. 
 * 
 * Returns: 
 * - Always returns 0. 
 */
int AST_block_free(AST_block_t *ast);

/* list_how_many_AST_block: Function that checks how many AST_block_t there are
 *                          in a list
 *
 * Input:
 *      - head: The AST_block_t to check
 * 
 * Return: Int value of how many items are found in linked list
 */
int list_how_many_AST_block(AST_block_t* head);

/*
 * Appends the add to the end of the list
 * Input:
 *      - head: The first AST_block_t 
 *      - add : The AST_block_t that is trying to be added in linked list
 * 
 * Returns: SUCCESS if successfully added, FAILURE otherwise
 *
 * Note: Adding the same block twice can cause errors
 */
int append_list_AST_block(AST_block_t*head, AST_block_t* add);

/*
 * Prepends the add to the start of the list
 * Input:
 *      - head: The first AST_block_t
 *      - add : The AST_block_t that is trying to be added in linked list
 *
 * Returns: SUCCESS if successfully added, FAILURE otherwise
 *
 * Note: Adding the same block twice can cause errors
 */
int prepend_list_AST_block(AST_block_t* head, AST_block_t* add);

/* list_remove_AST_block: Deletes a certain block_type from linked list
 *
 * Input:
 *      - head: The AST_block containing linked list
 *      - del: The specific AST_block that wants to be deleted from list
 * 
 * Return: SUCCESS 
 */
int list_remove_AST_block(AST_block_t* head, AST_block_t* del);
/* Executes a given AST block (the essential element
 * of a custom action)
 * 
 * Parameters: 
 * - block: A pointer to the AST block to be executed
 * 
 * Returns:
 * - Integer value of SUCCESS or FAILURE
 */
int run_ast_block(AST_block_t *block);

#endif /* INCLUDE_AST_BLOCK_H */
