#ifndef BATTLE_FLOW_STRUCTS_H
#define BATTLE_FLOW_STRUCTS_H

#include <stdbool.h>
#include <string.h>
#include "battle_state.h"
#include "battle_structs.h"
#include "common/common.h"
#include "common/utlist.h"


/* Stub for the player struct in game-state */
typedef struct player {
    // Other fields: hash handle, inventory, other stats
    char *player_id;
    stat_t *stats;
    move_t *moves;
    item_t *items;
} player_t;

/* Stub for the game_t struct in game-state */
typedef struct game {
    // Would have other fields (eg hash tables for players, rooms, items)
    player_t *curr_player;
} game_t;

/* Stub, similar to chiventure_ctx_t except adding in_battle, which
 * marks whether or not a battle is in progress (true if in progress,
 * false if not)
 */
typedef struct chiventure_ctx_battle {
    // would have UI context here
    game_t *game;
    // would have lookup table here
    bool in_battle;
} chiventure_ctx_battle_t;

/* Stub to simulate NPC enemy, that will then later be converted to
 * the combatant struct specific to battle flow
 */
typedef struct npc_enemy {
    char *npc_id;
    stat_t *stats;
    move_t *moves;
    item_t *items;
    struct npc_enemy *prev;
    struct npc_enemy *next;
} npc_enemy_t;

/* Stub for the player_new function in player.h game-state module 
 * 
 * Parameters: 
 *     - p_id: player id 
 *     - stats: player stats stub
 *     - moves: player moves stub
 *     - items: player items stub
 * 
 * Returns: a newly allocated player_t with p_id, stats, moves, items
 */
player_t *new_ctx_player(char* p_id, stat_t *stats, move_t *moves, item_t* items);

/* Sets up pointer to npc struct, stub for an npc representing the enemy
 * 
 * Parameters: 
 *     - npc_id: npc id 
 *     - stats: npc stats stub
 *     - moves: npc moves stub
 *     - items: npc items stub
 * 
 * Returns: a single newly allocated npc_enemy_t with npc_id, stats, moves, items
 */
npc_enemy_t *make_npc_enemy(char* npc_id, stat_t *stats, move_t *moves, item_t* items);

/* Stub for the game_new function in game.h game-state module
 * 
 * Parameters: None 
 * 
 * Returns: a newly allocated game_t with no current player 
 */
game_t *new_game();
#endif
