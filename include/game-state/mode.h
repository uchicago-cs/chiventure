#ifndef _MODE_H
#define _MODE_H

#include "game_state_common.h"
#include "cli/cmd.h"
#include "npc/dialogue.h"

/* Forward declarations */
typedef struct chiventure_ctx chiventure_ctx_t;
typedef int cli_callback(chiventure_ctx_t *ctx, char *outstring, void *args);


/*
 * Mode operation function should run a step of the
 * respective mode, consisting of parsing the user's
 * input and printing the corresponding outstring
 * with the cli_callback function.
 *
 * Parameters:
 * str: the user's input obtained from the UI.
 * callback_func: pointer to a callback function
 * callback_args: additional arguments to callback function
 * ctx: pointer to chiventure context struct
 *
 * Returns:
 * SUCCESS on success, FAILURE if an error occurs
 */ 
typedef int mode_operation(char *str, cli_callback callback_func, 
                           void *callback_args, chiventure_ctx_t *ctx);

/* An enumeration of game mode types */
typedef enum mode_type {
    NORMAL,        //run chiventure as normal
    CONVERSATION,  //for conversations with NPCs
    BATTLE         //for battles
} mode_type_t;

/* Mode data type */
typedef struct game_mode {
    mode_type_t curr_mode;
    mode_operation *run_mode; //the mode's run function
    char* mode_ctx; //for specifying mode's context, e.g. npc_id
} game_mode_t;


/*
 * Initializes a mode with given parameters.
 *
 * Parameters:
 * mode: a mode already allocated in memory
 * curr_mode: the mode type
 * run_mode: the run operation for the mode of the mode_operation type
 * mode_ctx: identifier for mode's context, such as npc_id in conversation mode
 *
 * Returns:
 * SUCCESS on success, FAILURE if an error occurs
 */
int game_mode_init(game_mode_t *mode, mode_type_t curr_mode, 
                   mode_operation run_mode, char *mode_ctx);

/*
 * Allocates a new mode struct in the heap.
 * Parameters:
 * curr_mode: the mode type
 * run_mode: the run operation for the mode of the mode_operation type
 * mode_ctx: identifier for mode's context, such as npc_id in conversation mode
 *
 * Returns:
 * pointer to allocated mode
 */
game_mode_t *game_mode_new(mode_type_t curr_mode, mode_operation run_mode, 
                           char *mode_ctx);

/*
 * Frees resources associated with a mode.
 *
 * Parameters:
 * mode: the mode to be freed
 *
 * Returns:
 * SUCCESS on success, FAILURE if an error occurs
 */
int game_mode_free(game_mode_t *mode);

/*
 * Sets game's mode field to newly allocated mode struct in normal mode.
 * 
 * Parameters:
 * g: the game pointer
 *
 * Returns:
 * SUCCESS if mode successfully allocated, FAILURE if an error occurs
 */
int load_normal_mode(game_t *g);

/*
 * Sets game's already allocated mode struct to the specified mode.
 *
 * Parameters:
 * g: the game pointer
 * curr_mode: the mode_type to switch to
 * mode_ctx: identifier for mode's context
 *
 * Returns:
 * SUCCESS if mode successfully set, FAILURE if an error occurs
 */
int set_game_mode(game_t *g, mode_type_t curr_mode, char *mode_ctx);

/*
 * Mode operation function for conversation mode.
 * Parses the user's input and run's the next step of a converation.
 *
 * Parameters:
 * str: the user's input obtained from the UI.
 * callback_func: pointer to a callback function
 * callback_args: additional arguments to callback function
 * ctx: pointer to chiventure context struct
 *
 * Returns:
 * SUCCESS on success, FAILURE if an error occurs
 * Prints the next NPC dialogue node, along with dialogue 
 * options to the CLI.
 */ 
int run_conversation_mode(char *input, cli_callback callback_func, 
                          void *callback_args, chiventure_ctx_t *ctx);

/*
 * Mode operation function for battle mode.
 * Parses the user's input and runs a turn of the fight.
 *
 * Parameters:
 * str: the user's input obtained from the UI.
 * callback_func: pointer to a callback function
 * callback_args: additional arguments to callback function
 * ctx: pointer to chiventure context struct
 *
 * Returns:
 * SUCCESS on success, FAILURE if an error occurs
 * Prints the next turn of the fight, along with 
 * options to the CLI.
 */ 
int run_battle_mode(char *input, cli_callback callback_func, 
                          void *callback_args, chiventure_ctx_t *ctx);
#endif
