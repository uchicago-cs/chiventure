#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "game-state/stats.h"

/* Checks that add_stat_player correctly adds a new stat 
   to a hash table*/
Test (stats, add_stat_player)
{
    stats_hash_t *sh = NULL;
    stats_global_t g;
    g.name = "health";
    g.max = 100;

    stats_t s;
    s.global = &g;
    s.val = 50;
    s.max = 75;
    s.modifier = 1.1;

    int rc = add_stat_player(sh, s);

    cr_assert_eq(rc, SUCCESS, "add_stat_player failed");

    stats_t *test;
    HASH_FIND(hh, sh, g, sizeof(stats_global_t), test);

    cr_assert_not_null(test, "add_stat_player did not add the stat");
}