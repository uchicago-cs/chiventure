#include <stdio.h>
#include "common/sample_game.h"
#include "common/ctx.h"
#include "ui/ui.h"

const char* banner = "SKILLTREES PRESENTATION";

chiventure_ctx_t* create_example_ctx() {
    game_t* game = create_sample_game();

    chiventure_ctx_t* ctx = chiventure_ctx_new(game);

    return ctx;

}

int main(int argc, char **argv) {
    chiventure_ctx_t* ctx = create_example_ctx();

    start_ui(ctx, banner);

    game_free(
    return 0;
}
