#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "game-state/stats.h"


Test(stats, deep_copy_global_stat)
{
    char *hp = "Health";
    int ret_val;

    stats_global_t* g1 = stats_global_new(hp, 100);

    cr_assert_not_null(g1, "stats_global_new() failed to allocate g1");

    stats_global_t* z1 = copy_global_stat(g1);

    cr_assert_not_null(z1, "copy_global_stat() failed to copy g1 to new pointer");

    cr_assert_str_eq(g1->name, z1->name, "copy_global_stat() results in different name");
    cr_assert_eq(g1->max, z1->max, "copy_global_stat() results in a different max value");

    if (g1 == z1)
        cr_assert_fail("copy_global_stat() results in copy and original still sharing same pointer");

    /* Free the original global stat */
    ret_val = free_stats_global(g1);
    cr_assert_eq(ret_val, SUCCESS, "free_stats_global() failed to return SUCCESS");

    /* Free the copied global stat */
    ret_val = free_stats_global(z1);
    cr_assert_eq(ret_val, SUCCESS, "free_stats_global() failed to return SUCCESS");
}

Test(stats, deep_copy_stat)
{
    char *hp = "Health";
    int ret_val;

    stats_global_t* g1 = stats_global_new(hp, 100);
    cr_assert_not_null(g1, "stats_global_new() failed to return g1");

    stats_t *stat = stats_new(g1, 100);
    cr_assert_not_null(stat, "stats_new() failed. Health stat is NULL");

    stats_t* new_stat = copy_stat(stat);
    cr_assert_not_null(new_stat, "copy_stat() failed to create deep copy of stat");

    /* Check that the global_stat linked in both version are the same */
    if (stat->global != new_stat->global)
        cr_assert_fail("copy_stat results in new_stat and original stat having different global_stat");
    /* Check that the char* in both versions are NOT the same */
    if (stat->key == new_stat->key)
        cr_assert_fail("copy_stat results in new stat and original stat having same char*");
    /* Check that the rest of fields in the original and copied versions are the same */
    cr_assert_eq(stat->val, new_stat->val, 
                 "copy_stat results in new stat and original stat having different val field");
    cr_assert_eq(stat->max, new_stat->max,
                 "copy_stat results in new stat and original stat having different max field");
    cr_assert_eq(stat->modifier, new_stat->modifier,
                 "copy_stat results in new stat and original stat having different modifier fields");
    cr_assert_str_eq(stat->key, new_stat->key, 
                     "copy_stat results in new stat and original stat having different key names");

    /* Free the original stat */
    ret_val = free_stats(stat);
    cr_assert_eq(ret_val, SUCCESS, "freeing the original stat failed");

    /* Free the copied stat */
    ret_val = free_stats(new_stat);
    cr_assert_eq(ret_val, SUCCESS, "freeing the deep copy new_stat failed");

    free_stats_global(g1);
}

