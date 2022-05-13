#ifndef CLI_CTX_H
#define CLI_CTX_H

#include "cmdlist.h"
#include "cmd.h"

//Forward Declaration
typedef struct lookup_entry lookup_t;
typedef struct command_list command_list_t;

/*
 * CLI context struct.  Contains the following fields:
 *  - command_history: list of previous commands
 *  - lookup: hashtable of action entries 
 */
typedef struct cli_ctx {
    command_list_t *command_history;
    lookup_t **table;
    
} cli_ctx_t;


/*
 * Crates a new CLI context struct
 *
 * Parameters:
 * - None
 *
 * Returns:
 * - The created CLI context struct upon SUCCESS
 * - NULL upon FAILURE
 */
cli_ctx_t *cli_ctx_new();

/*
 * Frees the given cli_ctx_t struct and associated resources
 *
 * Parameters:
 *   - cli_ctx: cli context struct to be freed
 *
 * Always returns 0
 */
int free_cli_ctx(cli_ctx_t *cli_ctx);




#endif
