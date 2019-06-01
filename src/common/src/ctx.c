#include <stdlib.h>
#include "ctx.h"
#include "game.h"
#include "ui_ctx.h"


/* See ctx.h */
chiventure_ctx_t* chiventure_ctx_new()
{
    chiventure_ctx_t *ctx;
    int rc;

    ctx = malloc(sizeof(chiventure_ctx_t));

    if(ctx == NULL)
    {
        return NULL;
    }

    rc = chiventure_ctx_init(ctx);
    if(rc != SUCCESS)
    {
        return NULL;
    }

    return ctx;
}

/* See ctx.h */
int chiventure_ctx_init(chiventure_ctx_t *ctx)
{
    assert(ctx != NULL);
    char *desc = "Welcome to Chiventure";

    game_t *game = game_new(desc);

    ui_ctx_t *ui_ctx = ui_ctx_new(game);

    ctx->game = game;
    ctx->ui_ctx = ui_ctx;

    /* Add calls to component-specific initialization here */

    return SUCCESS;
}

/* See ctx.h */
int chiventure_ctx_free(chiventure_ctx_t *ctx)
{
    assert(ctx != NULL);

    /* Add calls to component-specific freeing functions here */

    free(ctx);

    return SUCCESS;
}
