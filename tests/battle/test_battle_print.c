#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>
#include <stdbool.h>
#include <string.h>
#include "battle/battle_flow.h"
#include "battle/battle_flow_structs.h"
#include "battle/battle_print.h"
#include "battle/battle_structs.h"
#include "npc/npc.h"
#include "npc/npc_battle.h"

/* Creates + initializes a battle_item*/
 battle_item_t *npc_create_battle_item(int id, int quantity, int durability, 
                            char* description, bool battle, int attack,
                            int defense, int hp)
 {
     battle_item_t* item = (battle_item_t*) calloc(1, sizeof(battle_item_t));

     item->id = id;
     item->quantity = quantity;
     item->durability = durability;
     item->description = description;
     item->battle = battle;
     item->attack = attack;
     item->hp = hp;
     item->defense = defense;

     return item;
 }

/* Tests print_start_battle() */
Test(battle_print, print_start_battle)
{
    // Setting up a battle with set_battle
    stat_t *player_stats = calloc(1,sizeof(stat_t));
    stat_t *enemy_stats = calloc(1,sizeof(stat_t));
    battle_player_t *ctx_player = new_ctx_player("player_name", NULL, 
                                                player_stats, NULL, NULL);
    move_t *move = move_new("Test", 0, NULL, true, 80, 0);
    npc_t *npc_enemy = npc_new("Bob", "Enemy!", "Enemy!", NULL, NULL, true);
    class_t* test_class = class_new("Bard", "Music boi",
                                "Charismatic, always has a joke or song ready",
                                NULL, NULL, NULL);
    battle_item_t *dagger = npc_create_battle_item(1, 1, 20, 
    "A hearty dagger sure to take your breath away... for good",
    true, 20, 5, 0);  
    npc_battle_t *npc_b = npc_battle_new(100, enemy_stats, move,
            BATTLE_AI_GREEDY, HOSTILE, 0, test_class, dagger);
    npc_enemy->npc_battle = npc_b;
    environment_t env = ENV_DESERT;
    battle_t *b = set_battle(ctx_player, npc_enemy, env);
    cr_assert_not_null(b, "set_battle() failed");
    b->player->stats->hp = 100;
    b->enemy->stats->hp = 100;
    char* string = print_start_battle(b);
    cr_assert_not_null(string, "print_start_battle() failed");

    char *expected_string = "You have encountered bob!\n\n"
                            "Let the battle begin!\n";
    cr_expect_str_eq(string, expected_string, 
                    "print_start_battle() failed to set string %s", string);

    free(string);
}

/* Tests print_hp() for battle against one enemy */
Test(battle_print, print_hp_one_enemy)
{
    /* Setting up a battle with set_battle */
    stat_t *player_stats = calloc(1,sizeof(stat_t));
    stat_t *enemy_stats = calloc(1,sizeof(stat_t));
    battle_player_t *ctx_player = new_ctx_player("player_name", NULL,
                                                player_stats, NULL, NULL);
    move_t *move = move_new("Test", 0, NULL, true, 80, 0);
    npc_t *npc_enemy = npc_new("Bob", "Enemy!", "Enemy!", NULL, NULL, true);
    class_t* test_class = class_new("Bard", "Music boi",
                                "Charismatic, always has a joke or song ready",
                                NULL, NULL, NULL);
    battle_item_t *dagger = npc_create_battle_item(1, 1, 20, 
    "A hearty dagger sure to take your breath away... for good",
    true, 20, 5, 0);
    npc_battle_t *npc_b = npc_battle_new(100, enemy_stats, move,
            BATTLE_AI_GREEDY, HOSTILE, 0, test_class, dagger);
    npc_enemy->npc_battle = npc_b;
    environment_t env = ENV_DESERT;
    battle_t *b = set_battle(ctx_player, npc_enemy, env);
    cr_assert_not_null(b, "set_battle() failed");
    b->player->stats->hp = 89;
    b->enemy->stats->hp = 64;

    /* Set up string to store message in */
    char* string = calloc(BATTLE_BUFFER_SIZE + 1, sizeof(char));

    /* Test print_hp() */
    int rc = print_hp(b, string);
    cr_assert_eq(rc, SUCCESS, "print_hp() failed");

    char *expected_string = "-- Your HP: 89\n"
                            "-- bob's HP: 64\n";

    cr_expect_str_eq(string, expected_string, 
                    "print_hp() failed to set string %s", string);

    free(string);
}

