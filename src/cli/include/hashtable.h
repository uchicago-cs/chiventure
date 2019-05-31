#ifndef _CLI_INCLUDE_HASHTABLE_H
#define _CLI_INCLUDE_HASHTABLE_H
#include "uthash.h"
#include "action_structs.h"
#include "actionmanagement.h"
#include "ctx.h"
#include "operations.h"

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
// typedef struct
// {
//     char **tokens;    //should be of TOKEN_LIST_SIZE
//     operation *func_of_cmd;
// } cmd;

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


#endif /* _CLI_INCLUDE_HASHTABLE_H */
