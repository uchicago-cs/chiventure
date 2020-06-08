#ifndef INCLUDE_INTERFACE_H_
#define INCLUDE_INTERFACE_H_

#include <stdlib.h>
#include <stdio.h>
#include "custom_action.h"
#include "ast_block.h"
#include "action_block.h"
#include "branch_block.h"
#include "conditional_block.h"
#include "control_block.h"
#include "game-state/game.h"
#include "common/uthash.h"
#include "custom-actions-cond.h"
#include "custom-actions-common.h"

/* 
 * A custom action struct. Holds the contexts for each action
 * (action, context, item, and type) along with a pointer to the
 * first block (AST_block_t) in the action sequence.
 */

/* 
 * Given a custom action and its corresponding arguments, 
 * attempt to execute the given action.
 * 
 * Parameters: 
 * - action: A pointer to the custom action to be executed (most likely
 *   acquired from search_for_custom_action)
 * - args: An array of strings of the arguments passed to the action
 *   (i.e. the words succeeding the action written in the command line)
 * - num_args: The number of arguments being passed in
 * 
 * Returns:
 * - SUCCESS on successful execution
 * - FAILURE if any one of the blocks fails to execute
 */
int do_custom_action(custom_action_t *action);

#endif
