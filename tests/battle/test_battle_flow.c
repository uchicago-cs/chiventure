#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>
#include <stdbool.h>
#include <string.h>
#include "battle/battle_flow.h"
#include "battle/battle_flow_structs.h"
#include "battle/battle_structs.h"

/* Tests set_player() */
Test(battle_flow, set_player)
{
    combatant_t *comb_player;

    class_t* test_class = class_new("Bard", "Music boi",
                                    "Charismatic, always has a joke or song ready",
                                    NULL, NULL, NULL);

    player_t *ctx_player = new_ctx_player("set_player_Name", test_class,
                                           NULL, NULL, NULL);

    comb_player = set_player(ctx_player);

    cr_assert_not_null(comb_player, "set_player() failed");
    cr_assert_str_eq(comb_player->name, "set_player_Name", "set_player() didn't set name");
    cr_assert_eq(comb_player->is_friendly, true, "set_player() didn't set type");
    cr_assert_eq(comb_player->next, NULL, "set_player() didn't set next");
    cr_assert_eq(comb_player->prev, NULL, "set_player() didn't set prev");

    cr_assert_str_eq(comb_player->class->name, "Bard",
                     "set_player() didn't set class name");
    cr_assert_str_eq(comb_player->class->shortdesc, "Music boi",
                     "set_player() didn't set class short description");
    cr_assert_str_eq(comb_player->class->longdesc,
                     "Charismatic, always has a joke or song ready",
                     "set_player() didn't set class short description");

    cr_assert_null(comb_player->class->attributes, "set_player() didn't set class attribute");
    cr_assert_null(comb_player->class->stats, "set_player() didn't set class stats");
}

/* Tests set_enemies() with 1 enemy */
Test(battle_flow, set_one_enemy)
{
    class_t* test_class = class_new("Bard", "Music boi",
                                    "Charismatic, always has a joke or song ready",
                                     NULL, NULL, NULL);

    npc_enemy_t *npc_enemy = make_npc_enemy("enemy_name",
                                            test_class, NULL, NULL, NULL, BATTLE_AI_GREEDY);

    combatant_t *comb_enemy = set_enemies(npc_enemy);

    cr_assert_not_null(comb_enemy, "set_enemies() failed");
    cr_assert_str_eq(comb_enemy->name, "enemy_name", "set_enemies() didn't set name");
    cr_assert_eq(comb_enemy->is_friendly, false, "set_enemies() didn't set type");
    cr_assert_eq(comb_enemy->ai, BATTLE_AI_GREEDY, "set_enemies() didn't set ai");
    cr_assert_eq(comb_enemy->next, NULL, "set_enemies() didn't set next");
    cr_assert_not_null(comb_enemy->prev, "set_enemies() didn't set prev");

    cr_assert_str_eq(comb_enemy->class->name, "Bard",
                     "set_player() didn't set class name");
    cr_assert_str_eq(comb_enemy->class->shortdesc, "Music boi",
                     "set_player() didn't set class short description");
    cr_assert_str_eq(comb_enemy->class->longdesc,
                     "Charismatic, always has a joke or song ready",
                     "set_player() didn't set class short description");

    cr_assert_null(comb_enemy->class->attributes, "set_player() didn't set class attribute");
    cr_assert_null(comb_enemy->class->stats, "set_player() didn't set class stats");
}


