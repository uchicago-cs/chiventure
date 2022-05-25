/*
 * Functions and structs to be used in action_block_t implementation
 */

#ifndef INCLUDE_ACTION_BLOCK_H
#define INCLUDE_ACTION_BLOCK_H

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "game-state/game.h"
#include "game-state/room.h"

/* Forward declaration */
typedef struct AST_block AST_block_t;

/* An enumeration type for an action block */
typedef enum action_type
{
    SET,
    ADDITION,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    GEN,

    // To be implemented:
    EXEC,
    SAY,
    TELEPORT,
} action_enum_t;

/* A struct that holds the possible parameters for an action */
typedef struct action_param
{
    attribute_t **args;
    room_t *room;
    game_t *game;
} action_param_t;

/* A block that holds an action, as well as corresponding attributes and actions */
typedef struct action_block
{
    action_enum_t action_type;
    int num_args;
    action_param_t *action_params;
} action_block_t;

/*
 * Allocates an action block in the heap.
 *
 * Parameters:
 * - enum representing the action type
 * - integer containing the number of arguments
 * - pointer to a list of action parameters
 *
 * Returns:
 * - An action block.
 */
action_block_t *action_block_new(action_enum_t action_type, int num_args,
                                 action_param_t *action_params;);

/*
 * Allocates an AST type action block in the heap, and allocates an action block
 * and type within the AST block.
 *
 * Parameters:
 * - enum representing the action type
 * - integer containing the number of arguments
 * - pointer to a list of action parameters
 *
 * Returns:
 * - An AST block.
 */
AST_block_t *AST_action_block_new(action_enum_t action_type, int num_args,
                                  action_param_t *action_params;);

/*
 * Initializes an action block.
 *
 * Parameters:
 * - action block. Must point to already allocated memory.
 * - enum representing the action type
 * - integer containing the number of arguments
 * - pointer to a struct of action parameters
 *
 * Returns:
 * - SUCCESS if success, FAILURE if error occurs
 */
int action_block_init(action_block_t *action, action_enum_t action_type, int num_args,
                      action_param_t *action_params;);

/*
 * Frees an action block.
 *
 * Parameters:
 * - action block. Must point to an action block allocated with action_block_new.
 *
 * Returns:
 * - Always returns 0.
 */
int action_block_free(action_block_t *action);

/*
 * Executes an action block
 *
 * Procedure:
 * - Checks action type
 * - Checks that correct number of arguments are present
 * - Calls effect-applying function associated with action type
 * - Success or failure based on success or failure of effect-applying function
 *
 * Parameters:
 * - action block
 *
 * Returns:
 * - SUCCESS if successful, FAILURE if not
 */
int exec_action_block(action_block_t *a);

#endif /* INCLUDE_ACTION_BLOCK_H */
