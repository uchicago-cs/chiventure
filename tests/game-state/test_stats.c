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

/*test(stats, get_stat_current) {
    stats_global_t* stat_global = stats_global_new("health", 100);

    stats_t* stat = stats_new("health", 100);
    HASH_ADD_INT(stat)

    int ret_val = get_stat_current(stat_global, stat, 0.5);
    cr_assert_eq(ret_val, 100, "free_stats_global() failed to return SUCCESS");
}*/

stats_hash_t *add_stats(int type) {
    stats_hash_t *sh = NULL;

    stats_global_t g1;
    g1.name = "health";
    g1.max = 100;

    stats_global_t g2;
    g2.name = "charisma";
    g2.max = 200;

    stats_global_t g2;
    g3.name = "charisma";
    g3.max = 200;

    stats_t s1;
    s1.key = "health";
    s1.global = &g2;
    s1.val = 50;
    s1.max = 75;
    s1.modifier = 1.1;

    stats_t s2;
    s2.key = "charisma";
    s2.global = &g2;
    s2.val = 75;
    s2.max = 130;
    s2.modifier = 1;

    stats_t s3;
    s3.key = "strength";
    s3.global = &g2;
    s3.val = 20;
    s3.max = 92;
    s3.modifier = 2;

    int rc, rc1, rc2;

    if (type == 1) {
        rc = add_stat_player(&sh, &s);
    } else if  (type == 2) {
        rc = add_stat_player(&sh, &s);
        rc2 = add_stat_player(&sh, &s2);
    } else if  (type == 3) {
        rc = add_stat_player(&sh, &s);
        rc2 = add_stat_player(&sh, &s2);
        rc3 = add_stat_player(&sh, &s3);
    }

    return sh;
}

Test(stats, change_stat) {
    stats_hash_t *sh = add_stats(3);
    
    cr_assert_eq(sh->val, 50, 
        "change_stat base value not equal initially");

    change_stat(sh, "strength", 10);
    cr_assert_eq(sh->val, 63, 
        "change_stat failed to return success");
}

/*Test(stats, get_stat_max) {}

Test(stats, get_stat_mod) {}*/