/* Tests set_enemies() with 2 enemies */
Test(battle_flow, set_two_enemies)
{
    npc_enemy_t *head = NULL;
    npc_enemy_t *e1 = make_npc_enemy("enemy_name", NULL, NULL, NULL, NULL, BATTLE_AI_GREEDY);
    npc_enemy_t *e2 = make_npc_enemy("enemy_name2", NULL, NULL, NULL, NULL, BATTLE_AI_RANDOM);
    DL_APPEND(head, e1);
    DL_APPEND(head, e2);
    cr_assert_not_null(e1, "make_npc_enemy() failed");
    cr_assert_not_null(e2, "make_npc_enemy() failed");

    // Check first enemy
    combatant_t *comb_enemy1 = set_enemies(head);

    cr_assert_not_null(comb_enemy1, "set_enemies() failed");
    cr_assert_str_eq(comb_enemy1->name, "enemy_name", "set_enemies() didn't set name");
    cr_assert_eq(comb_enemy1->is_friendly, false, "set_enemies() didn't set type");
    cr_assert_eq(comb_enemy1->ai, BATTLE_AI_GREEDY, "set_enemies() didn't set first ai");
    cr_assert_not_null(comb_enemy1->next, "set_enemies() didn't set next");
    cr_assert_not_null(comb_enemy1->prev, "set_enemies() didn't set prev");

    // Check second enemy
    combatant_t *comb_enemy2 = comb_enemy1->next;

    cr_assert_not_null(comb_enemy2, "set_enemies() failed");
    cr_assert_str_eq(comb_enemy2->name, "enemy_name2", "set_enemies() didn't set name");
    cr_assert_eq(comb_enemy2->is_friendly, false, "set_enemies() didn't set type");
    cr_assert_eq(comb_enemy2->ai, BATTLE_AI_RANDOM, "set_enemies() didn't set second type");
    cr_assert_eq(comb_enemy2->next, NULL, "set_enemies() didn't set next");
    cr_assert_not_null(comb_enemy2->prev, "set_enemies() didn't set prev");
}

/* Tests set_battle() */
Test(battle_flow, set_battle)
{
    player_t *ctx_player = new_ctx_player("set_battle_Name", NULL, NULL, NULL, NULL);
    npc_enemy_t *npc_enemy = make_npc_enemy("set_battle_Name", NULL, NULL, NULL, NULL, BATTLE_AI_NONE);
    environment_t env = ENV_DESERT;
    battle_t *b = set_battle(ctx_player, npc_enemy, env);
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
    chiventure_ctx_battle_t *ctx = calloc(1, sizeof(chiventure_ctx_battle_t));
    game_t *g = new_game();
    player_t *ctx_player = new_ctx_player("start_battle_Name", NULL, NULL, NULL, NULL);
    g->player = ctx_player;
    ctx->game = g;
    ctx->status = BATTLE_IN_PROGRESS;
    npc_enemy_t *npc_enemy = make_npc_enemy("start_battle_Name", NULL, NULL, NULL, NULL, BATTLE_AI_NONE);
    environment_t env = ENV_SNOW;

    int rc = start_battle(ctx, npc_enemy, env);

    cr_assert_eq(rc, SUCCESS, "start_battle() failed");

}

/* this tests to see if it returns a ctx_battle */
Test(battle_flow, return_success_battle_flow)
{
    chiventure_ctx_battle_t *ctx = calloc(1, sizeof(chiventure_ctx_battle_t));
    game_t *g = new_game();
    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 20;
    player_t *ctx_player = new_ctx_player("Player", NULL, pstats, NULL, NULL);
    g->player = ctx_player;
    ctx->game = g;
    ctx->status = BATTLE_IN_PROGRESS;
    stat_t *estats = calloc(1, sizeof(size_t));
    estats->hp = 20;
    npc_enemy_t *npc_enemy = make_npc_enemy("Enemy", NULL, estats, test_move_bard(), 
        NULL, BATTLE_AI_GREEDY);
    environment_t env = ENV_WATER;

    int rc = start_battle(ctx, npc_enemy, env);
    cr_assert_eq(rc, SUCCESS, "start_battle() failed");

    move_t *move = calloc(1, sizeof(move_t));
    move->damage = 10;

    int res = battle_flow(ctx, move, "Enemy");
    cr_assert_eq(res, SUCCESS, "battle_flow() returned FAILURE");
}

