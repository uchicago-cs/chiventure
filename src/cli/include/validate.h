#ifndef _CLI_INCLUDE_VALIDATE_H_
#define _CLI_INCLUDE_VALIDATE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parser.h"
#include "shell.h"
#include "cmd.h"
#include "item.h"
#include "room.h"
/*
 * THIS FILE INCLUDES A SET OF FUNCTIONS THAT VALIDATE A COMMAND
 */

/*
 * If the input action is valid (checks by calling validate_action), go through
 * the hashtable again to find the corresponding operation and creates a cmd struct
 *
 * Input:
 *  - ts: parsed command line input (an array of tokens)
 *  - table: hashtable that stores all supported actions
 *
 * Returns:
 *  - A cmd struct that contains the given tokens and a pointer to an operation
 *    function (function selected based on the first token)
 *
 *    If the action is invalid, assigns the cmd pointer
 *    to action_error_operation
 */
cmd *assign_action(char *ts[TOKEN_LIST_SIZE], lookup_t **table);


/*
 * Checks if a given action is supported by the game
 *
 * Input:
 *  - tokens: an array of parsed input
 *  - table: hashtable that stores all supported actions
 *
 * Returns:
 *  - FALSE if the action is not supported; TRUE if it is.
 */
bool validate_action(char *tokens[TOKEN_LIST_SIZE], lookup_t **table);


/*
 * Checks if a given object is in the current room
 *
 * Input:
 *  - c: cmd struct returned by assign_action
 *  - we also need a list of accessible items as input.
 *    This needs to be provided by game state
 *
 * Returns:
 *  - FALSE if the object is not accessible; TRUE if it is.
 *    Additionally, we may set the cmd pointer to an error function
 *    that returns a error message with respect to the type of error
 */
bool validate_object(char *tokens[TOKEN_LIST_SIZE], game_t * game);


/*
 * Checks if an input preposition is valid
 *
 * Input:
 *  - c: cmd struct returned by assign_action
 *  - we also need a list of valid actions as input.
 *    This needs to be provided by action management
 *
 * Returns:
 *  - FALSE if the preposition is invalid; TRUE if it is.
 */
bool validate_prep(cmd *c);


/*
 *  Checks if the specefied indirect object (2nd item) (e.g. NPC) is
 *  accessible
 *
 * Input:
 *  - c: cmd struct returned by assign_action
 *  - we also need a list of accessible items as input.
 *    This needs to be provided by game state
 * Returns:
 *  - FALSE if the item is not accessible; TRUE if it is.
 */
bool validate_ind_objects(char *tokens[TOKEN_LIST_SIZE], game_t * game);

/*
 * Checks that a specified filetype is a .dat file
 *
 * Parameters:
 * - A string of the filename
 *
 *
 * Returns:
 * - TRUE if proper filename, FALSE if not
 */
bool validate_filename(char *filename);


#endif /* _CLI_INCLUDE_VALIDATE_H_ */
