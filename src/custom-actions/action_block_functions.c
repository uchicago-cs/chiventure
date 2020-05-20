/* 
 * Basic functions for action blocks to be used in custom-actions implementation. 
 *
 * Please see "action_block_functions.h" for function documentation.
 */

#include <stdlib.h>
#include <stdio.h>
#include "custom-actions.struct.h"
#include "game-state/item.h"
#include "custom-actions/action_block_functions.h"

/* See action_block_functions.h */
action_block_t* action_block_new(enum action_type action_type, int num_args, 
attribute_t** args, AST_block_t *next)
{
    action_block_t *action;
    int new_action;

    action = malloc(sizeof(action_block_t));

    if (action == NULL)
    {
        error("Could not allocate memory");
        return NULL;
    }

    new_action = action_block_init(action, action_type, num_args, args, next);
    if (new_action != SUCCESS) 
    {
        error("Could not initialize action_block_t");
        return NULL;    
    }

    return action
}

/* See action_block_functions.h */
int action_block_init(action_block_t *action, enum action_type action_type, 
int num_args, attribute_t** args, AST_block_t *next)
{
    assert(action != NULL);
    assert(action_type != NULL);
    assert(num_args != NULL);
    assert(args != NULL);
    assert(next != NULL);

    action->action_type = action_type;
    action->num_args = num_args;
    action->args = args;
    action->next = next;

    return SUCCESS;
}

/* See action_block_functions.h */
int action_block_free(action_block_t *action)
{
    assert(action != NULL);

    free(action);

    return SUCCESS;
}
