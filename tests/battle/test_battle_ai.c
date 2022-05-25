#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "battle/battle_ai.h"
#include "battle/battle_moves.h"

/* Creates example hardcoded moves for the enemy*/
move_t* create_moveset1()
{
    stat_changes_t* eq_stats = stat_changes_new();
    stat_changes_init(eq_stats);
    eq_stats->phys_def = -10;
    eq_stats->accuracy = -10;
    
    stat_changes_t* swp_stats_pl = stat_changes_new();
    stat_changes_init(swp_stats_pl);
    swp_stats_pl->speed = 10;  

    stat_changes_t* swp_stats_en = stat_changes_new();
    stat_changes_init(swp_stats_en);
    swp_stats_en->speed = -10;  

    move_t *head, *earthquake, *poke, *sweep;
    head = earthquake; //NULL;
    earthquake = move_new(1, "Earthquake", 
    "Throws your enemy off balance, reducing their physical defense and accuracy.", 
                          MAG, TARGET, NO_TARGET, SINGLE, 25, NULL, 100, 
                          100, NULL, eq_stats, NULL, poke);
    poke = move_new(2, "Branch Poke", 
    "You poke your foe with a branch off the ground.", 
                    PHYS, NO_TARGET, NO_TARGET, SINGLE, 0, NULL, 
                    20, 100, NULL, NULL, earthquake, sweep);
    sweep = move_new(3, "Leg Sweep", 
    "With blinding speed, you knock your opponent down, decreasing their speed and increasing your own.", 
                     PHYS, BOTH, NO_TARGET, SINGLE, 10, 
                     NULL, 75, 100, swp_stats_pl, swp_stats_en, poke, NULL);
/*    DL_APPEND(head, earthquake);
    DL_APPEND(head, poke);
    DL_APPEND(head, rock_throw); */
    return head;
}

/* Creates example hardcoded stats for the battle_player*/
move_t* create_moveset2()
{
    stat_changes_t* lt_stats = stat_changes_new();
    stat_changes_init(lt_stats);
    lt_stats->speed = 15;
    
    move_t *head, *fire_blast, *punch, *lightning_touch;
    head = fire_blast; //NULL;
    fire_blast = move_new(4, "Fire Blast", "Fire is spewed over your foe.", 
                          MAG, NO_TARGET, NO_TARGET, SINGLE, 25, NULL, 95, 
                          100, NULL, NULL, NULL, punch);
    punch = move_new(5, "Punch", "You throw a solid punch at your foe.", 
                     PHYS, NO_TARGET, NO_TARGET, SINGLE, 0, NULL, 30, 100, 
                     NULL, NULL, fire_blast, lightning_touch);
    lightning_touch = move_new(6, "Lightning Touch", 
    "Your speed increases so you're as fast as lightning and you shock your opponent.", 
                               MAG, USER, NO_TARGET, SINGLE, 15, 
                               NULL, 75, 100, lt_stats, NULL, punch, NULL);
/*    DL_APPEND(head, fire_blast);
    DL_APPEND(head, punch);
    DL_APPEND(head, blaze_kick); */
    return head;
}

/* Creates example hardcoded stats for the enemy*/
stat_t* create_enemy_stats_avg()
{
    stat_t* test_stats = calloc(1, sizeof(stat_t));

    test_stats->max_hp = 200;
    test_stats->hp = 200;
    test_stats->max_sp = 75;
    test_stats->sp = 75;
    test_stats->phys_atk = 100;
    test_stats->mag_atk = 50;
    test_stats->phys_def = 60;
    test_stats->mag_def = 60;
    test_stats->speed = 50;
    test_stats->crit = 0;
    test_stats->accuracy = 100;
    test_stats->xp = 0;
    test_stats->level = 1;

    return test_stats;
}

/* Creates example hardcoded stats for the enemy*/
stat_t* create_enemy_stats_crit()
{
    stat_t* test_stats = create_enemy_stats_avg();
    test_stats->crit = 100;

    return test_stats;
}

/* Creates example hardcoded stats for the battle_player*/
stat_t* create_player_stats_avg()
{
    stat_t* test_stats = calloc(1, sizeof(stat_t));

    test_stats->max_hp = 150;
    test_stats->hp = 150;
    test_stats->max_sp = 80;
    test_stats->sp = 80;
    test_stats->phys_atk = 50;
    test_stats->mag_atk = 100;
    test_stats->phys_def = 60;
    test_stats->mag_def = 60;
    test_stats->speed = 55;
    test_stats->crit = 0;
    test_stats->accuracy = 100;
    test_stats->xp = 0;
    test_stats->level = 1;

    return test_stats;
}

stat_t* create_player_stats_critacc()
{
    stat_t* test_stats = create_player_stats_avg();
    test_stats->crit = 20;
    test_stats->accuracy = 90;
    
    return test_stats;
}

combatant_t* create_combatant(char* name, bool friendly, stat_t* stats, 
                              move_t* moves, difficulty_t ai)
{
    combatant_t* comb = combatant_new(name, friendly, NULL, stats, moves, NULL,
                                      NULL, NULL, NULL, ai);
    return comb;
}


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
    int expected_dmg = round(((2 * 1) / 5) * (((75 * (100 / 60)) / 50) + 2));

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
    int expected_dmg = round(((2 * 1) / 5) * (((20 * (100 / 60)) / 50) + 2) * 1.5);

    cr_assert_eq(expected_dmg, act_phys_dmg, 
                 "Crit Damage Calculated Incorrectly: Got %d instead of %d",
                  act_phys_dmg, expected_dmg);

    combatant_free(player);
    combatant_free(enemy);
}
