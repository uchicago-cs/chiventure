#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <readline/history.h>
#include <ctype.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include "common.h"
#include "ctx.h"
#include "ui.h"
#include "window.h"
#include "print_functions.h"
#include "ui_ctx.h"

/* MAIN_WIN_NUM will indicate we are in the main window
 * MAP_WIN_NUM will mean we are in the map window
 * INV_WIN_NUM will indicate we are in the inventory window
 */
#define MAIN_WIN_NUM 1
#define MAP_WIN_NUM 2
#define INV_WIN_NUM 3

void start_ui(chiventure_ctx_t *ctx, const char *banner)
{
    // prevents program from closing on CTRL+C
    signal(SIGINT, SIG_IGN);

    ui_ctx_t *ui_ctx = ctx->ui_ctx;
    int ch;


    // starts curses mode
    initscr();
    // pressed keys are not displayed in the window
    noecho();
    // height and width of the terminal window
    int width = COLS;
    int height = LINES /2;
     
    // Begin a session in which the history functions might be used 
    using_history();

    map_t *map = ui_ctx->map;
    // Initializes the CLI window
    window_t *cli = ui_ctx->cli_win;
    window_t *info = ui_ctx->displayed_win;

    //Initializes Colors
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    
    wbkgd(ui_ctx->cli_win->w, COLOR_PAIR(1));
    wbkgd(ui_ctx->displayed_win->w, COLOR_PAIR(1));
    wbkgd(ui_ctx->map->pad, COLOR_PAIR(1));
    
    // prints home screen
    print_homescreen(info, banner);
    wrefresh(info->w);

    // prints the score and number of moves in the info window
    window_print(ctx, cli);

    // refreshes both windows to show the above changes
    wrefresh(cli->w);

    // sample game loop. uses ctrl+D key to exit
    while ((ch = wgetch(cli->w)) != 4) {

        height = LINES / 2;
        width = COLS;

        int curr_page = ui_ctx->curr_page;
        /* clears the borders of the info window  and resizes both windows
         * to adjust for new terminal window size. moves the bottom window to
         * the adequate position
         */
        if(curr_page == MAIN_WIN_NUM) {
            wclear(info->w);
            wresize(info->w, height, width);
            mvwin(info->w, (ui_ctx->cli_top) * height, 0);
            // redraws the info box
            box(info->w, 0, 0);
            window_print(ctx, info);
            wrefresh(info->w);
        }

        wresize(cli->w, height, width);
        mvwin(cli->w, !(ui_ctx->cli_top) * height, 0);


        // detects ALt+key commands
        if (ch == 27) {
            ch = wgetch(cli->w);
            // Alt+m switches the info window to the map window
            // Alt+s switches the position of the CLI
            if (ch == 'm') {
                ch = 27;

                toggle_map(ctx);
                ui_ctx = ctx->ui_ctx;

            } else if (ch == 's') {
                ch = 27;
                layout_switch(ctx);
            }
        }
        else if (isalnum(ch)) {
            ungetch(ch);
            window_print(ctx,  cli);

        }
	curr_page = ui_ctx->curr_page;
        // This conditional refreshes the non-CLI window
        if (curr_page == MAIN_WIN_NUM) {
            window_print(ctx, info);
            mvwin(info->w, (ui_ctx->cli_top) * height, 0);
        } else if (curr_page == MAP_WIN_NUM) {
            wresize(info->w, 0, 0);
            touchwin(info->w);
            wrefresh(info->w);
            int cli_top = ui_ctx->cli_top;
            if (map != NULL) {
                map_set_displaywin(map, 0, cli_top * height, width,
                                   height + cli_top * height);
                map_center_on(ctx, 0, 0, 0);
            }
        }

        // Refreshes the displayed windows
        wrefresh(info->w);
        wrefresh(cli->w);
    }

    // End curses mode
    endwin();
}
