#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parser.h"
#include "shell.h"
#include "cmd.h"
#include "validate.h"

/*
 *  THIS FILE INCLUDES A SET OF FUNCTIONS THAT VALIDATE A COMMAND
 */

/* Forward declaration. Need to collaborate with game state */
// game_t *curr_game;
bool is_in_room(char *object);

/* See validate.h */
cmd *assign_action(char **ts)
{
    cmd *output = cmd_new(ts);
    if(strcmp(ts[0],"QUIT")==0) output->func_of_cmd = quit_operation;
    else if(strcmp(ts[0],"HELP")==0) output->func_of_cmd = help_operation;
    else if(strcmp(ts[0],"HIST")==0) output->func_of_cmd = hist_operation;
    else if(strcmp(ts[0],"OPEN")==0) output->func_of_cmd = type1_action_operation;
    else if(strcmp(ts[0],"GO")==0) output->func_of_cmd = type2_action_operation;
    else if(strcmp(ts[0],"TALK")==0) output->func_of_cmd = type3_action_operation;
    else if(strcmp(ts[0],"GIVE")==0) output->func_of_cmd = type4_action_operation;
    // statement cases
    // Add a new one for each new command.
    else
    {
        output->func_of_cmd = action_error_operation;
    }
    //HERE WE VALIDATE THE COMMANDS

    return output;
}

/* See validate.h */
bool validate_object(cmd *c)
{

    return true;
}

/* See validate.h */
bool validate_prep(cmd *c)
{
    //Once the commands are finalized we can match the preposition with the command,
    // talk to, vs talk from, take from, vs take to. give from vs give to.
    return true;
}

/* See validate.h */
bool validate_ind_objects(cmd *c)
{
    //similar to validate_in_objects
    return true;
}
