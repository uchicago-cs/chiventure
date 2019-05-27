#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "player.h"
#include "item.h"
#include "game.h"
#include "common-player.h"
#include "game_state_common.h"

// NEED TO WRITE ALL THE COMMENTS FOR EACH TEST

Test(player, new)
{
  player_t *player = player_new("1", 100);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(player->health, 100, "player_new() didn't set player health");
  cr_assert_eq(player->level, 1, "player_new() didn't properly call player_init()");
  cr_assert_eq(player->xp, 0, "player_new() didn't properly call player_init()");
  cr_assert_eq(strcmp(player->player_id, "1"), 0, "player_new() didn't properly call player_init() for player_id");
}

Test(player, init)
{
  player_t *player = player_new("1", 100);

  int res = player_init(player, "1", 56);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(player->health, 56, "player_init() didn't set player health");
  cr_assert_eq(player->level, 1, "player_init() didn't set level to 1");
  cr_assert_eq(player->xp, 0, "player_init() didn't set experience to 0");
  cr_assert_eq(strcmp(player->player_id, "1"), 0, "player_init() didn't set player_id to 1");
  cr_assert_eq(res, SUCCESS, "player_init() failed");
}

Test(player, free)
{
  player_t *player = player_new("1", 100);
  
  int res = player_free(player);

  cr_assert_not_null(player, "player_new() failed");
  
  cr_assert_eq(res, SUCCESS, "player_free() failed");
}

Test(player, get_health)
{
  player_t *player = player_new("1", 99);
  
  int health = get_health(player);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(health, 99, "get_health() returned incorrect health");
}

Test(player, change_health)
{
  player_t *player = player_new("1", 99);

  int health = change_health(player, 2, 100);
  int health2 = change_health(player, -20, 100);
  int health3 = change_health(player, 3, 83);

  cr_assert_not_null(player, "player_new() failed");
  
  cr_assert_eq(health, 100, "change_health() increased health past max");
  cr_assert_eq(health2, 80, "change_health() did not properly reduce health");
  cr_assert_eq(health3, 83, "change_health() did not properly add health");
}

Test(player, get_level)
{
  player_t *player = player_new("1", 99);

  int level = get_level(player);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(level, 1, "get_level() failed to return player level");
}

Test(player, change_level)
{
  player_t *player = player_new("1", 99);

  int level = change_level(player, 3);
  int level2 = change_level(player, -1);

  cr_assert_not_null(player, "player_new() failed");
  
  cr_assert_eq(level, 4, "change_level() failed to add to player level");
  cr_assert_eq(level2, 3, "change_level() failed to subtract from player level");
}

Test(player, get_xp)
{
  player_t *player = player_new("1", 99);

  int xp = get_xp(player);
  
  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(xp, 0, "get_xp() failed to return player experience");
}

Test(player, change_xp)
{
  player_t *player = player_new("1", 99);

  int xp = change_xp(player, 20);
  int xp2 = change_xp(player, -5);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(xp, 20, "change_xp() failed to add to player experience");
  cr_assert_eq(xp2, 15, "change_xp() failed to subtract from player experience");
}

Test(player, get_inventory)
{
  player_t *player = player_new("1", 99);
  player_t *player2 = player_new("1", 100);
  item_t *new_item = item_new();
  item_init(new_item, "a", "b", "c");
  add_item_to_player(player2, new_item);

  item_hash_t inv = get_inventory(player);
  item_hash_t inv2 = get_inventory(player2);
  
  cr_assert_not_null(player, "player_new() failed");
  cr_assert_not_null(player2, "player_new() failed");
  cr_assert_not_null(new_item, "item_new() failed");

  cr_assert_eq(inv, player->inventory, "get_inventory() failed to return NULL for empty inventory");
  cr_assert_eq(inv2, player2->inventory, "get_inventory() failed to return inventory");
}

Test(player, add_player_to_hash)
{
  player_t *player = player_new("1", 99);
  game_t *game = game_new();
  int res = add_player_to_hash(game, player);

  cr_assert_not_null(player, "player_new() failed");
  cr_assert_not_null(game->all_players, "add_player_to_hash failed to add player");

  cr_assert_eq(res, SUCCESS, "add_player_to_hash failed to add player");
}

Test(player, add_item_to_player)
{
  player_t *player = player_new("1", 100);
  item_t *new_item = item_new();
  item_init(new_item, "a", "b", "c");
  add_item_to_player(player, new_item);

  cr_assert_not_null(player, "player_new() failed");
  cr_assert_not_null(new_item, "item_new() failed");
  cr_assert_not_null(player->inventory, "add_item_to_player() failed to add item");
}

Test(player, delete_all_players)
{
  
}
