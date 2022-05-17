#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

#include "cli/operations.h"
#include "npc/npc.h"
#include "npc/dialogue.h"
#include "ui/print_functions.h"
#include "cli/shell.h"
#include "wdl/load_game.h"
#include "libobj/load.h"
#include "cli/cmdlist.h"
#include "cli/util.h"

#define NUM_ACTIONS 30
#define BUFFER_SIZE (100)
#define min(x,y) (((x) <= (y)) ? (x) : (y))

char* actions_for_sug[NUM_ACTIONS] = {"OPEN", "CLOSE", "PUSH", "PULL", "TURNON", "TURNOFF", 
                        "TAKE", "PICKUP", "DROP","CONSUME","USE","DRINK",
                        "EAT", "GO", "WALK", "USE_ON", "PUT", "QUIT","HIST", "HELP",
                        "CREDITS", "LOOK", "INV", "MAP", "SWITCH", "LOAD_WDL", "NAME", 
                        "PALETTE", "ITEMS", "VIEW"};


/* 
 * This function returns a integer 
 * which is the number of matching letters 
 * between the user input and action
 * 
 */
int compare(char* word, char* action)
{

    int current = 0;
    for (int i = 0; i < min(strlen(word), strlen(action)); i++)
    {
        if (&action[i] != NULL && &word[i] != NULL) 
        {
            if (tolower(word[i]) == tolower(action[i]))
            {
                current++;
            }
        }

    }

    return current;
}

/* 
 * This function returns a string which is the suggestion
 * It finds the suggestion by comparing 
 * each possible action to the input
 * using the compare helper function
 * 
 */
char* suggestions(char *action_input, char** actions)
{
    int i = 0;
    int initial = 0;
    int temp = 0;
    int index = -1;
    
    for (int i = 0; i < NUM_ACTIONS; i++)
    {
        if (action_input != NULL) 
        {
            temp = compare(strdup(action_input), strdup(actions[i]));
            if (temp > initial) 
            {
                index = i;
                initial = temp;
            }
        }
    }
    
    if (index == -1) 
    {
        return NULL;
    }

    return actions[index];

}



char *credits_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    return "Class of CMSC 22000 Spring 2019\n   Class of CMSC 22000 Spring 2020\n   Class of CMSC 22000 Spring 2021\n   Class of CMSC 22000 Spring 2022\n";
}

char *quit_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    return NULL;
}

char *help_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    help_text(ctx);
    return NULL;
}

char *hist_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    command_list_t *temp = new_command_list(NULL);

    print_to_cli(ctx, "Start of command history: \n");
    LL_FOREACH(ctx->cli_ctx->command_history, temp)
    {
        if (temp->command != NULL) 
        {
            print_to_cli(ctx, temp->command);
        }
    } 
    return "End of command history.\n";
}


bool validate_wdl_filename(char *filename)
{
    int len = strlen(filename);
    int min_filename_length = 4;
    int file_extension_length = 4;
    if (len < min_filename_length)
    {
        return false;
    }
    const char *ending = &filename[len - file_extension_length];
    int cmp = strcmp(ending, ".wdl");
    if (cmp == 0)
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
    int valid_path;

    valid_path = access(tokens[1], F_OK);

    if (valid_path == -1) //Triggers if file does not exist
    {
        return "Loading WDL file failed: Invalid Input for file path\n";
    }
    if ((validate_wdl_filename(tokens[1])) == false) //Triggers if file is not wdl
    {
        return "Loading WDL file failed: Invalid Input, please only use wdl file types\n";
    }

    obj_t *obj_store = load_obj_store(tokens[1]);

    game_t *game = load_game(obj_store);

    if (game == NULL)
    {
        return "Load WDL failed!";
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

/* See operation.h */
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
        char *string = malloc(BUFFER_SIZE);
        sprintf(string, "%s", curr_item->long_desc);
        if (curr_item->next != NULL)
        {
            int count = 0;
            item_t *iter;
            LL_FOREACH(curr_item, iter)
            {
                count++;
            }
            char *count_str = malloc(BUFFER_SIZE);
            sprintf(count_str, " There are %d of these in this room.", count);
            string = strcat(string, count_str);
        }
        return string;
    }
    return "specified item not found\n";
}

