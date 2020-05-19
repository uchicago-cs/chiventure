/* 
 * Basic functions for action blocks to be used in custom-actions implementation. 
 * 
 * Please see "action_block_functions.h" for function documentation. 
 */

#include <stdlib.h>
#include <stdio.h>
#include "custom-actions/struct.h"
#include "custom-actions/action_block_functions.h"
#include "game-state/item.h"

/* See action_block_functions.h */
action_block_t* action_block_new(enum action_type action_type, int num_args, 
attribute_t** args, AST_block *next)
{
    return NULL;
}

/* See action_block_functions.h */
int action_block_init(action_block_t *action, enum action_type action_type, int num_args, 
attribute_t** args, AST_block *next)
{
    return 0;
}

/* See action_block_functions.h */
int action_block_free(action_block_t *branch)
{
    return 0;
} 
