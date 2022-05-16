#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "playerclass/class_structs.h"
#include "common/ctx.h"
#include "game-state/game.h"
#include "playerclass/class.h"
#include "playerclass/class_prefabs.h"
#include "skilltrees/skilltree.h"
#include "skilltrees/inventory.h"
#include "common/utlist.h"
#include "playerclass/multiclass.h"

//testing here is modeled after test_class_prefabs.c

/* Initializes a chicventure context */
chiventure_ctx_t* init_incomplete_context() {
    game_t* game = game_new("Sample game, incomplete context");
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

/* In this case, the stat hashtable is NULL: all stats will have to be generated
   when the class is. */
chiventure_ctx_t* init_statless_context() {
    game_t* game = game_new("Sample game, statless context");
    chiventure_ctx_t* ctx = chiventure_ctx_new(game);

    return ctx;
}

/* Checks whether the class and its basic fields are not null */
void check_field_presence(class_t* c) {
    cr_assert_not_null(c, "failed to be initialized (NULL)");
    cr_assert_not_null(c->name, "failed to initialize name");
    cr_assert_not_null(c->shortdesc, "failed to initialize short description");
    cr_assert_not_null(c->longdesc, "failed to initialize long description");
    cr_assert_not_null(c->attributes, "failed to initialize attributes object");
    cr_assert_not_null(c->base_stats, "failed to initialize stats");
    /* Currently, effects are not implemented, so this is NULL */
    // cr_assert_not_null(c->effects, "failed to initialize effects");

    /* Checks for stat presence, but not value */
    cr_assert_neq(get_stat_current(c->base_stats, "max_health"), -1, "failed to add stat");
    cr_assert_neq(get_stat_current(c->base_stats, "speed"), -1, "failed to add stat");
    cr_assert_neq(get_stat_current(c->base_stats, "physical_defense"), -1, "failed to add stat");
    cr_assert_neq(get_stat_current(c->base_stats, "physical_attack"), -1, "failed to add stat");
    cr_assert_neq(get_stat_current(c->base_stats, "ranged_attack"), -1, "failed to add stat");
    cr_assert_neq(get_stat_current(c->base_stats, "magic_defense"), -1, "failed to add stat");
    cr_assert_neq(get_stat_current(c->base_stats, "magic_attack"), -1, "failed to add stat");
    cr_assert_neq(get_stat_current(c->base_stats, "max_mana"), -1, "failed to add stat");
}

/* Checks whether skill fields are present, and whether the initialized skills 
 * match the expected list */
void check_skill_presence(class_t* c, int num_skills, char** names) {
    cr_assert_not_null(c->skilltree, "failed to initialize skilltree");
    cr_assert_not_null(c->starting_skills, "failed to initialize skill inventory");

    for(int i = 0; i < num_skills; i++)
        cr_assert_str_eq(c->skilltree->nodes[i]->skill->name, names[i], "failed to add skill");
}

Test(multiclass, multiclassing){
    chiventure_ctx_t* ctx = init_incomplete_context();
    int succ;

    class_t* c1 = class_prefab_new(ctx->game, "warrior");
    class_t* c2 = class_prefab_new(ctx->game, "bard");
    class_t* c3 = class_prefab_new(ctx->game, "rogue");

    check_field_presence(c1);
    check_field_presence(c2);
    check_field_presence(c3);

    class_t* multiclass = multiclass(c1, multiclass(c2, c3, "brogue"), "strong");

    check_field_presence(multiclass);
}

Test(multiclass, basic_shortdesc){

    chiventure_ctx_t* ctx = init_incomplete_context();
    int succ;

    class_t* c1 = class_prefab_new(ctx->game, "warrior");
    class_t* c2 = class_prefab_new(ctx->game, "bard");

    check_field_presence(c1);
    check_field_presence(c2);

    char* shortdesc = multiclass_shortdesc(c1, c2, &succ);

    cr_assert_eq(succ, SUCCESS, "exceeded maximum length flag was raised");

    cr_assert_str_eq(shortdesc, "Multiclass of warrior and bard",
                                "expected: Multiclass of warrior and bard, got %s", shortdesc);
}

Test(multiclass, iterated_shortdesc){

    chiventure_ctx_t* ctx = init_incomplete_context();

    class_t* c1 = class_prefab_new(ctx->game, "warrior");
    class_t* c2 = class_prefab_new(ctx->game, "bard");
    class_t* c3 = class_prefab_new(ctx->game, "rogue");

    check_field_presence(c1);
    check_field_presence(c2);
    check_field_presence(c3);

    class_t* multiclass = multiclass(c1, multiclass(c2, c3, "brogue"), "strong");

    check_field_presence(multiclass);

    char* shortdesc = multiclass->shortdesc;

    cr_assert_str_eq(shortdesc, "Multiclass of warrior, bard, and rogue",
                                "expected: Multiclass of warrior, bard and rogue. Got %s", shortdesc);
}