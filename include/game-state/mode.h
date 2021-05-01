#ifndef _MODE_H
#define _MODE_H

#include "game_state_common.h"

/* Forward declaration */
typedef struct chiventure_ctx chiventure_ctx_t;

/* Mode operation function should run a step of the
 * respective mode, consisting of parsing the user's
 * input and printing the corresponding outstring
 * with the cli_callback function */ 
typedef int mode_operation(char* str, cli_callback callback_func, 
                           void* callback_args, chiventure_ctx_t* ctx);

/* An enumeration of game mode types */
typedef enum mode_type {
    NORMAL,        //run chiventure as normal
    CONVERSATION   //for conversations with NPCs
} mode_type_t;

/* Mode data type */
typedef struct mode {
    mode_type_t curr_mode;
    mode_operation run_mode; //the mode's run function
    char* mode_ctx; //for specifying mode's context, e.g. npc_id
} mode_t;

// STRUCT FUNCTIONS ----------------------------------------------------------

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
int mode_init(mode_t *mode, mode_type_t curr_mode, 
              mode_operation run_mode, char* mode_ctx);

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
mode_t *mode_new(mode_type_t curr_mode, mode_operation run_mode, 
                 char* mode_ctx);

/*
 * Frees resources associated with a mode.
 *
 * Parameters:
 * mode: the mode to be freed
 *
 * Returns:
 * SUCCESS on success, FAILURE if an error occurs
 */
int mode_free(mode_t *mode);

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
