#include <criterion/criterion.h>
#include <stdio.h>

#include "playerclass/class_prefabs.h"
#include "common/ctx.h"
#include "game-state/game.h"

/* In this case, stats hashtables are complete with the stats we intend to use */
chiventure_ctx_t* init_complete_context() {
    game_t* game = game_new("Sample game, complete context");
    chiventure_ctx_t* ctx = chiventure_ctx_new(game);

    /* Cook up initial stats */

    game->curr_stats = NULL;
    // Weird double pointer to the hash table

    /* Placeholder global stats */
    stats_global_t *gs_health = stats_global_new("health", 100);
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

Test(class_prefabs, Warrior) {
    chiventure_ctx_t* ctx = init_complete_context();

    class_t *c = class_prefab_warrior(ctx);

    cr_assert_not_null(c, "Prefab class Warrior failed to be initialized (NULL)");
    cr_assert_not_null(c->name, "Prefab class Warrior failed to have name");
    cr_assert_not_null(c->shortdesc, "Prefab class Warrior failed to have short description");
    cr_assert_not_null(c->longdesc, "Prefab class Warrior failed to have long description");
    cr_assert_not_null(c->attributes, "Prefab class Warrior failed to have attributes object");
    
    /* Stat the was pre-declared */
    cr_assert_eq(get_stat_current(c->stats, "moxie"), 10, "Prefab class Warrior failed to have 10 moxie");
    /* Stat the is new */
    cr_assert_eq(get_stat_current(c->stats, "blood-thirst"), 97, "Prefab class Warrior failed to have 97 blood-thirst");
}
