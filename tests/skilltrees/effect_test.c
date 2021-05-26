#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>
#include "skilltrees/effect.h"
#include "common/ctx.h"
#include "common/uthash.h"
#include "game-state/stats.h"
#include "game-state/item.h"

/* Creating a context object and some basic hash tables so that we can test our functions.
   Also adding a player to the ctx object. */

chiventure_ctx_t* create_player_and_stats (){
    game_t* game = game_new("TEST GAME");
    chiventure_ctx_t* ctx = chiventure_ctx_new(game);
    game->curr_stats = NULL;
    player_t* player = player_new("TEST CHARACTER");
    stats_global_t *gs_health = stats_global_new("max_health", 100);
    stats_t* gs_health_stat = stats_new(gs_health, 100);
    HASH_ADD_KEYPTR(hh, game->curr_stats, gs_health->name, strlen(gs_health->name), gs_health);
    HASH_ADD_KEYPTR(hh, player->player_stats, gs_health_stat->key, strlen(gs_health_stat->key), gs_health_stat);
    stats_global_t *player_health = stats_global_new("current_health", 50);
    stats_t* player_health_stat = stats_new(player_health, 50);
    HASH_ADD_KEYPTR(hh, game->curr_stats, player_health->name, strlen(player_health->name), player_health);
    HASH_ADD_KEYPTR(hh, player->player_stats, player_health_stat->key, strlen(player_health_stat->key), player_health_stat);
    game->all_players = NULL;
    HASH_ADD_KEYPTR(hh, game->all_players, player->player_id, strlen(player->player_id), player);
    game->curr_player = player;
    player -> player_effects = (effects_hash_t*)malloc(sizeof(effects_hash_t));
    /*Checking if everything works*/

    stats_global_t* stat_test;
    HASH_FIND_STR(game->curr_stats, "max_health", stat_test);
    cr_assert_eq(100, stat_test->max);

    player_hash_t*  player_test;
    HASH_FIND_STR(game->all_players, "TEST CHARACTER", player_test);
    
    return ctx;
}

/* Also adding an item to the game so that we can test item attribute effects */
int add_item (chiventure_ctx_t* ctx)
{
    game_t* game = ctx -> game;
    item_t* bomb = item_new("BOMB", "An armed bomb", "5 seconds till detonation");
    attribute_t* is_armed = bool_attr_new("ARMED", true);
    int check = add_attribute_to_hash(bomb, is_armed);
    cr_assert_eq(check, SUCCESS, "Error: Failed to add attribute to item");
    game->all_items = NULL;
    check = add_item_to_hash(&(game->all_items), bomb);
    cr_assert_eq(check, SUCCESS, "Error: Failed to add item to hash");
    // Checking if the bomb is added to the item hash and is armed
    item_t* item_test;
    HASH_FIND_STR(game->all_items, "BOMB", item_test);
    cr_assert_not_null(item_test, "Error : Bomb not found");
    attribute_t* attr_test = get_attribute(item_test, "ARMED");
    cr_assert_eq(attr_test->attribute_value.bool_val, true, "Error : Bomb not armed");
    return SUCCESS;
}

// Tests for move unlock effects
Test(effect_tests, define_move_effect_test)
{
    move_t *move = move_new("abc", 1, NULL, true, 10, 55);
    cr_assert_not_null(move, "Error: move_new failed to create move");
    move_effect_t* moveeffect = define_move_effect(move);
    cr_assert_not_null(moveeffect, "Error: define_move_effect failed to create move effect");

}

Test(effect_tests, make_move_effect_test)
{
    move_t *move = move_new("abc", 1, NULL, true, 10, 55);
    cr_assert_not_null(move, "Error: move_new failed to create move");
    move_effect_t* moveeffect = define_move_effect(move);
    cr_assert_not_null(moveeffect, "Error: define_move_effect failed to create move effect");
    effect_t* effect = make_move_effect(moveeffect);
    cr_assert_eq(effect->effect_type, MOVE_UNLOCK, "Error: make_move_effect failed to set effect type");
    cr_assert_not_null(effect, "Error: make_move_effect failed to create effect");

}

//Tests for stat mod effects

/* This test checks if the define function works correctly if all values provided are valid */
Test(effect_tests, define_player_stat_effect_correct_vals) 
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    char* stats_to_change[] = {"max_health", "current_health"};
    double mods[] = {150, 100};
    int durations[] = {5, 5};
    player_stat_effect_t* health_boost = define_player_stat_effect("health boost", stats_to_change, mods, durations, 2, ctx);
    cr_assert_not_null(health_boost, "Error: define_player_stat failed");
    cr_assert_eq(health_boost->player_stat_effect_name, "health boost", "Error: Name not assigned correctly");
    cr_assert_eq(health_boost->modifications[0], 150, "Error:  First modification is wrong");
    cr_assert_eq(health_boost->modifications[1], 100, "Error:  Second modification is wrong");
    cr_assert_eq(health_boost->durations[0], 5, "Error: First Duration is wrong");
    cr_assert_eq(health_boost->durations[1], 5, "Error: Second Duration is wrong");
    cr_assert_eq(health_boost->num_stats, 2, "Number of stats is wrong");
}

