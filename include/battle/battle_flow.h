#ifndef BATTLE_FLOW_H
#define BATTLE_FLOW_H

#include <stdbool.h>
#include <string.h>
#include "battle_ai.h"
#include "battle_common.h"
#include "battle_flow_structs.h"
#include "battle_logic.h"
#include "battle_move_maker.h"
#include "battle_state.h"
#include "battle_structs.h"
#include "common/common.h"
#include "common/utlist.h"
#include "npc/npc.h"
#include "npc/npc_battle.h"
#include "cli/cli_ctx.h"
#include "common/ctx.h"
#include "ui/print_functions.h"
#include "cli/operations.h"
#include "ui/ui.h"

/*
 * Starts the battle, sets up battle struct including any associated structs
 *
 * In the future, this will include converting a moves list to custom action
 * blocks, but for now, this will be ignored and a stub used instead.
 *
 * Parameters:
 *  - ctx = the current battle context
 *  - npc_enemy = pointer to the npc enemy
 *  - env = environment for the battle
 *
 * Returns:
 *  - SUCCESS if initialized, FAILURE if error
 */
int start_battle(battle_ctx_t *ctx, npc_t *npc_enemy,
                  environment_t env);

/*
 * Sets up the battle_player's combatant_t struct for a new battle
 *
 * Parameters:
 *  - ctx_player = the current battle_player in the battle_game_t struct, which is in
 *                 the chiventure context struct
 *
 * Returns:
 *  - pointer to battle_player's combatant_t struct initialized for new battle
 */
combatant_t *set_battle_player(battle_player_t *ctx_player);

/*
 * Sets up all enemy combatant structs for a new battle
 *
 * Parameters:
 *  - npc_enemy = pointer to the npc enemy
 *
 * Returns:
 *  - pointer to list of enemy's/enemies' combatant_t structs initialized for
 *  a new battle
 */
combatant_t *set_enemy(npc_t *npc_enemy);

/*
 * Sets up battle struct for a new battle
 *
 * Parameters:
 *  - ctx_player = pointer to battle_player_t battle_player in battle_game_t struct
 *  - npc_enemy = pointer to the npc enemy
 *  - env = the environment for the battle
 *
 * Returns:
 *  - A pointer to new battle struct initialized for a new battle
 *
 */
battle_t *set_battle(battle_player_t *ctx_player, npc_t *npc_enemy,
                      environment_t env);

/*
* Determines whether a move hits based on accuracy stat.
 * Parameters:
 * - user_accuracy : the accuracy of the user using the move
 * - move_accuracy : the accuracy of the move itself
 * returns: the 1 or 0 depending on if the move hits
 */
int calculate_accuracy(int user_accuracy, int move_accuracy);

/*
 * Calculates Critical Damage
 *
 * Parameters:
 * - crit_chance : the crit chance of the user using the move
 *
 * returns: the critical damage multiplier
 */
 double crit_modifier(int crit_chance);
 
/*
 * Carries out one iteration of the battle flow loop when a move is used
 *     This includes:
 *         - receiving battle_player's move
 *         - handling battle_player's move
 *     
 *
 * Parameters:
 *  - ctx: current chiventure battle context
 *  - move: pointer to the battle_player's move
 *  - target: name of target
 *
 * Returns:
 *  - A string consisting of the output from the turn
 */
char *battle_flow_move(battle_ctx_t *ctx, move_t *move, char *target);


/*
 * Carries out one iteration of the battle flow loop when an item is used
 *     This includes:
 *         - receiving battle_player's item
 *         - handling using the item and the changes associated with it
 *
 * Parameters:
 *  - ctx: current chiventure battle context
 *  - item: pointer to the battle_player's item
 *
 * Returns:
 *  - A string consisting of the output from the turn
 */
char *battle_flow_item(battle_ctx_t *ctx, battle_item_t *item);



/*
 * Carries out one iteration of the battle flow loop when the user asks for 
 * a list of items or moves 
 *     This includes:
 *         - receiving battle_player's input
 *         - listing out all the players items or moves
 *
 * Parameters:
 *  - ctx: current chiventure battle context
 *  - label: player input either "items or moves"
 *
 * Returns:
 *  - A string consisting of the list output
 *  - Does not change the turn
 */
char *battle_flow_list(battle_ctx_t *ctx, char* label);

/*
 * runs the enemy's turn (each turn component)
 * for now, the ai only knows how to make moves. if it can't
 * make a move, it passes.
 * 
 * Parameters: 
 *  - ctx: current chiventure battle context
 * 
 * Returns:
 *  - A string consisting of the output from the enemy's turn
 */
char *enemy_run_turn(battle_ctx_t *ctx);

/*
 * Helper function for battle_flow functions
 * Allows the enemy to make their move
 * This includes:
 *      - choosing the enemy's move (if available)
 *      - handling enemy's move (if available)
 *      - check battle status
 * 
 * Parameters: 
 *  - ctx: current chiventure battle context
 * 
 * Returns:
 *  - A string consisting of the output from the turn
 */
char *enemy_make_move(battle_ctx_t *ctx);

/* Runs a turn component, which includes allowing user to choose their action,
 * using the action, and reporting results
 * 
 * Parameters:
 * - ctx: the current chiventure context
 * - component: the turn component being run
 * - callback_func: pointer to a callback function
 * - callback_args: additional arguments to callback function
 *
 * Returns:
 * - returns int 1 if everything runs smoothly,
 *   or calls callback function if invalid input
 */
int run_turn_component(chiventure_ctx_t *ctx, turn_component_t *component,
                        void *callback_args, cli_callback callback_func);


/* Runs the action chosen
 *
 * Parameters:
 * - ctx: the current chiventure context
 * - input: the player's input
 *
 * Returns:
 * - returns the string that is the result of the action
 */
char *run_action(char *input, chiventure_ctx_t *ctx);

/*
 * Uses a stat changing move. Works for stat changes
 * that affect the player, opponent, or both.
 * 
 * Parameters: 
 *  - move: the move used
 *  - target: the target the move is used on
 *  - source: the user that is using the move
 * Returns:
 *  - A success if the move was done correctly
 */
int use_stat_change_move(combatant_t* target, move_t* move, combatant_t* source);



#endif
