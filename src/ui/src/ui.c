#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include "window.h"
#include "ui.h"
#include "print_functions.h"




void start_ui()
{
    // prevents program from closing on CTRL+C
    signal(SIGINT, SIG_IGN);

    /* 1 will indicate we are in the main window, 0 will mean
     * we are in the map window
     */
    int on_main = 1;
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




    /* initializes the widows. there is a main window, one where
     * maps could be displayed, and the cli window
     */
    window_t *main_win = window_new(height, width, cli_top * height, 0, print_info, true);
    window_t *map = window_new(height, width, cli_top * height, 0, print_map, true);
    window_t *cli = window_new(height, width, (!cli_top)* height, 0, print_cli, false);

    // info window is the window to be displayed in addition to cli
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
        wclear(info->w);
        wresize(info->w, height, width);
        wresize(cli->w, height, width);
        mvwin(cli->w, !(cli_top) * height, 0);
        mvwin(info->w, (cli_top) * height, 0);


        // redraws the info box
        box(info->w, 0, 0 );

        // detects ALt+key commands
        if (ch == 27)
        {
            ch = wgetch(cli->w);
            // Alt+m switches the info window to the map window
            // Alt+s switches the position of the CLI
            if (ch == 'm')
            {
                if (on_main)
                {
                    info = map;
                }
                else
                {
                    info = main_win;
                }
                on_main = !on_main;
                ch = 27;
            }
            else if (ch == 's')
            {
                cli_top = !cli_top;
                ch = 27;
                mvwin(cli->w, !(cli_top) * height, 0);
                mvwin(main_win->w, (cli_top) * height, 0);
                mvwin(map->w, (cli_top) * height, 0);

            }
        }
        else if (isalnum(ch))
        {
            echo();
            ungetch(ch);

            window_print(cli);


            noecho();

        }

        window_print(info);

        // refreshes windows to reflect changes
        wrefresh(info->w);
        wrefresh(cli->w);


    }

    window_free(main_win);
    window_free(map);
    window_free(cli);

    // End curses mode
    endwin();
}
