#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>
#include <stdbool.h>
#include <string.h>
#include "battle/battle_ai.h"
#include "battle/battle_flow.h"
#include "battle/battle_flow_structs.h"
#include "battle/battle_structs.h"
#include "npc/npc.h"
#include "npc/npc_battle.h"

class_t *make_wizard()
{
    return class_new("Wizard", "Wise", "Old and wise", NULL, NULL, NULL);
}

/* Tests set_battle_player() */
Test(battle_flow_move, set_battle_player)
{
    combatant_t *comb_player;

    class_t* test_class = class_new("Bard", "Music boi",
                                    "Charismatic, always has a joke or song ready",
                                    NULL, NULL, NULL);

    battle_player_t *ctx_player = new_ctx_player("set_player_Name", test_class,
                                           NULL, NULL, NULL);

    comb_player = set_battle_player(ctx_player);

    cr_assert_not_null(comb_player, "set_player() failed");
    cr_assert_str_eq(comb_player->name, "set_player_Name", "set_player() didn't set name");
    cr_assert_eq(comb_player->is_friendly, true, "set_player() didn't set type");
    cr_assert_eq(comb_player->next, NULL, "set_player() didn't set next");
    cr_assert_eq(comb_player->prev, NULL, "set_player() didn't set prev");

    cr_assert_str_eq(comb_player->class_type->name, "Bard",
                     "set_player() didn't set class name");
    cr_assert_str_eq(comb_player->class_type->shortdesc, "Music boi",
                     "set_player() didn't set class short description");
    cr_assert_str_eq(comb_player->class_type->longdesc,
                     "Charismatic, always has a joke or song ready",
                     "set_player() didn't set class short description");

    cr_assert_null(comb_player->class_type->attributes, "set_player() didn't set class attribute");
    cr_assert_null(comb_player->class_type->base_stats, "set_player() didn't set class stats");
}

/* Tests set_enemies() with 1 enemy */
Test(battle_flow_move, set_one_enemy)
{
    class_t* test_class = class_new("Bard", "Music boi",
                                    "Charismatic, always has a joke or song ready",
                                     NULL, NULL, NULL);

    move_t *move = move_new("Test", 0, NULL, true, 80, 0);
    stat_t *stats = (stat_t*)malloc(sizeof(stat_t));
    npc_t *npc_enemy = npc_new("enemy_name", "Enemy!", "Enemy!", test_class, NULL, true);
    npc_battle_t *npc_b = npc_battle_new(100, stats, move, BATTLE_AI_GREEDY, HOSTILE, 0);
    npc_enemy->npc_battle = npc_b;

    combatant_t *comb_enemy = set_enemy(npc_enemy);

    cr_assert_not_null(comb_enemy, "set_enemies() failed");
    cr_assert_str_eq(comb_enemy->name, "enemy_name", "set_enemies() didn't set name");
    cr_assert_eq(comb_enemy->is_friendly, false, "set_enemies() didn't set type");
    cr_assert_eq(comb_enemy->ai, BATTLE_AI_GREEDY, "set_enemies() didn't set ai");
    cr_assert_eq(comb_enemy->next, NULL, "set_enemies() didn't set next");
    cr_assert_eq(comb_enemy->prev, NULL, "set_enemies() didn't set prev");

    cr_assert_str_eq(comb_enemy->class_type->name, "Bard",
                     "set_player() didn't set class name");
    cr_assert_str_eq(comb_enemy->class_type->shortdesc, "Music boi",
                     "set_player() didn't set class short description");
    cr_assert_str_eq(comb_enemy->class_type->longdesc,
                     "Charismatic, always has a joke or song ready",
                     "set_player() didn't set class short description");

    cr_assert_null(comb_enemy->class_type->attributes, "set_player() didn't set class attribute");
    cr_assert_null(comb_enemy->class_type->base_stats, "set_player() didn't set class stats");
}

