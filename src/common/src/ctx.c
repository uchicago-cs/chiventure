#include <stdlib.h>

#include "common/ctx.h"


/* See ctx.h */
chiventure_ctx_t* chiventure_ctx_new(game_t *game)
{
    chiventure_ctx_t *ctx;
    int rc;

    ctx = malloc(sizeof(chiventure_ctx_t));

    if (ctx == NULL)
    {
        return NULL;
    }

    rc = chiventure_ctx_init(ctx, game);
    if (rc != SUCCESS)
    {
        return NULL;
    }

    return ctx;
}

/* See ctx.h */
int chiventure_ctx_init(chiventure_ctx_t *ctx, game_t *game)
{
    assert(ctx != NULL);

    if (game)
    {
        ctx->game = game;
    }
    else
    {
        ctx->game = game_new("No game has been loaded! Use the LOAD command to load a game.");
    }

    if (ctx->game->mode == NULL)
    {
        load_normal_mode(ctx->game);
    }

    ctx->obj_store = NULL;
    ctx->cli_ctx = cli_ctx_new();

    return SUCCESS;
}

/* See ctx.h */
int chiventure_ctx_free(chiventure_ctx_t *ctx)
{
    assert(ctx != NULL);

    /* Add calls to component-specific freeing functions here */
    assert(free_cli_ctx(ctx->cli_ctx) == SUCCESS);
    free(ctx);

    return SUCCESS;
}
