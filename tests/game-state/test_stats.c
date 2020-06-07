#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "game-state/stats.h"




Test(stats, global_init){
    stats_global_t *global_stat = malloc(sizeof(stats_global_t));
    
    int ret_val = stats_global_init(global_stat, "health", 100);
    
    cr_assert_eq(ret_val, SUCCESS, "stats_global_init() failed to return SUCCESS");
    
    cr_assert_not_null(global_stat, "stats_global_init() failed. Health stat is NULL");
    
    cr_assert_eq(strcmp(global_stat->name,
        "health"), 0,
        "stats_global_init() failed to set the starting stat name");
    cr_assert_eq(global_stat->max, 100, 
        "stats_global_init() failed to set the maximal value");
    free_stats_global(global_stat);
}

Test(stats, stats_init){
    stats_global_t *stat_global = stats_global_new("health", 100);
    cr_assert_not_null(stat_global, 
        "stats_global_new() failed. Health stat is NULL");

    stats_t* stat = malloc(sizeof(stats_t));
    int ret_val = stats_init(stat, stat_global, 100);
    cr_assert_eq(ret_val, SUCCESS, "stats_init() failed to return SUCCESS");

    cr_assert_not_null(stat, "stats_init() failed. Health stat is NULL");
    
    cr_assert_eq(strcmp(stat->global->name,
        "health"), 0,
        "stats_init() failed to set the pointer to the global stat");
    cr_assert_eq(strcmp(stat->key,
        "health"), 0,
        "stats_init() failed to set the key");
    cr_assert_eq(stat->val, 100, 
        "stats_init() failed to set the starting stat value");
    cr_assert_eq(stat->modifier, 1, 
        "stats_init() failed be set the modifier to 1");
    cr_assert_leq(stat->val, stat->global->max, 
        "stat base value exceeds maximal value");
    free_stat(stat);
    free_stats_global(global_stat);
}

/* Checks that stats_global_new() mallocs memory for a stats_global struct*/
/* and initializes it with a stat's name and the maximal value*/
Test(stats, stats_global_new){
    
    stats_global_t *global_stat;
    global_stat = stats_global_new("health", 100);
    cr_assert_not_null(global_stat, "stats_global_new() failed. Health stat is NULL");
    cr_assert_eq(strcmp(global_stat->name,
        "health"), 0,
        "stats_global_new() failed to set stat name to health");
    cr_assert_eq(global_stat->max, 100, 
    "stats_global_new() failed to set the maximal stat value correctly");
    free_stats_global(global_stat);
}

/* Checks that stats_new() mallocs memory for a stat struct
and initializes it with the pointer to the global stat and a starting value */
Test(stats, stats_new){
    stats_global_t *stat_global = stats_global_new("health", 100);
    cr_assert_not_null(stat_global, 
        "stats_global_new() failed. Health stat is NULL");

    stats_t *stat = stats_new(stat_global, 100);
    cr_assert_not_null(stat, "stats_new() failed. Health stat is NULL");
    cr_assert_eq(strcmp(stat-> global -> name,
        "health"), 0,
        "stats_new() failed to link the global stat pointer");
    cr_assert_eq(stat->val, 100, 
        "stats_new() failed to set the starting stat value");
    cr_assert_leq(stat->val, stat->global->max, 
        "stat base value exceeds maximal value.");
    free_stat(stat);
    free_stats_global(global_stat);
}


Test(stats, free){
    stats_global_t *stat_global = stats_global_new("health", 100);
    cr_assert_not_null(stat_global, "stats_global_new() failed. Global health stat is NULL");

    stats_t* stat = stats_new(stat_global, 100);
    cr_assert_not_null(stat, "stats_new() failed. Player health stat is NULL");
    
    int ret_val = free_stats(stat);
    cr_assert_eq (ret_val, SUCCESS, "free_stats() failed to return SUCCESS");
}

Test(stats,global_free){
    stats_global_t *stat_global = stats_global_new("health", 100);
    cr_assert_not_null(stat_global, "stats_global_new() failed. Global health stat is NULL");

    int ret_val = free_stats_global(stat_global);
    cr_assert_eq(ret_val, SUCCESS, "free_stats_global() failed to return SUCCESS");
}

/* Checks that add_stat correctly adds a new stat 
   to a hash table*/
Test (stats, add_stat)
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

    int rc = add_stat(&sh, &s);

    cr_assert_eq(rc, SUCCESS, "add_stat failed");

    cr_assert_not_null(sh, "add_stat did not add the stat");
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

    int rc = add_stat(&sh, &s1);

    cr_assert_eq(rc, SUCCESS, "add_stat failed");


    stats_global_t speed;
    speed.name = "speed";
    speed.max = 100;

    stats_t s2;
    s2.key = "speed";
    s2.global = &speed;
    s2.val = 25;
    s2.max = 50;
    s2.modifier = 0.9;

    rc = add_stat(&sh, &s2);

    cr_assert_eq(rc, SUCCESS, "add_stat failed");

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
