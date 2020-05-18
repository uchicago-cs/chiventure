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
    class_t class;
} combatant_info_t;

/* Stub for enemy npc */
typedef struct enemynpc {
    char *npc_id;
    stats_t *stats;
    move_t *moves;
    item_t *items;
    class_t class;
} enemynpc_t;

/* Stub to simulate NPC enemy, that will then later be converted to
 * the combatant struct specific to battle flow
 */
typedef struct _elist_t elist_t;
struct _ilist_t
{
    enemynpc_t *enemynpc;
    elist_t *next;
};

/*
 * Starts the battle, sets up structs, then runs a battle loop until finished
 * For now, since we will be starting out with an implementation fo the set-up
 * of a new background, this function will essentially act as a battle set-up
 * function. Later, the battle loop and other aspects of running the game
 * at the high-level will be added.
 *
 * Parameters:
 *  - ctx = the current chiventure context
 *  - enemynpcs = pointer to list of enemy/ies (stub for enemy NPCs)
 *  - pinfo = pointer to player info (stats, moves, items stub)
 *  - env = environment for the battle
 *
 * Returns:
 *  - SUCCESS if successful, FAILURE otherwise
 */
 int start_battle(chiventure_ctx_t *ctx, elist_t *enemynpcs, combatant_info_t *pinfo, environment_t env);

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
combatant_t *set_player(player_t *player, combatant_info_t *pinfo);

/*
 * Sets up all enemy combatant structs for a new battle
 *
 * Parameters:
 *  - enemies = pointer to list of enemy/ies (stub for enemy NPCs)
 enemynpcs
 * Returns:
 *  - pointer to list of enemy's/enemies' combatant_t struct
 */
combatant_t *set_enemies(elist_t *enemynpcs);

/*
 * Sets up battle struct for a new battle
 *
 * Parameters:
 *  - player = pointer to player
 *  - enemynpcs = pointer to list of enemy/ies
 *  - env = the environment for the battle
 *
 * Returns:
 *  - A pointer to new battle struct initialized for a new battle
 *
 */
battle_t *set_battle(player_t *player, combatant_info_t *pinfo, elist_t *enemynpcs, environment_t env);
