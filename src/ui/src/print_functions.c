#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <signal.h>
#include <string.h>
#include "window.h"
#include "ctx.h"
#include "print_functions.h"
#include "cmd.h"
#include "operations.h"
#include "shell.h"
#include "validate.h"



/* see print_functions.h */
void print_info(chiventure_ctx_t *ctx, window_t *win)
{
    mvwprintw(win->w, 1, 2, "Main Window");
}

/* see print_functions.h */
void print_cli(chiventure_ctx_t *ctx, window_t *win)
{
    static bool first_run = true;

    if (first_run) {
        first_run = false;
        mvwprintw(win->w, 1, 2, ">");
        return;
    }
    echo();
    int x, y;
    char input[80];
    int quit = 1;
    char *cmd_string;
    wgetnstr(win->w, input, 80);

    noecho();
    cmd_string = strdup(input);
    //check whether user input is empty
    if (!strcmp(cmd_string, "")) {
        return;
    }

    cmd *c = cmd_from_string(cmd_string, ctx);
    if (!c) {
        print_to_cli(ctx, "Error: Malformed input (4 words max)");
    }
    else {
        do_cmd(c, &quit, ctx);
    }

    if (cmd_string) {
        free(cmd_string);
    }

    getyx(win->w, y, x);
    y++;
    int height  = LINES / 2;
    if (y >= height - 2) {
        wscrl(win->w, y - height + 2);
        y = height - 2;
    }
    mvwprintw(win->w, y, 2, ">");
}

/* see print_functions.h */
void print_map(chiventure_ctx_t *ctx, window_t *win)
{
    // prints the word map in the window
    mvwprintw(win->w, 1,2, "map");
    return;
}

/* see print_functions.h */
void print_to_cli(chiventure_ctx_t *ctx, char *str)
{
    int x, y, height;

    height  = LINES / 2;

    WINDOW *cli = ctx->ui_ctx->cli_win->w;

    char *tmp = strtok(str, "\n");

    getyx(cli, y, x);

    // scrolls the screen up if there is no space to print the first line of output
    if (y >= height - 1) {
        wscrl(cli, y - height + 2);
        y = height - 2;
    }
    while (tmp != NULL) {
        mvwprintw(cli, y, 3, tmp);
        tmp = strtok(NULL, "\n");

        getyx(cli, y, x);
        y++;

        // if there is no space to print the next line, instuction to press ENTER
        // to see more is given
        if (y >= height - 1 && tmp != NULL) {
            mvwprintw(cli, y, 3, "Press ENTER to see more");
            int ch;

            while ((ch = wgetch(cli)) != '\n') {
                /* wait until enter is pressed */
            }
            // sets the cursor to the begining of the line just printed
            // ("Press ENTER to see more"), and then clears it
            wmove(cli, y, 2);
            wclrtoeol(cli);

            // scrolls the screen up
            wscrl(cli, y - height + 2);
            y = height - 2;
        }
    }


}
