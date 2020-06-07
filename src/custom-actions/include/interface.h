#ifndef INCLUDE_INTERFACE_H_
#define INCLUDE_INTERFACE_H_

#include <stdlib.h>
#include <stdio.h>
#include "ast_block.h"
#include "action_block.h"
#include "branch_block.h"
#include "conditional_block.h"
#include "control_block.h"
#include "game-state/game.h"

typedef struct
{
    int x;
} json_dict_obj;

/* 
 * A custom action struct. Holds the contexts for each action
 * (action, context, item, and type) along with a pointer to the
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
 * - all_actions: Comprehensive list of all previously defined custom actions
 * 
 * Returns:
 * - custom_action_t* Pointer to the custom action with the same name as
 *   action_name if it exists
 * - NULL if no such action_name custom action exists in game
 * 
 */
custom_action_t *search_for_custom_action(char *action_name,
                                          custom_actions_list_t *all_actions);

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
 * actions. Also associates custom actions with objects and attributes
 * if necessary.
 * 
 * NOTE: Any objects or attributes the action is associated with need to be
 * initialized before the action is compiled.
 * 
 * Parameters:
 * - action: obj_t representing information about a custom action and
 *           its attributes (created when a custom action is parsed from
 *           a json file)
 * - all_actions: list of previously defined custom actions
 * 
 * Returns:
 * - custom_action_t* A pointer to the compiled custom action if successful
 * - NULL if there was an error working with the obj_t struct or an error
 *        adding the resulting custom action to the list
 */
custom_action_t *compile_custom_action(obj_t *action,
                                       custom_actions_list_t *all_actions);

/*
 * Adds a custom action object to the game's list of custom actions.
 * 
 * Parameters:
 * - action: The custom action to be added
 * - all_actions: list of previously defined custom actions
 * 
 * Returns:
 * - SUCCESS if the custom action was successfully added to the list
 * - FAILURE if otherwise
 */
int *add_custom_action_to_game(custom_action_t *action,
                               custom_actions_list_t *all_actions);

/* 
 * Translates information about a custom action and its attributes (an obj_t,
 * having just been parsed from a json file) into an actual custom_action_t.
 * 
 * Parameters:
 * - action: obj_t representing information about a custom action and
 *           its attributes (created when a custom action is parsed from
 *           a json file)
 * 
 * Returns:
 * - custom_action_t* A pointer to the created custom action if successful
 * - NULL if there was an error working with the obj_t struct
 */
custom_action_t *translate_custom_action(obj_t *action);

#endif