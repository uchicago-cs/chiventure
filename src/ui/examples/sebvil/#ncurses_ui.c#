#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdbool.h>

/* create_newwin
 * creates a window with the specified dimensions at the specified location
 * and if show is true, then it draws the border of the WINDOW
 * inputs:
 *    - height : height of the window
 *    - width : width of the window
 *    - starty : initial vertical position of the window
 *    - startx : initial horizontal position of the window
 *    - show : indicates whether or not to draw a box around the window
 *
 * returns:
 *    - WINDOW created, displays the window if show = true
 *
 * NOTE: the top left corener of the terminal is (0,0)
 */
WINDOW *create_newwin(int height, int width, int starty, int startx, int show){
    WINDOW *local_win;

    // initializes the window with the given parameters
    local_win = newwin(height, width, starty, startx);

    // displays the window if show = true
    if(show){
        // 0,0 indicate the default characters for the border of the window
        box(local_win, 0 , 0);
        // refreshes to show the window
        wrefresh(local_win);
    }


    return local_win;
}



int main(){

    WINDOW *top;
    WINDOW *bottom;
    int  width, height;
    int moves = 0;
    int score = 0;
    int ch;
    int x,y;
    int line = 1;
    int char_count = 0;

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
    top = create_newwin(height, width, 0, 0, true);
    bottom = create_newwin(height, width, height, 0, false);


    // the bottom window will be waiting for key presses
    keypad(bottom, TRUE);

    // prints '>' in the bottom window
    mvwprintw(bottom, line, 2, ">");

    // prints the score and number of moves in the top window
    mvwprintw(top, 1, 2, "Score: %i", score);
    mvwprintw(top, 2, 2, "Moves: %i", moves);

    // refreshes both windows to show the above changes
    wrefresh(top);
    wrefresh(bottom);

    // sample game loop. uses F1 key to exit

    while((ch = wgetch(bottom)) != KEY_F(1)){

        height = LINES / 2;
        width = COLS;

        /* clears the borders of the top window  and resizes both windows
         * to adjust for new terminal window size. moves the bottom window to
         * the adequate position
         */
        wclear(top);
        wresize(top, height, width);
        wresize(bottom, height, width);
        mvwin(bottom, height, 0);

        // redraws the top box
        box(top, 0, 0 );



        /* if user presses a number/letter or a space, it inserts it at the
         * position of the cursor, and moves the cursor one position to the right
         */
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

        // prints the top box messaged again
        mvwprintw(top, 1, 2, "Score: %i", score);
        mvwprintw(top, 2, 2, "Moves: %i", moves);


        // refreshes windows to relfect changes
        wrefresh(top);
        wrefresh(bottom);


    }

    endwin();			/* End curses mode		  */
    return 0;
}
