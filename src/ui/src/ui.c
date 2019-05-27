#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include "ctx.h"
#include "ui.h"
#include "window.h"
#include "print_functions.h"

#define MAIN_WIN_NUM 1
#define MAP_WIN_NUM 2
#define INV_WIN_NUM 3

void start_ui(chiventure_ctx_t *ctx)
{
    // prevents program from closing on CTRL+C
    signal(SIGINT, SIG_IGN);

    /* MAIN_WIN_NUM will indicate we are in the main window
     * MAP_WIN_NUM will mean we are in the map window
     * INV_WIN_NUM will indicate we are in the inventory window
     */
    int curr_page = MAIN_WIN_NUM;
    int ch;

    // 0 if the cli will be in the bottom, 1 if it will be on top
    int cli_top = 0;

    // starts curses mode
    initscr();

    // pressed keys are not displayed in the window
    noecho();

    // height and width of the terminal window
    int height = LINES / 2;
    int width = COLS;


    // Initializes the main window
    window_t *main_win = window_new(height, width, cli_top * height, 0, print_info, true);

    // The map window is initialized and a random room array is generated
    int num_rooms = 20;
    room_t **rooms = get_test_rooms(num_rooms);
    map_t *map = map_init(rooms,num_rooms);

    // Initializes the CLI window
    window_t *cli = window_new(height, width, (!cli_top)* height, 0, print_cli, false);
    window_t *info = main_win;

    // reads input from the cli window, allows scrolling
    keypad(cli->w, TRUE);
    scrollok(cli->w, TRUE);

    // prints the score and number of moves in the info window
    window_print(info);
    window_print(cli);

    // refreshes both windows to show the above changes
    wrefresh(info->w);
    wrefresh(cli->w);

    // sample game loop. uses ctrl+D key to exit

    while ((ch = wgetch(cli->w)) != 4)
    {

        height = LINES / 2;
        width = COLS;

        /* clears the borders of the info window  and resizes both windows
         * to adjust for new terminal window size. moves the bottom window to
         * the adequate position
         */
        if(curr_page == MAIN_WIN_NUM) {
            wclear(info->w);
            wresize(info->w, height, width);
            mvwin(info->w, (cli_top) * height, 0);
            // redraws the info box
            box(info->w, 0, 0);
        }
        wresize(cli->w, height, width);
        mvwin(cli->w, !(cli_top) * height, 0);



        // detects ALt+key commands
        if (ch == 27)
        {
            ch = wgetch(cli->w);
            // Alt+m switches the info window to the map window
            // Alt+s switches the position of the CLI
            if (ch == 'm') {
                if (curr_page != MAP_WIN_NUM) {
                    curr_page = MAP_WIN_NUM;
                }
		else {
                    curr_page = MAIN_WIN_NUM;
                    info = main_win;
                    wresize(info->w, height,width);
                }

                ch = 27;
            }
	    else if (ch == 's') {
                cli_top = !cli_top;
                ch = 27;
                mvwin(cli->w, !(cli_top) * height, 0);
                mvwin(main_win->w, (cli_top) * height, 0);
                map_set_displaywin(map, 0, cli_top * height, width,
                                   height + cli_top * height);
                map_center_on(map, 0, 0, 0);
            }
        }
        else if (isalnum(ch))
        {
            echo();
            ungetch(ch);

            window_print( cli);


            noecho();

        }

        // Prints the cli to the screen
        window_print(cli);

        // This conditional refreshes the non-CLI window
        if (curr_page == MAIN_WIN_NUM) {
            window_print(info);
            wrefresh(info->w);
        }
	else if (curr_page == MAP_WIN_NUM) {
            wresize(info->w, 0, 0);
            map_set_displaywin(map, 0, cli_top * height, width,
                               height + cli_top * height);
            map_center_on(map, 0, 0, 0);
        }

        // Refreshes the CLI window
        wrefresh(cli->w);
    }

    window_free(main_win);
    window_free(cli);

    // End curses mode
    endwin();
}
