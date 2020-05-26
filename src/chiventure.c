#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "common/ctx.h"
#include "ui/ui.h"

const char *banner =
    "    ________________________________________________________________________________________\n"
    "  / \\                                                                                       \\\n"
    " |   |                                                                                      |\n"
    "  \\_ |     ██████╗██╗  ██╗██╗██╗   ██╗███████╗███╗   ██╗████████╗██╗   ██╗██████╗ ███████╗  |\n"
    "     |    ██╔════╝██║  ██║██║██║   ██║██╔════╝████╗  ██║╚══██╔══╝██║   ██║██╔══██╗██╔════╝  |\n"
    "     |    ██║     ███████║██║██║   ██║█████╗  ██╔██╗ ██║   ██║   ██║   ██║██████╔╝█████╗    |\n"
    "     |    ██║     ██╔══██║██║╚██╗ ██╔╝██╔══╝  ██║╚██╗██║   ██║   ██║   ██║██╔══██╗██╔══╝    |\n"
    "     |    ╚██████╗██║  ██║██║ ╚████╔╝ ███████╗██║ ╚████║   ██║   ╚██████╔╝██║  ██║███████╗  |\n"
    "     |     ╚═════╝╚═╝  ╚═╝╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═══╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚══════╝  |\n"
    "     |   ___________________________________________________________________________________|___\n"
    "     |  /                                                                                      /\n"
    "     \\_/______________________________________________________________________________________/\n";


int main(int argc, char **argv)
{
    struct winsize w;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
    int ncols = w.ws_col, nrows = w.ws_row;
    if (ncols < MIN_COLS || nrows < MIN_ROWS) {
        fprintf(stderr, "Chiventure prefers to run in terminals of at least %d columns and %d rows. Please resize your terminal!\n", MIN_COLS, MIN_ROWS);
        exit(1);
    }
    
    if (argc <= 1) {
        chiventure_ctx_t *ctx = chiventure_ctx_new(NULL);
    }

    chiventure_ctx_t *ctx = chiventure_ctx_new(argv[1]);

    /* Add calls to component-specific initializations here */

    start_ui(ctx, banner);

    game_free(ctx->game);
    return 0;
}
