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
