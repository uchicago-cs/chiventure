#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include <assert.h>

#include "cli/cli_ctx.h"

// see cli_ctx.h
cli_ctx_t *cli_ctx_new()
{
    cli_ctx_t *cli_ctx = (cli_ctx_t*)malloc(sizeof(cli_ctx_t));

    lookup_t **table = lookup_t_new();

    cli_ctx->command_history = NULL;
    cli_ctx->table = table;

    return cli_ctx;
}


int free_cli_ctx(cli_ctx_t *cli_ctx)
{
    if(cli_ctx == NULL || cli_ctx->command_history == NULL)
    {
        return SUCCESS;
    }
    free(cli_ctx);
    return SUCCESS;
}


