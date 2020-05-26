#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "common/ctx.h"
#include "ui/print_functions.h"
#include "cli/cmd.h"
#include "cli/operations.h"

// approximate length of chiventure banner
#define BANNER_WIDTH (COLS > 100 ? 96 : 78)
#define BANNER_HEIGHT (12)

/* see print_functions.h */
void print_homescreen(window_t *win, const char *banner)
{
    // hides cursor
    curs_set(0);

    // calculate the position of the banner so that is is approximately centered.
    // The -1 in the y position is to give space for the message below the banner
    // x_pos and y_pos indicate the x-y coordinates of the top left corner of the banner
    int x_pos = COLS / 2 - BANNER_WIDTH / 2;
    int y_pos = LINES / 4 - BANNER_HEIGHT / 2 - 1;
    if (x_pos < 0)
    {
        x_pos = 0;
    }

    // runs the animation of the banner (flashes a few times, the last couple a
    // a bit slower). usleep is used to control for how long the banner is on/off
    for (int i = 0; i < 7; i ++)
    {
        int x = x_pos;
        int y = y_pos;
        wclear(win->w);
        box(win->w, 0, 0);

        wrefresh(win->w);



        if (i > 4)
        {
            usleep(600 * 1000);
        }
        else
        {
            usleep(100 * 1000);
        }

        int len = strlen(banner);
        char temp[len];
        strcpy(temp, banner);
        char *str = strtok(temp, "\n");

        while (str != NULL)
        {
            mvwprintw(win->w, y, x, str);
            str = strtok(NULL, "\n");
            y++;
        }
        box(win->w, 0, 0);

        wrefresh(win->w);



        if (i > 3)
        {
            usleep(600 * 1000);
        }
        else
        {
            usleep(100 * 1000);
        }
        if (i == 6)
        {
            y_pos = y;
        }

    }
    usleep(1000 * 1000);

    char help[] = "Type 'HELP' to show help menu";
    // similarly, as above, calculates where to place the message so it's centered
    int help_x_pos = COLS /2 - strlen(help) / 2;

    mvwprintw(win->w, y_pos + 2, help_x_pos, help);

    curs_set(1);
}

void print_banner(window_t *win, const char *banner)
{
    // calculate the position of the banner so that is is approximately centered.
    // The -1 in the y position is to give space for the message below the banner
    // x_pos and y_pos indicate the x-y coordinates of the top left corner of the banner
    int x_pos = COLS / 2 - BANNER_WIDTH / 2;
    int y_pos = LINES / 4 - BANNER_HEIGHT / 2 - 1;
    if (x_pos < 0)
    {
        x_pos = 0;
    }

    int x = x_pos;
    int y = y_pos;

    int len = strlen(banner);
    char temp[len];
    strcpy(temp, banner);
    char *str = strtok(temp, "\n");

    while (str != NULL)
    {
        mvwprintw(win->w, y, x, str);
        str = strtok(NULL, "\n");
        y++;
    }
}

/* see print_functions.h */
void print_info(chiventure_ctx_t *ctx, window_t *win)
{
    mvwprintw(win->w, 1, 2, "Main Window");
}

/* Wrapper for print_to_cli that can be used as a
 * callback function when calling do_cmd.
 *
 * This function conforms to the cli_callback type
 * (see that type for more details) */
int cli_ui_callback(chiventure_ctx_t *ctx, char *str, void *args)
{
    if(print_to_cli(ctx, str) == EXIT_SUCCESS)
    {
        return CLI_CMD_SUCCESS;
    }
    else
    {
        return CLI_CMD_CALLBACK_ERROR;
    }
}

/* see print_functions.h */
void print_cli(chiventure_ctx_t *ctx, window_t *win)
{
    static bool first_run = true;
    int x, y;
    getyx(win->w, y, x);

    if (first_run)
    {
        first_run = false;
        mvwprintw(win->w, y + 1, 2, "> ");
        return;
    }
    echo();

    char input[80];
    char *cmd_string;
    wgetnstr(win->w, input, 80);

    noecho();
    cmd_string = strdup(input);

    if (!strcmp(cmd_string, ""))
    {
        return;
    }

    cmd *c = cmd_from_string(cmd_string, ctx);
    if (!c)
    {
        print_to_cli(ctx, "Error: Malformed input (4 words max)");
    }
    else
    {
        int rc = do_cmd(c, cli_ui_callback, NULL, ctx);
    }

    /* Note: The following statement should be replaced by a logging function
     * in order to properly implement the HIST command. Should take about
     * half an hour, tops for someone who's experienced.
     */
    if (cmd_string)
    {
        free(cmd_string);
    }
    getyx(win->w, y, x);

    // scrolls the screen up if there is no space to print the next line
    int height = LINES / 2;
    if (y >= height - 2)
    {
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
int print_to_cli(chiventure_ctx_t *ctx, char *str)
{
    int x, y, height;
    static bool first_run = true;

    height = LINES / 2;

    WINDOW *cli = ctx->ui_ctx->cli_win->w;

    int len = strlen(str);
    char temp[len];
    strcpy(temp, str);
    char *tmp = strtok(temp, "\n");

    getyx(cli, y, x);

    // scrolls the screen up if there is no space to print the first line of output
    if (y >= height - 1)
    {
        wscrl(cli, y - height + 2);
        y = height - 2;
    }

    while (tmp != NULL)
    {
        if(first_run)
        {
            mvwprintw(cli, y + 1, 3, tmp);
            first_run = false;
        }
        else
        {
            mvwprintw(cli, y, 3, tmp);
        }
        tmp = strtok(NULL, "\n");

        getyx(cli, y, x);
        y++;

        // if there is no space to print the next line, instruction to press ENTER
        // to see more or q to continue is given,
        if (y >= height - 1 && tmp != NULL)
        {
            mvwprintw(cli, y, 3, "Press ENTER to see more, 'q' to continue");
            int ch;

            while ((ch = wgetch(cli)) != '\n' && ch != 'q')
            {
                /* wait until enter is pressed or q are pressed */
            }

            wmove(cli, y, 2);
            wclrtoeol(cli);
            if (ch == 'q')
            {
                return EXIT_SUCCESS;
            }
            // sets the cursor to the begining of the line just printed
            // ("Press ENTER to see more, 'q' to continue"), and then clears it



            // scrolls the screen up
            wscrl(cli, y - height + 2);
            y = height - 2;


        }

    }

    getyx(cli, y, x);
    wmove(cli, y+1, 2);

    return EXIT_SUCCESS;
}

