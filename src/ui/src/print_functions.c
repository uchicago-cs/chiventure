#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <signal.h>
#include <string.h>
#include "window.h"
#include "print_functions.h"
#include "cmd.h"
#include "operations.h"
#include "shell.h"
#include "validate.h"



/* see print_functions.h */
void print_info(window_t *win)
{
    mvwprintw(win->w, 1, 2, "Score: %i", 0);
    mvwprintw(win->w, 2, 2, "Moves: %i", 0);
}

/* see print_functions.h */
void print_cli(window_t *win)
{
    static bool first_run = true;
    int x,y;
    char input[80];
    int quit = 1;
    char *cmd_string;
    if (!first_run)
    {

        wgetnstr(win->w, input, 80);

        getyx(win->w, y, x);
        //mvwprintw(win->w, y, 3, str);
    }
    else
    {
        first_run = false;
        mvwprintw(win->w,1, 2, ">");
        return;
    }


    getyx(win->w, y, x);

    int height  = LINES / 2;
    if (y >= height - 2)
    {
        wscrl(win->w, y - height + 2);
        y = height - 2;
    }
    //char* input = readline("chiventure (enter HELP for help)> ");

    cmd_string = strdup(input);
    //putchar('\n');
    //check whether user input is empty
    if (!strcmp(cmd_string,""))
    {
        return;
    }

    cmd *c = cmd_from_string(cmd_string);
    if (!c)
    {
        shell_error_arg("unrecognized or malformed command: \"%s\"", input);
    //    putchar('\n');
    }
    else
    {
        do_cmd(c,&quit);
        // Add valid input to readline history.
        //add_history(input);
    }

    if (cmd_string)
        free(cmd_string);
    //cmd_free(c);
    //free(input);

    mvwprintw(win->w, y + 1, 2, ">");




}

/* see print_functions.h */
void print_map(window_t* win)
{
    // prints the word map in the window
    mvwprintw(win->w, 1,2, "map");
    return;
}