/* See operation.h */
char *kind4_action_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    //expecting token string list to be "view" "arg2"
    //support for each arg2 to be specified (as of 5/2/2022)
    game_t *game = ctx->game;
    char *arg2 = tokens[1];
    if(game == NULL)
    {
        //return "No game found!\n";
        return "game null";
    }
    if(arg2 == NULL)
    {
        //return "Second argument needed. Pick from: TODO: [LIST OF WANTED SECOND ARGUMENTS HERE]\n";
        return "arg2 null";
    }
    /* checking if there is more than one argument
     * for now this returns null, but if actions wants any kind4 to have 
     * more than 1 argument, this check can be removed and onus transfers
     * to action management's `do_self_action()` command */
    if(tokens[2] != NULL)
    {
        //return "Sorry, only one page can be viewed at a time :(\n";
        return "arg3 not null";
    }

    lookup_t **table = ctx->cli_ctx->table;

    /* uses the find_action command to go from string to action,
     * this table is made using the add_action_entry and lookup_t_init 
     * in cmd.c*/
    //action_type_t *action = find_action(tokens[0], table);

    /* placeholder for error string that do_self_action will modify */
    //char *str;
        
    //TODO add description here of what the return codes mean
    //int rc = do_self_action(ctx, action, curr_item, arg2, &str);
    //return str;
    return "normal";

    /* ALL OF THE BELOW IS NOW HANDLED BY ACTION_MANAGEMENT 
     * and is thus defunct
     * This is to be removed once the kind4 actions work as expected on dev
     * (5/16/2022) - faruk badur
    pass into the do_self_action
    if(strcmp(arg2,"stats") == 0)
    {
        //TODO: Ask action management what they want to happen, 
        //as they likely want to call some other function.
        return "Second argument was \"stats\"";
    }
    if(strcmp(arg2,"advanced") == 0)
    {
        //TODO: Ask action management what they want to happen, 
        //as they likely want to call some other function.
        return "Second argument was \"advanced\"";
    }
    //all possible options should have been matched before this
    return "Invalid second argument\n";
    */
}

/* See operation.h */
char *exit_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    //expecting token string list to be "exit" "arg2"
    //support for each arg2 to be specified (as of 5/2/2022)
    game_t *game = ctx->game;
    char *arg2 = tokens[1];
    if(game == NULL)
    //TODO look exactly what the game pointer being NULL means
    {
        return "No game found!\n";
    }
    if(arg2 == NULL)
    {
        return "Second argument needed. Pick from: [LIST OF WANTED SECOND ARGUMENTS HERE]\n";
    }
    if(strcmp(arg2,"stats") == 0)
    {
        //TODO: Ask action management what they want to happen, 
        //as they likely want to call some other function.

        // If the user exits stats, the GUI function that
        // removes the stats from the screen should be called.
        return "Second argument was \"stats\"";
    }
    if(strcmp(arg2,"advanced") == 0)
    {
        //TODO: Ask action management what they want to happen, 
        //as they likely want to call some other function.

        // If the user exits advanced, the GUI function that
        // removes the advanced stats from the screen should be called.
        return "Second argument was \"advanced\"";
    }
    //all possible options should have been matched before this
    return "Invalid second argument\n";
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
    lookup_t **table = ctx->cli_ctx->table;

    if(tokens[1] == NULL)
    {
        return "You must identify an object to act on\n";
    }
    if(tokens[2] != NULL)
    {
        return "Sorry, act upon one item \n";
    }
    item_t *curr_item;
    curr_item = get_item_in_room(game->curr_room, tokens[1]);
    if(curr_item != NULL)
    {
        action_type_t *action = find_action(tokens[0], table);
        char *str;
        bool action_success = false;
        
        /* Loops through items with identical ids 
         * until action success or all items fail */
        while (!action_success && curr_item != NULL)
        {
            int rc = do_item_action(ctx, action, curr_item, &str);
            if (rc == SUCCESS)
            {
                action_success = true;
                if(strcmp(tokens[0], "take") == 0 || strcmp(tokens[0], "pickup") == 0)
                {
                    remove_item_from_room(game->curr_room, curr_item);
                    add_item_to_player(game->curr_player, curr_item);
                }
            }
            curr_item = curr_item->next;
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
    lookup_t **table = ctx->cli_ctx->table;

    if(tokens[1] == NULL)
    {
        return "You must specify a direction to go \n";
    }
    if(tokens[2] != NULL)
    {
        return "Sorry, you can only go one direction \n";
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
    lookup_t **table = ctx->cli_ctx->table;

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
    bool action_success = false;
    
    /* Loops through items with identical ids 
     * until action succeeds or all items fail */
    while (!action_success && item1 != NULL)
    {
        item_t *item2_iter = item2;
        while (!action_success && item2_iter != NULL)
        {
            int rc = do_item_item_action(ctx, action, item1, item2_iter, &str);
            if (rc == SUCCESS)
            {
                action_success = true;
            }
            item2_iter = item2_iter->next;
        }
        item1 = item1->next;
    }
    
    return str;
}



char *action_error_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{

    if (tokens[0] == NULL) 
    {
        return "This input returned as NULL";
    }

    char* suggestion = NULL;
    suggestion = suggestions(strdup(tokens[0]), actions_for_sug);

    if (suggestion != NULL) 
    {
        int str1 = strlen(suggestion);
        int str2 = strlen("This action is not supported. Did you mean: ");
        int len = str1 + str2;
        char msg[] =  "This action is not supported. Did you mean: ";
        print_to_cli(ctx, strncat(msg, suggestion, len));
        return "";
    }
    return "This action is not supported. No suggestions could be found";
}

char *inventory_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if(game == NULL || game->curr_player == NULL)
    {
        print_to_cli(ctx, tokens[0]);
        return "Error! We need a loaded player to check inventory.\n";
    }
    item_list_t *t;
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

        print_to_cli(ctx, t->item->item_id);
    }
    return "This was your inventory";
}


