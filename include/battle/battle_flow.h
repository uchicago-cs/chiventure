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

/*
 * Starts the battle, sets up battle struct including any associated structs
 *
 * In the future, this will include converting a moves list to custom action
 * blocks, but for now, this will be ignored and a stub used instead.
 *
 * Parameters:
 *  - ctx = the current chiventure context
 *  - npc_enemies = pointer to list of enemy/ies (stub for enemy NPCs)
 *  - env = environment for the battle
 *
 * Returns:
 *  - SUCCESS if initialized, FAILURE if error
 */
int start_battle(chiventure_ctx_battle_t *ctx, npc_enemy_t *npc_enemies,
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
 *  - npc_enemies = pointer to list of enemy/ies (stub for enemy NPCs)
 *
 * Returns:
 *  - pointer to list of enemy's/enemies' combatant_t structs initialized for
 *  a new battle
 */
combatant_t *set_enemies(npc_enemy_t *npc_enemies);

/*
 * Sets up battle struct for a new battle
 *
 * Parameters:
 *  - ctx_player = pointer to battle_player_t battle_player in battle_game_t struct
 *  - npc_enemies = pointer to list of enemy/ies (NPC enemy stub)
 *  - env = the environment for the battle
 *
 * Returns:
 *  - A pointer to new battle struct initialized for a new battle
 *
 */
battle_t *set_battle(battle_player_t *ctx_player, npc_enemy_t *npc_enemies,
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
 *  - Success or failure and modifies the status
 *    variable within the ctx_battle will as seen fit
 *    aka whether it is in progress or if there was a victor
 */
int battle_flow_move(chiventure_ctx_battle_t *ctx, move_t *move, char *target);

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
 *  - Success or failure and modifies the status
 *    variable within the ctx_battle will as seen fit
 *    aka whether it is in progress or if there was a victor
 */
int battle_flow_item(chiventure_ctx_battle_t *ctx, battle_item_t *item);

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
 *  - Always SUCCESS
 */
int enemy_make_move(chiventure_ctx_battle_t *ctx);

#endif
