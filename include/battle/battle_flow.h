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
 * Sets up all necessary structs and details for a new battle
 *
 * Parameters:
 *  - g = the current game
 *  - enemies = pointer to list of enemy/ies (stub for enemy NPCs)
 *  - pinfo = pointer to player info (stats, moves, items stub)
 *
 * Returns:
 *  - SUCCESS if successful, FAILURE otherwise
 */
 int battle_setup(game_t *g, npc_t *enemies, combatant_info *pinfo, environment_t env);

/*
 * Sets up all combatant structs for a new battle
 *
 * Parameters:
 *  - p = the current player
 *  - enemies = list of enemies to be fought
 *
 * Returns:
 *  - SUCCESS if successful, FAILURE otherwise
 */
int set_combatants();

/*
 * Sets up battle struct for a new battle
 *
 * Parameters:
 *  -
 *
 * Returns:
 *  - A pointer to the point, or NULL if a point
 *    cannot be allocated
 */
int set_battle();

/***** below: not yet to be implemented */

// int run_battle();

// int battle_turn();
