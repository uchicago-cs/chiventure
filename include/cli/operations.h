#ifndef _CLI_INCLUDE_OPERATIONS_H
#define _CLI_INCLUDE_OPERATIONS_H
#include "cmd.h"
#include "game-state/game.h"
#include "game-state/mode.h"
#include "action_management/actionmanagement.h"
#include "ui/print_functions.h"
#include "checkpointing/save.h"
#include "checkpointing/load.h"

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
 * Displays course authors of chiventure
 *
 * Input:
 *  - tokens: parsed input string
 *  - ctx: pointer to a chiventure context struct, unused
 *
 * Returns:
 *  - system message listing contributors
 *
 */
char *credits_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);


/*
 * Quits the game
 *
 * Input:
 *  - tokens: parsed input string
 *  - ctx: pointer to a chiventure context struct, unused
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
 *  - ctx: pointer to a chiventure context struct, unused
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
 *  - ctx: pointer to a chiventure context struct, unused
 *
 * Returns:
 * - Said list of previous actions as a string
 */
char *hist_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);

/*
 * Loads a new game from a .wdl file
 * Prints and Error message if filename improperly specified
 *
 * Parameters:
 * - tokens: parsed input string
 * - ctx: pointer to a chiventure context struct
 *
 * Returns: 
 * - A success or error message
 */
char *load_wdl_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);

/* Checks that a specified filetype is a .wdl file
 *
 * Parameters:
 * - A string of the filename
 *
 *
 * Returns:
 * - true if proper filename, false if not
 */
bool validate_wdl_filename(char *filename);

/*
 * If the input action is valid (checks by calling validate_action), go through
 * the hashtable again to find the corresponding operation and creates a cmd struct
 *
 * Input:
 *  - ts: parsed command line input (an array of tokens)
 *  - table: hashtable that stores all supported actions
 *
 * Returns:
 *  - A cmd struct that contains the given tokens and a pointer to an operation
 *    function (function selected based on the first token)
 *
 *    If the action is invalid, assigns the cmd pointer
 *    to action_error_operation
 */
cmd *assign_action(char *ts[TOKEN_LIST_SIZE], lookup_t **table);

/*
 * Returns a description of either a specefied item, or the room
 * if no item was specified
 *
 * Parameters:
 *  - tokens: parsed input string
 *  - ctx: pointer to a chiventure context struct
 *
 * Returns:
 * - Said description as a string
 */
char *look_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);

/*Returns a description of the player inventory contents
 *
 * Parameters:
 *  - tokens: parsed input string
 *  - ctx: pointer to a chiventure context struct
 *
 * Returns:
 * - Said description as a string
 */
char *inventory_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);


/* 
 *
 * Parameters:
 *  - tokens: parsed input string
 *  - ctx: pointer to a chiventure context struct
 *
 * Returns:
 * - lists items that are in the room a player 
 * is currently in as a list
 */
char *items_in_room_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);


/* 
 *
 * Parameters:
 *  - tokens: parsed input string
 *  - ctx: pointer to a chiventure context struct
 *
 * Returns:
 * - lists NPCs that are in the room a player 
 * is currently in as a list
 */
char *npcs_in_room_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);


/* Error Operations that returns an error message with suggestion as string
 *
 * Parameters:
 *  - tokens: parsed input string
 *  - ctx: pointer to a chiventure context struct, unused
 *
 * Returns:
 * - Said error message with suggestion as a string
 */
char *action_error_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);

/* 
 * This function returns a string which is a suggestion 
 * obtained from comparing the input command with a list
 * of actual commands. This is found by using the Levenshtein's Distance formula, 
 * a fuzzy search mechanism to evaluate word similarity. More details linked here:
 * https://en.wikipedia.org/wiki/Levenshtein_distance
 *
 * Parameters:
 *  - action_input: parsed input command (a string)
 *  - actions: the actions_for_sug array that is globally defined 
 *    here is what the suggestions function is called with currently
 *    but any array of words to suggest would do.
 *
 * Returns:
 *  - a string suggestion, which is a word from the actions array
 */
char* suggestions(char *action_input, char** actions);

/* Validates an item is in a room, passes an action struct on to
 * action management's function that handles ACTION ITEM
 *
 * Parameters:
 *  - tokens: parsed input string (validified)
 *  - ctx:pointer to a chiventure context struct
 *
 * Returns:
 *  - Said list of supported operations as a string
 */
char *kind1_action_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);


/* Validates a path is available in a room, passes an action struct on to
 * action management's function that handles ACTION PATH
 *
 * Parameters:
 *  - tokens: parsed input string (validified)
 *  - ctx: pointer to a chiventure context struct
 *
 * Returns:
 *  - Said list of supported operations as a string
 */
char *kind2_action_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);


/* Validates both items are in a room, passes an action struct on to
 * action management's function that handles ACTION ITEM ITEM
 *
 * Parameters:
 *  - tokens: parsed input string (validified)
 *  - ctx: pointer to a chiventure context struct
 *
 * Returns:
 *  - Said list of supported operations as a string
 */
char *kind3_action_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);

/* Validates game state and passes action struct to 
 * action management's function that handles ACTION SELF_ATTRIBUTE
 *
 * eg: VIEW stats
 *
 * Parameters:
 *  - tokens: parsed input string (validated)
 *  - ctx: pointer to a chiventure context struct
 *
 * Returns:
 *  - Status message based on control flow.
 */
char *kind4_action_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);

/* Toggles the map by calling the toggle_map function in ui_ctx.c. Essentially a
 * wrapper, passing on the context struct only.
 * Parameters:
 *  - tokens: parsed input string (validified)
 *  - ctx: pointer to a chiventure context struct
 * Returns:
 * The text saying the map has been toggled.
 */
char *map_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);


/* Switches the layout by calling the layout_switch function in ui_ctx.c. Essentially a
 * wrapper, passing on the context struct only.
 * Parameters:
 *  - tokens: parsed input string (validified)
 *  - ctx: pointer to a chiventure context struct
 * Returns:
 * The text saying the layout has been switched.
 */
char *switch_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);
 

/* Inserts a new command as a synonym for an existing one.
 * The third word becomes a synonym for the second, if it doesn't mean anything already.
 * The text saying the naming is complete or has failed.
 */
char *name_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);


/* Changes UI color.
 * The second word, if a keyword of the following: "DEFAULT", "BRIGHT", "NIGHT","PAIN"
 * changes the UI color to that theme.
 * Parameters:
 *  - tokens: parsed input string (validified)
 *  - ctx: pointer to a chiventure context struct
 * Returns:
 * A string notifying them if the color was changed or not.
 */
char *palette_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);

/* Initiates Dialogue between NPC and Player
 * 
 * Parameters:
 *  - tokens: parsed input string (validified)
 *  - ctx: pointer to a chiventure context struct
 *
 * Returns:
 * The NPC's response and player's dialogue options.
 */
char *talk_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);

/* Changes the game state to BATTLE mode
 *
 * Parameters:
 *  - tokens: parsed input string (validified)
 *  - ctx: pointer to a chiventure context struct
 *
 * Note:
 * Changing the game mode to battle mode should automatically call a function that 
 * initiates and runs the battle.
 *
 * Returns:
 * A string notifying the user that the battle has begun (or cannot begin).
 */
char *battle_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx);

#endif /* _CLI_INCLUDE_OPERATIONS_H */