Test(stats, deep_copy_stat_alter_original)
{
    stats_hash_t *sh = NULL;
    char *hp = "Health";
    char *xp = "XP";
    int ret_val;

    stats_global_t* g1 = stats_global_new(hp, 100);
    stats_global_t* g2 = stats_global_new(xp, 100);

    cr_assert_not_null(g1, "stats_global_new() could not create g1");
    cr_assert_not_null(g2, "stats_global_new() could not create g2");

    stats_t* s1 = stats_new(g1, 50);
    stats_t* s2 = stats_new(g2, 50);

    cr_assert_not_null(s1, "stats_new() could not create s1");
    cr_assert_not_null(s2, "stats_new() could not create s2");

    /* Create the deep copies of the stats BEFORE changing values */
    stats_t* c1 = copy_stat(s1);
    stats_t* c2 = copy_stat(s2);
    
    cr_assert_not_null(c1, "stats_new() could not create c1");
    cr_assert_not_null(c2, "stats_new() could not create c2");

    /* Change the stats with usage of change_stat_max */
    add_stat(&sh, s1);
    add_stat(&sh, s2);

    change_stat_max(sh, "Health", 50);
    change_stat_max(sh, "XP", 25);

    /* Check that s1 and s2 where changed according to change_stat_max */
    cr_assert_float_eq(s1->max, 100, 1E-6, "change_stat_max didn't set the right value");
    cr_assert_float_eq(s2->max, 75, 1E-6, "change_stat_max didn't set the right value");

    /* Check that c1 and c2 where completely unaffected with what happened to s1 & s2 */
    cr_assert_float_eq(c1->max, 50, 1E-6, "change_stat_max didn't set the right value");
    cr_assert_float_eq(c2->max, 50, 1E-6, "change_stat_max didn't set the right value");

    /* Free the original stats: s1 & s2 */
    ret_val = free_stats_table(sh);
    cr_assert_eq(ret_val, SUCCESS, "free_stats_table failed to free s1 & s2");

    /* Free the deep copies: c1 & c2 */
    ret_val = free_stats(c1);
    cr_assert_eq(ret_val, SUCCESS, "free_stats() failed to free c1");

    ret_val = free_stats(c2);
    cr_assert_eq(ret_val, SUCCESS, "free_stats() failed to free c2");

    /* Free the global stats: g1 & g2 */
    ret_val = free_stats_global(g1);
    cr_assert_eq(ret_val, SUCCESS, "free_stats_global() failed to free g1");

    ret_val = free_stats_global(g2);
    cr_assert_eq(ret_val, SUCCESS, "free_stats_global() failed to free g2");
}

Test(stats, free_global_effect)
{
    effects_global_t* effect;
    int ret_val;

    effect = global_effect_new("health");

    cr_assert_not_null(effect, "global_effect_new failed");
    cr_assert_not_null(effect->name, "global_effect_new did not set set a name");
    cr_assert_str_eq(effect->name, "health", "global_effect_init did not set with correct name");

    ret_val = free_global_effect(effect);
    cr_assert_eq(ret_val, SUCCESS, "free_global_effect did not free resources of global effect");
}

Test(stats, deep_copy_global_stat_effect)
{
    effects_global_t* effect;
    int ret_val;

    effect = global_effect_new("health");
    cr_assert_not_null(effect, "global_effect_new failed");
    cr_assert_str_eq(effect->name, "health", "global_effect_init did not set with correct name");

    effects_global_t* copy = copy_global_effect(effect);
    cr_assert_not_null(copy, "copy_global_effect() failed to copy effect to new pointer");

    /* Check that both versions share the same name */
    cr_assert_str_eq(effect->name, copy->name, 
                     "copy_global_effect() results in copied version having a different name than original");

    /* Free the original global effect */
    ret_val = free_global_effect(effect);
    cr_assert_eq(ret_val, SUCCESS, "free_global_effect() did not free resources of effect");

    /* Free the copied global stats */
    ret_val = free_global_effect(copy);
    cr_assert_eq(ret_val, SUCCESS, "free_stats_global() did not free resources of copy_effect");
}

Test(stats, free_stat_effect)
{
    effects_global_t* global;
    int ret_val;

    global = global_effect_new("health");
    /* Check that global effect field resources where created */
    cr_assert_not_null(global, "global_effect_new failed");
    cr_assert_not_null(global->name, "global_effect_new did not set set a name");

    stat_effect_t* effect = stat_effect_new(global);
    /* Check that effect field resources where created */
    cr_assert_not_null(effect, "stat_effect_new failed to create new stat effect");
    cr_assert_str_eq(effect->key, global->name, "stat_effect_new did not set key");
    cr_assert_eq(effect->global, global, "stat_effect_new did not set global pointer");

    ret_val = free_global_effect(global);
    cr_assert_eq(ret_val, SUCCESS, "free_global_effect did not free resources of global effect");

    ret_val = free_stat_effect(effect);
    cr_assert_eq(ret_val, SUCCESS, "free_stat_effect did not free resources of effect");
}

