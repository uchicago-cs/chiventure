#ifndef _COMMAND_H
#define _COMMAND_H

#include "game_state_common.h"


/* 
 * The linked list is built to contain the command history
 * of a user during a certain round
 */
typedef struct command_list
{
    char* command;
    struct command_list *next;
} command_list_t;


/* 
 * Creates a new command list stuct 
 * sets the command, and sets the next command to NULL
 */
command_list_t* new_command_list(char* command);

#endif