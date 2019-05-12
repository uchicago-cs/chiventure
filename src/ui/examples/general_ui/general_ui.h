#ifndef GENERAL_UI_H
#define GENERAL_UI_H

typedef struct window {
    WINDOW *w;
    void (*print)(struct window *win);
} window_t;

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
 window_t *create_newwin(int height, int width, int starty,
                         int startx, int show, void (*print)(window_t *win));


/* Signal Handler for SIGINT */
void sigintHandler(int sig_num);


/*
 * Prints score and number of moves
 *
 * Parameters:
 *   - win : window where to print the info
 *
 * No value is returned
 */
void print_info(window_t *win);

/*
 * Prints the CLI- adds and deltees character based on user input
 *
 * Parameters:
 *   - win : window where to print the info
 *
 * No value is returned
 */
void print_cli(window_t *win);

/*
 * Prints the word map in the window (top left corner)
 *
 * Parameters:
 *   - win : window where to print the info
 *
 * No value is returned
 */
void print_map(window_t *win);
#endif
