#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parser.h"
#include "shell.h"
#include "cmd.h"

/*
*  THIS FILE INCLUDES A SET OF FUNCTIONS THAT VALIDATE A COMMAND
*/

/*
*  assign_action(), checks if the action is valid, and assigns the function pointer cmd
*/

cmd *assign_action(char **ts);

/*
*  validate object, checks if object is in room and whether or not the action is applicable to that object
*/

bool validate_object(cmd *c);

/*
*  validate preposition
*/

bool validate_prep(cmd *c);

/*
*  validate_ind_object checks if the specefied indirect object (e.g. NPC) is accesible, and if action is applicable
*/

bool validate_ind_objects(cmd *c);
