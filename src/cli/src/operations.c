#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "shell.h"
#include "assert.h"
#include "item.h"
#include "validate.h"

char *quit_operation(char *tokens[TOKEN_LIST_SIZE], game_t * game)
{
    return NULL;
}

char *help_operation(char *tokens[TOKEN_LIST_SIZE], game_t * game)
{
    help_text();
    return NULL;
}

char *hist_operation(char *tokens[TOKEN_LIST_SIZE], game_t * game)
{
    print_history();
    return NULL;
}



char *look_operation(char *tokens[TOKEN_LIST_SIZE], game_t * game)
{
    if(tokens[1]==NULL){
        return "room description";
    }
    item_t *i = get_item(tokens[1],NULL);
    if(i == NULL){
        return "specified item not found";
    }
    return "item description";
}


//KIND 1:   ACTION <item>
char *type1_action_operation(char *tokens[TOKEN_LIST_SIZE], game_t * game)
{   
    if(tokens[1]==NULL){
        return "You must identify an object to act on";
    }
    item_t *i = get_item(tokens[1], NULL);
    if(i == NULL){
        return "The object could not be found";
    }
    return "is an action!";
}

//KIND 2:   ACTION <direction>
char *type2_action_operation(char *tokens[TOKEN_LIST_SIZE], game_t * game)
{
    printf("%s\n",tokens[0] );
    return "is a direction action!";
}

//KIND 3:   ACTION <item> <item>

char *type3_action_operation(char *tokens[TOKEN_LIST_SIZE], game_t * game)
{
    if(tokens[1]==NULL || tokens[3]==NULL){
        return "You must identify two objects to act on";
    }
    item_t *i1 = get_item(tokens[1], NULL);
    item_t *i2 = get_item(tokens[3], NULL);
    if(i1 == NULL || i2 == NULL){
        return "The object(s) could not be found";
    }
    return "is an action!";
}


char *action_error_operation(char *tokens[TOKEN_LIST_SIZE], game_t * game){
    return "You cannot perform this action !";
}

char *inventory_operation(char *tokens[TOKEN_LIST_SIZE], game_t * game){
    return "TODO: Inventory operation";
}
//Because action managment does not support NPCs type 4 is not supported
//char *type4_action_operation(char *tokens[TOKEN_LIST_SIZE], game_t * game)
//{
//    printf("%s\n",tokens[0] );
//    return "is an action!";
//}

void create_type1_action(char *tokens[TOKEN_LIST_SIZE], game_t * game) {}
void create_type2_action(char *tokens[TOKEN_LIST_SIZE], game_t * game) {}
void create_type3_action(char *tokens[TOKEN_LIST_SIZE], game_t * game) {}

//void create_type4_action(char *tokens[TOKEN_LIST_SIZE], game_t * game) {}
