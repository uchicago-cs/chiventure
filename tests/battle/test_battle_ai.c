#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../include/battle/battle_test_utility.h"

/* Ensures give_move returns a random move when enum is BATTLE_AI_RANDOM*/
Test(battle_ai, give_move_random)
{
    combatant_t* player = create_combatant("Player", true, 
                          create_player_stats_avg(), create_moveset2(), 
                          BATTLE_AI_NONE);
    combatant_t* enemy = create_combatant("Enemy", false, 
                          create_enemy_stats_avg(), create_moveset1(), 
                          BATTLE_AI_RANDOM); 
    move_t* rand_mv = give_move(player, enemy, BATTLE_AI_RANDOM);
    
    cr_assert_gt(rand_mv->id, 0, "find_random_move returned val < 1: %d", 
                 rand_mv->id);
    cr_assert_lt(rand_mv->id, 4, "find_random_move returned val > 3: %d", 
                 rand_mv->id);

    combatant_free(player);
    combatant_free(enemy);
}

/* Ensures give_move returns the highest damage move when enum is BATTLE_AI_GREEDY */
Test(battle_ai, give_move_greedy)
{
    combatant_t* player = create_combatant("Player", true,
                          create_player_stats_avg(), create_moveset2(),
                          BATTLE_AI_NONE);
    combatant_t* enemy = create_combatant("Enemy", false,
                          create_enemy_stats_avg(), create_moveset1(),
                          BATTLE_AI_GREEDY);
    move_t* greed_mv = give_move(player, enemy, BATTLE_AI_GREEDY);

    cr_assert_eq(greed_mv->id, 1, "find_greedy_move returned %d instead of 1", 
                 greed_mv->id);

    combatant_free(player);
    combatant_free(enemy);
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
