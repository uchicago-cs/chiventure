#ifndef _CLI_INCLUDE_CMD_H
#define _CLI_INCLUDE_CMD_H
#include "parser.h"
#include "operations.h"

/* Operation data type */
typedef char *operation(char *tokens[TOKEN_LIST_SIZE]);

/* Command data type */
typedef struct
{   
    char **tokens;    //should be of TOKEN_LIST_SIZE
    operation *func_of_cmd;
} cmd;


/* Heap allocates a new cmd struct
 * 
 *
 * Parameters:
 * - an array of characters, with a defined lengh
 *
 * Returns:
 * - a pointer to a new cmd struct
 */
cmd *cmd_new(char *tokens[TOKEN_LIST_SIZE]);


/* Frees resources associated with the cmd struct
 *
 * Parameters:
 * - pointer to a cmd struct
 *
 * Returns:
 * - nothing
 */
void cmd_free(cmd *c);


/* === command debugging === */

/* Returns first token as command name (for debugging)
 *
 * Parameters:
 * - pointer to a cmd struct
 *
 * Returns:
 * - command name as a string
 */
char *cmd_name_tos(cmd *c);


/* Print the entire command (for debugging)
 *
 * Parameters:
 * - pointer to a cmd struct
 *
 * Returns:
 * - nothing - prints in stdout
 */
void cmd_show(cmd *c);


/* === command parsing === */

/*
 * Builds a cmd (as defined above) from a string
 * Almost unneeded, but will stay so that AND is a working command.
 *
 * Parameters:
 * - array of characters
 *
 * Returns:
 * - pointer to command struct, NULL if parse fails
 */
cmd *cmd_from_string(char *s);


/*
 * creates a command from parsed string.
 *
 * Parameters:
 * - Array of tokens 
 *
 * Returns:
 * - pointer to a cmd struct, NULL if there is an error
 */
cmd *cmd_from_tokens(char **ts);


/* 
 * Executes the given command
 * 
 * Parameters:
 * - pointer to a cmd struct
 *
 * Returns:
 * - nothing -> output handled elsewhere
 */
void do_cmd(cmd *c,int *quit);

#endif /* _CLI_INCLUDE_CMD_H */ 
