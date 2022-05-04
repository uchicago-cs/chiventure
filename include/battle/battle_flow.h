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

#endif
