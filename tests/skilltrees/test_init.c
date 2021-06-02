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
item_t* add_item (chiventure_ctx_t* ctx)
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