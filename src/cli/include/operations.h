#ifndef _CLI_INCLUDE_OPERATIONS_H
#define _CLI_INCLUDE_OPERATIONS_H
#include "cmd.h"

/*
 * We list all demanded operations over here.
 * All meta operations must be defined here.
 * Later on, we can support other operations
 * within similar types, as in a general action operation
 * that feeds the right type of command to action management
 */

/* Operation data type
 * typedef char * operation(char * tokens[TOKEN_LIST_SIZE]);
 * The type is listed here for convenience, but for compiler
 * niceness, it is in cmd.h.
 */

/*
 * Quits the game
 *
 * Input:
 *  - tokens: parsed input string
 *
 * Returns:
 *  - Some system message
 *
 * Note that this command literally does nothing right now.
 */
char *quit_operation(char *tokens[TOKEN_LIST_SIZE]);


/* 
 * Prints out a help menu (help_text() in shell.c needs to be intergrated
 * into this function) 
 */
char *help_operation(char *tokens[TOKEN_LIST_SIZE]);


/*                                                                                                                             
 * Prints out a history of commands (print_history() in shell.c needs 
 * to be intergrated into this function)
 */  
char *hist_operation(char *tokens[TOKEN_LIST_SIZE]);


/*
 * The functions below take in a validated parsed command, package the 
 * command into structs that can be passed onto the corresponding action 
 * functions provided by the action management team.
 *
 * Will be further clarified. 
 *
 */
char *type1_action_operation(char *tokens[TOKEN_LIST_SIZE]);
char *type2_action_operation(char *tokens[TOKEN_LIST_SIZE]);
char *type3_action_operation(char *tokens[TOKEN_LIST_SIZE]);
char *type4_action_operation(char *tokens[TOKEN_LIST_SIZE]);


/* 
 * Prints the operation and tells the user that it was not recognised
 */
char *action_error_operation(char *tokens[TOKEN_LIST_SIZE]);


/* 
 * Prints the object and tells the user that it was not recognised
 */
char *object_error_operation(char *tokens[TOKEN_LIST_SIZE]);


/* 
 * Prints the input action and tells the user that it was not recognised
 */
char *prep_error_operation(char *tokens[TOKEN_LIST_SIZE]);


/*                                                                                                                             
 * Prints the second input item and tells the user 
 * that it was not recognised                                                          
 */   
char *ind_object_error_operation(char *tokens[TOKEN_LIST_SIZE]);

// Put more operations here!

#endif /* _CLI_INCLUDE_OPERATIONS_H */
