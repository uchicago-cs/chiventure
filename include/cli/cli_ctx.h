#ifndef CLI_CTX_H
#define CLI_CTX_H

#include "cmdlist.h"
#include "cmd.h"


/*
 * CLI context struct.  Contains the following fields:
 *  - command_history: list of previous commands
 *  - lookup 
 */
typedef struct cli_ctx {
    command_list_t *command_history;
    lookup_t **table;
    
} cli_ctx_t;


/*
 * Crates a new CLI context struct
 *
 * Parameters:
 * - 
 *
 * Returns:
 * - The created CLI context struct upon SUCCESS
 * - NULL upon FAILURE
 */
cli_ctx_t *cli_ctx_new();


/*
 * Initializes the values of a CLI context struct.
 *
 *
 * Parameters
 * - cli_ctx_t : cli context struct to be initialized
 * 
 * Returns:
 * - SUCCESS if every field can be initialized
 * - FAILURE if there is a problem
 *
 */
int cli_ctx_init(cli_ctx_t *cli_ctx);

/*
 * Frees the given cli_ctx_t struct and associated resources
 *
 * Parameters:
 *   - cli_ctx: cli context struct to be freed
 *
 * Always returns 0
 */
int cli_ctx_free(cli_ctx_t *cli_ctx);




#endif