/* This test checks if the define function works correctly if a value provided is invalid */
Test(effect_tests, define_player_stat_effect_incorrect_vals)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    char* stats_to_change[] = {"max_health", "max_attack"};
    double mods[] = {150, 100};
    int durations[] = {5, 5};
    player_stat_effect_t* health_boost = define_player_stat_effect("health boost", stats_to_change, mods, durations, 2, ctx);
    cr_assert_eq(health_boost, NULL, "Error: Health boost should be null due to incorrect input");
}

/*This test checks if the make test sets the enum correctly */
Test(effect_tests, make_player_stat_effect_test)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    char* stats_to_change[] = {"max_health", "current_health"};
    double mods[] = {150, 100};
    int durations[] = {5, 5};
    player_stat_effect_t* health_boost = define_player_stat_effect("health boost", stats_to_change, mods, durations, 2, ctx);
    cr_assert_not_null(health_boost, "Error: define_player_stat failed");
    cr_assert_eq(health_boost->player_stat_effect_name, "health boost", "Error: Name not assigned correctly");
    cr_assert_eq(health_boost->modifications[0], 150, "Error:  First modification is wrong");
    cr_assert_eq(health_boost->modifications[1], 100, "Error:  Second modification is wrong");
    cr_assert_eq(health_boost->durations[0], 5, "Error: First Duration is wrong");
    cr_assert_eq(health_boost->durations[1], 5, "Error: Second Duration is wrong");
    cr_assert_eq(health_boost->num_stats, 2, "Number of stats is wrong");
    effect_t* stat_effect = make_player_stat_effect(health_boost);
    cr_assert_not_null(stat_effect, "Error: returns a null effect");
    cr_assert_not_null(stat_effect->data.s, "Error: did not copy over the effect correctly");
    cr_assert_eq(stat_effect->effect_type, PLAYER_STATISTIC_MOD, "Error: Enum value not correct");
}

/*This test checks if the execution function works as expected */
Test(effect_tests, execute_player_stat_effect_test)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    char* stats_to_change[] = {"max_health", "current_health"};
    double mods[] = {150, 100};
    int durations[] = {5, 5};
    player_stat_effect_t* health_boost = define_player_stat_effect("health boost", stats_to_change, mods, durations, 2, ctx);
    cr_assert_not_null(health_boost, "Error: define_player_stat failed");
    cr_assert_eq(health_boost->player_stat_effect_name, "health boost", "Error: Name not assigned correctly");
    cr_assert_eq(health_boost->modifications[0], 150, "Error:  First modification is wrong");
    cr_assert_eq(health_boost->modifications[1], 100, "Error:  Second modification is wrong");
    cr_assert_eq(health_boost->durations[0], 5, "Error: First Duration is wrong");
    cr_assert_eq(health_boost->durations[1], 5, "Error: Second Duration is wrong");
    cr_assert_eq(health_boost->num_stats, 2, "Number of stats is wrong");
    effect_t* stat_effect = make_player_stat_effect(health_boost);
    cr_assert_not_null(stat_effect, "Error: returns a null effect");
    cr_assert_not_null(stat_effect->data.s, "Error: did not copy over the effect correctly");
    cr_assert_eq(stat_effect->effect_type, PLAYER_STATISTIC_MOD, "Error: Enum value not correct");
    int check = execute_player_stat_effect(health_boost, ctx);
    cr_assert_eq(check, SUCCESS, "Error:  Failure of execute_player_stat");
    stats_hash_t* player_stats = ctx->game->curr_player->player_stats;
    stats_t* current_health;
    stats_t* max_health;
    HASH_FIND_STR(player_stats, "max_health", max_health);
    cr_assert_eq(150, max_health->modifier, "Max health not changed correctly");
    HASH_FIND_STR(player_stats, "current_health", current_health);
    cr_assert_eq(100, current_health->modifier, "Current health not changed correctly");
}

/*** TESTS FOR ITEM ATT EFFECT ***/

// This test checks if define_item_att_effect works correctly if all values input are correct



// This test checks if define_item_att_effect works correctly if the inputted value is not correct
Test(effect_tests, define_item_att_effect_invalid_vals)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    int check = add_item(ctx);
    cr_assert_eq(check, SUCCESS, "Error : Failed to add item");
}

/*
// This test checks if make_item_att_effect works correctly
Test(effect_tests, make_item_att_effect_test)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    int check = add_item(ctx);
    cr_assert_eq(check, SUCCESS, "Error : Failed to add item");
}
// This test checks if execute_item_att_effect works correctly
Test(effect_tests, execute_item_att_effect_test)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    int check = add_item(ctx);
    cr_assert_eq(check, SUCCESS, "Error : Failed to add item");
}
*/