#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "game-state/stats.h"

Test(stats, change_stat_max)
{
    stats_hash_t *sh = NULL;

    stats_global_t g1, g2;
    g1.name = "Health";
    g1.max = 100;
    g2.name = "XP";
    g2.max = 100;

    stats_t s1, s2;
    s1.key = "Health";
    s1.global = &g1;
    s1.val = 50;
    s1.max = 50;
    s1.modifier = 1;

    s2.key = "XP";
    s2.global = &g2;
    s2.val = 50;
    s2.max = 50;
    s2.modifier = 1;
    
    add_stat_player(&sh, &s1);
    add_stat_player(&sh, &s2);

    change_stat_max(sh, "Health", 50);
    change_stat_max(sh, "XP", 25);

    cr_assert_float_eq(s1.max, 100, 1E-6, "change_stat_max didn't set the right value");
    cr_assert_float_eq(s2.max, 75, 1E-6, "change_stat_max didn't set the right value");
}

/* Checks that add_stat_player correctly adds a new stat 
   to a hash table*/
Test (stats, add_stat_player)
{
    stats_hash_t *sh = NULL;
    stats_global_t g;
    g.name = "health";
    g.max = 100;

    stats_t s;
    s.key = "health";
    s.global = &g;
    s.val = 50;
    s.max = 75;
    s.modifier = 1.1;

    int rc = add_stat_player(&sh, &s);

    cr_assert_eq(rc, SUCCESS, "add_stat_player failed");

    cr_assert_not_null(sh, "add_stat_player did not add the stat");
}

/* Checks that display_stat returns the correct list of stats */
Test(stats, display_stat)
{
    stats_hash_t *sh = NULL;

    stats_global_t health;
    health.name = "health";
    health.max = 100;

    stats_t s1;
    s1.key = "health";
    s1.global = &health;
    s1.val = 50;
    s1.max = 75;
    s1.modifier = 1.1;

    int rc = add_stat_player(&sh, &s1);

    cr_assert_eq(rc, SUCCESS, "add_stat_player failed");


    stats_global_t speed;
    speed.name = "speed";
    speed.max = 100;

    stats_t s2;
    s2.key = "speed";
    s2.global = &speed;
    s2.val = 25;
    s2.max = 50;
    s2.modifier = 0.9;

    rc = add_stat_player(&sh, &s2);

    cr_assert_eq(rc, SUCCESS, "add_stat_player failed");

    char *list = display_stats(sh);

    cr_assert_str_eq(list, "health, speed",
                     "expected: health, speed, but display_stat returned %s",
                     list);

    free(list);
}

/* Checks that global_effect_init correctly initializes a global effect struct */
Test (stats, effect_global_init)
{
    effects_global_t effect;

    int rc = global_effect_init(&effect, "health");

    cr_assert_eq(rc, SUCCESS, "global_effect_init failed");
    cr_assert_not_null(effect.name, "global_effect_init did not set effect name");
    cr_assert_str_eq(effect.name, "health", "global_effect_init did not set name");
}

/* Checks that global_effect_new correctly creates a new global effect struct */
Test (stats, effect_global_new)
{
    effects_global_t *effect = global_effect_new("health");

    cr_assert_not_null(effect, "global_effect_new failed");
    cr_assert_str_eq(effect->name, "health", "global_effect_new did not set name");
}

/* Checks that effect_init correctly initializes an effect struct */
Test (stats, stat_effect_init)
{
    effects_global_t *global = global_effect_new("speed");
    cr_assert_not_null(global, "global_effect_new failed");

    stat_effect_t effect;

    int rc = stat_effect_init(&effect, global);

    cr_assert_eq(rc, SUCCESS, "stat_effect_init failed");
    cr_assert_str_eq(effect.key, global->name, "stat_effect_init did not set key");
    cr_assert_eq(effect.global, global, "stat_effect_init did not set global pointer");
}

/* Checks that stat_effect_new correctly creates a new player effect */
Test (stats, stat_effect_new)
{
    effects_global_t *global = global_effect_new("health");
    cr_assert_not_null(global, "global_effect_new failed");

    stat_effect_t *effect = stat_effect_new(global);

    cr_assert_not_null(effect, "stat_effect_new failed");
    cr_assert_str_eq(effect->key, global->name, "stat_effect_new did not set key");
    cr_assert_eq(effect->global, global, "stat_effect_new did not set global pointer");
}