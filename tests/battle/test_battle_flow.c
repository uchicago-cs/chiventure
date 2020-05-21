#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "battle/battle_flow.h"

/* Stub for the player_new function in player.h game-state module */
player_t *player_new(char* p_id, stat_t *stats, move_t *moves, item_t* items)
{
      player_t *plyr = calloc(1,sizeof(player_t));
      assert(plyr != NULL);

      plyr->player_id = p_id;
      plyr->stats = stats;
      plyr->moves = moves;
      plyr->items = items;

      return plyr;
}

/* Stub for the game_new function in game.h game-state module */
game_t *game_new()
{
      game_t *g = calloc(1,sizeof(game_t));
      assert(g != NULL);
      g->curr_player = NULL;

      return g;
}

/* Sets up pointer to npc enemy struct, stub for an npc representing the enemy */
npc_enemy_t *make_npc_enemy(char* npc_id, stat_t *stats, move_t *moves, item_t* items)
{
    npc_enemy_t *npc_e = calloc(1,sizeof(npc_enemy_t));
    assert(npc_e != NULL);

    npc_e->npc_id = npc_id;
    npc_e->stats = stats;
    npc_e->moves = moves;
    npc_e->items = items;
    npc_e->prev = NULL;
    npc_e->next = NULL;

    return npc_e;
}

/* Tests set_player() */
Test(battle_flow, set_player)
{
    combatant_t *comb_player;

    player_t *ctx_player = player_new("set_player_Name",NULL,NULL,NULL);

    comb_player = set_player(ctx_player);

    cr_assert_not_null(comb_player, "set_player() failed");
    cr_assert_str_eq(comb_player->name, "set_player_Name", "set_player() didn't set name");
    cr_assert_eq(comb_player->is_friendly, true, "set_player() didn't set type");
    cr_assert_eq(comb_player->next, NULL, "set_player() didn't set next");
    cr_assert_eq(comb_player->prev, NULL, "set_player() didn't set prev");
}

/* Tests set_enemies() */
Test(battle_flow, set_enemies)
{
    npc_enemy_t *head = NULL;
    npc_enemy_t *e1 = make_npc_enemy("set_enemies_Name2",NULL,NULL,NULL);
    npc_enemy_t *e2 = make_npc_enemy("set_enemies_Name1",NULL,NULL,NULL);
    DL_APPEND(head,e1);
    DL_APPEND(head,e2);
    cr_assert_not_null(e1, "set_enemies() failed");
    cr_assert_not_null(e2, "set_enemies() failed");

    combatant_t *comb_enemy1 = set_enemies(head);

    cr_assert_not_null(comb_enemy1, "set_enemies() failed");
    cr_assert_str_eq(comb_enemy1->name, "set_enemies_Name2", "set_enemies() didn't set name");
    cr_assert_eq(comb_enemy1->is_friendly, false, "set_enemies() didn't set type");
    cr_assert_not_null(comb_enemy1->next, "set_enemies() didn't set next");
    cr_assert_not_null(comb_enemy1->prev, "set_enemies() didn't set prev");

    combatant_t *comb_enemy2 = comb_enemy1->next;

    cr_assert_not_null(comb_enemy2, "set_enemies() failed");
    cr_assert_str_eq(comb_enemy2->name, "set_enemies_Name1", "set_enemies() didn't set name");
    cr_assert_eq(comb_enemy2->is_friendly, false, "set_enemies() didn't set type");
    cr_assert_eq(comb_enemy2->next, NULL, "set_enemies() didn't set next");
    cr_assert_not_null(comb_enemy2->prev, "set_enemies() didn't set prev");
}

/* Tests set_battle() */
Test(battle_flow, set_battle)
{
    player_t *ctx_player = player_new("set_battle_Name",NULL,NULL,NULL);
    npc_enemy_t *npc_enemy = make_npc_enemy("set_battle_Name",NULL,NULL,NULL);
    environment_t env = ENV_DESERT;
    battle_t *b = set_battle(ctx_player,npc_enemy,env);
    cr_assert_not_null(b, "set_battle() failed");
    // Check player field
    cr_assert_not_null(b->player, "set_battle() failed");
    cr_assert_str_eq(b->player->name, "set_battle_Name", "set_battle() didn't set name");
    cr_assert_eq(b->player->is_friendly, true, "set_battle() didn't set type");
    cr_assert_eq(b->player->next, NULL, "set_battle() didn't set next");
    cr_assert_eq(b->player->prev, NULL, "set_battle() didn't set prev");

    // Check enemy field
    cr_assert_not_null(b->enemy, "set_battle() failed");
    cr_assert_str_eq(b->enemy->name, "set_battle_Name", "set_battle() didn't set name");
    cr_assert_eq(b->enemy->is_friendly, false, "set_battle() didn't set type");
    cr_assert_eq(b->enemy->next, NULL,"set_battle() didn't set next");
    cr_assert_not_null(b->enemy->prev, "set_battle() didn't set prev");

    // Check environment field
    cr_assert_eq(b->environment, ENV_DESERT, "set_battle() didn't set next");

    // Check turn field
    cr_assert_eq(b->turn, PLAYER, "set_battle() didn't set prev");
}

/* Tests start_battle() */
Test(battle_flow, start_battle)
{
    chiventure_ctx_battle_t *ctx = calloc(1,sizeof(chiventure_ctx_battle_t));
    game_t *g = game_new();
    player_t *ctx_player = player_new("start_battle_Name",NULL,NULL,NULL);
    g->curr_player = ctx_player;
    ctx->game = g;
    ctx->battle_mode = true;
    npc_enemy_t *npc_enemy = make_npc_enemy("start_battle_Name",NULL,NULL,NULL);
    environment_t env = ENV_SNOW;

    int rc = start_battle(ctx,npc_enemy,env);

    cr_assert_eq(rc,SUCCESS,"start_battle() failed");

}
