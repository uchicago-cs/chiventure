#ifndef _COMMAND_H
#define _COMMAND_H

#include "game_state_common.h"


typedef struct command_list
{
    char* command;
    struct command_list *next;
} command_list_t;

command_list_t* new_command_list(char* command);

#endif