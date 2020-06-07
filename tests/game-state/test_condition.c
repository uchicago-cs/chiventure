#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game-state/item.h"
#include "game-state/game.h"
#include "game-state/player.h"
#include "game-state/condition.h"

Test(condition, new_attr_condition)
{
    item_t *item = item_new("pen", "applepen", "penpineappleapplepen");
    set_int_attr(item, "length",2);
    attribute_value_t value;
    value.int_val = 2;

    condition_t *condition = attribute_condition_new(item, "length", value);

    cr_assert_not_null(condition, "attribute_condition_new() failed");
    
    cr_assert_not_null(condition->cond, "attribute_condition_new() failed to "
    "create the appropriate condition type");
}

Test(condition, new_inven_condition)
{
    player_t *player = player_new("test", 1);
    item_t *item = item_new("pen", "applepen", "penpineappleapplepen");

    condition_t *condition = inventory_condition_new(player, item);

    cr_assert_not_null(condition, "inventory_condition_new() failed");
}