#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdbool.h>
#include <signal.h>
#include "general_ui.h"


int score = 0;
int moves = 0;
int char_count = 0;
int line = 1;

void print_info(window_t *win, int ch){
    mvwprintw(win->w, 1, 2, "Score: %i", score);
    mvwprintw(win->w, 2, 2, "Moves: %i", moves);
}

void print_cli(window_t *win, int ch){
    int y,x;
    WINDOW *bottom = win->w;
    if(isalnum(ch) || ch == ' ' ){
        // inserts character
        winsch(bottom, ch);
        char_count++;
        // gets position of cursor and moves it one space right
        getyx(bottom, y, x);
        wmove(bottom, y, x+1);
    }
    // implements a backspace (deletes charcter before the cursor)
    if(ch == KEY_BACKSPACE){
        // gets cursor position
        getyx(bottom, y, x);
        // deletes character before cursor unless it is the '>' character
        if(x > 3){
            mvwdelch(bottom, y, x-1);
            char_count--;
        }
    }
    // moves the cursor to the left
    if(ch == KEY_LEFT){
        getyx(bottom, y, x);
        // checks to make sure cursor is not right after the '>' character
        if(x > 3){
            wmove(bottom, y, x-1);
        }
    }
    // moves cursor to the right
    if(ch == KEY_RIGHT){
        getyx(bottom, y, x);
        // checks that cursor is not past the charcters inserted
        if(x < char_count + 3){
            wmove(bottom, y, x + 1);
        }
    }
    // implements the delete key
    if(ch == KEY_DC){
        getyx(bottom, y, x);
        // checks that cursor is not past the charcters inserted
        if(x < char_count + 3){
            mvwdelch(bottom, y, x);
            char_count--;
        }
    }
    // enters a new line (which includes an new '>' character)
    if(ch == '\n'){
        line++;
        moves++;
        mvwprintw(bottom, line, 2, ">");
    }
}

void print_nothing(window_t* win, int ch){
    return;
}

int main(){

    window_t *top;
    window_t *bottom;
    window_t *blank;
    int  width, height;
    int mainw = 1;
    int ch;
    int cli_top = 0; // 0 if the cli will be in the bottom, 1 if it will be on top

    signal(SIGINT, sigintHandler);

    // starts curses mode
    initscr();

    // pressed keys are not displayed in the window
    noecho();

    // height and width of the terminal window
    height = LINES / 2;
    width = COLS;


    /* creates 2 windows that span the width of the terminal
     * and each occupy half of the terminal height
     */


    printw("Press 1 if you want the CLI on top, anything else to continue");
    refresh();


    // wait for key prss to determine position of cli
    keypad(stdscr, TRUE);

    if((ch = getch()) == '1'){
        cli_top = 1;
    }

    top = create_newwin(height, width, cli_top * height, 0, true, print_info);
    blank = create_newwin(height, width, cli_top * height, 0, true, print_nothing);

    bottom = create_newwin(height, width, (!cli_top)* height , 0, false, print_cli);

    keypad(bottom->w, TRUE);

    // prints '>' in the bottom window
    mvwprintw(bottom->w, line, 2, ">");

    // prints the score and number of moves in the top window
    top->print(top, 0);

    // refreshes both windows to show the above changes
    wrefresh(top->w);
    wrefresh(bottom->w);

    // sample game loop. uses F1 key to exit

    while((ch = wgetch(bottom->w)) != 4){


        height = LINES / 2;
        width = COLS;

        /* clears the borders of the top window  and resizes both windows
         * to adjust for new terminal window size. moves the bottom window to
         * the adequate position
         */
        wclear(top->w);
        wresize(top->w, height, width);
        wresize(bottom->w, height, width);
        mvwin(bottom->w, !(cli_top) * height, 0);
        mvwin(top->w, (cli_top) * height, 0);


        // redraws the top box
        box(top->w, 0, 0 );


        if(ch == KEY_F(3)){
            switch_windows(&top, &blank);
            mainw = !mainw;
        }
        /* if user presses a number/letter or a space, it inserts it at the
         * position of the cursor, and moves the cursor one position to the right
         */
        // prints the top box messaged again
        bottom->print(bottom, ch);
        top->print(top, 0);

        // refreshes windows to relfect changes
        wrefresh(top->w);
        wrefresh(bottom->w);


    }

    endwin();			/* End curses mode		  */
    return 0;
}
