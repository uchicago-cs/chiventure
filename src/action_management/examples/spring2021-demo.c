#include <stdio.h>
#include "action_management/action_structs.h"
#include "action_management/actionamangement.h"
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "chiventure/src/custom-actions/include/interface.h"

const char *banner = "This is the 2021 Action-Management team demo";


int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    chiventure_ctx_t *ctx = chiventure_ctx_new(NULL);

    game_t *game = game_new("Welcome to Chiventure!");

    /* Free default game and replace it with ours */
    game_free(ctx->game);
    ctx->game = game;

    return ctx;
}