Test(stats, deep_copy_effect)
{
    int ret_val;

    effects_global_t* global = global_effect_new("health");

    cr_assert_not_null(global, "global_effect_new failed");

    stat_effect_t* effect = stat_effect_new(global);

    cr_assert_not_null(effect, "stat_effect_new failed to create new stat effect");
    cr_assert_str_eq(effect->key, global->name, "stat_effect_new did not set key");
    cr_assert_eq(effect->global, global, "stat_effect_new did not set global pointer");

    stat_effect_t* copy = copy_effect(effect);

    cr_assert_not_null(copy, "copy_effect failed to create copy stat effect");
    cr_assert_str_eq(copy->key, global->name, "copy_effect did not set key");

    /* Check that the global_stat effect linked in both version are the same */
    if (effect->global != copy->global)
        cr_assert_fail("copy_effect results in copy and original effect having different global_stat");
    /* Check that both versions contain the same name */
    cr_assert_str_eq(effect->key, copy->key, 
                     "copy_effect results in copied version having a different key/name than original");

    /* Free the original effect */
    ret_val = free_stat_effect(effect);
    cr_assert_eq(ret_val, SUCCESS, "free_stat_effect failed to free resources of effect");

    /* Free the new copied effect */
    ret_val = free_stat_effect(copy);
    cr_assert_eq(ret_val, SUCCESS, "free_stat_effect failed to free resources of copy");

    /* Free the global effect */
    ret_val = free_global_effect(global);
    cr_assert_eq(ret_val, SUCCESS, "free_global_effect() did not free resources of global");
}

/* Checks that copy_effect correctly points to affected stats */
Test (stats, deep_copy_effect_check_list)
{
    effects_hash_t *hash = NULL;
    char *hp = "health";
    char *spd = "speed";

    effects_global_t *global = global_effect_new("poison");
    cr_assert_not_null(global, "global_effect_new failed");


    stat_effect_t *effect = stat_effect_new(global);
    cr_assert_not_null(effect, "stat_effect_new failed");

    /* Create global stat health, and a stat corresponding to it */
    stats_global_t *health = stats_global_new(hp, 100);

    stats_t *s1 = malloc(sizeof(stats_t));
    s1->key = strndup(hp,100);
    s1->global = health;
    s1->val = 50.0;
    s1->max = 75.0;
    s1->modifier = 0.75;  

    /* Create global stat speed, and a stat corresponding to it */
    stats_global_t *speed = stats_global_new(spd, 100); 

    stats_t *s2 = malloc(sizeof(stats_t));
    s2->key = strndup(spd,100);
    s2->global = speed;
    s2->val = 25;
    s2->max = 50;
    s2->modifier = 1.0;

    stats_t *stats[] = {s1, s2};
    double intensities[] = {2.0, 0.5};
    int durations[] = {2, 5};

    int rc = apply_effect(&hash, effect, stats, 
                          intensities, durations, 2);
    
    cr_assert_eq(rc, SUCCESS, "apply_effect failed");
    cr_assert_not_null(hash, "apply_effect did not add effect to hash");

    stat_effect_t* copy = copy_effect(effect);

    stat_mod_t *tmp1, *tmp2, *ctmp1, *ctmp2, l1, l2;
    l1.stat = s1;
    l2.stat = s2;

    /* Check that original effect contains correct list of applied effects */
    LL_SEARCH(effect->stat_list, tmp1, &l1, stat_mod_equal);
    cr_assert_not_null(tmp1, "apply_effect did not add s1 to stat_mod_t list");
    cr_assert_str_eq(tmp1->stat->key, l1.stat->key, "fail");

    LL_SEARCH(effect->stat_list, tmp2, &l2, stat_mod_equal);
    cr_assert_not_null(tmp2, "apply_effect did not add s2 to stat_mod_t list");
    cr_assert_str_eq(tmp2->stat->key, l2.stat->key, "fail");

    /* Check that copied effect also points to correct list of applied effects */
    LL_SEARCH(copy->stat_list, ctmp1, &l1, stat_mod_equal);
    cr_assert_not_null(ctmp1, "copy_effect fails to see s1 added in stat_mod_t list");
    cr_assert_str_eq(ctmp1->stat->key, l1.stat->key, "fail");

    LL_SEARCH(copy->stat_list, ctmp2, &l2, stat_mod_equal);
    cr_assert_not_null(ctmp2, "copy_effect fails to see s2 added in stat_mod_t list");
    cr_assert_str_eq(ctmp2->stat->key, l2.stat->key, "fail");

    free_stats(s1);
    free_stats(s2);

    free_stats_global(health);
    free_stats_global(speed);

    free_global_effect(global);
    delete_all_stat_effects(hash);

    free_stat_effect(copy);
}

