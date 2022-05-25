#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "battle/battle_ai.h"
#include "battle/battle_moves.h"
#include "test_battle_common.h"

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
    combatant_t* player = create_combatant("Player", true,
                          create_player_stats_avg(), create_moveset2(),
                          BATTLE_AI_NONE);
    combatant_t* enemy = create_combatant("Enemy", false,
                          create_enemy_stats_avg(), create_moveset1(),
                          BATTLE_AI_GREEDY);

    int act_phys_dmg = damage(player, enemy->moves->next->next, enemy);
    int act_mag_dmg = damage(enemy, player->moves->next->next, player);
    int expected_dmg = round(((2.0 * 1.0) / 5.0) * (((75.0 * (100.0 / 60.0)) / 50.0) + 2.0));

    cr_assert_eq(expected_dmg, act_phys_dmg, 
                 "Physical Damage Calculated Incorrectly: Got %d instead of %d",
                  act_phys_dmg, expected_dmg);
    cr_assert_eq(expected_dmg, act_mag_dmg,
                 "Magical Damage Calculated Incorrectly: Got %d instead of %d",
                  act_mag_dmg, expected_dmg);
    cr_assert_eq(act_phys_dmg, act_mag_dmg,
                 "Physical and Magical Damage With Same Stats Not Equal; Got %d Phys and %d Mag", 
                  act_phys_dmg, act_mag_dmg);

    combatant_free(player);
    combatant_free(enemy);
}

/* Ensures that critical hits happen a reasonable amount for the odds */
Test(battle_ai, calculate_crit)
{
    int i, crits = 0;
    double mod;
    for (i = 0; i < 100; i++) {
        mod = crit_modifier(10);
        if (mod == 1.5) {
            crits++;
        }
    }
    cr_assert_gt(20, crits, "Too Many Crits for ten percent odds; Got %d crits",
                 crits);
} 

/* Ensures critical damage is calculated correctly*/
//Need to change to account for new crit changes in another PR
Test(battle_ai, damage_crit)
{
    combatant_t* player = create_combatant("Player", true,
                          create_player_stats_avg(), create_moveset2(),
                          BATTLE_AI_NONE);
    combatant_t* enemy = create_combatant("Enemy", false,
                          create_enemy_stats_crit(), create_moveset1(),
                          BATTLE_AI_GREEDY);

    int act_phys_dmg = damage(player, enemy->moves->next, enemy);
    int expected_dmg = round(((2.0 * 1.0) / 5.0) * (((20.0 * (100.0 / 60.0)) / 50.0) + 2.0) * 1.5);

    cr_assert_eq(expected_dmg, act_phys_dmg, 
                 "Crit Damage Calculated Incorrectly: Got %d instead of %d",
                  act_phys_dmg, expected_dmg);

    combatant_free(player);
    combatant_free(enemy);
}
