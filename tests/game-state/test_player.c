#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "game-state/player.h"
#include "game-state/item.h"
#include "game-state/game.h"
#include "game-state/game_state_common.h"

/* Checks that player_new() properly mallocs and inits a new player struct */
Test(player, new)
{
  player_t *player = player_new("1", 100);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(player->health, 100, "player_new() didn't set player health");
  cr_assert_eq(player->level, 1,
      "player_new() didn't properly call player_init()");
  cr_assert_eq(player->xp, 0,
      "player_new() didn't properly call player_init()");
  cr_assert_eq(strncmp(player->player_id, "1", MAX_ID_LEN), 0,
  "player_new() didn't properly call player_init() for player_id");
}

/* Checks that player_init() initializes the fields in the new player struct */
Test(player, init)
{
  player_t *player = player_new("1", 100);

  int res = player_init(player, "1", 56);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(player->health, 56, "player_init() didn't set player health");
  cr_assert_eq(player->level, 1, "player_init() didn't set level to 1");
  cr_assert_eq(player->xp, 0, "player_init() didn't set experience to 0");
  cr_assert_eq(strncmp(player->player_id, "1", MAX_ID_LEN), 0,
  "player_init() didn't set player_id to 1");
  cr_assert_eq(res, SUCCESS, "player_init() failed");
}

/* Checks that player_free() frees the given player struct from memory */
Test(player, free)
{
  player_t *player = player_new("1", 100);

  int res = player_free(player);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(res, SUCCESS, "player_free() failed");
}

/* Checks that get_health() returns the health of the player */
Test(player, get_health)
{
  player_t *player = player_new("1", 99);

  int health = get_health(player);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(health, 99, "get_health() returned incorrect health");
}

/* Checks that a player's health is changed by change_health()
both positively and negatively with a set maximum */
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

/* Checks that get_level() returns the level of the player */
Test(player, get_level)
{
  player_t *player = player_new("1", 99);

  int level = get_level(player);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(level, 1, "get_level() failed to return player level");
}

/* Checks that a player's level is changed by change_level()
both positively and negatively */
Test(player, change_level)
{
  player_t *player = player_new("1", 99);

  int level = change_level(player, 3);
  int level2 = change_level(player, -1);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(level, 4, "change_level() failed to add to player level");
  cr_assert_eq(level2, 3,
      "change_level() failed to subtract from player level");
}

/* Checks that get_xp() returns the experience points of the player */
Test(player, get_xp)
{
  player_t *player = player_new("1", 99);

  int xp = get_xp(player);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(xp, 0, "get_xp() failed to return player experience");
}

/* Checks that a player's experience points is changed
by change_xp positively and negatively */
Test(player, change_xp)
{
  player_t *player = player_new("1", 99);

  int xp = change_xp(player, 20);
  int xp2 = change_xp(player, -5);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(xp, 20, "change_xp() failed to add to player experience");
  cr_assert_eq(xp2, 15,
      "change_xp() failed to subtract from player experience");
}

/* Checks that get_inventory() returns the player's inventory */
Test(player, get_inventory)
{
  player_t *player = player_new("1", 99);
  player_t *player2 = player_new("1", 100);
  item_t *new_item = item_new("test_item", "item for player testing",
  "item for testing get_inventory()");
  add_item_to_player(player2, new_item);

  item_hash_t* inv = get_inventory(player);
  item_hash_t* inv2 = get_inventory(player2);

  cr_assert_not_null(player, "player_new() failed");
  cr_assert_not_null(player2, "player_new() failed");
  cr_assert_not_null(new_item, "item_new() failed");

  cr_assert_eq(inv, player->inventory,
      "get_inventory() failed to return NULL for empty inventory");
  cr_assert_eq(inv2, player2->inventory,
      "get_inventory() failed to return inventory");
}

/* Checks that add_player_to_game adds a player
to a game struct's player hash table */
Test(player, add_player_to_game)
{
  player_t *player = player_new("1", 99);
  game_t *game = game_new("welcome");
  int res = add_player_to_game(game, player);

  cr_assert_not_null(player, "player_new() failed");
  cr_assert_not_null(game->all_players,
      "add_player_to_hash failed to add player");

  cr_assert_eq(res, SUCCESS, "add_player_to_hash failed to add player");
}

/* Checks that add_item_to_player adds item to a player struct's inventory */
Test(player, add_item_to_player)
{
  player_t *player = player_new("1", 100);
  item_t *new_item = item_new("test_item", "item for player testing",
  "item for testing add_item_to_player");
  add_item_to_player(player, new_item);

  cr_assert_not_null(player, "player_new() failed");
  cr_assert_not_null(new_item, "item_new() failed");
  cr_assert_not_null(player->inventory,
      "add_item_to_player() failed to add item");
}

/* Checks that remove_item_from_player properly removes items */
Test(player, remove_item_from_player)
{
    player_t *player = player_new("player", 100);
    item_t *test_item = item_new("item", "short", "long");
    int rc;
    
    rc = add_item_to_player(player, test_item);
    cr_assert_eq(rc, SUCCESS, "add_item_to_player failed to "
                 "add an item to player");
    
    rc = remove_item_from_player(player, test_item);
    cr_assert_eq(rc, SUCCESS, "remove_item_from_player failed to "
                 "remove an item from player");
}

/* Checks that delete_all_players successfully
empties the game's player hash table */
Test(player, delete_all_players)
{
  player_t *player = player_new("1", 100);
  player_t *player2 = player_new("2", 100);
  game_t *game = game_new("welcome");

  int res = add_player_to_game(game, player);
  int res2 = add_player_to_game(game, player2);

  cr_assert_eq(res, SUCCESS,
      "add_player_to_game() failed to add player to game");
  cr_assert_eq(res2, SUCCESS,
      "add_player_to_game() failed to add player to game");

  int res3 = delete_all_players(game->all_players);

  cr_assert_eq(res3, SUCCESS, "delete_all_players() failed to delete players");
}
