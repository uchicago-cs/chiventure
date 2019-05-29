#ifndef _CLI_INCLUDE_CMD_H
#define _CLI_INCLUDE_CMD_H
#include "parser.h"

#include "game.h"
#include "uthash.h"
#include "action_structs.h"
#include "actionmanagement.h"
//#include "../../game-state/include/game.h"

/* Operation data type */
typedef struct lookup_entry lookup_t;
typedef char *operation(char *tokens[TOKEN_LIST_SIZE], game_t *game, lookup_t **table);

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
#include "operations.h"

/* Iteratively adds each action, and its synonyms into the table. Commented out
until action_t is ready */

void add_action_entries(lookup_t **table);

/* Adds entry into hashtable
 *
 *
 * Parameters:
 * - command name and operation of added entry,
 *
 * Returns:
 * - nothing
 */
void add_entry(char *command_name, operation *associated_operation, lookup_t **table);

/* Finds entry in hashtable with the given name.
 *
 *
 * Parameters:
 * - command name and pointer to table
 *
 * Returns:
 * - a pointer to the entire entry
 */
lookup_t *find_entry(char *command_name, lookup_t **table);


/* Finds operation in hashtable corresponding to the given name.
 *
 *
 * Parameters:
 * - command name and pointer to table
 *
 * Returns:
 * - a pointer to the corresponding operation
 */
operation *find_operation(char *command_name, lookup_t **table);
/* Finds action in hashtable corresponding to the given name.
 *
 *
 * Parameters:
 * - command name and pointer to table
 *
 * Returns:
 * - a pointer to the corresponding action
 * - NULL if the command is not an action.
 */
action_type_t *find_action(char *command_name, lookup_t **table);
/*  Commented out until action_t is ready.*/


/* Deletes entry from hashtable. Doesn't get rid of synonyms.
 *
 *
 * Parameters:
 * - command name of entry and pointer to table
 *
 * Returns:
 * - nothing
 */
void delete_entry(char *command_name, lookup_t **table);

/* Clears out the entire table, and frees it too!
 *
 *
 * Parameters:
 * - command name of entry and pointer to table
 *
 * Returns:
 * - nothing
 */
void delete_entries(lookup_t **table);


/* Puts stuff into table, for testing purposes
 * You can see what is in there in the .c file.
 * Returns a pointer to the new table.
 */
lookup_t **initialize_lookup();


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
cmd *cmd_from_string(char *s, lookup_t **table);


/*
 * creates a command from parsed string.
 *
 * Parameters:
 * - Array of tokens
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
 * - pointer to game to be altered
 *
 * Returns:
 * - nothing -> output handled elsewhere
 */
void do_cmd(cmd *c,int *quit, game_t *game, lookup_t **table);

#endif /* _CLI_INCLUDE_CMD_H */
