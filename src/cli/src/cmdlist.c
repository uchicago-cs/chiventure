#include <stdlib.h>
#include <string.h>

#include "cli/cmdlist.h"

/* See cli/cmdlist.h for further documentation */
command_list_t *new_command_list(char* command)
{
    command_list_t *new = malloc(sizeof(command_list_t));

    if (command == NULL) 
    {
        new->command = NULL;
    } else {
        new->command = strdup(command);
    }
    
    new->next = NULL;
    return new;
}