/* Tests set_battle() */
Test(battle_flow_move, set_battle)
{
    battle_player_t *ctx_player = new_ctx_player("set_battle_name", NULL, NULL, NULL, NULL);
    move_t *move = move_new("Test", 0, NULL, true, 80, 0);
    stat_t *stats = (stat_t*)malloc(sizeof(stat_t));
    npc_t *npc_enemy = npc_new("set_battle_name", "Enemy!", "Enemy!", NULL, NULL, true);
    npc_battle_t *npc_b = npc_battle_new(100, stats, move, BATTLE_AI_GREEDY, HOSTILE, 0);
    npc_enemy->npc_battle = npc_b;

    environment_t env = ENV_DESERT;
    battle_t *b = set_battle(ctx_player, npc_enemy, env);
    cr_assert_not_null(b, "set_battle() failed");
    // Check player field
    cr_assert_not_null(b->player, "set_battle() failed");
    cr_assert_str_eq(b->player->name, "set_battle_name", "set_battle() didn't set name");
    cr_assert_eq(b->player->is_friendly, true, "set_battle() didn't set type");
    cr_assert_eq(b->player->next, NULL, "set_battle() didn't set next");
    cr_assert_eq(b->player->prev, NULL, "set_battle() didn't set prev");

    // Check enemy field
    cr_assert_not_null(b->enemy, "set_battle() failed");
    cr_assert_str_eq(b->enemy->name, "set_battle_name", "set_battle() didn't set name");
    cr_assert_eq(b->enemy->is_friendly, false, "set_battle() didn't set type");
    cr_assert_eq(b->enemy->next, NULL,"set_battle() didn't set next");
    cr_assert_eq(b->enemy->prev, NULL, "set_battle() didn't set prev");

    // Check environment field
    cr_assert_eq(b->environment, ENV_DESERT, "set_battle() didn't set next");

    // Check turn field
    cr_assert_eq(b->turn, PLAYER, "set_battle() didn't set prev");
}

/* Tests start_battle() */
Test(battle_flow_move, start_battle)
{
    battle_ctx_t *ctx = calloc(1, sizeof(battle_ctx_t));
    battle_game_t *g = new_battle_game();
    battle_player_t *ctx_player = new_ctx_player("start_battle_Name", NULL, NULL, NULL, NULL);
    g->player = ctx_player;
    ctx->game = g;
    ctx->status = BATTLE_IN_PROGRESS;
    move_t *move = move_new("Test", 0, NULL, true, 80, 0);
    stat_t *stats = (stat_t*)malloc(sizeof(stat_t));
    npc_t *npc_enemy = npc_new("start_battle_Name", "Enemy!", "Enemy!", NULL, NULL, true);
    npc_battle_t *npc_b = npc_battle_new(100, stats, move, BATTLE_AI_GREEDY, HOSTILE, 0);
    npc_enemy->npc_battle = npc_b;
    environment_t env = ENV_SNOW;

    int rc = start_battle(ctx, npc_enemy, env);

    cr_assert_eq(rc, SUCCESS, "start_battle() failed");
}

/* this tests to see if it returns a ctx_battle */
Test(battle_flow_move_, return_success_battle_flow_move)
{
    battle_ctx_t *ctx = calloc(1, sizeof(battle_ctx_t));
    battle_game_t *g = new_battle_game();

    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 200;
    pstats->level = 1;
    pstats->phys_atk = 200;
    pstats->phys_def = 30;
    pstats->accuracy = 100;
    pstats->crit = 0;
    battle_player_t *ctx_player = new_ctx_player("Player", make_wizard(), pstats, NULL, NULL);

    g->player = ctx_player;
    ctx->game = g;
    ctx->status = BATTLE_IN_PROGRESS;

    stat_t *estats = calloc(1, sizeof(stat_t));
    estats->hp = 200;
    estats->level = 5;
    estats->phys_atk = 150;
    estats->phys_def = 20;
    estats->accuracy = 100;
    estats->crit = 0;
    move_t *e_move = move_new("Test", 0, NULL, true, 80, 0);
    npc_t *npc_enemy = npc_new("enemy", "Enemy!", "Enemy!", NULL, NULL, true);
    npc_battle_t *npc_b = npc_battle_new(100, estats, e_move, BATTLE_AI_GREEDY, HOSTILE, 0);
    npc_enemy->npc_battle = npc_b;
    environment_t env = ENV_WATER;

    int rc = start_battle(ctx, npc_enemy, env);
    cr_assert_eq(rc, SUCCESS, "start_battle() failed");

    move_t *move = calloc(1, sizeof(move_t));
    move->damage = 100;
    move->name = "Test";

    char *res = battle_flow_move(ctx, move, "enemy");
    
    cr_assert_not_null(res, "battle_flow_move() returned %s",res);
}

