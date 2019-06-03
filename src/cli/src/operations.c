#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "shell.h"
#include "assert.h"
#include "validate.h"
#include "room.h"

// remove the comment as soon as checkpointing removes their dummy struct
//#include "../../checkpointing/include/save.h"

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
    //Commented out for now until an actual save and load function are provided
    /*  if(tokens[1] == NULL){
        fprintf(stderr,"Save Error, No filename specified. \n");
      }
      if (validate(tokens[1]) == true){
        int sv = save(game, tokens[1]);
    */  return NULL;
}

char *look_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;

    if(tokens[1] == NULL)
    {   
        if(game !=NULL){
            return game->curr_room->long_desc;
        }
        else{
            return "Error !";
        }
    }
    item_t *curr_item = NULL;
    curr_item = get_item_in_room(game->curr_room, tokens[1]);
    if(curr_item != NULL){
        return curr_item->long_desc;
    }
    return "specified item not found\n";
}

//KIND 1:   ACTION <item>
char *kind1_action_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    lookup_t **table = ctx->table;

    if(tokens[1] == NULL)
        {
            return "You must identify an object to act on\n";
        }
    item_t *curr_item;
    curr_item = get_item_in_room(game->curr_room, tokens[1]);
    if (curr_item != NULL)
        {
            action_type_t *action = find_action(tokens[0], table);
            do_item_action(game, action, curr_item);
            return "The object is found\n";
        }
    return "The object could not be found\n";
}

//KIND 2:   ACTION <direction>
char *kind2_action_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    lookup_t **table = ctx->table;

    path_t *curr_path;
    ITER_ALL_PATHS(game->curr_room, curr_path)
    {
        if (strcmp(curr_path->direction,tokens[1]) == 0)
        {
            action_type_t *action = find_action(tokens[0], table);
            do_path_action(game, action, curr_path);
            return "Direction available!\n";
        }
    }
    return "You cannot go in this direction\n";
}

//KIND 3:   ACTION <item> <item>
char *kind3_action_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    lookup_t **table = ctx->table;

    if(tokens[1] == NULL || tokens[3] == NULL)
    {
        return "You must identify two objects to act on";
    }

    item_t *item1, *item2;
    item1 = get_item_in_room(game->curr_room, tokens[1]);
    item2 = get_item_in_room(game->curr_room, tokens[3]);
    
    if(item1 == NULL || item2 == NULL){
        return "The object(s) could not be found";
    }
    action_type_t *action = find_action(tokens[0], table);
    do_item_item_action(game, action, item1, item2);
    return "is an action!";
}


char *action_error_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    return "You cannot perform this action !";
}

char *inventory_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;

    item_t *t;
    int i = 0;
    ITER_ALL_ITEMS_IN_INVENTORY(game->curr_player, t)
    {
        i++;
        print_to_cli(ctx, i);
        print_to_cli(ctx, t->item_id);
        print_to_cli(ctx, t->short_desc);
    }
    return "This was your inventory";
}

//Because action managment does not support NPCs type 4 is not supported
//char *kind4_action_operation(char *tokens[TOKEN_LIST_SIZE], game_t *game)
//{
//    printf("%s\n",tokens[0] );
//    return "is an action!";
//}
