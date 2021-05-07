#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "game-state/player.h"
#include "game-state/item.h"
#include "game-state/game.h"
#include "game-state/game_state_common.h"
#include "game-state/stats.h"
#include "playerclass/class.h"

/* Checks that player_new() properly mallocs and inits a new player struct */
Test(player, new)
{
  player_t *player = player_new("1");

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(player->level, 1,
      "player_new() didn't properly set starting level");
  cr_assert_eq(player->xp, 0,
      "player_new() didn't properly set starting xp");
  cr_assert_eq(strncmp(player->player_id, "1", MAX_ID_LEN), 0,
      "player_new() didn't properly set player id");
  
  player_free(player);
}

/* Checks that player_free() frees the given player struct from memory */
Test(player, free)
{
  player_t *player = player_new("1");

  int res = player_free(player);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(res, SUCCESS, "player_free() failed");
}

/* Checks that player_set_race correctly updates the race field of the player */
Test(player, player_set_race)
{
  player_t *player = player_new("1");

  char *race= "Human";

  int race_set = player_set_race(player, race);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(race_set, SUCCESS, "player_set_race() did not return SUCCESS");
  cr_assert_str_eq(player->player_race, race, "player_set_race() did not set correct race");

  player_free(player);
}

/* Checks that player_set_class correctly points to the given class_t object */
Test(player, player_set_class)
{
  player_t *player = player_new("1");

  class_t *test_class = class_new("Testclass", "shortdesc", "longdesc", NULL, NULL, NULL);

  int class_set = player_set_class(player, test_class);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(class_set, SUCCESS, "player_set_class() did not return SUCCESS");
  cr_assert_eq(player->player_class, test_class, "player_set_class() did not set correct class");

  player_free(player);
}

/* Checks that get_level() returns the level of the player */
Test(player, get_level)
{
  player_t *player = player_new("1");

  int level = get_level(player);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(level, 1, "get_level() failed to return player level");
  player_free(player);
}

/* Checks that a player's level is changed by change_level()
both positively and negatively */
Test(player, change_level)
{
  player_t *player = player_new("1");

  int level = change_level(player, 3);
  int level2 = change_level(player, -1);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(level, 4, "change_level() failed to add to player level");
  cr_assert_eq(level2, 3,
      "change_level() failed to subtract from player level");
  player_free(player);
}

/* Checks that get_xp() returns the experience points of the player */
Test(player, get_xp)
{
  player_t *player = player_new("1");

  int xp = get_xp(player);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(xp, 0, "get_xp() failed to return player experience");
  player_free(player);
}


/* Checks that a player's experience points is changed
by change_xp positively and negatively */
Test(player, change_xp)
{
  player_t *player = player_new("1");

  int xp = change_xp(player, 20);
  int xp2 = change_xp(player, -5);

  cr_assert_not_null(player, "player_new() failed");

  cr_assert_eq(xp, 20, "change_xp() failed to add to player experience");
  cr_assert_eq(xp2, 15,
      "change_xp() failed to subtract from player experience");
  player_free(player);

}

/* Checks that get_inventory() returns the player's inventory */
Test(player, get_inventory)
{
  player_t *player = player_new("1");
  player_t *player2 = player_new("1");
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
  player_free(player);
  player_free(player2);
}

/* Checks that add_player_to_game adds a player
to a game struct's player hash table */
Test(player, add_player_to_game)
{
  player_t *player = player_new("1");
  game_t *game = game_new("welcome");
  int res = add_player_to_game(game, player);

  cr_assert_not_null(player, "player_new() failed");
  cr_assert_not_null(game->all_players,
      "add_player_to_hash failed to add player");

  cr_assert_eq(res, SUCCESS, "add_player_to_hash failed to add player");
  game_free(game);
}

