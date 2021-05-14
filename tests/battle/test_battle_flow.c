#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>
#include <stdbool.h>
#include <string.h>
#include "battle/battle_ai.h"
#include "battle/battle_flow.h"
#include "battle/battle_flow_structs.h"
#include "battle/battle_structs.h"
#include "battle/battle_default_objects.h"

class_t *make_wizard()
{
    return class_new("Wizard", "Wise", "Old and wise", NULL, NULL, NULL);
}
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
    pstats->hp = 200;
    pstats->level = 1;
    pstats->strength = 200;
    pstats->defense = 30;
    player_t *ctx_player = new_ctx_player("Player", make_wizard(), pstats, NULL, NULL);

    g->player = ctx_player;
    ctx->game = g;
    ctx->status = BATTLE_IN_PROGRESS;

    stat_t *estats = calloc(1, sizeof(stat_t));
    estats->hp = 200;
    estats->level = 5;
    estats->strength = 150;
    estats->defense = 20;
    npc_enemy_t *npc_enemy = make_npc_enemy("Enemy", make_wizard(), estats, NULL, NULL, BATTLE_AI_GREEDY);
    environment_t env = ENV_WATER;

    int rc = start_battle(ctx, npc_enemy, env);
    cr_assert_eq(rc, SUCCESS, "start_battle() failed");

    move_t *move = calloc(1, sizeof(move_t));
    move->damage = 100;

    int res = battle_flow(ctx, move, "Enemy");
    cr_assert_eq(res, SUCCESS, "battle_flow() returned FAILURE");
}

