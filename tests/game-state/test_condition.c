#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game-state/item.h"
#include "game-state/game.h"
#include "game-state/player.h"
#include "game-state/condition.h"

/* Checks that attribute_condition_new() properly mallocs and inits a new condition struct */
Test(condition, new_attr_condition)
{
    item_t *item = item_new("pen", "applepen", "penpineappleapplepen");
    set_int_attr(item, "length",2);
    attribute_value_t *value = malloc(sizeof(attribute_value_t));
    value->int_val = 2;

    condition_t *condition = attribute_condition_new(item, "length", value);

    cr_assert_not_null(condition, "attribute_condition_new() failed");
    
    cr_assert_not_null(condition->condition.attribute_type, "attribute_condition_new() failed to "
    "create the appropriate condition struct");

    cr_assert_eq(condition->condition_tag, ATTRIBUTE, "attribute_condition_new() failed to "
    "correctly mark condition as attribute");
    
    item_free(item);
    free(condition->condition.attribute_type);
    free(condition);
    free(value);
}

/* Checks that inventory_condition_new() properly mallocs and inits a new condition struct */
Test(condition, new_inven_condition)
{
    player_t *player = player_new("test");
    item_t *item = item_new("pen", "applepen", "penpineappleapplepen");

    condition_t *condition = inventory_condition_new(player, item);

    cr_assert_not_null(condition, "inventory_condition_new() failed");

    cr_assert_not_null(condition->condition.inventory_type, "inventory_condition_new() failed to "
    "create the appropriate condition struct");

    cr_assert_eq(condition->condition_tag, INVENTORY, "inventory_condition_new() failed to "
    "correctly mark condition as inventory");

    player_free(player);
    item_free(item);
    free_condition(condition);
}

/* Checks that level_condition_new() properly mallocs and inits a new condition struct */
Test(condition, new_level_condition)
{
    player_t *player = player_new("test");
    int level_required = 15;

    condition_t *condition = level_condition_new(player, level_required);

    cr_assert_not_null(condition, "level_condition_new() failed");

    cr_assert_not_null(condition->condition.level_type, "level_condition_new() failed to "
    "create the appropriate condition struct");

    cr_assert_eq(condition->condition_tag, LEVEL, "level_condition_new() failed to "
    "correctly mark condition tag as LEVEL");

    player_free(player);
    free_condition(condition);
}

/* Tests free_condition on an attribute condition */
Test(condition, free_condition_on_attr)
{
    item_t *item = item_new("pen", "applepen", "penpineappleapplepen");
    set_int_attr(item, "length",2);
    attribute_value_t *value = malloc(sizeof(attribute_value_t));
    value->int_val = 2;
    int check;

    condition_t *condition = attribute_condition_new(item, "length", value);

    cr_assert_not_null(condition, "attribute_condition_new() failed");
    
    cr_assert_not_null(condition->condition.attribute_type, "attribute_condition_new() failed to "
    "create the appropriate condition struct");

    cr_assert_eq(condition->condition_tag, ATTRIBUTE, "attribute_condition_new() failed to "
    "correctly mark condition as attribute");
    
    check = free_condition(condition);

    cr_assert_eq(check, SUCCESS, "free_condition() failed to free");

    cr_assert_not_null(item, "free_condition mistakingly freed item as well");
    
    item_free(item);
    free(value);
}

/* Tests free_condition on an inventory condition */
Test(condition, free_condition_on_inven)
{
    player_t *player = player_new("test");
    item_t *item = item_new("pen", "applepen", "penpineappleapplepen");

    condition_t *condition = inventory_condition_new(player, item);

    int check;

    cr_assert_not_null(condition, "inventory_condition_new() failed");

    cr_assert_not_null(condition->condition.inventory_type, "inventory_condition_new() failed to "
    "create the appropriate condition struct");

    cr_assert_eq(condition->condition_tag, INVENTORY, "inventory_condition_new() failed to "
    "correctly mark condition as inventory");

    check = free_condition(condition);

    cr_assert_eq(check, SUCCESS, "free_condition() failed to free");

    cr_assert_not_null(item, "free_condition mistakingly freed item as well");
    cr_assert_not_null(player, "free_condition() mistakingly freed player as well");

    player_free(player);
    item_free(item);
}

