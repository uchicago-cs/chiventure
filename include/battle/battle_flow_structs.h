#ifndef BATTLE_FLOW_STRUCTS_H
#define BATTLE_FLOW_STRUCTS_H

#include <stdbool.h>
#include <string.h>
#include "battle/battle_common.h"
#include "battle/battle_logic.h" 
#include "battle/battle_state.h"
#include "battle/battle_structs.h"
#include "common/common.h"
#include "common/utlist.h"

/* Stub for the player struct in game-state */
typedef struct player {
    // Other fields: hash handle, inventory, other stats
    char *player_id;
    class_t *class_type;
    stat_t *stats;
    move_t *moves;
    battle_item_t *items;
} player_t;

/* Stub for the game_t struct in game-state */
typedef struct game {
    // Would have other fields (eg hash tables for players, rooms, battle_items)
    player_t *player;
    battle_t *battle;
} game_t;

/* Stub, similar to chiventure_ctx_t except adding status, which
 * is an enum that gives the current status of the game 
 * (see logic.h for details)
 */
typedef struct chiventure_ctx_battle {
    // would have UI context here
    game_t *game;
    // would have lookup table here
    battle_status_t status;
} chiventure_ctx_battle_t;

/* Stub to simulate NPC enemy, that will then later be converted to
 * the combatant struct specific to battle flow
 */
typedef struct npc_enemy {
    char *npc_id;
    class_t *class_type;
    stat_t *stats;
    move_t *moves;
    battle_item_t *items;
    difficulty_t ai;
    struct npc_enemy *prev;
    struct npc_enemy *next;
} npc_enemy_t;

/* Stub for the player_new function in player.h game-state module
 *
 * Parameters:
 *     - p_id: player id
 *     - class_type: pointer to player class struct
 *     - stats: player stats stub
 *     - moves: player moves stub
 *     - items: player battle_items stub
 *
 * Returns: a newly allocated player_t with p_id, stats, moves, battle_items
 */
player_t *new_ctx_player(char* p_id, class_t *c_type, stat_t *stats, move_t *moves, battle_item_t* items);

/* Sets up pointer to npc struct, stub for an npc representing the enemy
 *
 * Parameters:
 *     - npc_id: npc id
 *     - class_type: pointer to player_class struct
 *     - stats: npc stats stub
 *     - moves: npc moves stub
 *     - items: npc battle_items stub
 *     - ai: enemy ai
 *
 * Returns: a single newly allocated npc_enemy_t with npc_id, stats, moves, battle_items
 */
npc_enemy_t *make_npc_enemy(char* npc_id, class_t *c_type, stat_t *stats, move_t *moves, 
                            battle_item_t* items, difficulty_t ai);

/* Stub for the game_new function in game.h game-state module
 *
 * Parameters: None
 *
 * Returns: a newly allocated game_t with no current player
 */
game_t *new_game();
#endif
