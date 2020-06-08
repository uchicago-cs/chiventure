#include "common/load_objects.h"

/* See load_objects.h for documentation */
game_t *load_objects(wdl_ctx_h *ctx)
{
    game_t *game;

    if(ctx->game != NULL)
    {
        game = ctx->game;
        return game;
    }

    //this section must be filled out more properly to allow for WDL
    //objects to be loaded
    game = game_new("Temporary description");

    return game;
}
