#include <stdlib.h>
#include "common/ctx.h"
#include "game-state/game.h"
#include "ui/ui_ctx.h"
#include "cli/cmd.h"
#include "wdl/load_game.h"


/* See ctx.h */
chiventure_ctx_t* chiventure_ctx_new(char *filepath)
{
    chiventure_ctx_t *ctx;
    int rc;

    ctx = malloc(sizeof(chiventure_ctx_t));

    if (ctx == NULL)
    {
        return NULL;
    }

    rc = chiventure_ctx_init(ctx, filepath);
    if (rc != SUCCESS)
    {
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
        game = load_wdl(filepath);
    }

    ui_ctx_t *ui_ctx = ui_ctx_new(game);
    lookup_t **table = lookup_t_new();

    player_t *player1 = player_new("player1", 100);
    add_player_to_game(game, player1);
    game->curr_player = player1;

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
