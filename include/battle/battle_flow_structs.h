#ifndef BATTLE_FLOW_STRUCTS_H
#define BATTLE_FLOW_STRUCTS_H

#include <stdbool.h>
#include <string.h>
#include "battle/battle_common.h"
#include "battle/battle_state.h"
#include "battle/battle_structs.h"
#include "common/common.h"
#include "common/utlist.h"

/* Stub for the player struct in game-state */
typedef struct battle_player {
    // Other fields: hash handle, inventory, other stats
    char *player_id;
    class_t *class_type;
    stat_t *stats;
    move_t *moves;
    battle_item_t *items;
} battle_player_t;

/* Stub for the game_t struct in game-state */
typedef struct battle_game {
    // Would have other fields (eg hash tables for players, rooms, battle_items)
    battle_player_t *player;
    battle_t *battle;
} battle_game_t;

/* Stub, similar to chiventure_ctx_t except adding status, which
 * is an enum that gives the current status of the battle_game 
 * (see logic.h for details)
 */
typedef struct battle_ctx {
    // would have UI context here
    battle_game_t *game;
    // would have lookup table here
    battle_status_t status;
} battle_ctx_t;

/* Stub for the player_new function in player.h game-state module
 *
 * Parameters:
 *     - p_id: player id
 *     - class_type: pointer to player class struct
 *     - stats: player stats stub
 *     - moves: player moves stub
 *     - items: player battle_items stub
 *
 * Returns: a newly allocated battle_player_t with p_id, stats, moves, battle_items
 */
battle_player_t *new_ctx_player(char* p_id, class_t *class, stat_t *stats, move_t *moves, battle_item_t* items);

/* Stub for the game_new function in game.h game-state module
 *
 * Parameters: None
 *
 * Returns: a newly allocated game_t with no current player
 */
battle_game_t *new_battle_game();
#endif
