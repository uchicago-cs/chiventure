#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ctx.h"
#include "game.h"
#include "sample_game.h"
#include "cmd.h"
#include "shell.h"
#include <readline/readline.h>

int main()
{
    chiventure_ctx_t *ctx = chiventure_ctx_new();
    game_t *game = create_sample_game();
    ctx->game = game;
    greet(ctx);
    int quit = 1;
    while (quit)
    {
        // Display prompt and read input
        char *cmd_string = readline("chiventure (enter HELP for help)> ");
	
        
        putchar('\n');
        //check whether user input is empty
        if (!strcmp(cmd_string,""))
            continue;

        cmd *c = cmd_from_string(cmd_string, ctx);
        if (c == NULL)
        {
            shell_error_arg("unrecognized or malformed command: \"%s\"", cmd_string);
            putchar('\n');
        }
        else
        {
            do_cmd(c,&quit, ctx);
            // Add valid input to readline history.
            // add_history(input);
        }

        if (cmd_string)
            free(cmd_string);
        //cmd_free(c);
    }

    lookup_t_free(ctx->table);

    return 0;
}

