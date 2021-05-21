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
    struct AST_block *prev;
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

/* 
 * Frees an AST block, as well as all of the AST blocks in the sequence. 
 * 
 * Parameters: 
 * - AST block. Must point to an AST block allocated with AST_block_new. 
 * 
 * Returns: 
 * - Always returns 0. 
 */
int AST_block_free(AST_block_t *ast);

/* list_contains_AST_block: Function to check if a certain block_type exists
 *                          in a linked list of AST_blocks
 *
 * Inputs:
 *      - head: the AST_block to search (potentially having other AST_blocks linked)
 *      - block_type: The specific block_type that we are wanting to search for
 * 
 * Returns: false for does not contain, true for contains
 */
bool list_contains_AST_block(AST_block_t* head, block_type_t block_type);

/* list_add_AST_block: Function to add in an AST_block in a SPECIFIC place in
 *                     the linked list
 *
 * Input:
 *      - head: The first AST_block_t 
 *      - add : The AST_block_t that is trying to be added in linked list
 *      - num_to_place: The number specifying where to input the new AST_block_t
 *                      in the current list. Note: 1 denotes adding it as the FIRST
 *                      AST_block, 2 as the second, and so forth
 * 
 * Returns: SUCCESS if successfully added, FAILURE otherwise
 */
int list_add_AST_block(AST_block_t* head, AST_block_t* add, int num_to_place);

#endif /* INCLUDE_AST_BLOCK_H */
