#ifndef _CLI_INCLUDE_OPERATIONS_H
#define _CLI_INCLUDE_OPERATIONS_H
#include "cmd.h"
#include "game.h"
#include "path.h"
#include "actionmanagement.h"

typedef struct lookup_t lookup;

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
char *quit_operation(char *tokens[TOKEN_LIST_SIZE], game_t *game, lookup **table);


/* Generate a list of supported operations,
 * Could later be modefied to provide hints
 *
 *  Parameters:
 *  - tokens: parsed input string
 *  - pointer to game to be altered, unused
 * Returns:
 * - Said list of supported operations as a string
 */
char *help_operation(char *tokens[TOKEN_LIST_SIZE], game_t *game, lookup **table);


/*
 * Generates history of commands (print_history() in shell.c needs
 * to be intergrated into this function)
 *
 * Parameters:
 *  - tokens: parsed input string
 *  - pointer to game to be altered, unused
 * Returns:
 * - Said list of previous actions as a string
 */
char *hist_operation(char *tokens[TOKEN_LIST_SIZE], game_t *game, lookup **table);


/*
 * Saves the current state of a game to a .dat file
 * Prints an Error message if filename improperly specified
 *
 * Paramters:
 * - tokens: parsed input string
 * - pointer to game to be saved,
 *
 * Returns:
 * - A success or error message
 */
char *save_operation(char *tokens[TOKEN_LIST_SIZE], game_t *game, lookup **table);

/*
 * Returns a description of either a specefied item, or the room
 * if no item was specified
 *
 * Parameters:
 *  - tokens: parsed input string
 *  - pointer to game to be altered, unused
 * Returns:
 * - Said description as a string
 */
char *look_operation(char *tokens[TOKEN_LIST_SIZE], game_t *game, lookup **table);


/*Returns a description of the player inventory contents
 *
 * Parameters:
 *  - tokens: parsed input string
 *  - pointer to game to be altered, unused
 * Returns:
 * - Said description as a string
 */
char *inventory_operation(char *tokens[TOKEN_LIST_SIZE], game_t *game, lookup **table);


/* Error Operations that returns an error message as string
 *
 * Parameters:
 *  - tokens: parsed input string
 *  - pointer to game to be altered, unused
 * Returns:
 * - Said error message as a string
 */
char *action_error_operation(char *tokens[TOKEN_LIST_SIZE], game_t *game, lookup **table);


/* These functions will generate an action-struct (based on action management)
 * and pass a command along.
 *
 * Parameters:
 * - tokens: parsed input string (validified)
 *  - pointer to game to be altered, unused
 * Returns:
 * - Said list of supported operations as a string
 *
 */
char *type1_action_operation(char *tokens[TOKEN_LIST_SIZE], game_t * game, lookup **table);
char *type2_action_operation(char *tokens[TOKEN_LIST_SIZE], game_t * game, lookup **table);
char *type3_action_operation(char *tokens[TOKEN_LIST_SIZE], game_t * game, lookup **table);
//char *type4_action_operation(char *tokens[TOKEN_LIST_SIZE], game_t * game);

#endif /* _CLI_INCLUDE_OPERATIONS_H */
