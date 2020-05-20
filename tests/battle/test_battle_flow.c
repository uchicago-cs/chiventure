#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "battle/battle_flow.h"

/* Sets up pointer to combatant_info_t struct, contains stubs for stats, moves, items */
combatant_info_t *make_comb_info(stat_t *stats, move_t *moves, b_item_t* items)
{
    combatant_info_t *cinfo = calloc(1,sizeof(combatant_info_t));

    cinfo->stats = stats;
    cinfo->moves = moves;
    cinfo->items = items;

    return cinfo;
}

/* Sets up pointer to npc enemy struct, stub for an npc representing the enemy */
npc_enemy_t *make_npc_enemy(char* npc_id, stat_t *stats, move_t *moves, b_item_t* items)
{
    npc_enemy_t *npc_e = calloc(1,sizeof(npc_enemy_t));

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

    player_t *ctx_player = player_new("set_player_Name",100);
    combatant_info_t *pinfo = make_comb_info(NULL,NULL,NULL);

    comb_player = set_player(ctx_player,pinfo);

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
    cr_assert_eq(comb_enemy1->prev, NULL, "set_enemies() didn't set prev");

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
    player_t *ctx_player = player_new("set_battle_Name",100);
    combatant_info_t *pinfo = make_comb_info(NULL,NULL,NULL);
    npc_enemy_t *npc_enemy = make_npc_enemy("set_battle_Name",NULL,NULL,NULL);
    environment_t env = ENV_DESERT;
    printf("1 \n\n");
    battle_t *b = set_battle(ctx_player,pinfo,npc_enemy,env);
    printf("2 \n\n");
    cr_assert_not_null(b, "set_battle() failed");
    printf("3 \n\n");
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
    cr_assert_eq(b->enemy->prev, NULL, "set_battle() didn't set prev");

    // Check environment field
    cr_assert_eq(b->environment, ENV_DESERT, "set_battle() didn't set next");

    // Check turn field
    cr_assert_eq(b->turn, PLAYER, "set_battle() didn't set prev");
}

/* Tests start_battle() */
Test(battle_flow, start_battle)
{
    chiventure_ctx_battle_t *ctx = calloc(1,sizeof(chiventure_ctx_battle_t));
    game_t *g = game_new("start_battle_Start_Desc");
    player_t *ctx_player = player_new("start_battle_Name",100);
    int rc1 = set_curr_player(g,ctx_player);
    ctx->game = g;
    ctx->battle_mode = true;
    ctx->ui_ctx = NULL;
    ctx->table = NULL;

    npc_enemy_t *npc_enemy = make_npc_enemy("start_battle_Name",NULL,NULL,NULL);
    combatant_info_t *pinfo = make_comb_info(NULL,NULL,NULL);
    environment_t env = ENV_SNOW;

    int rc2 = start_battle(ctx,npc_enemy,pinfo,env);

    cr_assert_eq(rc2,SUCCESS,"start_battle() failed");

}
