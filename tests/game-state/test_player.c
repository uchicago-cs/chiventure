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
#include "battle/battle_default_objects.h"

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
  add_stat_effect(&(new_item->stat_effects), e2);

  add_item_to_player(player, new_item);

  cr_assert_not_null(e1->stat_list, 
                     "add_item did not add stat_mod to effect");
  cr_assert_eq(player->player_class->stats->modifier, 1.125, 
               "add_item did not update modifier");
  free_stats_table(class->stats);
  delete_all_stat_effects(class->effects);
  player_free(player);
  
  free_stats_global(health);
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

Test(player, add_combat_skill)
{
    player_t *player = player_new("test");

    cr_assert_not_null(player, "player_new() failed");

    /* These field will be set when we set the class in future implementations */
    player->player_combat_skills = inventory_new(5, 5);

    cr_assert_not_null(player->player_combat_skills, "inventory_new() failed");

    skill_t *wizardry = skill_new(1, ACTIVE, 
                                "wizardry", "wizarding test skill",
                                15, 200,
                                NULL);

    cr_assert_not_null(wizardry, "skill_new() failed");

    int skill_added = player_add_combat_skill(player, wizardry);

    cr_assert_eq(skill_added, SUCCESS, "player_add_combat_skill() did not return SUCCESS");

    cr_assert_eq(wizardry, player->player_combat_skills->active[0], 
    "player_add_combat_skill() failed to add the skill to the combat skill "
    "inventory");
 
    /* Freeing player_combat_skills and player_noncombat_skills fields
    will be handled by player_free once player_set_class 
    is updated to deep copy fields */
    inventory_free(player->player_combat_skills);

    skill_free(wizardry);

    player_free(player);
}

Test(player, add_noncombat_skill)
{
    player_t *player = player_new("test");

    cr_assert_not_null(player, "player_new() failed");

    /* These field will be set when we set the class in future implementations */
    player->player_noncombat_skills = inventory_new(5, 5);

    cr_assert_not_null(player->player_noncombat_skills, "inventory_new() failed");

    skill_t *cooking = skill_new(1, PASSIVE, 
                                "cooking", "cooking test skill",
                                15, 200,
                                NULL);

    cr_assert_not_null(cooking, "skill_new() failed");

    int skill_added = player_add_noncombat_skill(player, cooking);

    cr_assert_eq(skill_added, SUCCESS, "player_add_noncombat_skill() did not return SUCCESS");
 
    cr_assert_eq(cooking, player->player_noncombat_skills->passive[0], 
    "player_add_noncombat_skill() failed to add the skill to the noncombat skill "
    "inventory");

    /* Freeing player_combat_skills and player_noncombat_skills fields
    will be handled by player_free once player_set_class 
    is updated to deep copy fields */
    inventory_free(player->player_noncombat_skills);

    skill_free(cooking);

    player_free(player);
}

Test(player, remove_combat_skill)
{
    player_t *player = player_new("test");

    cr_assert_not_null(player, "player_new() failed");

    /* These field will be set when we set the class in future implementations */
    player->player_combat_skills = inventory_new(5, 5);

    cr_assert_not_null(player->player_combat_skills, "inventory_new() failed");

    /* Removing skills in skill inventories using inventory_skill_remove()
     reallocates the memory allocated to active/passive skill arrays.
    We must add a second skill in the active array to prevent it from being
    reallocated to 0 bytes when a skill is removed. */
    skill_t *wizardry = skill_new(1, ACTIVE, 
                                "wizardry", "wizardry test skill",
                                15, 200,
                                NULL);

    skill_t *sorcery = skill_new(2, ACTIVE, 
                                "sorcery", "sorcery test skill",
                                15, 200,
                                NULL);

    cr_assert_not_null(wizardry, "skill_new() failed");
    cr_assert_not_null(sorcery, "skill_new() failed");

    int skill_added = player_add_combat_skill(player, wizardry);

    cr_assert_eq(skill_added, SUCCESS, "player_add_combat_skill() did not return SUCCESS");

    skill_added = player_add_combat_skill(player, sorcery);

    cr_assert_eq(skill_added, SUCCESS, "player_add_combat_skill() did not return SUCCESS");

    int skill_removed = player_remove_combat_skill(player, wizardry);

    cr_assert_eq(skill_removed, SUCCESS, "player_remove_combat_skill() did not return SUCCESS");

    /* The first position in the active skill array previously held the
    wizardry skill. Once it is removed the sorcery skill should be moved to 
    take its place */
    cr_assert_eq(sorcery, player->player_combat_skills->active[0], 
    "player_add_combat_skill() failed to remove the skill to the combat skill "
    "inventory");

    /* Freeing player_combat_skills and player_noncombat_skills fields
    will be handled by player_free once player_set_class 
    is updated to deep copy fields */
    inventory_free(player->player_combat_skills);

    skill_free(wizardry);
    skill_free(sorcery);

    player_free(player);
}

