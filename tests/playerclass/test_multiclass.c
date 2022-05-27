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

// Testing here is modeled after test_class_prefabs.c

/* Initializes a chiventure context */
chiventure_ctx_t* init_incomplete_context1() {
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

Test(multiclass, basic_shortdesc){

    chiventure_ctx_t* ctx = init_incomplete_context1();
    int succ;

    class_t* c1 = class_prefab_new(ctx->game, "warrior");
    class_t* c2 = class_prefab_new(ctx->game, "bard");

    check_field_presence(c1);
    check_field_presence(c2);

    char* shortdesc = multiclass_shortdesc(c1, c2, &succ);

    cr_assert_eq(succ, SUCCESS, "exceeded maximum length flag was raised");

    char* expected = "Multiclass of warrior and bard.";
    cr_assert_str_eq(shortdesc, expected, "expected: %s. got %s", expected, shortdesc);
}

Test(multiclass, shortdesc_exceeds_max_length){

    chiventure_ctx_t* ctx = init_incomplete_context1();
    int succ;

    class_t* c1 = class_prefab_new(ctx->game, "warrior");
    strcpy(c1->name, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY");
    class_t* c2 = class_prefab_new(ctx->game, "bard");
    strcpy(c2->name, "ZYXWVUTSRQPONMLKJIHGFEDCBAzyxwvutsrqponmlkjihgfedcbaZYXWVUTSRQPONMLKJIHGFEDCBA");

    check_field_presence(c1);
    check_field_presence(c2);

    char* shortdesc = multiclass_shortdesc(c1, c2, &succ);

    cr_assert_eq(succ, FAILURE, "max length should have been exceeded but flag was not raised");
    cr_assert_str_eq(shortdesc, c1->shortdesc, "expected: %s. Got %s", c1->shortdesc, shortdesc);
}

Test(multiclass, basic_longdesc){

    chiventure_ctx_t* ctx = init_incomplete_context1();

    class_t* c1 = class_prefab_new(ctx->game, "warrior");
    class_t* c2 = class_prefab_new(ctx->game, "bard");

    check_field_presence(c1);
    check_field_presence(c2);

    class_t* mul = multiclass(c1, c2, "basic multiclass");

    check_field_presence(mul);

    char* longdesc = mul->longdesc;

    char* expected = "A mighty warrior.\n\nA skilled musician and magician.";
    cr_assert_str_eq(longdesc, expected, "expected: %s. Got %s", expected, longdesc);
}

Test(multiclass, longdesc_exceeds_max_length){

    chiventure_ctx_t* ctx = init_incomplete_context1();
    int succ;

    class_t* c1 = class_prefab_new(ctx->game, "warrior");
    strcpy(c1->shortdesc, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY"
                          "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY");
    class_t* c2 = class_prefab_new(ctx->game, "bard");
    strcpy(c2->shortdesc, "ZYXWVUTSRQPONMLKJIHGFEDCBAzyxwvutsrqponmlkjihgfedcbaZYXWVUTSRQPONMLKJIHGFEDCBA"
                          "ZYXWVUTSRQPONMLKJIHGFEDCBAzyxwvutsrqponmlkjihgfedcbaZYXWVUTSRQPONMLKJIHGFEDCBA");

    check_field_presence(c1);
    check_field_presence(c2);

    char* longdesc = multiclass_longdesc(c1, c2, &succ);

    cr_assert_eq(succ, FAILURE, "max length should have been exceeded but flag was not raised");
    cr_assert_str_eq(longdesc, c1->longdesc, "expected: %s. Got %s", c1->longdesc, longdesc);
}