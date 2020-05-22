/* 
 * Basic functions and structs for action blocks to be used 
 * in custom-actions implementation. 
 *
 * Please see "action_block.h" for function documentation.
 */

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "../include/action_block.h"

/* See action_block.h */
typedef struct action_block {
    enum action_type action_type;
    int num_args;
    attribute_t** args;
    AST_block_t* next;
} action_block_t;

/* See action_block.h */
action_block_t* action_block_new(enum action_type action_type, int num_args, 
attribute_t** args, AST_block_t *next)
{
    action_block_t *action;
    int new_action;

    action = malloc(sizeof(action_block_t));

    if (action == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory\n");
        return NULL;
    }

    new_action = action_block_init(action, action_type, num_args, args, next);
    if (new_action != SUCCESS) 
    {
        fprintf(stderr, "Error: Could not initialize action_block_t\n");
        return NULL;    
    }

    return action;
}

/* See action_block.h */
int action_block_init(action_block_t *action, enum action_type action_type, 
int num_args, attribute_t** args, AST_block_t *next)
{
    assert(action != NULL);
//    assert(action_type != NULL//);
//    assert(num_args != NULL);
    assert(args != NULL);
    assert(next != NULL);

    action->action_type = action_type;
    action->num_args = num_args;
    action->args = args;
    action->next = next;

    return SUCCESS;
}

/* See action_block.h */
int action_block_free(action_block_t *action)
{
    assert(action != NULL);

    free(action);

    return SUCCESS;
}
