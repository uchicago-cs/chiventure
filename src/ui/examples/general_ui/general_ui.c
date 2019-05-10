#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdbool.h>
#include "general_ui.h"
#include <signal.h>

/* Signal Handler for SIGINT */
void sigintHandler(int sig_num)
{
    /* Reset handler to catch SIGINT next time.
       Refer http://en.cppreference.com/w/c/program/signal */
    signal(SIGINT, sigintHandler);
//    fflush(stdout);
}

/* see general_ui.h
 */
window_t *create_newwin(int height, int width, int starty,
                        int startx, int show, void (*print)(window_t *win, int ch)){
    window_t *local_win;
    WINDOW *w;

    local_win = malloc(sizeof(window_t));

    // initializes the window with the given parameters
    w = newwin(height, width, starty, startx);

    local_win->w = w;
    local_win->print = print;
    // displays the window if show = true
    if(show){
        // 0,0 indicate the default characters for the border of the window
        box(local_win->w, 0 , 0);
        // refreshes to show the window
        //wrefresh(local_win);
    }


    return local_win;
}

void switch_windows(window_t **w1, window_t **w2){
    window_t *temp;

    temp = *w2;
    *w2 = *w1;
    *w1 = temp;

    return;
}