/* this tests to see if battle_flow does damage to the enemy */
Test(battle_flow, do_damage_battle_flow)
{
    chiventure_ctx_battle_t *ctx = calloc(1, sizeof(chiventure_ctx_battle_t));
    game_t *g = new_game();
    stat_t *pstats = calloc(1, sizeof(size_t));
    pstats->hp = 20;
    player_t *ctx_player = new_ctx_player("Player", NULL, pstats, NULL, NULL);
    g->player = ctx_player;
    ctx->game = g;
    ctx->status = BATTLE_IN_PROGRESS;
    stat_t *estats = calloc(1, sizeof(size_t));
    estats->hp = 20;
    npc_enemy_t *npc_enemy = make_npc_enemy("Enemy", NULL, estats, test_move_bard(), 
        NULL, BATTLE_AI_GREEDY);
    environment_t env = ENV_WATER;

    int rc = start_battle(ctx, npc_enemy, env);
    cr_assert_eq(rc, SUCCESS, "start_battle() failed");

    move_t *move = calloc(1, sizeof(move_t));
    move->damage = 10;

    int res = battle_flow(ctx, move, "Enemy");
    cr_assert_eq(res, SUCCESS, "battle_flow failed!");
    cr_assert_eq(ctx->game->battle->enemy->stats->hp,
                 10, 
                 "battle_flow() did not compute damage correctly");
    cr_assert_eq(ctx->game->battle->player->stats->hp,
                 5,
                 "battle_flow() did not compute damage correctly");
    cr_assert_eq(ctx->status, BATTLE_IN_PROGRESS,
                 "battle_flow() failed: battle is not in progress");
}

/*
 * Testing if the enemy is determiend as the winner if the player is defeated
 */
Test(battle_flow, battle_over_by_player)
{
    chiventure_ctx_battle_t *ctx = calloc(1, sizeof(chiventure_ctx_battle_t));
    game_t *g = new_game();
    stat_t *pstats = calloc(1, sizeof(size_t));
    pstats->hp = 1;
    player_t *ctx_player = new_ctx_player("Player", NULL, pstats, NULL, NULL);
    g->player = ctx_player;
    ctx->game = g;
    ctx->status = BATTLE_IN_PROGRESS;
    stat_t *estats = calloc(1, sizeof(size_t));
    estats->hp = 100;
    npc_enemy_t *npc_enemy = make_npc_enemy("Enemy", NULL, estats, test_move_bard(), 
        NULL, BATTLE_AI_GREEDY);
    environment_t env = ENV_WATER;

    int rc = start_battle(ctx, npc_enemy, env);
    cr_assert_eq(rc, SUCCESS, "start_battle() failed");

    move_t *move = calloc(1, sizeof(move_t));
    move->damage = 10;
    int res = battle_flow(ctx, move, "Enemy");
    cr_assert_eq(res, SUCCESS, "battle_flow() failed");
    res = battle_flow(ctx, move, "Enemy");
    cr_assert_eq(res, SUCCESS, "battle_flow() failed");
    cr_assert_eq(ctx->game->battle->player->stats->hp,
                 -29,
                 "battle_flow() did not compute damage correctly");
    cr_assert_eq(ctx->status, BATTLE_VICTOR_ENEMY,
                 "battle_flow() failed: battle is not over due to player");
}

/*
 * Testing if the player is determiend as the winner if the enemy is defeated
 */
Test(battle_flow, battle_over_by_enemy)
{
    chiventure_ctx_battle_t *ctx = calloc(1, sizeof(chiventure_ctx_battle_t));
    game_t *g = new_game();
    stat_t *pstats = calloc(1, sizeof(size_t));
    pstats->hp = 100;
    player_t *ctx_player = new_ctx_player("Player", NULL, pstats, NULL, NULL);
    g->player = ctx_player;
    ctx->game = g;
    ctx->status = BATTLE_IN_PROGRESS;
    stat_t *estats = calloc(1, sizeof(size_t));
    estats->hp = 20;
    npc_enemy_t *npc_enemy = make_npc_enemy("Enemy", NULL, estats, test_move_bard(), 
    NULL, BATTLE_AI_GREEDY);
    environment_t env = ENV_WATER;

    int rc = start_battle(ctx, npc_enemy, env);
    cr_assert_eq(rc, SUCCESS, "start_battle() failed");

    move_t *move = calloc(1, sizeof(move_t));
    move->damage = 10;
    int res = battle_flow(ctx, move, "Enemy");
    cr_assert_eq(res, SUCCESS, "battle_flow() failed");
    res = battle_flow(ctx, move, "Enemy");
    cr_assert_eq(res, SUCCESS, "battle_flow() failed");
    cr_assert_eq(ctx->game->battle->enemy->stats->hp,
                 0,
                 "battle_flow() did not compute damage correctly");
    cr_assert_eq(ctx->status, BATTLE_VICTOR_PLAYER, 
                 "battle_flow() failed: enemy was not declared the winner");
}
