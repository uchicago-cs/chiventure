#ifndef BATTLE_FLOW_H
#define BATTLE_FLOW_H

#include "battle_structs.h"
#include "battle_state.h"
#include "common/utlist.h"
#include "common/common.h"
#include "common/ctx.h"
#include <stdbool.h>
#include <string.h>

/* Stub, similar to chiventure_ctx_t except adding in battle mode component */
typedef struct chiventure_ctx_battle {
    ui_ctx_t *ui_ctx;
    game_t *game;
    lookup_t **table;
    bool battle_mode;
} chiventure_ctx_battle_t;



/* Stub to hold information about a combatant that isn't
 * yet readily available in the current chiventure
 */
typedef struct combatant_info {
    stat_t *stats;
    move_t *moves;
    b_item_t *items;
} combatant_info_t;

/* Stub to simulate NPC enemy, that will then later be converted to
 * the combatant struct specific to battle flow
 */
typedef struct npc_enemy {
    char *npc_id;
    stat_t *stats;
    move_t *moves;
    b_item_t *items;
    struct npc_enemy *prev;
    struct npc_enemy *next;
} npc_enemy_t;

/*
 * Starts the battle, sets up structs, then runs a battle loop until finished
 * For now, since we will be starting out with an implementation fo the set-up
 * of a new background, this function will essentially act as a battle set-up
 * function. Later, the battle loop and other aspects of running the game
 * at the high-level will be added.
 *
 * Parameters:
 *  - ctx = the current chiventure context
 *  - npc_enemies = pointer to list of enemy/ies (stub for enemy NPCs)
 *  - pinfo = pointer to player info (stats, moves, items stub)
 *  - env = environment for the battle
 *
 * Returns:
 *  - SUCCESS if successful, FAILURE otherwise
 */
 int start_battle(chiventure_ctx_battle_t *ctx, npc_enemy_t *npc_enemies, combatant_info_t *pinfo, environment_t env);

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
combatant_t *set_enemies(npc_enemy_t *npc_enemies);

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
battle_t *set_battle(player_t *player, combatant_info_t *pinfo, npc_enemy_t *npc_enemies, environment_t env);

#endif
