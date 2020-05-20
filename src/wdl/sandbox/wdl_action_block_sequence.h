#include "../../../include/common/utlist.h"
#include "../../../include/common/common.h"


/* 
 * wdl_action_block_sequence.h
 * 
 * Contains the utlist node structure and wrapper for a linked list
 * that stores the raw (pre-AST) sequence of action blocks, 
 * to be passed to and compiled by Custom Actions code.
 * 
 */


/* Definitions */

#define ACTION_BLOCK_NAME_MAXLEN 16
#define ACTION_BLOCK_PARAMS_MAXLEN 512

/* 
 * A dummy forward definition for json_dict_obj, which will be replaced
 * with whatever JSON object representation we get from our JSON library.
 */
typedef int json_dict_obj;


/* An outwards-facing header for the utlist action sequence */
typedef struct wdl_action_sequence {
    
    // n_blocks: The number of action blocks in the sequence
    int n_blocks;
    
    // n_args: The number of arguments to pass when executing the action sequence
    int n_args;
    
    // args: A string of space-separated action sequence arguments
    char *args;
    
    // head_block: A pointer to the first action block in the sequence.
    wdl_action_block_t *head;

} wdl_action_sequence_t;


/* A utlist node struct to store a single raw action block. */
typedef struct wdl_action_block {
    
    // block_name: The name of the block (e.g. "if" or "set" or "endwhile")
    char block_name[ACTION_BLOCK_NAME_MAXLEN]; 
    
    /* 
     * block_parameters:
     * A string which is a space-separated list of parameters for this block.
     * The reason why this module doesn't parse args into individual arg strings is
     * to leave open the possibility for Custom Actions to do their own
     * argument parsing (for things like SAY blocks' string argument(s).)
     */
    char *block_parameters;

    // next_block: A pointer to the next action block, for use with utlist.
    struct wdl_raw_action_block *next;

} wdl_action_block_t;


/* Functions */

/*
 * wdl_action_block_get_next
 * 
 * Given one action block, gets the next action block in the sequence.
 * Parameters:
 *  curr: a pointer to the current action block to get the next of
 * 
 * Returns:
 *  the pointer to the next action block, or NULL if the current block is
 * the last block in the sequence.
 */
wdl_action_block_t *wdl_action_block_get_next(wdl_action_block_t *curr);


/*
 * wdl_action_block_get_blockname
 * 
 * Given one action block, gets its name. (e.g. "if" or "set" or "endwhile")
 * Parameters:
 *  action_block: The action block to get the name of 
 * 
 * Returns:
 *  a char array pointer that points to the block's name string.
 */
char *wdl_action_block_get_name(wdl_action_block_t *action_block);


/*
 * wdl_action_block_get_params
 * 
 * Given one action block, get the space-separated string of parameters
 * passed to it.
 * Parameters:
 *  action_block: The action block to get the parameters from.
 * 
 * Returns:
 *  a string which is a space-separated list of parameters passed to the block.
 */
char *wdl_action_block_get_params(wdl_action_block_t *action_block);


/*
 * wdl_action_sequence_new
 * 
 * Creates an action sequence from a raw JSON list of objects (blocks).
 * 
 * Parameters:
 *  json_list: a raw list of the object blocks obtained from json parsing
 * 
 * Returns:
 *  A pointer to the created action sequence structure, or NULL 
 *  if function wasn't able to create it.
 */
wdl_action_sequence_t *wdl_action_sequence_new(json_dict_obj *raw_json_object);


/*
 * wdl_action_block_new
 * 
 * Creates an action sequence from a raw JSON list of objects (blocks).
 * 
 * Parameters:
 *  json_list: a raw list of the object blocks obtained from json parsing
 * 
 * Returns:
 *  A pointer to the created action sequence structure, or NULL 
 *  if function wasn't able to create it.
 */
wdl_action_block_t *wdl_action_block_new(char *block_name, char *block_parameters);


/*
 * wdl_action_sequence_free
 * 
 * Frees an action sequence, along with all the blocks in it.
 * To be run when the game is unloaded.
 * 
 * Parameters:
 *  action_seq: a pointer to the action sequence to be freed
 * 
 * Returns:
 *  SUCCESS if action_seq was able to be freed
 *  FAILURE if action_seq was NULL or otherwise not able to be freed
 */
int wdl_action_sequence_free(wdl_action_sequence_t *action_seq);
