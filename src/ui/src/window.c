#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <assert.h>

#include "ui/window.h"


/* see window.h */
window_t *window_new(int height, int width, int y_start,
                     int x_start, win_print print, int show)
{
    window_t *win = malloc(sizeof(window_t));

    window_init(win, height, width, y_start, x_start, print);

    if (show)
    {
        // 0,0 indicate the default characters for the border of the window
        box(win->w, 0, 0);
    }

    return win;

}

/* see window.h */
int window_init(window_t *win, int height, int width, int y_start,
                int x_start, win_print print)
{
    assert(win != NULL);

    WINDOW *w = newwin(height, width, y_start, x_start);

    win->w = w;
    win->print = print;

    return 0;

}

/* see window.h */
int window_free(window_t *win)
{
    assert(win != NULL);

    delwin(win->w);

    free(win);

    return 0;
}

/* see window.h */
void window_print(chiventure_ctx_t *ctx, window_t *win, int *retval)
{
    win->print(ctx, win, retval);
}