Test(player, remove_noncombat_skill)
{
    player_t *player = player_new("test");

    cr_assert_not_null(player, "player_new() failed");

    /* These field will be set when we set the class in future implementations */
    player->player_noncombat_skills = inventory_new(5, 5);

    cr_assert_not_null(player->player_noncombat_skills, "inventory_new() failed");

    /* Removing skills in skill inventories using inventory_skill_remove()
     reallocates the memory allocated to active/passive skill arrays.
    We must add a second skill in the active array to prevent it from being
    reallocated to 0 bytes when a skill is removed. */
    skill_t *cooking = skill_new(1, PASSIVE, 
                                "cooking", "cooking test skill",
                                15, 200,
                                NULL);
    skill_t *baking = skill_new(2, PASSIVE, 
                                "baking", "baking test skill",
                                15, 200,
                                NULL);

    cr_assert_not_null(cooking, "skill_new() failed");
    cr_assert_not_null(baking, "skill_new() failed");

    int skill_added = player_add_noncombat_skill(player, cooking);

    cr_assert_eq(skill_added, SUCCESS, "player_add_noncombat_skill() did not return SUCCESS");

    skill_added = player_add_noncombat_skill(player, baking);

    cr_assert_eq(skill_added, SUCCESS, "player_add_noncombat_skill() did not return SUCCESS");

    int skill_removed = player_remove_noncombat_skill(player, cooking);

    cr_assert_eq(skill_removed, SUCCESS, "player_remove_noncombat_skill() did not return SUCCESS");

    /* The first position in the active skill array previously held the
    wizardry skill. Once it is removed the sorcery skill should be moved to 
    take its place */
    cr_assert_eq(baking, player->player_noncombat_skills->passive[0], 
    "player_add_noncombat_skill() failed to remove the skill to the noncombat skill "
    "inventory");

    /* Freeing player_combat_skills and player_noncombat_skills fields
    will be handled by player_free once player_set_class 
    is updated to deep copy fields */
    inventory_free(player->player_noncombat_skills);

    skill_free(cooking);
    skill_free(baking);

    player_free(player);
}

Test(player, has_combat_skill)
{
    player_t *player = player_new("test");

    cr_assert_not_null(player, "player_new() failed");

    /* These field will be set when we set the class in future implementations */
    player->player_combat_skills = inventory_new(5, 5);

    cr_assert_not_null(player->player_combat_skills, "inventory_new() failed");

    skill_t *wizardry = skill_new(1, ACTIVE, 
                                "wizardry", "wizardry test skill",
                                15, 200,
                                NULL);

    skill_t *sorcery = skill_new(2, ACTIVE, 
                                "sorcery", "sorcery test skill",
                                15, 200,
                                NULL);

    cr_assert_not_null(wizardry, "skill_new() failed");
    cr_assert_not_null(sorcery, "skill_new() failed");

    int skill_added = player_add_combat_skill(player, wizardry);

    cr_assert_eq(skill_added, SUCCESS, "player_add_combat_skill() did not return SUCCESS");

    skill_added = player_add_combat_skill(player, sorcery);

    cr_assert_eq(skill_added, SUCCESS, "player_add_combat_skill() did not return SUCCESS");

    int has_skill = player_has_combat_skill(player, 2, ACTIVE);

    /* The sorcery skill should be stored in the second position in the active array */
    cr_assert_eq(has_skill, 1, "player_has_combat_skill() did not find the skill "
    "when it was present in the skill inventory");

    int skill_removed = player_remove_combat_skill(player, wizardry);

    has_skill = (player_has_combat_skill(player, 1, ACTIVE));

    cr_assert_eq(has_skill, -1, "player_has_combat_skill() found the skill after "
    "it was removed from the skill inventory");

    cr_assert_eq(skill_removed, SUCCESS, "player_remove_combat_skill() did not return SUCCESS");
 
 
    /* Freeing player_combat_skills and player_noncombat_skills fields
    will be handled by player_free once player_set_class 
    is updated to deep copy fields */
    inventory_free(player->player_combat_skills);

    skill_free(wizardry);
    skill_free(sorcery);

    player_free(player);
}

