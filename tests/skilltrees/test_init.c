#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <criterion/criterion.h>
#include "test_init.h"


/* Creating a context object and some basic hash tables so that we can test our functions.
   Also adding a player to the ctx object. */

chiventure_ctx_t* create_player_and_stats() {
    /* Creation of things to be used for testing */
    game_t* game = game_new("TEST GAME");
    chiventure_ctx_t* ctx = chiventure_ctx_new(game);
    player_t* player = player_new("TEST CHARACTER");
    stats_global_t *gs_health = stats_global_new("max_health", 100);
    stats_t* gs_health_stat = stats_new(gs_health, 100);
    stats_global_t *player_health = stats_global_new("current_health", 50);
    stats_t* player_health_stat = stats_new(player_health, 50);
    stats_global_t *gs_peace = stats_global_new("peace_level", 0);
    stats_t* player_peace = stats_new(gs_peace, 0);

    /* Setting values */
    game->curr_stats = NULL;
    game->all_players = NULL;
    game->curr_player = player;
    player -> player_effects = (effects_hash_t*)malloc(sizeof(effects_hash_t));

    /* Adding to hash table */
    HASH_ADD_KEYPTR(hh, game->curr_stats, gs_health->name, strlen(gs_health->name), gs_health);
    HASH_ADD_KEYPTR(hh, player->player_stats, gs_health_stat->key, strlen(gs_health_stat->key), gs_health_stat);
    HASH_ADD_KEYPTR(hh, game->curr_stats, player_health->name, strlen(player_health->name), player_health);
    HASH_ADD_KEYPTR(hh, player->player_stats, player_health_stat->key, strlen(player_health_stat->key), player_health_stat);
    HASH_ADD_KEYPTR(hh, game->curr_stats, gs_peace->name, strlen(gs_peace->name), gs_peace);
    HASH_ADD_KEYPTR(hh, player->player_stats, player_peace->key, strlen(player_peace->key), player_peace);
    HASH_ADD_KEYPTR(hh, game->all_players, player->player_id, strlen(player->player_id), player);
    
    /*Checking if everything works*/
    stats_global_t* stat_test;
    HASH_FIND_STR(game->curr_stats, "max_health", stat_test);
    cr_assert_eq(100, stat_test->max);

    player_hash_t*  player_test;
    HASH_FIND_STR(game->all_players, "TEST CHARACTER", player_test);
    
    return ctx;
}

/* Also adding an item to the game so that we can test item attribute effects */
item_t* add_bomb_item(chiventure_ctx_t* ctx)
{
    /* Creating item and attribute */
    game_t* game = ctx -> game;
    item_t* bomb = item_new("BOMB", "An armed bomb", "5 seconds till detonation");
    attribute_t* is_armed = bool_attr_new("ARMED", true);
    game -> all_items = NULL;
    
    /* Adding things to hash tables */
    int check = add_attribute_to_hash(bomb, is_armed);
    cr_assert_eq(check, SUCCESS, "Error: Failed to add attribute to item");
    check = add_item_to_hash(&(game->all_items), bomb);
    cr_assert_eq(check, SUCCESS, "Error: Failed to add item to hash");
    
    /* Checking if the bomb is added to the item hash and is armed */
    item_t* item_test = get_item_in_hash((game->all_items), "bomb");
    cr_assert_str_eq(item_test->item_id, "bomb");
    attribute_t* attr_test = get_attribute(item_test, "ARMED");
    cr_assert_eq(attr_test->attribute_value.bool_val, true, "Error : Bomb not armed");
    return bomb;
}

effect_t* make_bomb_effect(item_t* bombitem)
{
    enum attribute_tag bombatt_tag = BOOLE;
    attribute_value_t bombmod; 
    bombmod.bool_val = false;
    item_attr_effect_t* itemdefusebombeffect = define_item_attr_effect(bombitem, "ARMED", bombatt_tag, bombmod);
    effect_t* defusebombeffect = make_item_attr_effect(itemdefusebombeffect);
    return defusebombeffect;
}

item_t* add_chop_item(chiventure_ctx_t* ctx)
{
    /* Creating item and attribute */
    game_t* game = ctx -> game;
    item_t* tree = item_new("TREE", "A Sturdy Oak Tree", "Use your skill to cut it down!");
    attribute_t* is_standing = bool_attr_new("STANDING", true);

    /* Adding things to hash tables */
    int check = add_attribute_to_hash(tree, is_standing);
    cr_assert_eq(check, SUCCESS, "Error: Failed to add attribute to item");
    check = add_item_to_hash(&(game->all_items), tree);
    cr_assert_eq(check, SUCCESS, "Error: Failed to add item to hash");

    /* Checking if the bomb is added to the item hash and is armed */
    item_t* item_test = get_item_in_hash((game->all_items), "tree");
    cr_assert_str_eq(item_test->item_id, "tree");
    attribute_t* attr_test = get_attribute(item_test, "STANDING");
    cr_assert_eq(attr_test->attribute_value.bool_val, true, "Error : Tree not standing");
    return tree;
}

effect_t* make_choptree_effect(item_t* tree)
{
    enum attribute_tag choptree_tag = BOOLE;
    attribute_value_t choptreemod;
    choptreemod.bool_val = false;
    item_attr_effect_t* itemchoptreeeffect = define_item_attr_effect(tree, "CHOP", choptree_tag, choptreemod);
    effect_t* choptreeeffect = make_item_attr_effect(itemchoptreeeffect);
}
    
    
effect_t* make_innerpeace_effect(chiventure_ctx_t* ctx)
{ 
    char* innerpeace_stats[] = {"current_health", "peace_level"};
    double innerpeace_mod[] = {250, 15};
    int innerpeace_duration[] = {8, 8};
    player_stat_effect_t* playerstatpeace = define_player_stat_effect("innerpeace", innerpeace_stats,
                                                                    innerpeace_mod, innerpeace_duration, 2, ctx);
    effect_t* innerpeace = make_player_stat_effect(playerstatpeace);
}