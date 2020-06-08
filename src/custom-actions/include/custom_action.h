/* 
 * Functions and structs to be used in custom_action_t implementation
 */

#ifndef INCLUDE_CUSTOM_ACTION_H_
#define INCLUDE_CUSTOM_ACTION_H_

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "ast_block.h"

/* Forward declaration */
typedef struct AST_block AST_block_t;

/* Struct to contain a custom action, as well as information about the type 
 * of custom action and a pointer to the first AST block in the custom action sequence. 
 * If any information field does not apply to a given custom action, the field should read 
 * "None". 
 */
typedef struct custom_action
{
    char *action_name;
    char *context;
    char *item;
    char *type;
    AST_block_t *head;
    UT_hash_handle hh;
} custom_action_t;

/*
 * Allocates a custom action in the heap. 
 *
 * Parameters:
 * - string of characters that hold the name of the custom action
 * - string of characters that hold the context for the custom action
 * - string of characters that hold the name of the item involved
 * - string of characters that hold the type of the custom action
 * - AST block containing the current block for the custom action sequence
 *
 * Returns:
 * - A custom action. 
 */
custom_action_t *custom_action_new(char *action_name, char *context, char *item,
                                   char *type, AST_block_t *head);

/*
 * Initializes a custom action. 
 *
 * Parameters:
 * - a custom action, must point to already allocated memory
 * - string of characters that hold the name of the custom action
 * - string of characters that hold the context for the custom action
 * - string of characters that hold the name of the item involved
 * - string of characters that hold the type of the custom action
 * - AST block containing the current block for the custom action sequence 
 *
 * Returns:
 * - an integer, SUCCESS if success, FAILURE if error occurs
 */
int custom_action_init(custom_action_t *action, char *action_name, char *context,
                       char *item, char *type, AST_block_t *head);

/*
 * Frees a custom action. 
 *
 * Parameters:
 * - a custom action, must point to a custom action allocated with custom_action_new
 *
 * Returns:
 * - an integer, always returns 0
 */
int custom_action_free(custom_action_t *action);

#endif /* INCLUDE_CUSTOM_ACTION_H_ */
