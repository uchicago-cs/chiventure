#include <stdio.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "cli/operations.h"

const char* banner = "SKILLTREES PRESENTATION";

chiventure_ctx_t* create_example_ctx() {
    game_t *game = game_new("Welcome to the skilltrees team's presentation!");
    return ctx;
}

int main(int argc, char **argv) {
    chiventure_ctx_t* ctx = create_example_ctx();

    start_ui(ctx, banner);

    game_free(ctx->game);
    return 0;
}