/* Checks that add_item_to_player adds item to a player struct's inventory */
Test(player, add_item_to_player)
{
    player_t *player = player_new("1");
    item_t *new_item = item_new("test_item", "item for player testing",
                                "item for testing add_item_to_player");
    item_t *dup_item = item_new("test_item", "item for player testing",
                                "item for testing add_item_to_player");
    add_item_to_player(player, new_item);

    cr_assert_not_null(player, "player_new() failed");
    cr_assert_not_null(new_item, "item_new() failed");
    cr_assert_not_null(player->inventory,
                       "add_item_to_player() failed to add item");
    
    int rc = add_item_to_player(player, dup_item);
    cr_assert_eq(rc, SUCCESS, "add_item_to_player failed to add "
                 "item with identical id");
    player_free(player);
}

/* Checks that remove_item_from_player properly removes items */
Test(player, remove_item_from_player)
{
    player_t *player = player_new("player");
    item_t *test_item = item_new("item", "short", "long");
    item_t *dup_item = item_new("item", "short", "long");
    item_list_t *item_list;
    int rc;
    
    rc = add_item_to_player(player, test_item);
    cr_assert_eq(rc, SUCCESS, "add_item_to_player failed to "
                 "add an item to player");
    rc = add_item_to_player(player, dup_item);
    cr_assert_eq(rc, SUCCESS, "add_item_to_player failed to "
                 "add an item to player");
    
    rc = remove_item_from_player(player, test_item);
    cr_assert_eq(rc, SUCCESS, "remove_item_from_player failed to "
                 "remove an item from player");
    
    item_list = get_all_items_in_inventory(player);
    cr_assert_not_null(item_list, "remove_item_from_player removed "
                       "both identical items from player");
    player_free(player);
    item_free(test_item);
    delete_item_llist(item_list);
}

/* Checks that add_item_to_player adds an item with an effect to player's inventory */
Test(player, add_item_effect_to_player)
{
  player_t *player = player_new("1");
  item_t *new_item = item_new("test_item", "item for player testing",
  "item for testing add_item_to_player");
  new_item->stat_effects = NULL;
  effects_global_t *g1 = global_effect_new("effect 1");
  stat_effect_t *e1 = stat_effect_new(g1);
  stat_effect_t *e2 = stat_effect_new(g1);
  class_t *class = class_new("class", "short", "long",
                   NULL, NULL, NULL);
  player->player_class = class;
  add_stat_effect(&player->player_class->effects, e1);

  char *hp = "Health";
  
  stats_global_t *health = stats_global_new(hp, 100);

  stats_t *s1 = malloc(sizeof(stats_t));
  s1->key = strdup(hp);
  s1->global = health;
  s1->val = 50.0;
  s1->max = 75.0;
  s1->modifier = 0.75;

  add_stat(&player->player_class->stats, s1);

  stat_mod_t *mod1 = stat_mod_new(s1, 1.5, 5);
  LL_APPEND(e2->stat_list, mod1);
  new_item->stat_effects = e2;

  add_item_to_player(player, new_item);

  cr_assert_not_null(e1->stat_list, 
                     "add_item did not add stat_mod to effect");
  cr_assert_eq(player->player_class->stats->modifier, 1.125, 
               "add_item did not update modifier");
  free_stats_table(class->stats);
  delete_all_stat_effects(class->effects);
  free(new_item->stat_effects->key);
  free(new_item->stat_effects);
  new_item->stat_effects = NULL;
  player_free(player);
  free_stats_global(health);
  free(mod1);
  free(g1->name);
  free(g1);
}

/* Checks that delete_all_players successfully
empties the game's player hash table */
Test(player, delete_all_players)
{
  player_t *player = player_new("1");
  player_t *player2 = player_new("2");
  game_t *game = game_new("welcome");

  int res = add_player_to_game(game, player);
  int res2 = add_player_to_game(game, player2);

  cr_assert_eq(res, SUCCESS,
      "add_player_to_game() failed to add player to game");
  cr_assert_eq(res2, SUCCESS,
      "add_player_to_game() failed to add player to game");

  int res3 = delete_all_players(game->all_players);

  cr_assert_eq(res3, SUCCESS, "delete_all_players() failed to delete players");
  game->all_players = NULL;
  game_free(game);
}
