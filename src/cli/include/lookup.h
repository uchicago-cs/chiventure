#ifndef _CLI_INCLUDE_LOOKUP_H
#define _CLI_INCLUDE_LOOKUP_H
#include "../../common/include/uthash.h"
#include "cmd.h"
// Lookup entry for hashtable, using uthash.
typedef struct lookup_entry{
  char * name; // key
  operation * operation_type;
  // * action_t action_type;
  UT_hash_handle hh;
} lookup_t;

lookup_t * table;
//void add_action_entries(action_t * action_value);
/* Iteratively adds each action, and its synonyms into the table. Commented out
until action_t is ready */

void add_entry(char * command_name, operation * associated_operation);
/* Adds these in manually. */


lookup_t * find_entry(char * command_name);
/* The reason we implemented the table */
operation * find_operation(char * command_name);
/* Grabs the operation, using find entry*/
//action_t * find_action(char * command_name, lookup_t * table);
/* As above, but for the action. Commented out until action_t is ready.*/


void delete_entry(char * command_name);
/* Deletes entry with the above name. Doesn't get rid of synonyms. */

void delete_entries();
/* Clears out the entire table, and frees it too! */

void initialize_lookup();
/* Puts stuff into table, for testing purposes */

#endif /* _CLI_INCLUDE_CMD_H */