/* Tests free_condition on a level condition */
Test(condition, free_condition_on_level)
{
    player_t *player = player_new("test");
    int level_required = 15;

    condition_t *condition = level_condition_new(player, level_required);

    int check;

    cr_assert_not_null(condition, "level_condition_new() failed");

    cr_assert_not_null(condition->condition.level_type, "level_condition_new() failed to "
    "create the appropriate condition struct");

    cr_assert_eq(condition->condition_tag, LEVEL, "level_condition_new() failed to "
    "correctly mark condition tag as LEVEL");

    check = free_condition(condition);

    cr_assert_eq(check, SUCCESS, "free_condition() failed to free");

    cr_assert_not_null(player, "free_condition() mistakingly freed player as well");

    player_free(player);
}

/* Checks if delete_condition_llist() frees the condition list from memory */
Test(condition, condition_free)
{
    player_t *player = player_new("test");
    item_t *item = item_new("pen", "applepen", "penpineappleapplepen");
    set_int_attr(item, "length",2);
    attribute_value_t *value = malloc(sizeof(attribute_value_t));
    value->int_val = 2;

    condition_t *condition_1 = attribute_condition_new(item, "length", value);
    condition_t *condition_2 = inventory_condition_new(player, item);

    condition_list_t *conditions = condition_1;
    LL_APPEND(conditions, condition_2);

    int res = delete_condition_llist(conditions);

    cr_assert_eq(res, SUCCESS, "delete_condition_llist() failed");
    player_free(player);
    item_free(item);
    free(value);
}

/* Checks if valid_condition properly checks if the condition is actually valid */
Test(condition, valid_condition)
{
    game_t *game = game_new("Welcome to Chiventure!");

    // ITEM_MODIFY_NULL
    item_t *item = item_new("pen", "applepen", "penpineappleapplepen");
    set_int_attr(item, "length",2);
    attribute_value_t *value = malloc(sizeof(attribute_value_t));
    value->int_val = 2;

    condition_t *condition_1 = attribute_condition_new(item, "length", value);

    int valid = valid_condition(game, condition_1);
    cr_assert_eq(valid, ITEM_MODIFY_NULL, "valid_condition() expected ITEM_MODIFY_NULL(3) "
    "but instead got %i", valid);

    // SUCCESS
    add_item_to_game(game, item);
    valid = valid_condition(game, condition_1);
    cr_assert_eq(valid, SUCCESS, "valid_condition() expected SUCCESS(0) "
    "but instead got %i", valid);

    // ATTRIBUTE_NULL
    condition_1->condition.attribute_type->attribute_to_check = NULL;
    valid = valid_condition(game, condition_1);
    cr_assert_eq(valid, ATTRIBUTE_NULL, "valid_condition() expected ATTRIBUTE_NULL(5) "
    "but instead got %i", valid);

    // PLAYER_NULL
    player_t *player = player_new("test");

    condition_t *condition_2 = inventory_condition_new(player, item);

    valid = valid_condition(game, condition_2);
    cr_assert_eq(valid, PLAYER_NULL, "valid_condition() expected PLAYER_NULL(6) "
    "but instead got %i", valid);

    // SUCCESS
    player_t *player2 = player_new("test2");

    condition_t *condition_3 = level_condition_new(player2, 2);

    add_player_to_game(game, player2);
    valid = valid_condition(game, condition_3);
    cr_assert_eq(valid, SUCCESS, "valid_condition() expected SUCCESS(0) "
    "but instead got %i", valid);

    // CONDITION_NULL
    valid = valid_condition(game, NULL);
    cr_assert_eq(valid, CONDITION_NULL, "valid_condition() expected CONDITION_NULL(7) "
    "but instead got %i", valid);



    player_free(player);
    game_free(game);
    free(condition_1->condition.inventory_type);
    free(condition_2->condition.inventory_type);
    free(condition_1);
    free(condition_2);
    free(value);
}
