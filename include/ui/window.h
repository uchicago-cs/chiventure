
#ifndef WINDOW_H
#define WINDOW_H

typedef struct chiventure_ctx chiventure_ctx_t;


typedef struct window {
    WINDOW *w;
    void (*print)(chiventure_ctx_t *ctx, struct window *win, int *retval);
} window_t;

typedef void (win_print)(chiventure_ctx_t *ctx, window_t *win, int *retval);


/* window_new
 * allocates memory for a window_t struct and creates a window)t with the
 * specified dimensions at the specified location
 * and if show is true, then it draws the border of the window
 * inputs:
 *    - height : height of the window
 *    - width : width of the window
 *    - starty : initial vertical position of the window
 *    - startx : initial horizontal position of the window
 *    - print : print function associated with the window
 *    - box : indicates whether or not to draw a box around the window
 *
 * returns:
 *    - window_t created, displays the window if show = true
 *
 * NOTE: the top left corner of the terminal is (0,0)
 */
window_t *window_new(int height, int width, int y_start,
                     int x_start, win_print print, int box);


/* window_init
 * initializes the values for a window_t struct created with window_new
 *
 * inputs:
 *    - height : height of the window
 *    - width : width of the window
 *    - starty : initial vertical position of the window
 *    - startx : initial horizontal position of the window
 *    - print : print function associated with the window
 *
 * returns:
 *    - 0
 *
 * NOTE: the top left corner of the terminal is (0,0)
 */
int window_init(window_t *win, int height, int width, int y_start,
                int x_start, win_print print);


/* window_free
 * frees all resources associated with a window_t struct
 *
 * Parameters:
 *    - win : window_t struct to be freed
 *
 * Returns:
 *    - 0
 */
int window_free(window_t *win);

/* print_window
 * Calls the print function associated with the given window
 *
 * Parameters:
 *   - ctx : chiventure context struct
 *   - win : window which we want to print
 *   - retval: an out parameter to make the game close on "QUIT"
 *
 */
void window_print(chiventure_ctx_t *ctx, window_t *win, int *retval);



#endif
