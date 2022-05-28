#ifndef _CLI_INCLUDE_CMD_H
#define _CLI_INCLUDE_CMD_H
#include "parser.h"
#include "common/uthash.h"
#include "action_management/action_structs.h"
#include "common/ctx.h"

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
void add_entry(char *command_name, operation *associated_operation, action_type_t *action, lookup_t **table);


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


/* Creates a new lookup Hashtable
 *
 * Parameters:
 * - None
 *
 * Returns:
 * - a pointer to a new hashtable, NULL if failure
 */
lookup_t **lookup_t_new();


/* Initializes the values in a lookup Hashtable struct
 * Populates the hashtable with all possible commands
 *
 * Parameters:
 * - none
 *
 * Returns:
 * - an int corresponding to SUCCESS or FAILURE
 */
int lookup_t_init(lookup_t **t);


/* Frees resources associated with the lookup hashtable struct
 *
 * Parameters:
 * - pointer to a lookup hashtable
 *
 * Returns:
 * - always returns SUCCESS
 */
int lookup_t_free(lookup_t **t);


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
 * - always returns SUCCESS
 */
int cmd_free(cmd *c);


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
 * Builds a cmd (as defined above) from a string, separates inputs
 * into tokens separated by "AND"
 * Almost unneeded, but will stay so that AND, ';' are working commands.
 *
 * Parameters:
 * - array of characters, pointer to chiventure context struct
 *
 * Returns:
 * - arrays of arrays of command structs, NULL if parse fails
 */
cmd **cmd_from_string(char *s, chiventure_ctx_t *ctx);


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


#define CLI_CMD_SUCCESS (0)
#define CLI_CMD_SUCCESS_NOOUTPUT (1)
#define CLI_CMD_SUCCESS_QUIT (2)
#define CLI_CMD_CALLBACK_ERROR (3)

/*
 * Callback function type for the CLI.
 *
 * Functions of this type can be passed to do_cmd,
 * which will call the function if the command is run
 * successfully.
 *
 * Parameters:
 *  - ctx: pointer to chiventure context struct
 *  - outstring: The string to be printed as a result of running this command
 *  - args: Additional arguments
 *
 * Returns:
 *  - CLI_CMD_SUCCESS: Success
 *  - CLI_CMD_CALLBACK_ERROR: Callback function was unable to print the string
 */
typedef int cli_callback(chiventure_ctx_t *ctx, char *outstring, void *args);

/*
 * Executes the given command
 *
 * Parameters:
 * - pointer to a cmd struct
 * - callback_func: Pointer to a callback function
 * - callback_args: Additional arguments to callback function
 * - ctx: pointer to chiventure context struct
 *
 * Returns:
 * - CLI_CMD_SUCCESS: Success, and the command produced some output
 * - CLI_CMD_SUCCESS_NOOUTPUT: Success, but the command did not produce any output
 * - CLI_CMD_SUCCESS_QUIT: Success, but the command requires that chiventure quit
 * - CLI_CMD_CALLBACK_ERROR: Callback function reported an error
 */
int do_cmd(cmd *c, cli_callback callback_func, void *callback_args, chiventure_ctx_t *ctx);


#endif /* _CLI_INCLUDE_CMD_H */