/* this tests to see if battle_flow does damage to the enemy */
Test(battle_flow, do_damage_battle_flow)
{
    chiventure_ctx_battle_t *ctx = calloc(1, sizeof(chiventure_ctx_battle_t));
    game_t *g = new_game();

    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 200;
    pstats->defense = 30;
    pstats->level = 1;
    pstats->strength = 200;
    player_t *ctx_player = new_ctx_player("Player", make_wizard(), pstats, NULL, NULL);

    g->player = ctx_player;
    ctx->game = g;
    ctx->status = BATTLE_IN_PROGRESS;

    stat_t *estats = calloc(1, sizeof(stat_t));
    estats->hp = 200;
    estats->defense = 20;
    estats->level = 5;
    estats->strength = 150;
    npc_enemy_t *npc_enemy = make_npc_enemy("Enemy", make_wizard(), estats, NULL, NULL, BATTLE_AI_GREEDY);

    environment_t env = ENV_WATER;
    int rc = start_battle(ctx, npc_enemy, env);
    cr_assert_eq(rc, SUCCESS, "start_battle() failed");

    move_t *move = calloc(1, sizeof(move_t));
    move->damage = 100;

    combatant_t *player = ctx->game->battle->player;
    combatant_t *enemy = ctx->game->battle->enemy;

    int expected_enemy_hp = enemy->stats->hp - 
                      damage(enemy, move, player);
    int expected_player_hp = player->stats->hp -
                      damage(player, give_move(player, enemy, enemy->ai), enemy);

    int res = battle_flow(ctx, move, "Enemy");
    cr_assert_eq(res, SUCCESS, "battle_flow failed!");

    cr_assert_eq(enemy->stats->hp,
                 expected_enemy_hp, 
                 "battle_flow() did not compute damage on enemy correctly, %d",enemy->stats->hp);

    // note: this hp value relies on player class implementation of move_list()
    cr_assert_eq(player->stats->hp,
                 expected_player_hp,
                 "battle_flow() did not compute damage on player correctly");
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

    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 40;
    pstats->level = 1;
    pstats->strength = 200;
    pstats->defense = 30;
    player_t *ctx_player = new_ctx_player("Player", make_wizard(), pstats, NULL, NULL);

    g->player = ctx_player;
    ctx->game = g;
    ctx->status = BATTLE_IN_PROGRESS;

    stat_t *estats = calloc(1, sizeof(stat_t));
    estats->hp = 200;
    estats->level = 5;
    estats->strength = 150;
    estats->defense = 20;
    npc_enemy_t *npc_enemy = make_npc_enemy("Enemy", make_wizard(), estats, NULL, NULL, BATTLE_AI_GREEDY);

    environment_t env = ENV_WATER;
    int rc = start_battle(ctx, npc_enemy, env);
    cr_assert_eq(rc, SUCCESS, "start_battle() failed");

    move_t *move = calloc(1, sizeof(move_t));
    move->damage = 100;

    combatant_t *player = ctx->game->battle->player;
    combatant_t *enemy = ctx->game->battle->enemy;

    int expected_hp = player->stats->hp -
                      damage(player, give_move(player, enemy,enemy->ai), enemy);

    int res = battle_flow(ctx, move, "Enemy");
    cr_assert_eq(res, SUCCESS, "battle_flow() failed");

    // note: this hp value relies on player class implementation of move_list 
    cr_assert_eq(player->stats->hp,
                 expected_hp,
                 "battle_flow() did not compute damage correctly");

    expected_hp = player->stats->hp -
                  damage(player, give_move(player, enemy,enemy->ai), enemy);

    res = battle_flow(ctx, move, "Enemy");
    cr_assert_eq(res, SUCCESS, "battle_flow() failed");

    // note: this hp value relies on player class implementation of move_list 
    cr_assert_eq(player->stats->hp,
                 expected_hp,
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
    stat_t *pstats = calloc(1, sizeof(stat_t));
    pstats->hp = 150;
    pstats->level = 5;
    pstats->strength = 150;
    pstats->defense = 20;
    player_t *ctx_player = new_ctx_player("Player", make_wizard(), pstats, NULL, NULL);
    g->player = ctx_player;
    ctx->game = g;
    ctx->status = BATTLE_IN_PROGRESS;
    stat_t *estats = calloc(1, sizeof(stat_t));
    estats->hp = 20;
    estats->level = 1;
    estats->strength = 200;
    estats->defense = 30;
    npc_enemy_t *npc_enemy = make_npc_enemy("Enemy", make_wizard(), estats, NULL, NULL, BATTLE_AI_GREEDY);
    environment_t env = ENV_WATER;

    int rc = start_battle(ctx, npc_enemy, env);
    cr_assert_eq(rc, SUCCESS, "start_battle() failed");

    move_t *move = calloc(1, sizeof(move_t));
    move->damage = 100;

    combatant_t *player = ctx->game->battle->player;
    combatant_t *enemy = ctx->game->battle->enemy;

    int expected_hp = enemy->stats->hp -
                      2 * damage(enemy, move, player);  

    int res = battle_flow(ctx, move, "Enemy");
    cr_assert_eq(res, SUCCESS, "battle_flow() failed");

    res = battle_flow(ctx, move, "Enemy");
    cr_assert_eq(res, SUCCESS, "battle_flow() failed");

    cr_assert_eq(ctx->game->battle->enemy->stats->hp,
                 expected_hp,
                 "battle_flow() did not compute damage correctly");
    cr_assert_eq(ctx->status, BATTLE_VICTOR_PLAYER, 
                 "battle_flow() failed: enemy was not declared the winner");
}

Test(battle_flow, add_move_existing_list) {

    move_t *old_move = get_random_default_move();
    move_t *new_move = get_random_default_move();
    battle_item_t *item = get_random_default_battle_item();
    stat_t *cstats = get_random_stat();
    combatant_t *player = combatant_new("TESTER",true,NULL,cstats,old_move,item, 0);

    int res = add_move(player,new_move);
    cr_assert_eq(player->moves->next,
                 new_move,
                 "add_move() did not add the move correctly");
}

Test(battle_flow, add_move_empty_list) {
    
    move_t *new_move = get_random_default_move();
    battle_item_t *item = get_random_default_battle_item();
    stat_t *cstats = get_random_stat();
    combatant_t *player = combatant_new("TESTER",true,NULL,cstats,NULL,item, 0);

    int res = add_move(player,new_move);
    cr_assert_eq(player->moves,
                 new_move,
                 "add_move() did not add the move correctly");
}

