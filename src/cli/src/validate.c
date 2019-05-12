#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parser.h"
#include "shell.h"
#include "cmd.h"
#include "validate.h"
#include "../../game-state/include/game.h"

/*
*  THIS FILE INCLUDES A SET OF FUNCTIONS THAT VALIDATE A COMMAND
*/

/* current game - contains information about the current state of game
 * need to talk to game state to figure out how this is obtained */
game_t *curr_game;

/*
*  See validate.h
*/

cmd *assign_action(char **ts){
    cmd *output = cmd_new(ts);
    if(strcmp(ts[0],"QUIT")==0) output->functionofcommand = quit_operation;
    else if(strcmp(ts[0],"HELP")==0) output->functionofcommand = help_operation;
    else if(strcmp(ts[0],"HIST")==0) output->functionofcommand = hist_operation;
    else if(strcmp(ts[0],"OPEN")==0) output->functionofcommand = type1_action_operation;
    else if(strcmp(ts[0],"GO")==0) output->functionofcommand = type2_action_operation;
    else if(strcmp(ts[0],"TALK")==0) output->functionofcommand = type3_action_operation;
    else if(strcmp(ts[0],"GIVE")==0) output->functionofcommand = type4_action_operation;
    // statement cases
    // Add a new one for each new command.
    else {
        output->functionofcommand = action_error_operation;
        }
    //HERE WE VALIDATE THE COMMANDS

    return output;
}

/*
*  See validate.h
*/

bool validate_object(cmd *c){
    //curr_game->curr_room->items // this is a hash table
    return true;
}

/*
*  See validate.h
*/

bool validate_prep(cmd *c){
    return true;
}

/*
*  See validate.h
*/

bool validate_ind_objects(cmd *c){
    return true;
}


