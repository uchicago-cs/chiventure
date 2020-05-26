#include <string.h>
#include <ctype.h>

#include "cli/operations.h"
#include "ui/print_functions.h"
#include "cli/shell.h"
#include "wdl/load_game.h"


char *quit_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    return NULL;
}

char *help_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    help_text(ctx);
    return NULL;
}

/* backlog task */
char *hist_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    //print_history();
    return "history operation not implemented yet\n";
}

/* See operations.h */
char *save_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    if (tokens[1] == NULL)
    {
        return "Invalid Input, Save failed\n";
    }
    if (validate_filename(tokens[1]) == true)
    {
        int sv = save(ctx->game, tokens[1]);
        return "Game Saved\n";
    }
    else
    {
        return "Improper filename, Save failed\n";
    }
}

char *load_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    if(tokens[1] == NULL)
    {
        return "Invalid Input, Load failed\n";
    }
    if (validate_filename(tokens[1]) == true)
    {
        int ld = load(tokens[1], ctx->game);
        return "Load Successful\n!";
    }
    else
        return "Improper filename, Load failed\n";

}

bool validate_filename(char *filename)
{
    int len = strlen(filename);
    int min_filename_length = 4;
    if(len < min_filename_length)
    {
        return false;
    }
    const char *ending = &filename[len-4];
    int cmp = strcmp(ending, ".dat");
    if(cmp == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

char *load_wdl_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    if(tokens[1] == NULL)
    {
        return "Invalid Input, Loading WDL file failed\n";
    }

    game_t *game = load_wdl(tokens[1]);
    if(game == NULL)
    {
        return "Load WDL failed";
    }
    else
    {
        ctx->game = game;
        return "Load WDL succeeded!";
    }
}

/* See operation.h */
cmd *assign_action(char **ts, lookup_t ** table)
{
    cmd *output = cmd_new(ts);
    output->func_of_cmd = find_operation(ts[0], table);
    if(output->func_of_cmd == NULL)
    {
        output->func_of_cmd = action_error_operation;
    }
    return output;
}

char *look_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if(game == NULL || game->curr_room == NULL)
    {
        return "Room not found! Error! We need a room to be loaded to LOOK!\n";
    }
    if(tokens[1] == NULL)
    {
        if(game != NULL)
        {
            return game->curr_room->long_desc;
        }
        else
        {
            return "Error !";
        }
    }
    item_t *curr_item = NULL;
    curr_item = get_item_in_room(game->curr_room, tokens[1]);
    if(curr_item != NULL)
    {
        return curr_item->long_desc;
    }
    return "specified item not found\n";
}

//KIND 1:   ACTION <item>
char *kind1_action_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if(game == NULL || game->curr_room == NULL)
    {
        print_to_cli(ctx, tokens[0]);
        return ( "Error! We need a loaded room to do the above action. \n");
    }
    lookup_t **table = ctx->table;

    if(tokens[1] == NULL)
    {
        return "You must identify an object to act on\n";
    }
    item_t *curr_item;
    curr_item = get_item_in_room(game->curr_room, tokens[1]);
    if(curr_item != NULL)
    {
        action_type_t *action = find_action(tokens[0], table);
        char *str;
        do_item_action(ctx, action, curr_item, &str);
        if(strcmp(tokens[0], "TAKE") == 0)
        {
            HASH_DEL(game->curr_room->items, curr_item);
            add_item_to_player(game->curr_player, curr_item);

        }
        return str;
    }
    return "The object could not be found\n";
}

//KIND 2:   ACTION <direction>
char *kind2_action_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if(game == NULL || game->curr_room == NULL)
    {
        print_to_cli(ctx, tokens[0]);
        return "Error! We need a loaded room to do the above action. \n";
    }
    lookup_t **table = ctx->table;

    if(tokens[1] == NULL)
    {
        return "You must specify a direction to go \n";
    }

    path_t *curr_path;
    ITER_ALL_PATHS(game->curr_room, curr_path)
    {
        if(strcmp(curr_path->direction,tokens[1]) == 0)
        {
            action_type_t *action = find_action(tokens[0], table);

            char *str;
            do_path_action(ctx, action, curr_path, &str);
            return str;
        }
    }
    return "You cannot go in this direction\n";
}

