#ifndef _CLI_INCLUDE_CMD_H
#define _CLI_INCLUDE_CMD_H
#include "parser.h"
#include "operations.h"

/*
* DISCLAIMER; THIS CODE IS BASED ON THE LAB 6 ADRBOOK SHELL
* FROM THE CMSC 15200 (WIN 2019) COURSE TOUGHT BY ADAM SHAW (University of Chicago)
*/

/* ======================================= */
/* === command datatype and operations === */
/* ======================================= */

/* Operation data type */
typedef char *operation(char *tokens[TOKEN_LIST_SIZE]);

/* Command data type */
typedef struct
{   
    char **tokens;    //should be of TOKEN_LIST_SIZE
    operation *functionofcommand;
} cmd;


/* === command constructors === */

/* 
 * Makes a new heap-allocated command with the operation set to NULL 
 */
cmd *cmd_new(char *tokens[TOKEN_LIST_SIZE]);


/* === command free === */

/* 
 * Frees command struct and its associated tokens, if there is one
 *
 * NOTE: DOESN'T DELETE OPERATIONS. They should not be deleted (and I am pretty)
 *  sure they can't be.
 */
void cmd_free(cmd *c);


/* === command display (for debugging, logging) === */

/* 
 * Returns 1st token as a string constant for command name
 */
char *cmd_name_tos(cmd *c);


/* 
 * Print a command 
 * note: for debugging only 
 */
void cmd_show(cmd *c);


/* === command parsing === */

/*
 * Builds a cmd (as defined above) from a string
 * returns NULL if the parse fails
 * Almost unneeded, but will stay so that AND is a working command.
 */
cmd *cmd_from_string(char *s);


/*
 * Takes tokens (parsed command) and creates a command using them.
 * For the purposes of this, we will store the preposition
 * in the command, not the name.
 * Input is a list of tokens, output is a pointer to a new command.
 * If the command is not valid, (the first word), then it outputs a NULL pointer.
 * otherwise, it ignores bad prepositions, and keeps all other bits.
 * Also, if malloc fails for a string
 */
cmd *cmd_from_tokens(char **ts);


/* 
 * Executes the given command
 * note: address_book is of type bst** so it can be modified in READ
 */
void do_cmd(cmd *c,int *quit);

#endif /* _CLI_INCLUDE_CMD_H */