Test(player, has_noncombat_skill)
{
    player_t *player = player_new("test");

    cr_assert_not_null(player, "player_new() failed");

    /* These field will be set when we set the class in future implementations */
    player->player_combat_skills = inventory_new(5, 5);
    player->player_noncombat_skills = inventory_new(5, 5);

    cr_assert_not_null(player->player_combat_skills, "inventory_new() failed");
    cr_assert_not_null(player->player_noncombat_skills, "inventory_new() failed");

    skill_t *cooking = skill_new(1, PASSIVE, 
                                "cooking", "cooking test skill",
                                15, 200,
                                NULL);
    skill_t *baking = skill_new(2, PASSIVE, 
                                "baking", "baking test skill",
                                15, 200,
                                NULL);

    cr_assert_not_null(cooking, "skill_new() failed");
    cr_assert_not_null(baking, "skill_new() failed");

    int skill_added = player_add_noncombat_skill(player, cooking);

    cr_assert_eq(skill_added, SUCCESS, "player_add_noncombat_skill() did not return SUCCESS");

    skill_added = player_add_noncombat_skill(player, baking);

    cr_assert_eq(skill_added, SUCCESS, "player_add_noncombat_skill() did not return SUCCESS");

    int has_skill = player_has_noncombat_skill(player, 2, PASSIVE);

    /* The baking skill should be stored in the second position in the passive array */
    cr_assert_eq(has_skill, 1, "player_has_noncombat_skill() did not find the skill "
    "when it was present in the skill inventory");

    int skill_removed = player_remove_noncombat_skill(player, cooking);

    has_skill = (player_has_noncombat_skill(player, 1, PASSIVE));

    cr_assert_eq(has_skill, -1, "player_has_noncombat_skill() found the skill after "
    "it was removed from the skill inventory");

    cr_assert_eq(skill_removed, SUCCESS, "player_remove_noncombat_skill() did not return SUCCESS");
 
    /* Freeing player_combat_skills and player_noncombat_skills fields
    will be handled by player_free once player_set_class 
    is updated to deep copy fields */
    inventory_free(player->player_noncombat_skills);

    skill_free(cooking);
    skill_free(baking);

    player_free(player);
}

Test(player, add_stat)
{
    player_t *player = player_new("test");

    cr_assert_not_null(player, "player_new() failed");

    stats_global_t *health = stats_global_new("health", 100);
    stats_t *s = stats_new(health, 75);

    int added = player_add_stat(player, s);
    cr_assert_eq(added, SUCCESS, "player_add_stat() failed");

    cr_assert_not_null(player->player_stats, 
    "player_add_stat() did not add the stat to the player's stat hash");

    free_stats_table(player->player_stats);
    free_stats_global(health);

    player_free(player);  
}

Test(player, get_stat_current)
{
    player_t *player = player_new("test");

    cr_assert_not_null(player, "player_new() failed");

    double expected = 150.25;

    stats_global_t *health = stats_global_new("health", expected);
    stats_t *s = stats_new(health, expected);

    int added = player_add_stat(player, s);
    cr_assert_eq(added, SUCCESS, "player_add_stat() failed");

    cr_assert_not_null(player->player_stats, 
    "player_add_stat() did not add the stat to the player's stat hash");

    double current_health = player_get_stat_current(player, "health");

    cr_assert_float_eq(current_health, expected, .0001, 
    "player_get_stat_current() did not return correct health value. "
    "Actual: %.02f Expected: %.02f ", current_health, expected);

    free_stats_table(player->player_stats);
    free_stats_global(health);

    player_free(player);  
}


