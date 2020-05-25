#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "game-state/stats.h"

/* Checks that stats_new() mallocs memory for a stat struct
and initializes it with a the stat's name and a starting value */
Test(stats_init, new)
{
    stats_t *stat = stats_new("health", 100);
    cr_assert_not_null(stat, "stats_new() failed. Health stat is NULL");
    cr_assert_eq(strcmp(stat->name,
        "health"), 0,
        "stats_new() failed to set the starting stat name");
    cr_assert_eq(stat->val, 100, "stats_new() failed to set the starting stat value");
}

Test(stats_new, init){
    stats_t* stat;
    int ret_val = stats_init(stat, "health", 100);
    cr_assert_eq(ret_val, SUCCESS, "stats_new() failed to return SUCCESS")
    cr_assert_not_null(stat, "stats_init() failed. Health stat is NULL");
    cr_assert_eq(strcmp(stat->name,
        "health"), 0,
        "stats_init() failed to set the starting stat name");
    cr_assert_eq(stat->val, 100, "stats_new() failed to set the starting stat value");
    cr_assert_eq(stat->modifier, 0, "stats_new() failed be set the modifier to 0")
}

Test(free_stats, free){
    stats_t* stat = stats_new("health", 100);
    cr_assert_not_null(stat, "stats_new() failed. Health stat is NULL");
}

