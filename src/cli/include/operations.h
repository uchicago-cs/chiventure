#ifndef _CLI_INCLUDE_OPERATIONS_H
#define _CLI_INCLUDE_OPERATIONS_H
#include "cmd.h"
#include "game.h"
#include "path.h"
#include "actionmanagement.h"

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

/* Some operations take a game struct and a pointer
 * to a look up table even though these parameters are unused.
 * This is to keep the type of operation consistent, since it
 * is used in the lookup_t struct
 */

/*
 * Quits the game
 *
 * Input:
 *  - tokens: parsed input string
 *  - pointer to a chiventure context struct, unused
 *
 * Returns:
 *  - Some system message
 *
 */
char *quit_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);


/* Generate a list of supported operations,
 * Could later be modefied to provide hints
 *
 *  Parameters:
 *  - tokens: parsed input string
 *  - pointer to a chiventure context struct, unused
 * 
 * Returns:
 * - Said list of supported operations as a string
 */
char *help_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);


/*
 * Generates history of commands (print_history() in shell.c needs
 * to be intergrated into this function)
 *
 * Parameters:
 *  - tokens: parsed input string
 *  - pointer to a chiventure context struct, unused
 * 
 * Returns:
 * - Said list of previous actions as a string
 */
char *hist_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);


/*
 * Saves the current state of a game to a .dat file
 * Prints an Error message if filename improperly specified
 *
 * Paramters:
 * - tokens: parsed input string
 * - pointer to a chiventure context struct
 *
 * Returns:
 * - A success or error message
 */
char *save_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);


/*
 * Returns a description of either a specefied item, or the room
 * if no item was specified
 *
 * Parameters:
 *  - tokens: parsed input string
 *  - pointer to a chiventure context struct
 * 
 * Returns:
 * - Said description as a string
 */
char *look_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);


/*Returns a description of the player inventory contents
 *
 * Parameters:
 *  - tokens: parsed input string
 *  - pointer to a chiventure context struct
 * 
 * Returns:
 * - Said description as a string
 */
char *inventory_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);


/* Error Operations that returns an error message as string
 *
 * Parameters:
 *  - tokens: parsed input string
 *  - pointer to a chiventure context struct, unused
 * 
 * Returns:
 * - Said error message as a string
 */
char *action_error_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);


/* Validates an item is in a room, passes an action struct on to
 * action management's function that handles ACTION ITEM
 *
 * Parameters:
 *  - tokens: parsed input string (validified)
 *  - pointer to a chiventure context struct
 * 
 * Returns:
 *  - Said list of supported operations as a string
 */
char *type1_action_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);


/* Validates a path is available in a room, passes an action struct on to
 * action management's function that handles ACTION PATH
 *
 * Parameters:
 *  - tokens: parsed input string (validified)
 *  - pointer to a chiventure context struct
 * 
 * Returns:
 *  - Said list of supported operations as a string
 */
char *type2_action_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);


/* Validates both items are in a room, passes an action struct on to
 * action management's function that handles ACTION ITEM ITEM
 *
 * Parameters:
 *  - tokens: parsed input string (validified)
 *  - pointer to a chiventure context struct
 * 
 * Returns:
 *  - Said list of supported operations as a string
 */
char *type3_action_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);


//char *type4_action_operation(char *tokens[TOKEN_LIST_SIZE], game_t * game);

#endif /* _CLI_INCLUDE_OPERATIONS_H */