Test(stats, change_stat_max)
{
    stats_hash_t *sh = NULL;

    stats_global_t *g1, *g2;
    char *hp = "Health";
    char *xp = "XP";
    g1 = malloc(sizeof(stats_global_t));
    g2 = malloc(sizeof(stats_global_t));
    g1->name = strndup(hp,100);
    g1->max = 100;
    g2->name = strndup(xp,100);
    g2->max = 100;

    stats_t *s1, *s2;
    s1 = malloc(sizeof(stats_t));
    s2 = malloc(sizeof(stats_t));
    s1->key = strndup(hp,100);
    s1->global = g1;
    s1->val = 50;
    s1->max = 50;
    s1->modifier = 1;

    s2->key = strndup(xp, 100);
    s2->global = g2;
    s2->val = 50;
    s2->max = 50;
    s2->modifier = 1;
    
    add_stat(&sh, s1);
    add_stat(&sh, s2);

    change_stat_max(sh, "Health", 50);
    change_stat_max(sh, "XP", 25);

    cr_assert_float_eq(s1->max, 100, 1E-6, "change_stat_max didn't set the right value");
    cr_assert_float_eq(s2->max, 75, 1E-6, "change_stat_max didn't set the right value");
    free_stats_table(sh);
    free_stats_global(g1);
    free_stats_global(g2);
}



Test(stats, global_init)
{
    stats_global_t *global_stat = malloc(sizeof(stats_global_t));
    
    int ret_val = stats_global_init(global_stat, "health", 100);
    
    cr_assert_eq(ret_val, SUCCESS, "stats_global_init() failed to return SUCCESS");
    
    cr_assert_not_null(global_stat, "stats_global_init() failed. Health stat is NULL");
    
    cr_assert_str_eq(global_stat->name, "health",
        "stats_global_init() failed to set the starting stat name");
    cr_assert_eq(global_stat->max, 100, 
        "stats_global_init() failed to set the maximal value");
    free_stats_global(global_stat);
}

Test(stats, stats_init)
{
    stats_global_t *stat_global = stats_global_new("health", 100);
    cr_assert_not_null(stat_global, 
        "stats_global_new() failed. Health stat is NULL");

    stats_t *stat = malloc(sizeof(stats_t));
    int ret_val = stats_init(stat, stat_global, 100);
    cr_assert_eq(ret_val, SUCCESS, "stats_init() failed to return SUCCESS");

    cr_assert_not_null(stat, "stats_init() failed. Health stat is NULL");
    
    cr_assert_str_eq(stat->global->name, "health",
        "stats_init() failed to set the pointer to the global stat");
    cr_assert_str_eq(stat->key, "health",
        "stats_init() failed to set the key");
    cr_assert_eq(stat->val, 100, 
        "stats_init() failed to set the starting stat value");
    cr_assert_eq(stat->modifier, 1, 
        "stats_init() failed be set the modifier to 1");
    cr_assert_leq(stat->val, stat->global->max, 
        "stat base value exceeds maximal value");
    free_stats(stat);
    free_stats_global(stat_global);
}


/* Checks that stats_global_new() mallocs memory for a stats_global struct*/
/* and initializes it with a stat's name and the maximal value*/
Test(stats, stats_global_new)
{
    
    stats_global_t *global_stat;
    global_stat = stats_global_new("health", 100);
    cr_assert_not_null(global_stat, "stats_global_new() failed. Health stat is NULL");
    cr_assert_str_eq(global_stat->name, "health",
        "stats_global_new() failed to set stat name to health");
    cr_assert_eq(global_stat->max, 100, 
    "stats_global_new() failed to set the maximal stat value correctly");
    free_stats_global(global_stat);
}

