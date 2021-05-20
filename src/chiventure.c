#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "common/load_objects.h"
#include <wdl/load_game.h>
#include <ui/ui_ctx.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "ui/gui.h"

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

    wdl_ctx_t *wdl_ctx = NULL;
    game_t *game = NULL;
    /*Boolean to see if gui is trying to be used*/
    bool graphical = false;

    if (argc == 2)
    {
        /*Checks if the user is trying to access the gui*/
        if (!strcmp(argv[1], "--gui"))
        {
            /*Changes to true as they are trying to access the graphics of gui*/
            graphical = true;
        }
        else
        {
            wdl_ctx = load_wdl(argv[1]);
            game = load_objects(wdl_ctx);

            /*Helps prevent errors when there is no loaded game*/
            if (!game)
            {
                fprintf(stderr, "Could not load game: %s\n", argv[1]);
                exit(1);
            }
        }
    }

    /*Checks if the user is trying to load a game, as well as a gui*/
    if (argc == 3) 
    {
        if(!strcmp(argv[1], "--gui"))
        {
            graphical = true;
            wdl_ctx = load_wdl(argv[2]);
            game = load_objects(wdl_ctx);

            if (!game)
            {
                fprintf(stderr, "Could not load game: %s\n", argv[1]);
                exit(1);
            }
        }
        else
        {
            fprintf(stderr, "Unrecognized parameter: %s\n", argv[1]);
            exit(1);
        }
    }

    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    /* Add calls to component-specific initializations here */

    if (graphical)
    {   
        /*If graphical is true the user will be using GUI*/
        run_gui(ctx);
    }
    else 
    {
        struct winsize w;
        ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
        int ncols = w.ws_col, nrows = w.ws_row;
        if (ncols < MIN_COLS || nrows < MIN_ROWS) {
            fprintf(stderr, "Chiventure prefers to run in terminals of at least %d columns and %d rows. Please resize your terminal!\n", MIN_COLS, MIN_ROWS);
            exit(1);
        }

        /*If graphical is false the user will be using UI */
        if (ncols > 100) {
            start_ui(ctx, banner);
        } else {
            start_ui(ctx, banner_small);
        } 
    }

    game_free(ctx->game);

    return 0;
}



