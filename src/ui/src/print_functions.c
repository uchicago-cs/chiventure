#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <signal.h>
#include "window.h"
#include "ctx.h"
#include "print_functions.h"



/* see print_functions.h */
void print_info(chiventure_ctx_t *ctx)
{
    mvwprintw(ctx->ui_ctx->main_win->w, 1, 2, "Main Window");
}

/* see print_functions.h */
void print_cli(chiventure_ctx_t *ctx)
{
    static bool first_run = true;
    int x,y;

    if (!first_run)
    {
        char str[80];

        wgetnstr(win->w, str, 80);

        getyx(win->w, y, x);
        mvwprintw(win->w, y, 3, str);
    }
    else
    {
        first_run = false;
    }


    getyx(win->w, y, x);

    int height  = LINES / 2;
    if (y >= height - 2)
    {
        wscrl(win->w, y - height + 2);
        y = height - 2;
    }

    mvwprintw(win->w, y + 1, 2, ">");



    // prints '>' in the cli window
<<<<<<< Updated upstream
    //mvwprintw(win->w, 1, 2, ">");
=======
    mvwprintw(ctx->ui_ctx->cli_win->w, 1, 2, ">");
>>>>>>> Stashed changes
}

/* see print_functions.h */
void print_map(chiventure_ctx_t *ctx)
{
    // prints the word map in the window
    mvwprintw(ctx->ui_ctx->map_win->w, 1,2, "map");
    return;
}
