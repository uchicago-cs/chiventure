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
    attribute_value_t value;
    value.int_val = 2;

    condition_t *condition = attribute_condition_new(item, "length", value);

    cr_assert_not_null(condition, "attribute_condition_new() failed");
    
    cr_assert_not_null(condition->cond.attr_type, "attribute_condition_new() failed to "
    "create the appropriate condition struct");

    cr_assert_eq(condition->condition_tag, ATTRIBUTE, "attribute_condiiton_new() failed to "
    "correctly mark condiiton as attribute");
}

/* Checks that inventory_condition_new() properly mallocs and inits a new condition struct */
Test(condition, new_inven_condition)
{
    player_t *player = player_new("test", 1);
    item_t *item = item_new("pen", "applepen", "penpineappleapplepen");

    condition_t *condition = inventory_condition_new(player, item);

    cr_assert_not_null(condition, "inventory_condition_new() failed");

    cr_assert_not_null(condition->cond.inven_type, "inventory_condition_new() failed to "
    "create the appropriate condition struct");

    cr_assert_eq(condition->condition_tag, INVENTORY, "inventory_condiiton_new() failed to "
    "correctly mark condiiton as inventory");
}

/* Checks if delete_condition_llist() frees the condition list from memory */
Test(condition, condition_free)
{
    player_t *player = player_new("test", 1);
    item_t *item = item_new("pen", "applepen", "penpineappleapplepen");
    set_int_attr(item, "length",2);
    attribute_value_t value;
    value.int_val = 2;

    condition_t *condition_1 = attribute_condition_new(item, "length", value);
    condition_t *condition_2 = inventory_condition_new(player, item);

    condition_list_t *conditions = condition_1;
    LL_APPEND(conditions, condition_2);

    int res = delete_condition_llist(conditions);

    cr_assert_eq(res, SUCCESS, "delete_condition_llist() failed");
}

/* Checks if valid_condition properly checks if the condition is actually valid */
Test(condition, valid_condition)
{
    game_t *game = game_new("Welcome to Chiventure!");

    // ITEM_MODIFY_NULL
    item_t *item = item_new("pen", "applepen", "penpineappleapplepen");
    set_int_attr(item, "length",2);
    attribute_value_t value;
    value.int_val = 2;

    condition_t *condition_1 = attribute_condition_new(item, "length", value);

    int valid = valid_condition(game, condition_1);
    cr_assert_eq(valid, ITEM_MODIFY_NULL, "valid_condition() expected ITEM_MODIFY_NULL(3) "
    "but instead got %i", valid);

    condition_1->cond.attr_type->attribute_to_check = NULL;
    valid = valid_condition(game, condition_1);
    cr_assert_eq(valid, ATTRIBUTE_NULL, "valid_condition() expected ATTRIBUTE_NULL(5) "
    "but instead got %i", valid);


}