/* Checks that stats_new() mallocs memory for a stat struct
and initializes it with the pointer to the global stat and a starting value */
Test(stats, stats_new)
{
    stats_global_t *stat_global = stats_global_new("health", 100);
    cr_assert_not_null(stat_global, 
        "stats_global_new() failed. Health stat is NULL");

    stats_t *stat = stats_new(stat_global, 100);
    cr_assert_not_null(stat, "stats_new() failed. Health stat is NULL");
    cr_assert_str_eq(stat->global->name, "health",
        "stats_new() failed to link the global stat pointer");
    cr_assert_eq(stat->val, 100, 
        "stats_new() failed to set the starting stat value");
    cr_assert_leq(stat->val, stat->global->max, 
        "stat base value exceeds maximal value.");
    free_stats(stat);
    free_stats_global(stat_global);
}


Test(stats, free)
{
    stats_global_t *stat_global = stats_global_new("health", 100);
    cr_assert_not_null(stat_global, "stats_global_new() failed. Global health stat is NULL");

    stats_t *stat = stats_new(stat_global, 100);
    cr_assert_not_null(stat, "stats_new() failed. Player health stat is NULL");
    
    int ret_val = free_stats(stat);
    cr_assert_eq (ret_val, SUCCESS, "free_stats() failed to return SUCCESS");
    free_stats_global(stat_global);
}

Test(stats, global_free)
{
    stats_global_t *stat_global = stats_global_new("health", 100);
    cr_assert_not_null(stat_global, "stats_global_new() failed. Global health stat is NULL");

    int ret_val = free_stats_global(stat_global);
    cr_assert_eq(ret_val, SUCCESS, "free_stats_global() failed to return SUCCESS");
}


Test(stats, free_table)
{
    stats_hash_t *sh = NULL;

    stats_global_t *gs1 = stats_global_new("health", 100);
    cr_assert_not_null(gs1, "stats_global_new() failed. Global health stat is NULL");
    stats_global_t *gs2 = stats_global_new("speed", 100);
    cr_assert_not_null(gs2, "stats_global_new() failed. Global health stat is NULL");

    stats_t* s1 = stats_new(gs1, 50);
    cr_assert_not_null(s1, "stats_new() failed. Player health stat is NULL");
    stats_t* s2 = stats_new(gs2, 50);
    cr_assert_not_null(s2, "stats_new() failed. Player speed stat is NULL");

    add_stat(&sh, s1);
    add_stat(&sh, s2);
    
    int ret_val = free_stats_table(sh);
    cr_assert_eq (ret_val, SUCCESS, "free_stats_table() failed to return SUCCESS");

    free_stats_global(gs1);
    free_stats_global(gs2);
}

Test(stats, free_global_table)
{
    stats_global_hash_t *gsh = NULL;

    stats_global_t *gs1 = stats_global_new("health", 100);
    cr_assert_not_null(gs1, "stats_global_new() failed. Global health stat is NULL");
    stats_global_t *gs2 = stats_global_new("speed", 100);
    cr_assert_not_null(gs2, "stats_global_new() failed. Global health stat is NULL");

    HASH_ADD_KEYPTR(hh, gsh, gs1->name, strlen(gs1->name), gs1);
    HASH_ADD_KEYPTR(hh, gsh, gs2->name, strlen(gs2->name), gs2);


    int ret_val = free_stats_global_table(gsh);
    cr_assert_eq (ret_val, SUCCESS, "free_stats_global_table() failed to return SUCCESS");
}

/* Checks that add_stat correctly adds a new stat to a hash table*/
Test (stats, add_stat)
{
    stats_hash_t *sh = NULL;

    stats_global_t *health = stats_global_new("health", 100);
    stats_t *s = stats_new(health, 75);

    int rc = add_stat(&sh, s);
    cr_assert_eq(rc, SUCCESS, "add_stat failed");

    cr_assert_not_null(sh, "add_stat did not add the stat");
    free_stats_table(sh);
    free_stats_global(health);
}

