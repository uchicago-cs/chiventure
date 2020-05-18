#ifndef BATTLE_FLOW_H
#define BATTLE_FLOW_H

#include "battle_structs.h"
#include "battle_state.h"
#include "common/utlist.h"
#include "common/common.h"
#include <stdbool.h>
#include <string.h>


/* Stub to hold information about a combatant that isn't
 * yet readily available in the current chiventure
 */
typedef struct combatant_info {
    stat_t *stats;
    move_t *moves;
    item_t *items;
} combatant_info_t;

/*
 * Starts the battle, sets up structs, then runs a battle loop until finisheed
 *
 * Parameters:
 *  - ctx = the current chiventure context
 *  - enemies = pointer to list of enemy/ies (stub for enemy NPCs)
 *  - pinfo = pointer to player info (stats, moves, items stub)
 *  - env = environment for the battle
 *
 * Returns:
 *  - SUCCESS if successful, FAILURE otherwise
 */
 int start_battle(chiventure_ctx_t *ctx, npc_t *enemies, combatant_info_t *pinfo, environment_t env);

/*
 * Sets up the player's combatant_t struct for a new battle
 *
 * Parameters:
 *  - p = the current player in the game_t struct
 *  - pinfo = pointer to player info (stats, moves, items stub)
 *
 * Returns:
 *  - pointer to player's combatant_t struct initialized for new battle
 */
combatant_t *set_player(player_t *p, combatant_info_t *pinfo);

/*
 * Sets up all enemy combatant structs for a new battle
 *
 * Parameters:
 *  - enemies = pointer to list of enemy/ies (stub for enemy NPCs)
 *
 * Returns:
 *  - pointer to list of enemy's/enemies' combatant_t struct
 */
combatant_t *set_enemies(npc_t *enemies);

/*
 * Sets up battle struct for a new battle
 *
 * Parameters:
 *  - player = pointer to player
 *  - enemies = pointer to list of enemy/ies
 *  - env = the environment for the battle
 *
 * Returns:
 *  - A pointer to new battle struct initialized for a new battle
 *
 */
battle_t *set_battle(combatant_t *player, combatant_t *enemies, environment_t env);

/***** below: not yet to be implemented */

// int battle_turn();
