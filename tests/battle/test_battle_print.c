#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>
#include <stdbool.h>
#include <string.h>
#include "battle/battle_flow.h"
#include "battle/battle_flow_structs.h"
#include "battle/battle_print.h"
#include "battle/battle_structs.h"

/* Tests print_start_battle() */
Test(battle_flow, print_start_battle)
{
    // Setting up a battle with set_battle
    stat_t *player_stats = calloc(1,sizeof(stat_t));
    stat_t *enemy_stats = calloc(1,sizeof(stat_t));
    player_t *ctx_player = new_ctx_player("player_name", NULL, player_stats, NULL, NULL);
    npc_enemy_t *npc_enemy = make_npc_enemy("Bob", NULL, enemy_stats, NULL, NULL);
    environment_t env = ENV_DESERT;
    battle_t *b = set_battle(ctx_player, npc_enemy, env);
    cr_assert_not_null(b, "set_battle() failed");
    b->player->stats->hp = 100;
    b->enemy->stats->hp = 100;

    // Setting up malloced string - Taken from actionmanagement.c
    char *string = malloc(BUFFER_SIZE);
    memset(string, 0, BUFFER_SIZE);

    int rc = print_start_battle(b, string);
    cr_assert_eq(rc, SUCCESS, "print_start_battle() failed");

    char *expected_string = "You have encountered Bob!\n\n"
                            "Let the battle begin!\n"
                            "-- Your HP: 100\n"
                            "-- Bob's HP: 100\n";
    cr_expect_str_eq(string, expected_string, "print_start_battle() failed to set string");

    free(string);
}

/* Tests print_battle_move() on a player move */
Test(battle_flow, print_player_move)
{
    // Setting up a battle with set_battle
    stat_t *player_stats = calloc(1,sizeof(stat_t));
    stat_t *enemy_stats = calloc(1,sizeof(stat_t));
    player_t *ctx_player = new_ctx_player("player_name", NULL, player_stats, NULL, NULL);
    npc_enemy_t *npc_enemy = make_npc_enemy("Bob", NULL, enemy_stats, NULL, NULL);
    environment_t env = ENV_DESERT;
    battle_t *b = set_battle(ctx_player, npc_enemy, env);
    cr_assert_not_null(b, "set_battle() failed");
    b->player->stats->hp = 100;
    b->enemy->stats->hp = 98;

    // Set up a move
    move_t *move = calloc(1,sizeof(move_t));
    move->damage = 2;
    move->info = "Punch";
    b->player->moves = move;

    // Setting up malloced string - Taken from actionmanagement.c
    char *string = malloc(BUFFER_SIZE);
    memset(string, 0, BUFFER_SIZE);

    int rc = print_battle_move(b, PLAYER, move, string);
    cr_assert_eq(rc, SUCCESS, "print_player_move() failed");

    char *expected_string = "You used Punch! It did 2 damage.\n"
                            "-- Your HP: 100\n"
                            "-- Bob's HP: 98\n";

    cr_expect_str_eq(string, expected_string, "print_player_move() failed to set string");

    free(string);
}

/* Tests print_battle_move() on an enemy move */
Test(battle_flow, print_enemy_move)
{
    // Setting up a battle with set_battle
    stat_t *player_stats = calloc(1,sizeof(stat_t));
    stat_t *enemy_stats = calloc(1,sizeof(stat_t));
    player_t *ctx_player = new_ctx_player("player_name", NULL, player_stats, NULL, NULL);
    npc_enemy_t *npc_enemy = make_npc_enemy("Bob", NULL, enemy_stats, NULL, NULL);
    environment_t env = ENV_WATER;
    battle_t *b = set_battle(ctx_player, npc_enemy, env);
    cr_assert_not_null(b, "set_battle() failed");
    b->player->stats->hp = 1;
    b->enemy->stats->hp = 100;

    // Set up a move
    move_t *move = calloc(1,sizeof(move_t));
    move->damage = 99;
    move->info = "Laugh";
    b->player->moves = move;

    // Setting up malloced string - Taken from actionmanagement.c
    char *string = malloc(BUFFER_SIZE);
    memset(string, 0, BUFFER_SIZE);

    int rc = print_battle_move(b, ENEMY, move, string);
    cr_assert_eq(rc, SUCCESS, "print_player_move() failed");

    char *expected_string = "Bob used Laugh! It did 99 damage.\n"
                            "-- Your HP: 1\n"
                            "-- Bob's HP: 100\n";

    cr_expect_str_eq(string, expected_string, "print_enemy_move() failed to set string");

    free(string);
}


/* Tests print_battle_winner() when player wins */
Test(battle_flow, print_player_winner)
{
    battle_status_t status = BATTLE_VICTOR_PLAYER;
    int xp = 2;

    // Setting up malloced string - Taken from actionmanagement.c
    char *string = malloc(BUFFER_SIZE);
    memset(string, 0, BUFFER_SIZE);

    int rc = print_battle_winner(status, xp, string);
    cr_assert_eq(rc, SUCCESS, "print_player_winner() failed");

    char *expected_string = "You've won! You gain 2 XP!\n";
    cr_expect_str_eq(string, expected_string, "print_player_winner() failed to set string");

    free(string);
}

/* Tests print_battle_winner() when enemy wins */
Test(battle_flow, print_enemy_winner)
{
    battle_status_t status = BATTLE_VICTOR_ENEMY;
    int xp = 2;

    // Setting up malloced string - Taken from actionmanagement.c
    char *string = malloc(BUFFER_SIZE);
    memset(string, 0, BUFFER_SIZE);

    int rc = print_battle_winner(status, xp, string);
    cr_assert_eq(rc, SUCCESS, "print_player_winner() failed");

    char *expected_string = "You lost...\n";
    cr_expect_str_eq(string, expected_string, "print_player_winner() failed to set string");

    free(string);
}
