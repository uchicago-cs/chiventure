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
        print_to_cli(ctx, ">");
        return;
    }

    int x, y;
    char input[80];
    int quit = 1;
    char *cmd_string;
    wgetnstr(win->w, input, 80);


    cmd_string = strdup(input);
    //check whether user input is empty
    if (!strcmp(cmd_string, "")) {
        return;
    }

    cmd *c = cmd_from_string(cmd_string, ctx);
    if (!c) {
        shell_error_arg("unrecognized or malformed command: \"%s\"", input);
    }
    else {
        do_cmd(c, &quit, ctx);
        // Add valid input to readline history.
        add_history(input);
    }

    if (cmd_string) {
        free(cmd_string);
    }


    print_to_cli(ctx, ">");



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
    int x, y;

    WINDOW *cli = ctx->ui_ctx->cli_win->w;

    getyx(cli, y, x);

    int height  = LINES / 2;
    if (y >= height - 2) {
        wscrl(cli, y - height + 2);
        y = height - 2;
    }

    mvwprintw(cli, y + 1, 2, str);
}
