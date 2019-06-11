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

// approximate length of chiventure banner
#define BANNER_LENGTH (96)
#define BANNER_HEIGHT (12)

/* see print_functions.h */
void print_homescreen(window_t *win, const char *banner)
{
    // calculate the position of the banner so that is is approximately centered.
    // The -1 in the y position is to give space for the message below the banner
    // x_pos and y_pos indicate the x-y coordinates of the top left corner of the banner
    int x_pos = COLS / 2 - BANNER_LENGTH / 2;
    int y_pos = LINES / 4 - BANNER_HEIGHT / 2 - 1;
    if (x_pos < 0) {
        x_pos = 0;
    }
    int len = strlen(banner);
    char temp[len];
    strcpy(temp, banner);
    char *str = strtok(temp, "\n");

    while (str != NULL) {
        mvwprintw(win->w, y_pos, x_pos, str);
        str = strtok(NULL, "\n");
        y_pos++;
    }

    char help[] = "Type 'HELP' to show help menu";
    // similarly, as above, calculates where to place the message so it's centered
    x_pos = COLS /2 - strlen(help) / 2;

    mvwprintw(win->w, y_pos + 2, x_pos, help);

}

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
        mvwprintw(win->w, 1, 2, "> ");
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

    // scrolls the screen up if there is no space to print the next line
    int height = LINES / 2;
    if (y >= height - 2) {
        wscrl(win->w, y - height + 2);
        y = height - 2;
    }
    mvwprintw(win->w, y, 2, "> ");
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

    height = LINES / 2;

    WINDOW *cli = ctx->ui_ctx->cli_win->w;

    int len = strlen(str);
    char temp[len];
    strcpy(temp, str);
    char *tmp = strtok(temp, "\n");


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

        // if there is no space to print the next line, instruction to press ENTER
        // to see more or q to continue is given,
        if (y >= height - 1 && tmp != NULL) {
            mvwprintw(cli, y, 3, "Press ENTER to see more, 'q' to continue");
            int ch;

            while ((ch = wgetch(cli)) != '\n' && ch != 'q') {
                /* wait until enter is pressed or q are pressed */
            }

            if (ch == 'q') {
                return;
            }
            // sets the cursor to the begining of the line just printed
            // ("Press ENTER to see more, 'q' to continue"), and then clears it
            wmove(cli, y, 2);
            wclrtoeol(cli);


            // scrolls the screen up
            wscrl(cli, y - height + 2);
            y = height - 2;


        }

        wrefresh(cli);
    }


}
