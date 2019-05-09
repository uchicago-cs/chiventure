#ifndef _CMD_H
#define _CMD_H
#include "parser.h"
#include "operations.h"
/*
* DISCLAIMER; THIS CODE IS BASED ON THE LAB 6 ADRBOOK SHELL
* FROM THE CMSC 15200 (WIN 2019) COURSE TOUGHT BY ADAM SHAW (University of Chicago)
*/

/* ======================================= */
/* === command datatype and operations === */
/* ======================================= */

// Supported command tags
enum cmd_name {
  QUIT, HELP, HIST, LOOK, TAKE, GIVE
};

// Supported prepositions
enum preposition_name{
  NONE, WITH, TO, IN
};

// Operation data type
typedef char * operation(char * tokens[TOKEN_LIST_SIZE]);

// Command data type
typedef struct {
  char ** tokens; //should be of TOKEN_LIST_SIZE
  operation * functionofcommand;
} cmd;



/* === command constructors === */

/* cmd_new: make a new heap-allocated command with the operation set to NULL */
cmd *cmd_new(char * tokens[TOKEN_LIST_SIZE]);

/* === command free === */

/* cmd_free: free command struct and its associated tokens, if there is one */
/*
NOTE: DOESN'T DELETE OPERATIONS. They should not be deleted (and I am pretty)
sure they can't be.
*/
void cmd_free(cmd *c);

/* === command display (for debugging, logging) === */

/* cmd_name_tos: return 1st token as a string constant for command name */
/* note: for debugging only; not currently used in shell */
/* Above is not true, will now be used for hash table later*/
char *cmd_name_tos(cmd *c);

/* cmd_show: print command */
/* note: for debugging only */
void cmd_show(cmd *c);

/* === command parsing === */

/* cmd_from_string: build a cmd (as defined above) from a string
 * return NULL if the parse fails
 * Almost unneeded, but will stay so that AND is a working command.
 */
cmd *cmd_from_string(char *s);

/*
 * Takes tokens and creates a command using them.
 * Input is a list of tokens, output is a pointer to a new command.
 *
 */
cmd *cmd_from_tokens(char **ts);

/* do_cmd: execute the given command
 * note: address_book is of type bst** so it can be modified in READ
 */
void do_cmd(cmd *c,int *quit);
#endif /* _CMD_H */