Test(player, change_stat)
{
    player_t *player = player_new("test");

    double starting_health = 125.25;
    double health_change = -5.75;
    double expected = starting_health + health_change;

    cr_assert_not_null(player, "player_new() failed");

    stats_global_t *health = stats_global_new("health", 400.5);
    stats_t *s = stats_new(health, starting_health);

    int added = player_add_stat(player, s);
    cr_assert_eq(added, SUCCESS, "player_add_stat() failed");

    cr_assert_not_null(player->player_stats, 
    "player_add_stat() did not add the stat to the player's stat hash");

    int rc = player_change_stat(player, "health", health_change);

    cr_assert_eq(rc, SUCCESS, "player_change_stat() did not return SUCCESS");

    double current_health = player_get_stat_current(player, "health");

    cr_assert_float_eq(current_health, expected, .0001, 
    "player_change_stat() did not correctly update the health value. "
    "Expected: %.02f Actual: %.02f", expected, current_health);

    free_stats_table(player->player_stats);
    free_stats_global(health);

    player_free(player);  
}

Test(player, change_stat_max)
{
    player_t *player = player_new("test");

    double starting_max = 100.5;
    double max_change = -20;
    double health_change = 5;
    double expected = starting_max + max_change;

    cr_assert_not_null(player, "player_new() failed");

    stats_global_t *health = stats_global_new("health", 300);
    stats_t *s = stats_new(health, starting_max);

    int added = player_add_stat(player, s);
    cr_assert_eq(added, SUCCESS, "player_add_stat() failed");

    cr_assert_not_null(player->player_stats, 
    "player_add_stat() did not add the stat to the player's stat hash");

    int rc = player_change_stat_max(player, "health", max_change);

    cr_assert_eq(rc, SUCCESS, "player_change_stat_max() did not return SUCCESS");

    /* The local max of a stat is only relevant when updating the current value */
    rc = player_change_stat(player, "health", health_change);

    cr_assert_eq(rc, SUCCESS, "player_change_stat() did not return SUCCESS");

    double current_health = player_get_stat_current(player, "health");

    cr_assert_float_eq(current_health, expected, .0001, 
    "player_change_stat_max() did not correctly update the max health value. "
    "Expected: %.02f Actual: %.02f", expected, current_health);

    free_stats_table(player->player_stats);
    free_stats_global(health);

    player_free(player);  
}

Test(player, add_stat_effect)
{
    player_t *player = player_new("test");

    cr_assert_not_null(player, "player_new() failed");

    effects_hash_t *hash = NULL;
    effects_global_t *global = global_effect_new("effect");
    stat_effect_t *effect = stat_effect_new(global);
    int rc = player_add_stat_effect(player, effect);

    cr_assert_eq(rc, SUCCESS, "player_add_stat_effect failed");
    cr_assert_not_null(player->player_effects, 
    "player_add_stat_effect did not add effect to player_effects hash");

    delete_all_stat_effects(hash);
    free(global->name);
    free(global);
    
    player_free(player);
}

Test(add_move, add_move_existing_list) {

    move_t *old_move = get_random_default_move();
    move_t *new_move = get_random_default_move();
    battle_item_t *item = get_random_default_consumable();
    
    // The following two lines were from when this code was in battle_move_maker.
    //  Leaving it just in case it is helpful later.
    // stat_t *cstats = get_random_stat();
    // combatant_t *player = combatant_new("TESTER", true, NULL, cstats, old_move, item, 0);
    player_t *player = player_new("TESTER");
    add_item_to_player(player, item);
    add_move(player, old_move);

    int res = add_move(player,new_move);
    cr_assert_eq(player->moves->next,
                 new_move,  
                 "add_move() did not add the move correctly");
}

Test(add_move, add_move_empty_list) {
    
    move_t *new_move = get_random_default_move();
    battle_item_t *item = get_random_default_consumable();
    // The following two lines were from when this code was in battle_move_maker.
    //  Leaving it just in case it is helpful later.
    // stat_t *cstats = get_random_stat();
    // combatant_t *player = combatant_new("TESTER",true,NULL,cstats,NULL,item, 0);

    player_t *player = player_new("TESTER");
    int res = add_move(player,new_move);
    cr_assert_eq(player->moves,
                 new_move,
                 "add_move() did not add the move correctly");
}
