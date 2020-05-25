/* 
 * Basic functions and structs for action blocks to be used 
 * in custom-actions implementation. 
 *
 * Please see "action_block.h" for function documentation.
 */

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "../include/ast_block.h"
#include "../include/action_block.h"

/* See action_block.h */
ast_block_t* action_block_new(action_type_t action_type, int num_args, 
attribute_t** args)
{
    ast_block_t *ast;
    action_block_t *action;
    int new_action;
    block_type_t block_type = ACTION;

    action = malloc(sizeof(action_block_t));
    ast = malloc(sizeof(ast_block_t));

    if (action == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory\n");
        return NULL;
    }

    new_action = action_block_init(action, action_type, num_args, args);
    if (new_action != SUCCESS) 
    {
        fprintf(stderr, "Error: Could not initialize action_block_t\n");
        return NULL;    
    }
    
    ast = ast_block_new(action, block_type);
    return ast;
}

/* See action_block.h */
int action_block_init(action_block_t *action, action_type_t action_type, 
int num_args, attribute_t** args)
{
    assert(action != NULL); 
    assert(num_args > 0);
    assert(args != NULL);

    action->action_type = action_type;
    action->num_args = num_args;
    action->args = args;

    return SUCCESS;
}

/* See action_block.h */
int action_block_free(action_block_t *action)
{
    assert(action != NULL);

    free(action);

    return SUCCESS;
}
