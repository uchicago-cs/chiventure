#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "game-state/stats.h"

/* Checks that stats_global_new() mallocs memory for a stats_global struct*/
/* and initializes it with a stat's name and the maximal value*/
Test(stats, stats_global_new){
    stats_global_t* stat = stats_global_new("health", 100);
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
    stats_global_t* stat_global = stats_global_new("health", 100);
    cr_assert_not_null(stat_global, 
        "stats_global_new() failed. Health stat is NULL");

    stats_t *stat = stats_new("health", 100);
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
    stats_global_t* stat;
    
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
    stats_global_t* stat_global = stats_global_new("health", 100);
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
        "stats_new() failed to set the starting stat value");
    cr_assert_eq(stat->modifier, 0, 
        "stats_new() failed be set the modifier to 0");
    cr_assert_leq(stat->val, stat->global->max, 
        "stat base value exceeds maximal value");
}

Test(stats, free){
    stats_global_t* stat_global = stats_global_new("health", 100);
    cr_assert_not_null(stat_global, "stats_global_new() failed. Global health stat is NULL");

    stats_t* stat = stats_new("health", 100);
    cr_assert_not_null(stat, "stats_new() failed. Player health stat is NULL");
    
    int ret_val = free_stats(stat);
    cr_assert_eq (ret_val, SUCCESS, "free_stats() failed to return SUCCESS");
}

Test(stats,global_free){
    stats_global_t* stat = stats_global_new ("health",100);
    cr_assert_not_null(stat, "stats_global_new() failed. Global health stat is NULL");

    int ret_val = free_stats_global(stat);
    cr_assert_eq(ret_val, SUCCESS, "free_stats_global() failed to return SUCCESS");
}

Test(stats, change_stat) {
    stats_global_t* stat_global = stats_global_new("health", 100);
    cr_assert_not_null(stat_global, "stats_global_new() failed. Global health stat is NULL");

    stats_t* stat = stats_new("health", 100);
    cr_assert_not_null(stat, "stats_new() failed. Player health stat is NULL");

    stat -> global = stat_global;
    stat -> val = 3.0;
    stat -> max = 5.0;
    stat -> modifier = 1.0;



}

Test(stats, get_mod) {

}

Test(stats, get_max) {

}

Test(stats, -----) {

}