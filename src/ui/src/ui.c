#include <ncurses.h>
#include <ctype.h>
#include <signal.h>
#include <string.h>
#include <locale.h>

#include "common/ctx.h"
#include "ui/window.h"
#include "ui/print_functions.h"
#include "ui/ui_ctx.h"

/* MAIN_WIN_NUM will indicate we are in the main window
 * MAP_WIN_NUM will mean we are in the map window
 * INV_WIN_NUM will indicate we are in the inventory window
 */
#define MAIN_WIN_NUM 1
#define MAP_WIN_NUM 2
#define INV_WIN_NUM 3

void start_ui(chiventure_ctx_t *ctx, const char *banner)
{
    /* Create UI context */
    ui_ctx_t *ui_ctx = ui_ctx_new(ctx->game);
    ctx->ui_ctx = ui_ctx;

    // prevents program from closing on CTRL+C
    signal(SIGINT, SIG_IGN);

    int ch;
    int *quitval; 
    quitval = malloc(sizeof(int));
    *quitval = 1;
    

    // starts curses mode
    setlocale(LC_ALL, "");
    initscr();
    // pressed keys are not displayed in the window
    noecho();
    // height and width of the terminal window
    int width = COLS;
    int height = LINES / 2;

    window_t *map_win = window_new(height, width, 0, 0, print_map, true);
    window_t *main_win = window_new(height, width, 0, 0, print_info, true);
    window_t *displayed_win = main_win;

    window_t *cli_win = window_new(height, width, height, 0, print_cli, false);

    keypad(cli_win->w, TRUE);
    scrollok(cli_win->w, TRUE);
    wmove(cli_win->w, 0,0);

    ui_ctx->map_win = map_win;
    ui_ctx->main_win = main_win;
    ui_ctx->displayed_win = displayed_win;
    ui_ctx->cli_win = cli_win;

    ui_ctx->curr_page = MAIN_WIN_NUM;
    ui_ctx->cli_top = 0;

    ui_ctx->map = map_init();

    map_t *map = ui_ctx->map;
    // Initializes the CLI window
    window_t *cli = ui_ctx->cli_win;
    window_t *info = ui_ctx->displayed_win;

    //Initializes Colors
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_CYAN, COLOR_MAGENTA);

    wbkgd(ui_ctx->cli_win->w, COLOR_PAIR(1));
    wbkgd(ui_ctx->displayed_win->w, COLOR_PAIR(1));
    wbkgd(ui_ctx->map->pad, COLOR_PAIR(1));

    // prints home screen
    print_homescreen(info, banner);
    print_to_cli(ctx, ctx->game->start_desc);
    wrefresh(info->w);

    // prints the score and number of moves in the info window
    window_print(ctx, cli, quitval);

    // refreshes both windows to show the above changes
    wrefresh(cli->w);
    // sample game loop. uses ctrl+D key to exit
    while ((ch = wgetch(cli->w)) != 4 && *quitval)
    {

        height = LINES / 2;
        width = COLS;

        int curr_page = ui_ctx->curr_page;
        /* clears the borders of the info window  and resizes both windows
         * to adjust for new terminal window size. moves the bottom window to
         * the adequate position
         */
        if(curr_page == MAIN_WIN_NUM)
        {
            wclear(info->w);
            wresize(info->w, height, width);
            mvwin(info->w, (ui_ctx->cli_top) * height, 0);
            // redraws the info box
            box(info->w, 0, 0);
            // The following line is commented out for now, since window_print does not print much
            // window_print(ctx, info);
            // For now just continue showing the banner
            print_banner(info, banner);
            wrefresh(info->w);
        }

        wresize(cli->w, height, width);
        mvwin(cli->w, !(ui_ctx->cli_top) * height, 0);


        // detects ALt+key commands
        if (ch == 27)
        {
            ch = wgetch(cli->w);
            // Alt+m switches the info window to the map window
            // Alt+s switches the position of the CLI
            if (ch == 'm')
            {
                ch = 27;

                toggle_map(ctx);
                ui_ctx = ctx->ui_ctx;

            }
            else if (ch == 's')
            {
                ch = 27;
                layout_switch(ctx);
            }
        }
        else if (isalnum(ch))
        {
            ungetch(ch);
            window_print(ctx, cli, quitval);

        }
        curr_page = ui_ctx->curr_page;

        //This conditional refreshes the non-CLI window
        if (curr_page == MAIN_WIN_NUM)
        {
            //window_print(ctx, info);
            mvwin(info->w, (ui_ctx->cli_top) * height, 0);
        }
        else if (curr_page == MAP_WIN_NUM)
        {
            // The following lines of code were commented out since they were causing issues with the map view
            // wresize(info->w, 0, 0);
            // touchwin(info->w);
            // wrefresh(info->w);
            int cli_top = ui_ctx->cli_top;
            if (map != NULL)
            {
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

    free(quitval);

    /* Free UI context */
    ui_ctx_free(ctx->ui_ctx);
}

void stop_ui(chiventure_ctx_t *ctx)
{
    window_free(ctx->ui_ctx->map_win);
    window_free(ctx->ui_ctx->main_win);
    window_free(ctx->ui_ctx->cli_win);
}
