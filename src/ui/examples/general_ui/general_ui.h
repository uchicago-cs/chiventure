#ifndef GENERAL_UI_H
#define GENERAL_UI_H

typedef struct window {
    WINDOW *w;
    void (*print)(struct window *win, int ch);
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
                         int startx, int show, void (*print)(window_t *win, int ch));

void switch_windows(window_t **w1, window_t **w2);

/* Signal Handler for SIGINT */
void sigintHandler(int sig_num);
#endif
