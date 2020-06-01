#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "game-state/stats.h"


/* Checks that stats_global_new() mallocs memory for a stats_global struct*/
/* and initializes it with a stat's name and the maximal value*/
Test(stats, stats_global_new){
    
    stats_global_t *stat = stats_global_new(NULL, "health", 100);
    cr_assert_not_null(stat, "stats_global_new() failed. Health stat is NULL");
    cr_assert_eq(strcmp(stat->name,
        "health"), 0,
        "stats_new() failed to set stat name to health");
    cr_assert_eq(stat->max, 100, 
    "stats_global_new() failed to set the maximal stat value correctly");
}

/* Checks that stats_new() mallocs memory for a stat struct
and initializes it with the pointer to the global stat and a starting value */
Test(stats, stats_new){
    stats_global_t *stat_global = stats_global_new(NULL, "health", 100);
    cr_assert_not_null(stat_global, 
        "stats_global_new() failed. Health stat is NULL");

    stats_t *stat = stats_new(stat_global, "health", 100);
    cr_assert_not_null(stat, "stats_new() failed. Health stat is NULL");
    cr_assert_eq(strcmp(stat-> global -> name,
        "health"), 0,
        "stats_new() failed to link the global stat pointer");
    cr_assert_eq(stat->val, 100, 
        "stats_new() failed to set the starting stat value");
    cr_assert_leq(stat->val, stat->global->max, 
        "stat base value exceeds maximal value.");
}
Test(stats, global_init){
    stats_global_t *stat;
    
    int ret_val = stats_global_init(stat, "health", 100);
    
    cr_assert_eq(ret_val, SUCCESS, "stats_global_init() failed to return SUCCESS");
    
    cr_assert_not_null(stat, "stats_global_init() failed. Health stat is NULL");
    
    cr_assert_eq(strcmp(stat->name,
        "health"), 0,
        "stats_global_init() failed to set the starting stat name");
    cr_assert_eq(stat->max, 100, 
        "stats_global_init() failed to set the maximal value");
}

Test(stats, init){
    stats_global_t *stat_global = stats_global_new(NULL, "health", 100);
    cr_assert_not_null(stat_global, 
        "stats_global_new() failed. Health stat is NULL");

    stats_t* stat;
    int ret_val = stats_init(stat, "health", 100);
    cr_assert_eq(ret_val, SUCCESS, "stats_init() failed to return SUCCESS");

    cr_assert_not_null(stat, "stats_init() failed. Health stat is NULL");
    
    cr_assert_eq(strcmp(stat->global->name,
        "health"), 0,
        "stats_init() failed to set the starting stat name");
    cr_assert_eq(stat->val, 100, 
        "stats_init() failed to set the starting stat value");
    cr_assert_eq(stat->modifier, 0, 
        "stats_init() failed be set the modifier to 0");
    cr_assert_leq(stat->val, stat->global->max, 
        "stat base value exceeds maximal value");
}

Test(stats, free){
    stats_global_t* stat_global = stats_global_new(NULL, "health", 100);
    cr_assert_not_null(stat_global, "stats_global_new() failed. Global health stat is NULL");

    stats_t* stat = stats_new(stat_global, "health", 100);
    cr_assert_not_null(stat, "stats_new() failed. Player health stat is NULL");
    
    int ret_val = free_stats(stat);
    cr_assert_eq (ret_val, SUCCESS, "free_stats() failed to return SUCCESS");
}

Test(stats,global_free){
    stats_global_t* stat = stats_global_new (NULL, "health",100);
    cr_assert_not_null(stat, "stats_global_new() failed. Global health stat is NULL");

    int ret_val = free_stats_global(stat);
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
