#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <signal.h>
#include "window.h"
#include "print_functions.h"



/* see print_functions.h */
void print_info(window_t *win)
{
    mvwprintw(win->w, 1, 2, "Score: %i", 0);
    mvwprintw(win->w, 2, 2, "Moves: %i", 0);
}

/* see print_functions.h */
void print_cli(window_t *win)
{
    int x,y;
//    int height, width;
    getyx(win->w, y, x);
//    getmaxyx(win->w, height, width);
    int height  = LINES / 2;
    if (y >= height -2) {
        wscrl(win->w, y - height +2);
        y = height - 2;
    }
    mvwprintw(win->w, y+1, 2, ">");

    // prints '>' in the cli window
    //mvwprintw(win->w, 1, 2, ">");
}

/* see print_functions.h */
void print_map(window_t* win)
{
    // prints the word map in the window
    mvwprintw(win->w, 1,2, "map");
    return;
}