/* this tests to see if battle_flow_move does damage to the enemy */
Test(battle_flow_move, do_damage_battle_flow_move)
{
    battle_ctx_t *ctx = calloc(1, sizeof(battle_ctx_t));
    battle_game_t *g = new_battle_game();

    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 200;
    pstats->level = 1;
    pstats->phys_atk = 200;
    pstats->phys_def = 30;
    pstats->accuracy = 100;
    pstats->crit = 0;
    battle_player_t *ctx_player = new_ctx_player("Player", make_wizard(), pstats, NULL, NULL);

    g->player = ctx_player;
    ctx->game = g;
    ctx->status = BATTLE_IN_PROGRESS;

    stat_t *estats = calloc(1, sizeof(stat_t));
    estats->hp = 200;
    estats->level = 5;
    estats->phys_atk = 150;
    estats->phys_def = 20;
    estats->accuracy = 100;
    estats->crit = 0;
    move_t *emove = move_new("Test", 0, NULL, true, 80, 0);
    npc_t *npc_enemy = npc_new("enemy", "Enemy!", "Enemy!", NULL, NULL, true);
    npc_battle_t *npc_b = npc_battle_new(100, estats, emove, BATTLE_AI_GREEDY, HOSTILE, 0);
    npc_enemy->npc_battle = npc_b;

    environment_t env = ENV_WATER;
    int rc = start_battle(ctx, npc_enemy, env);
    cr_assert_eq(rc, SUCCESS, "start_battle() failed");

    move_t *move = calloc(1, sizeof(move_t));
    move->damage = 100;
    move->name = "Test";

    combatant_t *player = ctx->game->battle->player;
    combatant_t *enemy = ctx->game->battle->enemy;

    int expected_enemy_hp = enemy->stats->hp - 
                      damage(enemy, move, player);
    int expected_player_hp = player->stats->hp -
                      damage(player, give_move(player, enemy, enemy->ai), enemy);

    char *res = battle_flow_move(ctx, move, "enemy");
    
    
    cr_assert_not_null(res, "battle_flow_move() returned %s",res);

    cr_assert_eq(enemy->stats->hp,
                 expected_enemy_hp, 
                 "battle_flow_move() did not compute damage on enemy correctly,"
                 "Actual: %d, Expected: %d",enemy->stats->hp, expected_enemy_hp);

    // note: this hp value relies on player class implementation of move_list()
    cr_assert_eq(player->stats->hp,
                 expected_player_hp,
                 "battle_flow_move() did not compute damage on player correctly,"
                 "Actual: %d, Expected: %d",player->stats->hp, expected_player_hp);
    cr_assert_eq(ctx->status, BATTLE_IN_PROGRESS,
                 "battle_flow_move() failed: battle is not in progress");
}

/*
 * Testing if the enemy is determiend as the winner if the player is defeated
 */
