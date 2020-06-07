#ifndef INCLUDE_INTERFACE_H_
#define INCLUDE_INTERFACE_H_

#include <stdlib.h>
#include <stdio.h>
#include "action_block.h"
#include "ast_block.h"
#include "branch_block.h"
#include "conditional_block.h"
#include "control_block.h"
#include "game-state/game.h"
// #include "custom_action.h"

typedef struct
{
    int x;
} json_dict_obj;

/* 
 * A custom action struct. Holds the contexts for each action
 * (action, context, item, and class) along with a pointer to the
 * first block (AST_block_t) in the action sequence.
 */
typedef struct custom_action
{
    char *action_name;
    char *context;
    char *item;
    char *type;
    AST_block_t *head;
} custom_action_t;

/*
 * A list of all custom actions. This is a placeholder which will eventually
 * be replaced by a list inside of game-state/game.h.
 */
typedef struct custom_action_list
{
    // custom_action_t
} custom_actions_list_t;

/* 
 * Search for a custom action by name
 * 
 * Parameters: 
 * - action_name: The name of the custom action to be searched for
 * - game: The current game chiventure is running, and the custom action
 *         is contained in
 * 
 * Returns:
 * - custom_action_t* Pointer to the custom action with the same name as
 *   action_name if it exists
 * - NULL if no such action_name custom action exists in game
 * 
 */
custom_action_t *search_for_custom_action(char *action_name, game_t *game);

/* 
 * Given a custom action and its corresponding arguments, 
 * attempt to execute the given action.
 * 
 * Parameters: 
 * - action: A pointer to the custom action to be executed (most likely
 *   acquired from search_for_custom_action)
 * - args: An array of strings of the arguments passed to the action
 *   (i.e. the words succeeding the action written in the command line)
 * - num_args: The number of arguments being passed in
 * 
 * Returns:
 * - SUCCESS on successful execution
 * - FAILURE/TBD on specific types of failure
 */
int do_custom_action(custom_action_t *action, char **args, int num_args);

/*
 * Build a custom action object and add it to the game’s list of custom
 * actions (located in game-state/game.h). Also associates custom actions with objects
 * and attributes if necessary.
 * 
 * NOTE: Any objects or attributes the action is associated with need to be
 * initialized before the action is compiled.
 * 
 * Parameters:
 * - json: A dictionary(?) object containing the basic parsed json from a
 *   WDL++ file.
 * - game: The game the custom action should be associated with
 * 
 * Returns:
 * - custom_action_t* A pointer to the compiled custom action if successful
 * - NULL if there was an error parsing the json
 */
custom_action_t *compile_custom_action(json_dict_obj *json, game_t *game);

/*
 * Free a custom action and all its associated structs
 * 
 * Parameters:
 * - action: The custom action to be freed
 * 
 * Returns: 
 * - SUCCESS if the custom action was successfully freed
 * - FAILURE in any other case
 */
int free_custom_action(custom_action_t *action);

/* 
 * Get the name of the specified custom action
 * 
 * Parameters:
 * - action: The custom action to be queried
 * 
 * Returns:
 * - char* A string containing the name of the custom action
 * - NULL if the action passed in was invalid
 */
char *get_custom_action_name(custom_action_t *action);

#endif