#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_flow_structs.h"

/* Stub for the player_new function in player.h game-state module */

battle_player_t *new_ctx_player(char* p_id, class_t *c_type, stat_t *stats, move_t *moves, battle_item_t* items)
{
    battle_player_t *ctx_player = calloc(1, sizeof(battle_player_t));
    assert(ctx_player != NULL);

    ctx_player->player_id = p_id;
    ctx_player->class_type = c_type;
    ctx_player->stats = stats;
    ctx_player->moves = moves;
    ctx_player->items = items;

    return ctx_player;
}

/* Stub for the game_new function in game.h game-state module */
battle_game_t *new_battle_game()
{
    battle_game_t *g = calloc(1, sizeof(battle_game_t));
    assert(g != NULL);
    g->player = NULL;
    g->battle = NULL;

    return g;
}