/* Tests print_battle_move() on a player move */
Test(battle_print, print_player_move)
{
    // Setting up a battle with set_battle
    stat_t *player_stats = calloc(1,sizeof(stat_t));
    player_stats->hp = 50;
    player_stats->phys_atk = 20;
    player_stats->phys_def = 12;
    player_stats->crit = 0;
    player_stats->accuracy = 100;
    player_stats->xp = 100;
    player_stats->level = 5;
    player_stats->speed = 10;
    stat_t *enemy_stats = calloc(1,sizeof(stat_t));
    enemy_stats->hp = 30;
    enemy_stats->phys_atk = 14;
    enemy_stats->phys_def = 9;
    enemy_stats->crit = 0;
    enemy_stats->accuracy = 100;
    enemy_stats->xp = 100;
    enemy_stats->level = 5;
    enemy_stats->speed = 9;

    battle_player_t *ctx_player = new_ctx_player("player_name", 
                                                NULL, player_stats, NULL, NULL);
    move_t *e_move = move_new("Test", 0, NULL, true, 80, 0);
    npc_t *npc_enemy = npc_new("Bob", "Enemy!", "Enemy!", NULL, NULL, true);
    class_t* test_class = class_new("Bard", "Music boi",
                                "Charismatic, always has a joke or song ready",
                                NULL, NULL, NULL);
    battle_item_t *dagger = npc_create_battle_item(1, 1, 20, 
    "A hearty dagger sure to take your breath away... for good",
    true, 20, 5, 0);  
    npc_battle_t *npc_b = npc_battle_new(100, enemy_stats, e_move, 
            BATTLE_AI_GREEDY, HOSTILE, 0, test_class, dagger);
    npc_enemy->npc_battle = npc_b;
    environment_t env = ENV_DESERT;
    battle_t *b = set_battle(ctx_player, npc_enemy, env);
    cr_assert_not_null(b, "set_battle() failed");
    // Set up a move
    move_t *move = calloc(1,sizeof(move_t));
    move->damage = 60;
    move->info = "Punch";
    b->player->moves = move;
    b->enemy->stats->hp = 21;

    char* string = print_battle_move(b, PLAYER, move);
    cr_assert_not_null(string, "print_start_battle() failed");
    
    char *expected_string = "You used Punch! It did 9 damage.\n"
                            "-- Your HP: 50\n"
                            "-- bob's HP: 21\n";

    cr_expect_str_eq(string, expected_string, 
                    "print_player_move() failed to set string %s", string);

    free(string);
}

/* Tests print_battle_move() on a player move for crit */
Test(battle_print, print_player_move_crit)
{
    // Setting up a battle with set_battle
    stat_t *player_stats = calloc(1,sizeof(stat_t));
    player_stats->hp = 50;
    player_stats->phys_atk = 20;
    player_stats->phys_def = 12;
    player_stats->crit = 100;
    player_stats->accuracy = 100;
    player_stats->xp = 100;
    player_stats->level = 5;
    player_stats->speed = 10;
    stat_t *enemy_stats = calloc(1,sizeof(stat_t));
    enemy_stats->hp = 30;
    enemy_stats->phys_atk = 14;
    enemy_stats->phys_def = 9;
    enemy_stats->crit = 100;
    enemy_stats->accuracy = 100;
    enemy_stats->xp = 100;
    enemy_stats->level = 5;
    enemy_stats->speed = 9;

    battle_player_t *ctx_player = new_ctx_player("player_name", NULL, player_stats, NULL, NULL);
    move_t *e_move = move_new("Test", 0, NULL, true, 80, 0);
    npc_t *npc_enemy = npc_new("Bob", "Enemy!", "Enemy!", NULL, NULL, true);
    npc_battle_t *npc_b = npc_battle_new(100, enemy_stats, e_move,
                     BATTLE_AI_GREEDY, HOSTILE, 0, NULL, NULL);
    npc_enemy->npc_battle = npc_b;
    environment_t env = ENV_DESERT;
    battle_t *b = set_battle(ctx_player, npc_enemy, env);
    cr_assert_not_null(b, "set_battle() failed");
    // Set up a move
    move_t *move = calloc(1,sizeof(move_t));
    move->damage = 60;
    move->info = "Punch";
    b->player->moves = move;
    b->enemy->stats->hp = 16;

    char* string = print_battle_move(b, PLAYER, move);
    cr_assert_not_null(string, "print_start_battle() failed");
    
    char *expected_string = "You used Punch! It did 14 damage.\n"
                            "-- Your HP: 50\n"
                            "-- bob's HP: 16\n";

    cr_expect_str_eq(string, expected_string, "print_player_move_crit() failed to set string %s\n. We got %s", string, expected_string);

    free(string);
}

