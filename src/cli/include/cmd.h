#ifndef _CLI_INCLUDE_CMD_H
#define _CLI_INCLUDE_CMD_H
#include "parser.h"
#include "game.h"
#include "uthash.h"
#include "action_structs.h"
#include "actionmanagement.h"
#include <ncurses.h>
#include "ui_ctx.h"

typedef struct chiventure_ctx chiventure_ctx_t;
/* Operation data type */
typedef char *operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);

// Lookup entry for hashtable, using uthash.
typedef struct lookup_entry
{
    char *name; // key
    operation *operation_type;
    action_type_t *action;
    UT_hash_handle hh;
} lookup_t;

/* Command data type */
typedef struct
{
    char **tokens;    //should be of TOKEN_LIST_SIZE
    operation *func_of_cmd;
} cmd;

#include "ctx.h"
#include "operations.h"
#include "print_functions.h"

/* Iteratively adds each action into the table, from a
 * list of functions provided by action management
 * 
 * Parameters: 
 * - pointers to a lookup table
 * 
 * Returns:
 * - nothing
 */
void add_action_entries(lookup_t **table);


/* Adds entry into hashtable
 *
 *
 * Parameters:
 * - command name, operation of added entry, lookup table
 *
 * Returns:
 * - nothing
 */
void add_entry(char *command_name, operation *associated_operation, lookup_t **table);


/* Finds entry in hashtable with the given name.
 *
 *
 * Parameters:
 * - command name, pointer to table
 *
 * Returns:
 * - a pointer to the entire entry
 */
lookup_t *find_entry(char *command_name, lookup_t **table);


/* Finds operation in hashtable corresponding to the given name.
 *
 *
 * Parameters:
 * - command name, pointer to table
 *
 * Returns:
 * - a pointer to the corresponding operation
 */
operation *find_operation(char *command_name, lookup_t **table);


/* Finds action in hashtable corresponding to the given name.
 *
 *
 * Parameters:
 * - command name, pointer to table
 *
 * Returns:
 * - a pointer to the corresponding action
 * - NULL if the command is not an action.
 */
action_type_t *find_action(char *command_name, lookup_t **table);


/* Deletes entry from hashtable. Doesn't get rid of synonyms.
 *
 *
 * Parameters:
 * - command name of entry, pointer to table
 *
 * Returns:
 * - nothing
 */
void delete_entry(char *command_name, lookup_t **table);


/* Clears out the entire table, and frees it too!
 *
 *
 * Parameters:
 * -pointer to table
 *
 * Returns:
 * - nothing
 */
void delete_entries(lookup_t **table);


/* Creates a new lookup Hashtable
 *
 * Parameters:
 * - None
 * 
 * Returns:
 * - a pointer to a new hashtable, NULL if failure
 */
lookup_t **lookup_t_new();


/* Puts stuff into table, for testing purposes
 * You can see what is in there in the .c file.
 * Returns a pointer to the new table.
 */
int lookup_t_init();


/* Frees resources associated with the lookup hashtable struct
 *
 * Parameters:
 * - pointer to a lookup hashtable
 *
 * Returns:
 * - nothing
 */
void lookup_t_free();


/* Creates a new cmd struct
 *
 * Parameters:
 * - an array of characters, with a defined lengh
 *
 * Returns:
 * - a pointer to a new cmd struct, NULL if failure
 */
cmd *cmd_new(char *tokens[TOKEN_LIST_SIZE]);

/* Initializes the values in a cmd struct
 *
 * Parameters:
 * - an array of string tokens
 * - a pointer to a cmd struct
 * 
 * Returns:
 * - an int corresponding to SUCCESS or FAILURE
 */
int cmd_init(cmd *c, char *tokens[TOKEN_LIST_SIZE]);


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
void cmd_show(cmd *c, chiventure_ctx_t *ctx);


/* === command parsing === */

/*
 * Builds a cmd (as defined above) from a string
 * Almost unneeded, but will stay so that AND is a working command.
 *
 * Parameters:
 * - array of characters, pointer to chiventure context struct
 *
 * Returns:
 * - pointer to command struct, NULL if parse fails
 */
cmd *cmd_from_string(char *s, chiventure_ctx_t *ctx);


/*
 * creates a command from parsed string.
 *
 * Parameters:
 * - Array of tokens, pointer to table
 *
 * Returns:
 * - pointer to a cmd struct, NULL if there is an error
 */
cmd *cmd_from_tokens(char **ts, lookup_t **table);


/*
 * Executes the given command
 *
 * Parameters:
 * - pointer to a cmd struct
 * - pointer to chiventure context struct
 *
 * Returns:
 * - nothing -> output handled elsewhere
 */
void do_cmd(cmd *c,int *quit, chiventure_ctx_t *ctx);


#endif /* _CLI_INCLUDE_CMD_H */
