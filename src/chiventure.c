#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <wdl/load_game.h>
#include <ui/ui_ctx.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "libobj/load.h"

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

const char *banner_small =
    "   ____________________________________________________________________________\n"
    "  /\\                                                                      \\\n"
    " |  |                                                                     |\n"
    "  \\_|    █████╗█╗  █╗█╗█╗   █╗██████╗██╗  █╗███████╗█╗   █╗████╗ ██████╗  |\n"
    "    |   █╔════╝█║  █║█║█║   █║█╔════╝██╗  █║╚══█╔══╝█║   █║█╔══█╗█╔════╝  |\n"
    "    |   █║     █████║█║█║   █║████╗  █╔█╗ █║   █║   █║   █║████╔╝████╗    |\n"
    "    |   █║     █╔══█║█║╚█╗ █╔╝█╔══╝  █║╚█╗█║   █║   █║   █║█╔══█╗█╔══╝    |\n"
    "    |   ╚█████╗█║  █║█║ ╚██╔╝ ██████╗█║ ╚██║   █║   ╚████╔╝█║  █║██████╗  |\n"
    "    |    ╚════╝╚╝  ╚╝╚╝  ╚═╝  ╚═════╝╚╝  ╚═╝   ╚╝    ╚═══╝ ╚╝  ╚╝╚═════╝  |\n"
    "    |  ___________________________________________________________________|___\n"
    "    | /                                                                      /\n"
    "    \\/______________________________________________________________________/\n";

int main(int argc, char **argv)
{
    struct winsize w;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
    int ncols = w.ws_col, nrows = w.ws_row;
    if (ncols < MIN_COLS || nrows < MIN_ROWS) {
        fprintf(stderr, "Chiventure prefers to run in terminals of at least %d columns and %d rows. Please resize your terminal!\n", MIN_COLS, MIN_ROWS);
        exit(1);
    }

    obj_t *obj_store = NULL;
    game_t *game = NULL;

    if (argc == 2)
    {
        /* Load an object from the path specified */
        obj_store = load_obj(argv[1]);

        if (!obj_store)
        {
            fprintf(stderr, "Could not load game: %s\n", argv[1]);
            exit(1);
        }
    }
    // Else: load the obj_store using some other method

    /* Take an object store and, assuming it is a valid WDL set of objects, load it into in-game
    * data structures. Other components could add calls inside load_game to load their feature-specific
    * data structures */
    if (obj_store != NULL)
    {
        game = load_game(obj_store);
    }

    chiventure_ctx_t *ctx = chiventure_ctx_new(game);
    ctx->obj_store = obj_store;

    /* Add calls to component-specific initializations here */

    /*** UI ***/
    if (ncols > 100) {
        start_ui(ctx, banner);
    } else {
        start_ui(ctx, banner_small);
    } 

    game_free(ctx->game);

    return 0;
}
