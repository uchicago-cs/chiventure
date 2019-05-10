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

/*
*  See validate.h
*/

cmd *assign_action(char **ts){
    cmd *output = cmd_new(ts);
    if(strcmp(ts[0],"QUIT")==0) output->functionofcommand = quit_operation;
    else if(strcmp(ts[0],"HELP")==0) output->functionofcommand = help_operation;
    else if(strcmp(ts[0],"HIST")==0) output->functionofcommand = hist_operation;
    else if(strcmp(ts[0],"LOOK")==0) output->functionofcommand = state_operation;
    else if(strcmp(ts[0],"TAKE")==0) output->functionofcommand = action_operation;
    else if(strcmp(ts[0],"GIVE")==0) output->functionofcommand = action_operation;
    // These are macros defined above. Essentially, just treat them as switch
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


