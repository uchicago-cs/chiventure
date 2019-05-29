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