/* Checks that display_stat returns the correct list of stats */
Test(stats, display_stat)
{
    stats_hash_t *sh = NULL;

    stats_global_t *health = stats_global_new("health", 100);
    stats_t *s1 = stats_new(health, 75);

    int rc = add_stat(&sh, s1);
    cr_assert_eq(rc, SUCCESS, "add_stat failed");

    stats_global_t *speed = stats_global_new("speed", 100);
    stats_t *s2 = stats_new(speed, 50);

    rc = add_stat(&sh, s2);
    cr_assert_eq(rc, SUCCESS, "add_stat failed");

    char *list = display_stats(sh);

    cr_assert_str_eq(list, "health [75.00 / 75.00]\nspeed [50.00 / 50.00]\n",
                     "expected: health [75.00 / 75.00]\nspeed [50.00 / 50.00]\n,"
                     " but display_stat returned %s",
                     list);

    free(list);
    free_stats_table(sh);
    free_stats_global(speed);
    free_stats_global(health);
}

/* Checks that global_effect_init correctly initializes a global effect struct */
Test (stats, effect_global_init)
{
    effects_global_t effect;

    int rc = global_effect_init(&effect, "health");

    cr_assert_eq(rc, SUCCESS, "global_effect_init failed");
    cr_assert_not_null(effect.name, "global_effect_init did not set effect name");
    cr_assert_str_eq(effect.name, "health", "global_effect_init did not set name");
    free(effect.name);

}

/* Checks that global_effect_new correctly creates a new global effect struct */
Test (stats, effect_global_new)
{
    effects_global_t *effect = global_effect_new("health");

    cr_assert_not_null(effect, "global_effect_new failed");
    cr_assert_str_eq(effect->name, "health", "global_effect_new did not set name");
    free(effect->name);
    free(effect);

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
    free(global->name);
    free(global);
    free(effect.key);
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
    free(global->name);
    free(global);
    free(effect->key);
    free(effect);
}

/* Checks that add_stat_effect adds an effect to a hash table */
Test(stats, add_stat_effect)
{
    effects_hash_t *hash = NULL;
    effects_global_t *global = global_effect_new("effect");
    stat_effect_t *effect = stat_effect_new(global);
    int rc = add_stat_effect(&hash, effect);

    cr_assert_eq(rc, SUCCESS, "add_stat_effect failed");
    cr_assert_not_null(hash, "effect not added to hash");
    delete_all_stat_effects(hash);
    free(global->name);
    free(global);
}

/* Checks that apply_effect correctly applies and effect */
Test (stats, apply_effect)
{
    effects_global_t *global = global_effect_new("poison");
    cr_assert_not_null(global, "global_effect_new failed");
    effects_hash_t *hash = NULL;
    stat_effect_t *effect = stat_effect_new(global);
    cr_assert_not_null(effect, "stat_effect_new failed");
    char *hp = "health";
    char *spd = "speed";
    stats_global_t *health = malloc(sizeof(stats_global_t));
    health->name = strndup(hp, 100);
    health->max = 100;

    stats_t *s1 = malloc(sizeof(stats_t));
    s1->key = strndup(hp,100);
    s1->global = health;
    s1->val = 50.0;
    s1->max = 75.0;
    s1->modifier = 0.75;  

    stats_global_t *speed = malloc(sizeof(stats_global_t));
    speed->name = strndup(spd, 100);
    speed->max = 100;

    stats_t *s2 = malloc(sizeof(stats_t));
    s2->key = strndup(spd,100);
    s2->global = speed;
    s2->val = 25;
    s2->max = 50;
    s2->modifier = 1.0;

    stats_t *stats[] = {s1, s2};
    double intensities[] = {2.0, 0.5};
    int durations[] = {2, 5};

    int rc = apply_effect(&hash, effect, stats, 
                          intensities, durations, 2);
    
    cr_assert_eq(rc, SUCCESS, "apply_effect failed");
    cr_assert_eq(s1->modifier, 1.5, "apply_effect did not update s1 modifier");
    cr_assert_eq(s2->modifier, 0.5, "apply_effect did not update s2 modifier");

    cr_assert_not_null(hash, "apply_effect did not add effect to hash");

    stat_mod_t *tmp1, *tmp2, l1, l2;
    l1.stat = s1;
    LL_SEARCH(effect->stat_list, tmp1, &l1, stat_mod_equal);
    cr_assert_not_null(tmp1, "apply_effect did not add s1 to stat_mod_t list");
    cr_assert_str_eq(tmp1->stat->key, l1.stat->key, "fail");

    l2.stat = s2;
    LL_SEARCH(effect->stat_list, tmp2, &l2, stat_mod_equal);
    cr_assert_not_null(tmp2, "apply_effect did not add s2 to stat_mod_t list");
    cr_assert_str_eq(tmp2->stat->key, l2.stat->key, "fail");

    cr_assert_eq(tmp1->modifier, intensities[0], 
                 "apply_effect did not set stat_mod modifier");
    cr_assert_eq(tmp2->modifier, intensities[1], 
                 "apply_effect did not set stat_mod modifier");

    cr_assert_eq(tmp1->duration, durations[0], 
                 "apply_effect did not set stat_mod duration");
    cr_assert_eq(tmp2->duration, durations[1], 
                 "apply_effect did not set stat_mod duration");
    free_stats(s1);
    free_stats(s2);
    free_stats_global(health);
    free_stats_global(speed);
    free_global_effect(global);
    delete_all_stat_effects(hash);
}