/* Tests print_battle_move_miss() on a player move for crit */
Test(battle_print, print_player_move_miss)
{
    // Setting up a battle with set_battle
    stat_t *player_stats = calloc(1,sizeof(stat_t));
    player_stats->hp = 50;
    player_stats->phys_atk = 20;
    player_stats->phys_def = 12;
    player_stats->crit = 0;
    player_stats->accuracy = 0;
    player_stats->xp = 100;
    player_stats->level = 5;
    player_stats->speed = 10;
    stat_t *enemy_stats = calloc(1,sizeof(stat_t));
    enemy_stats->hp = 30;
    enemy_stats->phys_atk = 14;
    enemy_stats->phys_def = 9;
    enemy_stats->crit = 0;
    enemy_stats->accuracy = 0;
    enemy_stats->xp = 100;
    enemy_stats->level = 5;
    enemy_stats->speed = 9;

    battle_player_t *ctx_player = new_ctx_player("player_name", NULL, player_stats, NULL, NULL);
    move_t *e_move = move_new("Test", 0, NULL, true, 80, 0);
    npc_t *npc_enemy = npc_new("Bob", "Enemy!", "Enemy!", NULL, NULL, true);
    npc_battle_t *npc_b = npc_battle_new(100, enemy_stats, e_move, BATTLE_AI_GREEDY, HOSTILE, 0, NULL, NULL);
    npc_enemy->npc_battle = npc_b;
    environment_t env = ENV_DESERT;
    battle_t *b = set_battle(ctx_player, npc_enemy, env);
    cr_assert_not_null(b, "set_battle() failed");
    // Set up a move
    move_t *move = calloc(1,sizeof(move_t));
    move->damage = 60;
    move->info = "Punch";
    b->player->moves = move;
    b->enemy->stats->hp = 30;

    char* string = print_battle_miss(b, PLAYER, move);
    cr_assert_not_null(string, "print_start_battle() failed");
    
    char *expected_string = "You used Punch, but it missed!\n"
                            "-- Your HP: 50\n"
                            "-- bob's HP: 30\n";

    cr_expect_str_eq(string, expected_string, "print_player_move_miss() failed to set string %s", string);

    free(string);
}

/* Tests print_battle_move() on an enemy move */
Test(battle_print, print_enemy_move)
{
    // Setting up a battle with set_battle
    stat_t *player_stats = calloc(1,sizeof(stat_t));
    stat_t *enemy_stats = calloc(1,sizeof(stat_t));
    player_stats->hp = 50;
    player_stats->phys_atk = 20;
    player_stats->phys_def = 12;
    player_stats->crit = 0;
    player_stats->accuracy = 100;
    player_stats->xp = 100;
    player_stats->level = 5;
    player_stats->speed = 10;

    enemy_stats->hp = 30;
    enemy_stats->phys_atk = 14;
    enemy_stats->phys_def = 9;
    enemy_stats->crit = 0;
    enemy_stats->accuracy = 100;
    enemy_stats->xp = 100;
    enemy_stats->level = 5;
    enemy_stats->speed = 9;
    battle_player_t *ctx_player = new_ctx_player("player_name", NULL,
                                                player_stats, NULL, NULL);
    move_t *e_move = move_new("Test", 0, NULL, true, 80, 0);
    npc_t *npc_enemy = npc_new("Bob", "Enemy!", "Enemy!", NULL, NULL, true);
    class_t* test_class = class_new("Bard", "Music boi",
                                "Charismatic, always has a joke or song ready",
                                NULL, NULL, NULL);
    battle_item_t *dagger = npc_create_battle_item(1, 1, 20, 
                "A hearty dagger sure to take your breath away... for good",
                true, 20, 5, 0);                                   
    npc_battle_t *npc_b = npc_battle_new(100, enemy_stats, e_move,
            BATTLE_AI_GREEDY, HOSTILE, 0, test_class, dagger);
    npc_enemy->npc_battle = npc_b;
    environment_t env = ENV_WATER;
    battle_t *b = set_battle(ctx_player, npc_enemy, env);
    cr_assert_not_null(b, "set_battle() failed");

    // Set up a move
    move_t *move = calloc(1,sizeof(move_t));
    move->damage = 99;
    move->info = "Laugh";
    b->player->moves = move;
    b->player->stats->hp = 42;
    char* string = print_battle_move(b, ENEMY, move);
    cr_assert_not_null(string, "print_start_battle() failed");
    char *expected_string = "bob used Laugh! It did 8 damage.\n"
                            "-- Your HP: 42\n"
                            "-- bob's HP: 30\n";

    cr_expect_str_eq(string, expected_string, 
                    "print_enemy_move() failed to set string %s", string);

    free(string);
}

/* Tests print_battle_winner() when player wins */
Test(battle_print, print_player_winner)
{
    battle_status_t status = BATTLE_VICTOR_PLAYER;
    int xp = 2;

    char* string = print_battle_winner(status, xp);
    cr_assert_not_null(string, "print_start_battle() failed");

    char *expected_string = "You've won! You gain 2 XP!\n";
    cr_expect_str_eq(string, expected_string, 
                    "print_player_winner() failed to set string");

    free(string);
}

/* Tests print_battle_winner() when enemy wins */
Test(battle_print, print_enemy_winner)
{
    battle_status_t status = BATTLE_VICTOR_ENEMY;
    int xp = 2;

    char* string = print_battle_winner(status, xp);
    cr_assert_not_null(string, "print_start_battle() failed");

    char *expected_string = "You have been defeated!\n";
    cr_expect_str_eq(string, expected_string, 
                    "print_enemy_winner() failed to set string");

    free(string);
}
