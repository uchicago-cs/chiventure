#include <stdio.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"

const char *banner = "THIS IS AN EXAMPLE PROGRAM";

int main(int argc, char **argv)
{
    /*
    struct winsize w;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
    int ncols = w.ws_col, nrows = w.ws_row;
    if (ncols < MIN_COLS || nrows < MIN_ROWS) {
        fprintf(stderr, "Chiventure prefers to run in terminals of at least %d columns and %d rows. Please resize your terminal!\n", MIN_COLS, MIN_ROWS);
        exit(1);
    }*/

    chiventure_ctx_t *ctx = chiventure_ctx_new("../src/action_management/examples/test_game.wdl");

    /* Add calls to component-specific initializations here */

    start_ui(ctx, banner);

    game_free(ctx->game);
    return 0;
}