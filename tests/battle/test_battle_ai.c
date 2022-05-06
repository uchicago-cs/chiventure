#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "battle/battle_ai.h"


class_t *create_test_class()
{
    class_t* test_class = class_new("Bard", "Music boi",
                                    "Charismatic, always has a joke or song ready",
                                    NULL, NULL, NULL);
}

/* Creates + initializes a move*/
move_t *create_move(int id, battle_item_t* item, bool attack, int damage, int defense)
 {
     move_t* move = (move_t*) calloc(1, sizeof(move_t));

     move->id = id;

     move->item = item;

     move->attack = attack;
     move->damage = damage;
     move->defense = defense;

     return move;
 }

/* Creates + initializes a battle_item*/
 battle_item_t *create_battle_item(int id, int quantity, int durability, char* description,
            bool battle, int attack, int defense, int hp)
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

/* Creates example hardcoded stats for the enemy*/
stat_t* create_enemy_stats_norm()
{
    stat_t* test_stats = calloc(1, sizeof(stat_t));

    test_stats->speed = 50;
    test_stats->phys_def = 20;
    test_stats->phys_atk = 150;
    test_stats->mag_atk = 150;
    test_stats->mag_def = 20;
    test_stats->max_sp = 20;
    test_stats->sp = 20;
    test_stats->crit = 0;
    test_stats->accuracy = 100;
    test_stats->hp = 200;
    test_stats->max_hp = 200;
    test_stats->xp = 0;
    test_stats->level = 5;

    return test_stats;
}

/* Creates example hardcoded stats for the enemy*/
stat_t* create_enemy_stats_crit()
{
    stat_t* test_stats = calloc(1, sizeof(stat_t));

    test_stats->speed = 50;
    test_stats->phys_def = 20;
    test_stats->phys_atk = 150;
    test_stats->mag_atk = 150;
    test_stats->mag_def = 20;
    test_stats->max_sp = 20;
    test_stats->sp = 20;
    test_stats->crit = 100;
    test_stats->accuracy = 100;
    test_stats->hp = 200;
    test_stats->max_hp = 200;
    test_stats->xp = 0;
    test_stats->level = 5;

    return test_stats;
}

/* Creates example hardcoded stats for the battle_player*/
stat_t* create_battle_player_stats()
{
    stat_t* test_stats = calloc(1, sizeof(stat_t));
    test_stats->speed = 50;
    test_stats->phys_def = 30;
    test_stats->phys_atk = 200;
    test_stats->mag_atk = 200;
    test_stats->mag_def = 30;
    test_stats->max_sp = 20;
    test_stats->sp = 20;
    test_stats->crit = 0;
    test_stats->accuracy = 100;
    test_stats->hp = 150;
    test_stats->max_hp = 150;
    test_stats->xp = 0;
    test_stats->level = 1;

    return test_stats;
}

/* Creates example hardcoded battle_items for the player*/
battle_item_t* create_player_battle_items()
{
    battle_item_t *head, *dagger, *tea_leaves, *medicine;
    head = NULL;
    dagger = create_battle_item(1, 1, 20, "A hearty dagger sure to take your breath away... for good",
    true, 20, 5, 0);
    tea_leaves = create_battle_item(2, 1, 1, "Make yourself a warm cup of tea to heal your wounds!", true,
    0, 0, 10);
    medicine = create_battle_item(3, 1, 1, "A first aid kit, straight from your doctor!", true, 0, 0, 30);
    DL_APPEND(head, dagger);
    DL_APPEND(head, tea_leaves);
    DL_APPEND(head, medicine);
    return head;
}

/* Creates example hardcoded items for the enemy*/
battle_item_t* create_enemy_battle_items()
{
    battle_item_t *head, *mace, *diamond_sword, *force_shield;
    head = NULL;
    mace = create_battle_item(4, 1, 20, "Temporary blindness leaves you quite vulnerable...", true,
        0, -30, 0);
    diamond_sword = create_battle_item(5, 1, 50, "Brings quick death to those who dare battle you...",
        true, 20, 0, 0);
    force_shield = create_battle_item(6, 1, 30, "Rest comfortably as this shield protects you for 1 move",
        true, 0, 30, 5);
    DL_APPEND(head, mace);
    DL_APPEND(head, diamond_sword);
    DL_APPEND(head, force_shield);
    return head;
}

/* Creates example hardcoded moves for the enemy*/
move_t* create_enemy_moves()
{
    move_t *head, *earthquake, *poke, *rock_throw;
    head = NULL;
    earthquake = create_move(1, NULL, true, 100, 0);
    poke = create_move(2, NULL, true, 40, 0);
    rock_throw = create_move(3, NULL, true, 90, 0);
    DL_APPEND(head, earthquake);
    DL_APPEND(head, poke);
    DL_APPEND(head, rock_throw);
    return head;
}

/* Creates example hardcoded stats for the battle_player*/
move_t* create_battle_player_moves()
{
    move_t *head, *fire_blast, *punch, *blaze_kick;
    head = NULL;
    fire_blast = create_move(4, NULL, true, 100, 0);
    punch = create_move(5, NULL, true, 20, 0);
    blaze_kick = create_move(6, NULL, true, 60, 0);
    DL_APPEND(head, fire_blast);
    DL_APPEND(head, punch);
    DL_APPEND(head, blaze_kick);
    return head;
}

/* Creates the expected return value for when the AI should return the greediest move*/
move_t* expected_move_greedy()
{
    move_t* earthquake = create_move(1, NULL, true, 100, 0);
    return earthquake;
}