Test(stats, change_stat) {
    stats_hash_t *sh = NULL;
    stats_global_t *g1 = stats_global_new("health", 100);
    stats_t *s1 = stats_new(g1, 75);
    
    s1->val = 50;
    s1->modifier = 1.1;

    stats_global_t *g2 = stats_global_new("charisma", 200);
    stats_t *s2 = stats_new(g2, 130);

 
    s2->val = 75;
    s2->modifier = 1;

    int rc1 = add_stat(&sh, s1);
    cr_assert_eq(rc1, SUCCESS, "add_stat_player_failed");
    int rc2 = add_stat(&sh, s2);
    stats_t *curr; 
    HASH_FIND(hh, sh, "health", strlen("health"), curr);
    cr_assert_eq(curr->val, 50,
        "change_stat base value not equal initially");

    change_stat(sh, "health", 10);
    cr_assert_eq(curr->val, 60,
       "change_stat failed to return success");
    change_stat(sh, "health", 20);
    cr_assert_eq(curr->val, 75,
        "change_stat local max failed");
    change_stat(sh, "health", 30);
    cr_assert_eq(curr->val, 75, 
        "change_stat global max failed");
    

    HASH_FIND(hh, sh, "charisma", strlen("charisma"), curr);
    cr_assert_eq(curr->val, 75,
        "change_stat base value not equal initially");


    change_stat(sh, "charisma", 10);
    cr_assert_eq(curr->val, 85,
       "change_stat failed to return success");
    change_stat(sh, "charisma", 60);
    cr_assert_eq(curr->val, 130,
        "change_stat local max failed");
    change_stat(sh, "charisma", 80);
    cr_assert_eq(curr->val, 130, 
        "change_stat global max failed");
    free_stats_global(g1);
    free_stats_global(g2);
    free_stats_table(sh);
}

Test(stats, get_stat_current) {
    stats_hash_t *sh = NULL;
    stats_global_t *g1 = stats_global_new("health", 100);
    stats_t *s1 = stats_new(g1, 75);

    s1->val = 50;
    s1->modifier = 1.1;
    int rc1 = add_stat(&sh, s1);
    cr_assert_eq(rc1, SUCCESS, "add_stat_player_failed");
    int s1_value = get_stat_current(sh, s1->key);
    cr_assert_eq(s1_value, 55, "get_stat_current failed");

    s1->val = 99;
    s1_value = get_stat_current(sh, s1->key);
    cr_assert_eq(s1_value, 100, "get_stat_current global max failed");
    free_stats_table(sh);
    free_stats_global(g1);
}