//KIND 3:   ACTION <item> <item>
char *kind3_action_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if(game == NULL || game->curr_room == NULL)
    {
        print_to_cli(ctx, tokens[0]);
        return "Error! We need a loaded room to do the above action. \n";
    }
    lookup_t **table = ctx->table;

    if(tokens[1] == NULL || tokens[3] == NULL)
    {
        return "You must identify two objects to act on";
    }

    item_t *item1, *item2;
    item1 = get_item_in_room(game->curr_room, tokens[1]);
    item2 = get_item_in_room(game->curr_room, tokens[3]);

    if(item1 == NULL || item2 == NULL)
    {
        return "The object(s) could not be found";
    }
    action_type_t *action = find_action(tokens[0], table);

    char *str;
    do_item_item_action(ctx, action, item1, item2, &str);
    return str;
}


char *action_error_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    return "This action is not supported.";
}

char *inventory_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if(game == NULL || game->curr_player == NULL)
    {
        print_to_cli(ctx, tokens[0]);
        return "Error! We need a loaded player to check inventory.\n";
    }
    item_t *t;
    int i = 0;
    ITER_ALL_ITEMS_IN_INVENTORY(game->curr_player, t)
    {
        i++;

        //To print an integer with print_to_cli, int i must be cast to a string
        //10 was chosen as a buffer, i should not need all 10 bytes

        //Commenting the code that prints what item number the loop is on for now, if this functionality
        //is useful in the future it can be uncommented

        // int strbuff = 10;
        // char str[strbuff];
        // sprintf(str, "%d", i);
        // print_to_cli(ctx, str);

        print_to_cli(ctx, t->item_id);
    }
    return "This was your inventory";
}

char *map_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    toggle_map(ctx);
    return "Map toggled.";
}

char *switch_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    layout_switch(ctx);
    return "Layout switched.";
}

/* A function that capitalizes a word to be used in name_operation
 * Parameters:
 * - word: A pointer to a string to be capitalized.
 * Output:
 * - The newly capitalized string.
*/
char *capitalize(char *word)
{
    char *command = word;
    int i = 0;
    char ch;

    while(command[i])
    {
        ch = toupper(command[i]);
        command[i] = ch;
        i++;
    }
    return word;
}

char *name_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    capitalize(tokens[1]);
    capitalize(tokens[2]);
    if(find_entry(tokens[1], (ctx->table)) == NULL)
    {
        return "New words must be defined using only words that are already defined!";
    }
    if(find_entry(tokens[2],(ctx->table)) != NULL)
    {
        return "You can't change the meaning of a word that's already defined!";
    }
    add_entry(tokens[2],(find_operation(tokens[1],(ctx->table))), (find_action(tokens[1],(ctx->table))), (ctx->table));
    return "The two words are now synonyms!";
}

char *palette_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    int n = 0;
    if (tokens[1] == NULL)
    {
        return "Please input a theme";
    }
    capitalize(tokens[1]);
    if(strcmp(tokens[1], "DEFAULT") == 0)
    {
        n = 1;
    }
    if(strcmp(tokens[1], "NIGHT") == 0)
    {
        n = 2;
    }
    if(strcmp(tokens[1], "BRIGHT") == 0)
    {
        n = 3;
    }
    if(strcmp(tokens[1], "PAIN") == 0)
    {
        n = 4;
    }
    if(n != 0)
    {
        wbkgd(ctx->ui_ctx->cli_win->w, COLOR_PAIR(n));
        wbkgd(ctx->ui_ctx->displayed_win->w, COLOR_PAIR(n));
        wbkgd(ctx->ui_ctx->map->pad, COLOR_PAIR(n));
        return "The color palette has been changed";
    }
    return "I don't have that palette yet. You must make do with the current style.";
}