/* Creates the expected return value for when the AI should return a random move*/
move_t* expected_move_random()
{
    srand(1);
    int randomish = rand() % 3;
    move_t* rock_throw = create_move(randomish, NULL, true, 90, 0);
    return rock_throw;
}

/* Creates sandbox enemy*/
combatant_t* new_enemy()
{
    char* name = "Skeleton";
    bool is_friendly = false;
    class_t *c_type = create_test_class();
    stat_t *stats = create_enemy_stats_norm();
    move_t *moves = create_enemy_moves();
    battle_item_t *items = create_enemy_battle_items();
    struct combatant *next = NULL;
    struct combatant *prev = NULL;
    return combatant_new(name, is_friendly, c_type, stats, moves, items, BATTLE_AI_GREEDY);

}

/* Creates sandbox enemy with crit value 100% */
combatant_t* new_enemy_crit()
{
    char* name = "Skeleton";
    bool is_friendly = false;
    class_t *c_type = create_test_class();
    stat_t *stats = create_enemy_stats_crit();
    move_t *moves = create_enemy_moves();
    battle_item_t *items = create_enemy_battle_items();
    struct combatant *next = NULL;
    struct combatant *prev = NULL;
    return combatant_new(name, is_friendly, c_type, stats, moves, items, BATTLE_AI_GREEDY);

}

/* Creates sandbox enemy with accuracy value 0*/
combatant_t* new_enemy_miss()
{
    char* name = "Skeleton";
    bool is_friendly = false;
    class_t *c_type = create_test_class();
    stat_t *stats = create_enemy_stats_miss();
    move_t *moves = create_enemy_moves();
    battle_item_t *items = create_enemy_battle_items();
    struct combatant *next = NULL;
    struct combatant *prev = NULL;
    return combatant_new(name, is_friendly, c_type, stats, moves, items, BATTLE_AI_GREEDY);

}

/* Creates sandbox battle_player*/
combatant_t* new_battle_player()
{
    char* name = "Steve";
    bool is_friendly = true;

    class_t *c_type = create_test_class();
    stat_t *stats = create_battle_player_stats();
    move_t *moves = create_battle_player_moves();
    battle_item_t *items = create_player_battle_items();
    struct combatant *next = NULL;
    struct combatant *prev = NULL;
    return combatant_new(name, is_friendly, c_type, stats, moves, items, BATTLE_AI_NONE);
}

/* Called by test functions to check give_move returns properly*/
void check_give_move(combatant_t* player, combatant_t* enemy, difficulty_t difficulty, move_t* expected)
{
    move_t *actual_move, *expected_move;
    actual_move = give_move(player, enemy, difficulty);

    cr_assert_eq(actual_move->id, expected->id, "give_move did not return expected move!");
}

/* Ensures give_move returns a random move when enum is BATTLE_AI_RANDOM*/
Test(battle_ai, give_move_random)
{
    check_give_move(new_battle_player(),
            new_enemy(),
            BATTLE_AI_RANDOM,
            expected_move_random());
}

/* Ensures give_move returns the hardest move when enum is BATTLE_AI_BEST*/
Test(battle_ai, give_move_greedy)
{
    check_give_move(new_battle_player(),
            new_enemy(),
            BATTLE_AI_GREEDY,
            expected_move_greedy());
}

/* Ensures find_random returns a random move*/
Test(battle_ai, find_random)
{
    combatant_t *player, *enemy;
    move_t *expected_move, *actual_move;

    player = new_battle_player();
    enemy = new_enemy();

    expected_move = expected_move_random();
    actual_move = find_random(player, enemy);

    cr_assert_not_null(player, "combatant_new() failed");
    cr_assert_not_null(enemy, "combatant_new() failed");

    cr_assert_eq(actual_move->id, expected_move->id, "find_random did not return random move!");
}

/* Ensures find_greedy returns the hardest move*/
Test(battle_ai, find_greedy)
{
    combatant_t *player, *enemy;
    move_t *expected_move, *actual_move;

    player = new_battle_player();
    enemy = new_enemy();

    expected_move = expected_move_greedy();
    actual_move = find_greedy(player, enemy);

    cr_assert_not_null(player, "combatant_new() failed");
    cr_assert_not_null(enemy, "combatant_new() failed");

    cr_assert_eq(actual_move->id, expected_move->id, "find_greedy did not find the hardest move!");
}

/* Ensures normal damage is calculated correctly*/
Test(battle_ai, damage_norm)
{
    combatant_t *player, *enemy;
    move_t* move;

    player = new_battle_player();
    enemy = new_enemy();
    move = expected_move_greedy();

    double expected = 1.0*24.0;
    double actual = damage(player, move, enemy);

    cr_assert_not_null(player, "combatant_new() failed");
    cr_assert_not_null(enemy, "combatant_new() failed");

    cr_assert_float_eq(actual, expected, 1E-6, "Expected %.2f damage but calculated %.2f damage", expected, actual);
}

/* Ensures critical damage is calculated correctly*/
Test(battle_ai, damage_crit)
{
    combatant_t *player, *enemy;
    move_t* move;

    player = new_battle_player();
    enemy = new_enemy_crit();
    move = expected_move_greedy();

    double expected = 1.5*24.0;
    double actual = damage(player, move, enemy);

    cr_assert_not_null(player, "combatant_new() failed");
    cr_assert_not_null(enemy, "combatant_new() failed");

    cr_assert_float_eq(actual, expected, 1E-6, "Expected %.2f damage but calculated %.2f damage", expected, actual);
}


