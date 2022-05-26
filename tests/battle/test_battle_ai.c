#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../include/battle/battle_test_utility.h"

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
