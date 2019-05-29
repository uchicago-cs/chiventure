#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parser.h"
#include "shell.h"
#include "cmd.h"
#include "validate.h"
#include "room.h"
#include "item.h"


/*
 *  THIS FILE INCLUDES A SET OF FUNCTIONS THAT VALIDATE A COMMAND
 */


/* See validate.h */
cmd *assign_action(char **ts, lookup_t ** table)
{
    cmd *output = cmd_new(ts);
    output->func_of_cmd = find_operation(ts[0], table);
    if(output->func_of_cmd == NULL) output->func_of_cmd = action_error_operation;
    //HERE WE VALIDATE THE COMMANDS

    return output;
}

/* See validate.h */
bool validate_action(char *tokens[TOKEN_LIST_SIZE], lookup_t ** table)
{
    return true;
}

/* See validate.h */
bool validate_object(char *tokens[TOKEN_LIST_SIZE], game_t * game)
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
bool validate_ind_objects(char *tokens[TOKEN_LIST_SIZE], game_t * game)
{
    //similar to validate_in_objects
    return true;
}

/* See validate.h */
bool validate_filename(char *filename)
{
    int len = strlen(filename);
    if(len < 4)
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