Test(battle_flow_move, battle_over_by_player)
{
    battle_ctx_t *ctx = calloc(1, sizeof(battle_ctx_t));
    battle_game_t *g = new_battle_game();

    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 40;
    pstats->level = 1;
    pstats->phys_atk = 200;
    pstats->phys_def = 30;
    pstats->accuracy = 100;
    pstats->crit = 0; 
    battle_player_t *ctx_player = new_ctx_player("Player", make_wizard(), pstats, NULL, NULL);

    g->player = ctx_player;
    ctx->game = g;
    ctx->status = BATTLE_IN_PROGRESS;

    stat_t *estats = calloc(1, sizeof(stat_t));
    estats->hp = 200;
    estats->level = 5;
    estats->phys_atk = 150;
    estats->phys_def = 20;
    estats->accuracy = 100;
    estats->crit = 0;

    move_t *emove = move_new("Test", 0, NULL, true, 80, 0);
    npc_t *npc_enemy = npc_new("enemy", "Enemy!", "Enemy!", NULL, NULL, true);
    npc_battle_t *npc_b = npc_battle_new(100, estats, emove, BATTLE_AI_GREEDY, HOSTILE, 0);
    npc_enemy->npc_battle = npc_b;

    environment_t env = ENV_WATER;
    int rc = start_battle(ctx, npc_enemy, env);
    cr_assert_eq(rc, SUCCESS, "start_battle() failed");

    move_t *move = calloc(1, sizeof(move_t));
    move->damage = 100;
    move->name = "Test";

    combatant_t *player = ctx->game->battle->player;
    combatant_t *enemy = ctx->game->battle->enemy;

    int expected_hp = player->stats->hp -
                      damage(player, give_move(player, enemy,enemy->ai), enemy);

    char *res = battle_flow_move(ctx, move, "enemy");
    
    cr_assert_not_null(res, "battle_flow_move() returned %s",res);

    // note: this hp value relies on player class implementation of move_list 
    cr_assert_eq(player->stats->hp,
                 expected_hp,
                 "battle_flow_move() did not compute damage correctly");

    expected_hp = player->stats->hp -
                  damage(player, give_move(player, enemy,enemy->ai), enemy);

    res = battle_flow_move(ctx, move, "enemy");
    cr_assert_not_null(res, "battle_flow_move() returned %s",res);

    // note: this hp value relies on player class implementation of move_list 
    cr_assert_eq(player->stats->hp,
                 expected_hp,
                 "battle_flow_move() did not compute damage correctly");
    cr_assert_eq(ctx->status, BATTLE_VICTOR_ENEMY,
                 "battle_flow_move() failed: battle is not over due to player");
}

/*
 * Testing if the battle_player is determiend as the winner if the enemy is defeated
 */
Test(battle_flow_move, battle_over_by_enemy)
{
    battle_ctx_t *ctx = calloc(1, sizeof(battle_ctx_t));
    battle_game_t *g = new_battle_game();
    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 150;
    pstats->level = 5;
    pstats->phys_atk = 150;
    pstats->phys_def = 20;
    pstats->accuracy = 100;
    pstats->crit = 0;
    battle_player_t *ctx_player = new_ctx_player("Player", make_wizard(), pstats, NULL, NULL);
    g->player = ctx_player;
    ctx->game = g;
    ctx->status = BATTLE_IN_PROGRESS;
    stat_t *estats = calloc(1, sizeof(stat_t));
    estats->hp = 20;
    estats->level = 1;
    estats->phys_atk = 200;
    estats->phys_def = 30;
    estats->accuracy = 100;
    estats->crit = 0;
    move_t *emove = move_new("Test", 0, NULL, true, 80, 0);
    npc_t *npc_enemy = npc_new("enemy", "Enemy!", "Enemy!", NULL, NULL, true);
    npc_battle_t *npc_b = npc_battle_new(100, estats, emove, BATTLE_AI_GREEDY, HOSTILE, 0);
    npc_enemy->npc_battle = npc_b;
    environment_t env = ENV_WATER;

    int rc = start_battle(ctx, npc_enemy, env);
    cr_assert_eq(rc, SUCCESS, "start_battle() failed");

    move_t *move = calloc(1, sizeof(move_t));
    move->damage = 100;
    move->name = "Test";

    combatant_t *player = ctx->game->battle->player;
    combatant_t *enemy = ctx->game->battle->enemy;

    //There was a 2*
    int expected_hp = enemy->stats->hp -
                      damage(enemy, move, player);  

    char *res = battle_flow_move(ctx, move, "enemy");
    
    cr_assert_not_null(res, "battle_flow_move() returned %s",res);

    res = battle_flow_move(ctx, move, "enemy");
    
    cr_assert_not_null(res, "battle_flow_move() returned %s",res);

    cr_assert_eq(ctx->game->battle->enemy->stats->hp,
                 expected_hp,
                 "battle_flow_move() did not compute damage correctly",
                 "Calculated: %.2d, Expected: %.2d", 
                 ctx->game->battle->enemy->stats->hp, expected_hp);
    cr_assert_eq(ctx->status, BATTLE_VICTOR_PLAYER, 
                 "battle_flow_move() failed: enemy was not declared the winner");
}

