#include <stdlib.h>

#include "common/ctx.h"
#include "cli/cmd.h"


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
        ctx->game = game_new("No game has been loaded! Use the LOAD_WDL command to load a game.");
    }

    lookup_t **table = lookup_t_new();
    
    
    stats_global_t *gs1 = stats_global_new("Health", 1000);
    stats_global_t *gs2 = stats_global_new("XP", 10000);
    stats_global_t *gs3 = stats_global_new("Stamina", 1000);
    add_stat_to_game(game, gs1);
    add_stat_to_game(game, gs2);
    add_stat_to_game(game, gs3);

    effects_global_t *eg1, *eg2;
    eg1 = effects_global_new("POISONED");
    eg2 = effects_global_new("STUNNED");
    add_effect_to_game(game, eg1);
    add_effect_to_game(game, eg2);

    player_t *player1 = player_new("player1", 100);
    add_player_to_game(ctx->game, player1);
    ctx->game->curr_player = player1;

    ctx->table = table;

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
