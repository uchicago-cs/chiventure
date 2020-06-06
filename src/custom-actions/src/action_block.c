/* 
 * Basic functions and structs for action blocks to be used 
 * in custom-actions implementation. 
 *
 * Please see "action_block.h" for function documentation.
 */

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "ast_block.h"
#include "action_block.h"

/* See action_block.h */
action_block_t* action_block_new(action_enum_t action_type, int num_args, 
                                 attribute_t** args)
{
    action_block_t *action;
    int new_action;
    block_type_t block_type = ACTION;

    action = malloc(sizeof(action_block_t));

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
    
    return action;
}

/* See action_block.h */
AST_block_t* AST_action_block_new(action_enum_t action_type, int num_args, 
                                  attribute_t** args)
{
    AST_block_t *ast;
    action_block_t *action;
    int new_action;
    block_type_t block_type = ACTION;
    int num_AST = 1;
    AST_block_t *next;
    
    next = malloc(sizeof(AST_block_t));
    action = malloc(sizeof(action_block_t));
    ast = malloc(sizeof(AST_block_t));

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
    
    block_t* block = malloc(sizeof(block));
    block->action_block = action;
    ast = AST_block_new(block, block_type, num_AST, &next);
    return ast;
}

/* See action_block.h */
int action_block_init(action_block_t *action, action_enum_t action_type, 
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
