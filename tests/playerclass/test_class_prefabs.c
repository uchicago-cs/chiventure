#include <criterion/criterion.h>
#include <stdio.h>

#include "playerclass/class_prefabs.h"
#include "common/ctx.h"
#include "game-state/game.h"
#include "skilltrees/skilltree.h" 

/* In this case, the stat hashtable is incomplete: some of our stats exists,
   some are not yet declared. */
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
void check_field_pressence(class_t* c) 
{
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
void check_skill_pressence(class_t* c, int num_skills, char** names) 
{
    cr_assert_not_null(c->skilltree, "failed to initialize skilltree");
    cr_assert_not_null(c->starting_skills, "failed to initialize skill inventory");

    for(int i = 0; i < num_skills; i++)
        cr_assert_str_eq(c->skilltree->nodes[i]->skill->name, names[i], "failed to add skill");
}

/* Tests the bard class */
Test(class_prefabs, Bard) {
    chiventure_ctx_t* ctx = init_statless_context();

    /* Tests if we can find the name even if its case is wrong */
    class_t *c = class_prefab_new(ctx->game, "BARD");
    check_field_pressence(c);
    
    
    cr_assert_eq(get_stat_current(c->base_stats, "max_health"), 15, "failed to initialize stat");

    class_prefab_add_skills(c);

    char* skill_list[] = {"Magic Word", "Poetic Line", "Enchanted Stanza"};
    check_skill_pressence(c, 3, skill_list);

    cr_assert_str_eq(c->starting_skills->active[0]->name, "Magic Word", "failed to initialize skill inventory");
}

/* Tests the basic class */
Test(class_prefabs, Basic) {
    chiventure_ctx_t* ctx = init_statless_context();

    class_t* c = class_prefab_new(ctx->game, "basic");
    check_field_presence(c);

    cr_assert_eq(get_stat_current(c->base_stats, "max_health"), 25, "failed to initialize stat");
    cr_assert_eq(get_stat_current(c->base_stats, "speed"), 5, "failed to initalize stat");

    /* Skills not needed yet for this class */
}

/* Tests the monk class */
Test(class_prefabs, Monk) {
    chiventure_ctx_t* ctx = init_statless_context();

    class_t *c = class_prefab_new(ctx->game, "monk");
    check_field_pressence(c);
    
    cr_assert_eq(get_stat_current(c->base_stats, "max_health"), 25, "failed to initialize stat");

    class_prefab_add_skills(c);

    char* skill_list[] = {"Acrobatic Powers", "Spirit of Strength", "Supernova Circle"};
    check_skill_pressence(c, 3, skill_list);

    cr_assert_str_eq(c->starting_skills->active[0]->name, "Acrobatic Powers", "failed to initialize skill inventory");
}

/* Tests the ranger class */
Test(class_prefabs, Ranger) {
    chiventure_ctx_t* ctx = init_statless_context();

    class_t *c = class_prefab_new(ctx->game, "ranger");
    check_field_pressence(c);
    
    cr_assert_eq(get_stat_current(c->base_stats, "max_health"), 10, "failed to initialize stat");

    class_prefab_add_skills(c);

    char* skill_list[] = {"Close Shot", "Mid-range Shot", "Long Shot"};
    check_skill_pressence(c, 3, skill_list);

    cr_assert_str_eq(c->starting_skills->active[0]->name, "Close Shot", "failed to initialize skill inventory");
}

/* Tests the rogue class */
Test(class_prefabs, Rogue) {
    chiventure_ctx_t* ctx = init_statless_context();

    class_t *c = class_prefab_new(ctx->game, "rogue");
    check_field_pressence(c);
    
    cr_assert_eq(get_stat_current(c->base_stats, "max_health"), 10, "failed to initialize stat");

    class_prefab_add_skills(c);

    char* skill_list[] = {"Quick Hit", "Backstab", "Leg Swipe"};
    check_skill_pressence(c, 3, skill_list);

    cr_assert_str_eq(c->starting_skills->active[0]->name, "Quick Hit", "failed to initialize skill inventory");
}

/* Tests whether the warrior class is initialized as expected.
 * This test is a little more in depth than the rest, since the warrior has 
 * stats currently, unlike most of the other classes.  */
Test(class_prefabs, Warrior) {
    /* Tests a context were SOME stats were not declared */
    chiventure_ctx_t* ctx = init_incomplete_context();

    /* Note that the name is always stored lowercase. */
    class_t *c = class_prefab_new(ctx->game, "Warrior");
    check_field_pressence(c);
    
    cr_assert_eq(get_stat_current(c->base_stats, "max_health"), 20, "failed to initialize previously declared stat");
    cr_assert_eq(get_stat_current(c->base_stats, "speed"), 15, "failed to initialize new stat");

    class_prefab_add_skills(c);
        
    char* skill_list[] = {"Sword Slash", "Double Slash", "Triple Slash"};
    check_skill_pressence(c, 3, skill_list);

    cr_assert_str_eq(c->starting_skills->active[0]->name, "Sword Slash", "failed to initialize skill inventory");
}


/* Tests the Wizard class */
Test(class_prefabs, Wizard) {
    chiventure_ctx_t* ctx = init_statless_context();

    class_t *c = class_prefab_new(ctx->game, "WIZARD");
    check_field_pressence(c);
    
    cr_assert_eq(get_stat_current(c->base_stats, "max_health"), 10, "failed to initialize stat");

    class_prefab_add_skills(c);

    char* skill_list[] = {"Blinding Charm", "Paralyze Spell", "Arcane Explosion"};
    check_skill_pressence(c, 3, skill_list);

    cr_assert_str_eq(c->starting_skills->active[0]->name, "Blinding Charm", "failed to initialize skill inventory");
}

/* Tests the Druid class */
Test(class_prefabs, Druid) {
    chiventure_ctx_t* ctx = init_statless_context();

    class_t *c = class_prefab_new(ctx->game, "druid");
    check_field_pressence(c);

    cr_assert_eq(get_stat_current(c->base_stats, "max_health"), 15, "failed to initialize stat");

    class_prefab_add_skills(c);

    char* skill_list[] = {"frostbite", "control flames", "flame blade"};
    check_skill_pressence(c, 3, skill_list);

    cr_assert_str_eq(c->starting_skills->active[0]->name, "frostbite", "failed to initialize skill inventory");
}

/* Tests the Elementalist class */
Test(class_prefabs, Elementalist) {
    chiventure_ctx_t* ctx = init_statless_context();

    class_t *c = class_prefab_new(ctx->game, "elementalist");
    check_field_pressence(c);

    cr_assert_eq(get_stat_current(c->base_stats, "max_health"), 20, "failed to initialize stat");

    class_prefab_add_skills(c);

    char* skill_list[] = {"stone shards", "arc lightning", "dragon's tooth"};
    check_skill_pressence(c, 3, skill_list);

    cr_assert_str_eq(c->starting_skills->active[0]->name, "stone shards", "failed to initialize skill inventory");
}


/* Tests the Knight class */
Test(class_prefabs, Knight) {
    chiventure_ctx_t* ctx = init_statless_context();

    class_t *c = class_prefab_new(ctx->game, "knight");
    check_field_pressence(c);

    cr_assert_eq(get_stat_current(c->base_stats, "max_health"), 40, "failed to initialize stat");

    class_prefab_add_skills(c);

    char* skill_list[] = {"holy strike", "shield strike", "shackle strike"};
    check_skill_pressence(c, 3, skill_list);

    cr_assert_str_eq(c->starting_skills->active[0]->name, "holy strike", "failed to initialize skill inventory");
} 

/* Tests the Sorceror class */
Test(class_prefabs, Sorceror) {
    chiventure_ctx_t* ctx = init_statless_context();

    class_t *c = class_prefab_new(ctx->game, "sorceror");
    check_field_pressence(c);

    cr_assert_eq(get_stat_current(c->base_stats, "max_health"), 15, "failed to initialize stat");

    class_prefab_add_skills(c);
    
    char* skill_list[] = {"dark magic", "moon storm", "gates of rashonmon"};
    check_skill_pressence(c, 3, skill_list);

    cr_assert_str_eq(c->starting_skills->active[0]->name, "dark magic", "failed to initialize skill inventory");
}  



