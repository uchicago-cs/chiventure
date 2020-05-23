#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_flow.h"
#include "battle/battle_structs.h"

/* Stub for the player_new function in player.h game-state module */
player_t *player_new(char* p_id, stat_t *stats, move_t *moves, item_t* items)
{
      player_t *plyr = calloc(1, sizeof(player_t));
      assert(plyr != NULL);

      plyr->player_id = p_id;
      plyr->stats = stats;
      plyr->moves = moves;
      plyr->items = items;

      return plyr;
}

/* Sets up pointer to npc struct, stub for an npc representing the enemy */
npc_enemy_t *make_npc_enemy(char* npc_id, stat_t *stats, move_t *moves, item_t* items)
{
    npc_enemy_t *npc_e = calloc(1, sizeof(npc_enemy_t));
    assert(npc_e != NULL);

    npc_e->npc_id = npc_id;
    npc_e->stats = stats;
    npc_e->moves = moves;
    npc_e->items = items;
    npc_e->prev = NULL;
    npc_e->next = NULL;

    return npc_e;
}

/* Stub for the game_new function in game.h game-state module */
game_t *game_new()
{
      game_t *g = calloc(1, sizeof(game_t));
      assert(g != NULL);
      g->curr_player = NULL;

      return g;
}
