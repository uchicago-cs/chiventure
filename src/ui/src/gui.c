#include <ncurses.h>
#include <ctype.h>
#include <signal.h>
#include <string.h>
#include <locale.h>

#include "common/ctx.h"
#include "ui/window.h"
#include "ui/print_functions.h"

#define MIN_COLS 80
#define MIN_ROWS 24

/*Starts up shell of a graphic*/
void start_gui(chiventure_ctx_t *ctx)
{
    int ch;

    // starts curses mode
    setlocale(LC_ALL, "");
    initscr();
    // pressed keys are not displayed in the window
    noecho();
    // height and width of the terminal window
    int width = COLS;
    int height = LINES / 2;

    window_t *map_win = window_new(height, width, 0, 0, print_map, true);
    window_t *main_win = window_new(height, width, 0, 0, print_info, true);
    window_t *displayed_win = main_win;

    window_t *cli_win = window_new(height, width, height, 0, print_cli, false);

    keypad(cli_win->w, TRUE);
    scrollok(cli_win->w, TRUE);
    wmove(cli_win->w, 0,0);

    print_homescreen(main_win, "THIS IS GUI");
}

void stop_gui(chiventure_ctx_t *ctx)
{
    //todo
}

