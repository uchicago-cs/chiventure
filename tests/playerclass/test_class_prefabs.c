#include <criterion/criterion.h>
#include <stdio.h>

#include "playerclass/class_prefabs.h"
#include "common/ctx.h"
#include "game-state/game.h"

/* In this case, stats hashtables are complete with the stats we intend to use */
chiventure_ctx_t* init_incomplete_context() {
    game_t* game = game_new("Sample game, complete context");
    chiventure_ctx_t* ctx = chiventure_ctx_new(game);

    /* Cook up initial stats */

    game->curr_stats = NULL;
    // Weird double pointer to the hash table

    /* Placeholder global stats */
    stats_global_t *gs_health = stats_global_new("max_health", 100);
    // Unused stats
    stats_global_t *gs_wit = stats_global_new("wit", 50);
    stats_global_t *gs_moxie = stats_global_new("moxie", 27);

    HASH_ADD_KEYPTR(hh, game->curr_stats, gs_health->name, strlen(gs_health->name), gs_health);
    HASH_ADD_KEYPTR(hh, game->curr_stats, gs_wit->name, strlen(gs_wit->name), gs_wit);
    HASH_ADD_KEYPTR(hh, game->curr_stats, gs_moxie->name, strlen(gs_moxie->name), gs_moxie);

    // Quick tests of hashtable
    stats_global_t* test;
    HASH_FIND_STR(game->curr_stats, "moxie", test);
    cr_assert_eq(27, test->max);

    return ctx;
}

/* A hard hitting and beefy physical attacker:
 * 25 Max Health
 * 10 Speed
 * 15 Physical Defense
 * 25 Physical Attack
 *  5 Ranged Attack
 *  5 Magic Defense
 *  5 Magic Attack
 * 15 Max Magic Energy */
Test(class_prefabs, Warrior) {
    chiventure_ctx_t* ctx = init_incomplete_context();

    // Note that the name is always stored lowercase.
    class_t *c = class_prefab_new(ctx, "Warrior");

    cr_assert_not_null(c, "failed to be initialized (NULL)");
    cr_assert_not_null(c->name, "failed to have name");
    cr_assert_not_null(c->shortdesc, "failed to have short description");
    cr_assert_not_null(c->longdesc, "failed to have long description");
    cr_assert_not_null(c->attributes, "failed to have attributes object");
    
    cr_assert_eq(get_stat_current(c->stats, "max_health"), 25, "failed to initialize previously declared stat");
    cr_assert_eq(get_stat_current(c->stats, "speed"), 10, "failed to initialize new stat");


    class_prefab_add_skills(c);
        
    cr_assert_str_eq(c->skilltree->nodes[0]->skill->name, "Sword Slash", "failed to initialize skilltree");
    cr_assert_str_eq(c->skilltree->nodes[1]->skill->name, "Double Slash", "failed to initialize skilltree");
    cr_assert_str_eq(c->skilltree->nodes[2]->skill->name, "Triple Slash", "failed to initialize skilltree");

    cr_assert_str_eq(c->combat->active[0]->name, "Sword Slash", "failed to initialize combat skill inventory");
}

Test(class_prefabs, warrior_sword_slash) {
    cr_assert_str_eq(warrior_sword_slash(""), "6");
}