char *items_in_room_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if(game == NULL || game->curr_room == NULL)
    {
        print_to_cli(ctx, tokens[0]);
        return "Error! We need a loaded room to check items.\n";
    }
    item_list_t *t;
    int i = 0;
    ITER_ALL_ITEMS_IN_ROOM(game->curr_room, t)
    {
        i++;
        print_to_cli(ctx, t->item->item_id);
    }
    return "These are the items in the room";
}


char *npcs_in_room_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if(game == NULL || game->curr_room == NULL)
    {
        print_to_cli(ctx, tokens[0]);
        return "Error! We need a loaded room to check NPCs.\n";
    }

    npc_t *npc_tmp, *npc_elt;
    int i = 0;
    HASH_ITER(hh, game->curr_room->npcs->npc_list, npc_elt, npc_tmp) 
    {   
        i++;
        if (npc_elt->npc_battle->health > 0) 
        {
            print_to_cli(ctx, npc_elt->npc_id);
        }
    }

    if (i >= 1) 
    {
        return "These are the NPCs in the room";
    } 
    else 
    {
        return "There is no NPC in the room";
    }
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


char *name_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    case_insensitize(tokens[1]);
    case_insensitize(tokens[2]);
    if(find_entry(tokens[1], (ctx->cli_ctx->table)) == NULL)
    {
        return "New words must be defined using only words that are already defined!";
    }
    if(find_entry(tokens[2],(ctx->cli_ctx->table)) != NULL)
    {
        return "You can't change the meaning of a word that's already defined!";
    }
    add_entry(tokens[2],(find_operation(tokens[1],(ctx->cli_ctx->table))), (find_action(tokens[1],(ctx->cli_ctx->table))), (ctx->cli_ctx->table));
    return "The two words are now synonyms!";
}

char *palette_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    int n = 0;
    if (tokens[1] == NULL)
    {
        return "Please input a theme";
    }
    case_insensitize(tokens[1]);
    if(strcmp(tokens[1], "default") == 0)
    {
        n = 1;
    }
    if(strcmp(tokens[1], "night") == 0)
    {
        n = 2;
    }
    if(strcmp(tokens[1], "bright") == 0)
    {
        n = 3;
    }
    if(strcmp(tokens[1], "pain") == 0)
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

/* See cmd.h */
char *talk_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    if (tokens[1] == NULL || tokens[2] == NULL)
    {
        return "You must identify an NPC to talk to.";
    }

    int rc;

    npc_t *npc = get_npc_in_room(ctx->game->curr_room, tokens[2]);

    if (npc == NULL)
    {
        return "No one by that name wants to talk.";
    }

    if (npc->dialogue == NULL)
    {
        return "This person has nothing to say.";
    }

    char *str = start_conversation(npc->dialogue, &rc, ctx->game);

    assert(rc != -1); //checking for conversation error

    if (rc == 0)
    {
        set_game_mode(ctx->game, CONVERSATION, npc->npc_id);
    }

    return str;
}
