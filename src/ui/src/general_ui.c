#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdbool.h>
#include "general_ui.h"
#include <signal.h>

int score = 0;
int moves = 0;
int char_count = 0;
int line = 1;
int ch;

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
                        int startx, int show, void (*print)(window_t *wins)){
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

/* see general_ui.h */
void print_info(window_t *win){
    mvwprintw(win->w, 1, 2, "Score: %i", score);
    mvwprintw(win->w, 2, 2, "Moves: %i", moves);
}

/* see general_ui.h */
void print_cli(window_t *win){
    int y,x;
    WINDOW *window = win->w;
    // inserts charcater if it's a space or alphanumeric
    if(isalnum(ch) || ch == ' ' ){
        // inserts character
        winsch(window, ch);
        char_count++;
        // gets position of cursor and moves it one space right
        getyx(window, y, x);
        wmove(window, y, x+1);
    }

    switch(ch){
        // implements a backspace (deletes charcter before the cursor)
        case KEY_BACKSPACE:
        // gets cursor position
            getyx(window, y, x);
            // deletes character before cursor unless it is the '>' character
            if(x > 3){
                mvwdelch(window, y, x-1);
                char_count--;
            }
            break;
        // moves cursor left
        case KEY_LEFT:
            getyx(window, y, x);
            // checks to make sure cursor is not right after the '>' character
            if(x > 3){
                wmove(window, y, x-1);
            }
            break;
        case KEY_RIGHT:
            getyx(window, y, x);
            // checks that cursor is not past the charcters inserted
            if(x < char_count + 3){
                wmove(window, y, x + 1);
            }
            break;
        case KEY_DC:
            // implements delete key
            getyx(window, y, x);
            // checks that cursor is not past the charcters inserted
            if(x < char_count + 3){
                mvwdelch(window, y, x);
                char_count--;
            }
            break;
        // inserts a new line when enter is pressed
        case '\n':
            line++;
            moves++;
            if(line == LINES/2){
                wscrl(window,1);
                line --;
            }
            mvwprintw(window, line, 2, ">");
            break;
        default: break;
    }
}

/* see general_ui.h */
void print_map(window_t* win){
    // prints the word map in the window
    wprintw(win->w, "map");
    return;
}
