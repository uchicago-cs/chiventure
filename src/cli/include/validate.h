#ifndef _CLI_INCLUDE_VALIDATE_H_
#define _CLI_INCLUDE_VALIDATE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parser.h"
#include "shell.h"
#include "cmd.h"

/*
 * THIS FILE INCLUDES A SET OF FUNCTIONS THAT VALIDATE A COMMAND 
 */

/*
 * Checks if the action is valid (also needs a list of valid actions as input,
 * to be provided by the action management team). If the input action is valid,
 * this function creates a cmd struct, and assigns the function pointer to the 
 * operation function with the correspnding action type
 *
 * Input:
 *  - ts: parsed command line input (an array of tokens)
 *
 * Returns:
 *  - A cmd struct that contains the given tokens and a pointer to an operation 
 *    function (function selected based on the first token)
 *    
 *    If the action is invalid, assigns the cmd pointer 
 *    to action_error_operation
 */
cmd *assign_action(char **ts);


/*
 * Checks if a given object is in the current room
 *
 * Input:
 *  - c: cmd struct returned by assign_action
 *  - we also need a list of accessible items as input.
 *    This needs to be provided by game state
 *
 * Returns:
 *  - FALSE if the object is not accessible; TRUE if it is.
 *    Additionally, we may set the cmd pointer to an error function
 *    that returns a error message with respect to the type of error
 */
bool validate_object(cmd *c);


/*
 * Checks if an input preposition is valid
 *
 * Input:                                                                                                                      
 *  - c: cmd struct returned by assign_action                                                                                  
 *  - we also need a list of valid actions as input.                                                                        
 *    This needs to be provided by action management
 * 
 * Returns: 
 *  - FALSE if the preposition is invalid; TRUE if it is.
 */
bool validate_prep(cmd *c);


/*
 *  Checks if the specefied indirect object (2nd item) (e.g. NPC) is 
 *  accessible
 *
 * Input:                                                                                                                      
 *  - c: cmd struct returned by assign_action                                                                                  
 *  - we also need a list of accessible items as input.                                                                        
 *    This needs to be provided by game state    
 * Returns:                                                                                                                    
 *  - FALSE if the item is not accessible; TRUE if it is. 
 */
bool validate_ind_objects(cmd *c);

#endif /* _CLI_INCLUDE_VALIDATE_H_ */
