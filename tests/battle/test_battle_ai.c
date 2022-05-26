#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../include/battle/battle_test_utility.h"
#include "test_battle_common.h"

/* Common Functions */
/* Creates example moveset designed for the enemy*/
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
    head = earthquake;
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
    return head;
}

/* Creates example moveset designed for the player*/
move_t* create_moveset2()
{
    stat_changes_t* lt_stats = stat_changes_new();
    stat_changes_init(lt_stats);
    lt_stats->speed = 15;

    move_t *head, *fire_blast, *punch, *lightning_touch;
    head = fire_blast;
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
    return head;
}

/* Creates example stat spread for an average non-crit enemy */
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

/* Creates example stat spread for a crit enemy */
stat_t* create_enemy_stats_crit()
{
    stat_t* test_stats = create_enemy_stats_avg();
    test_stats->crit = 100;

    return test_stats;
}

/* Creates example stat spread for a player without crit or accuracy odds */
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

/* Creates example stat spread for a player with crit and accuracy odds */
stat_t* create_player_stats_critacc()
{
    stat_t* test_stats = create_player_stats_avg();
    test_stats->crit = 20;
    test_stats->accuracy = 90;

    return test_stats;
}

/* Creates basic combatant for testing purposes */
combatant_t* create_combatant(char* name, bool friendly, stat_t* stats,
                              move_t* moves, difficulty_t ai)
{
    combatant_t* comb = combatant_new(name, friendly, NULL, stats, moves, NULL,
                                      NULL, NULL, NULL, ai);
    return comb;
}
/* End of Common Functions */

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
