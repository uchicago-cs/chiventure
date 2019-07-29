#include <stdlib.h>
#include "ctx.h"
#include "game.h"
#include "ui_ctx.h"
#include "cmd.h"
#include "load_game.h"


/* See ctx.h */
chiventure_ctx_t* chiventure_ctx_new(char *filepath)
{
    chiventure_ctx_t *ctx;
    int rc;

    ctx = malloc(sizeof(chiventure_ctx_t));

    if (ctx == NULL) {
        return NULL;
    }

    rc = chiventure_ctx_init(ctx, filepath);
    if (rc != SUCCESS) {
        return NULL;
    }
    
    return ctx;
}

/* See ctx.h */
int chiventure_ctx_init(chiventure_ctx_t *ctx, char *filepath)
{
    assert(ctx != NULL);

    char *desc = "Welcome to Chiventure";
    game_t *game;

    if(filepath == NULL)
    {
        game = game_new(desc);
    }
    else
    {
        game = load_wdl("orb.yaml");
    }
    
    ui_ctx_t *ui_ctx = ui_ctx_new(game);

    lookup_t **table = lookup_t_new();

    ctx->game = game;
    ctx->ui_ctx = ui_ctx;
    ctx->table = table;

    return SUCCESS;
}

/* See ctx.h */
int chiventure_ctx_free(chiventure_ctx_t *ctx)
{
    assert(ctx != NULL);

    /* Add calls to component-specific freeing functions here */

    ui_ctx_free(ctx->ui_ctx);

    free(ctx);

    return SUCCESS;
}
