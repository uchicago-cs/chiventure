#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdbool.h>
#include <signal.h>
#include "general_ui.h"


extern int line;
extern int ch;

int main(){

    window_t *info;
    window_t *cli;
    window_t *map;
    window_t *score;
    int  width, height;
    int mainw = 1;
    int cli_top = 0; // 0 if the cli will be in the bottom, 1 if it will be on top

    // prevents program from closing on CTRL+C
    signal(SIGINT, sigintHandler);
    // starts curses mode
    initscr();

    // pressed keys are not displayed in the window
    noecho();

    // height and width of the terminal window
    height = LINES / 2;
    width = COLS;


    printw("Press 1 if you want the CLI on top, anything else to continue");
    // must refresh  every time a change is made to show change in screen
    refresh();

    // wait for key prss to determine position of cli
    keypad(stdscr, TRUE);

    if((ch = getch()) == '1'){
        cli_top = 1;
    }

    /* initializes the widows. there is one for score, one where maps could
     * be displayed, and the cli window
     */
    score = create_newwin(height, width, cli_top * height, 0, true, print_info);
    map = create_newwin(height, width, cli_top * height, 0, true, print_map);

    cli = create_newwin(height, width, (!cli_top)* height , 0, false, print_cli);

    // info window is the window to be displayed in addition to cli
    info = score;

    // reads input from the cli window, allows scrolling
    keypad(cli->w, TRUE);
    scrollok(cli->w, TRUE);

    // prints '>' in the cli window
    mvwprintw(cli->w, line, 2, ">");

    // prints the score and number of moves in the info window
    info->print(info);

    // refreshes both windows to show the above changes
    wrefresh(info->w);
    wrefresh(cli->w);

    // sample game loop. uses ctrl+D key to exit

    while((ch = wgetch(cli->w)) != 4){


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


        // redraws the top box
        box(info->w, 0, 0 );

        // detects ALt+key commands
        if(ch == 27){
            ch = wgetch(cli->w);
            // Alt+m switches the info window to the map window
            if(ch == 'm'){
                if(mainw){
                    info = map;
                }
                else{
                    info = score;
                }
                mainw = !mainw;
                ch = 27;
            }

        }

        cli->print(cli);
        info->print(info);

        // refreshes windows to reflect changes
        wrefresh(info->w);
        wrefresh(cli->w);


    }

    endwin();			/* End curses mode		  */
    return 0;
}
