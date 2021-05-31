#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "action_management/actionmanagement.h"
#include "action_management/action_structs.h"
#include "game-state/item.h"
#include "game-state/game.h"
#include "game-state/player.h"

#define BUFFER_SIZE (100)
#define WRONG_KIND (2)
#define NOT_ALLOWED_DIRECT (3)
#define NOT_ALLOWED_INDIRECT (4)
#define NOT_ALLOWED_PATH (5)
#define CONDITIONS_NOT_MET (6)
#define EFFECT_NOT_APPLIED (7)
#define END_FAIL (8)

int execute_do_item_item_action(char *act_name, enum action_kind kind, char *allowed_act_name1, int choose_condition, int choose_effect)
{
    chiventure_ctx_t *ctx_test = chiventure_ctx_new(NULL);
    
    action_type_t *a = action_type_new(act_name, kind);
    item_t *direct = item_new("direct", "The direct item", "The directmost object of interest");
    item_t *indirect = item_new("indirect", "The indirect item", "The indirectmost object of interest");
    add_action(direct, allowed_act_name1, "success1", "fail1");
    char *string = malloc(BUFFER_SIZE);
    game_action_t *ga;
    if (strcmp(act_name, allowed_act_name1) == 0)
    {
        ga = get_action(direct, act_name);
    }
    else
    {
        ga = get_action(direct, allowed_act_name1);
    }
    int rc;
    attribute_value_t value;
    attribute_t *attr;
    set_str_attr(indirect, "DUMMYATTRDEFAULT", 0);
    attr = get_attribute(indirect, "DUMMYATTRDEFAULT");
    value.int_val = 1;
    add_action_effect(ga, indirect, attr, value);


    player_t *player = player_new("player1");

    switch (choose_condition)
    {
    // Attribute conditional tests
    case 1:
        set_int_attr(indirect, "DUMMYCONDITON", 0);
        attr = get_attribute(indirect, "DUMMYCONDITON");
        value.int_val = 0;
        add_action_attribute_condition(ga, indirect, attr, value);
        break;
    case 2:
        set_int_attr(direct, "DUMMYCONDITON", 1);
        attr = get_attribute(direct, "DUMMYCONDITON");
        value.int_val = 0;
        add_action_attribute_condition(ga, direct, attr, value);
        break;
    case 3:
        set_int_attr(indirect, "DUMMYCONDITON", 0);
        attr = get_attribute(indirect, "DUMMYCONDITON");
        value.int_val = 0;
        add_action_attribute_condition(ga, indirect, attr, value);
        break;
    case 4:
        set_int_attr(indirect, "DUMMYCONDITON", 1);
        attr = get_attribute(indirect, "DUMMYCONDITON");
        value.int_val = 0;
        add_action_attribute_condition(ga, indirect, attr, value);
        break;
    
    // Inventory conditional tests
    case 5:
        // Item (direct) is in player inventory
        add_item_to_player(player, direct);
        add_action_inventory_condition(ga, player, direct);
        break;
    case 6:
        // Item (direct) is not in player inventory
        add_item_to_player(player, direct);
        add_action_inventory_condition(ga, player, indirect);
        break;

    // Testing multiple conditions
    case 7:
        add_item_to_player(player, direct);
        add_action_inventory_condition(ga, player, direct);

        set_int_attr(indirect, "DUMMYCONDITON", 0);
        attr = get_attribute(indirect, "DUMMYCONDITON");
        value.int_val = 0;
        add_action_attribute_condition(ga, indirect, attr, value);
        break;
    case 8:
        add_item_to_player(player, direct);
        add_action_inventory_condition(ga, player, direct);

        add_item_to_player(player, indirect);
        add_action_inventory_condition(ga, player, indirect);
        break;
    default:
        break;
    }

    switch (choose_effect)
    {
    case 0:
        rc = do_item_item_action(ctx_test, a, direct, indirect, &string);
        break;
    case 1:
        set_str_attr(indirect, "DUMMYATTR", "old");
        attr = get_attribute(indirect, "DUMMYATTR");
        value.str_val = "new";
        add_action_effect(ga, indirect, attr, value);
        do_item_item_action(ctx_test, a, direct, indirect, &string);
        if (strcmp(get_str_attr(indirect, "DUMMYATTR"), "new") == 0)
        {
            rc = SUCCESS;
        } else {
            rc = FAILURE;
        }
        break;
    case 2:
        set_int_attr(indirect, "DUMMYATTR", 0);
        attr = get_attribute(indirect, "DUMMYATTR");
        value.int_val = 1;
        add_action_effect(ga, indirect, attr, value);
        do_item_item_action(ctx_test, a, direct, indirect, &string);
        if (get_int_attr(indirect, "DUMMYATTR") == 1)
        {
            rc = SUCCESS;
        } else {
            rc = FAILURE;
        }
        break;
    case 3:
        set_double_attr(indirect, "DUMMYATTR", 0.0);
        attr = get_attribute(indirect, "DUMMYATTR");
        value.double_val = 1.0;
        add_action_effect(ga, indirect, attr, value);
        do_item_item_action(ctx_test, a, direct, indirect, &string);
        if (get_double_attr(indirect, "DUMMYATTR") == 1.0)
        {
            rc = SUCCESS;
        } else {
            rc = FAILURE;
        }
        break;
    case 4:
        set_char_attr(indirect, "DUMMYATTR", 'a');
        attr = get_attribute(indirect, "DUMMYATTR");
        value.char_val = 'b';
        add_action_effect(ga, indirect, attr, value);
        do_item_item_action(ctx_test, a, direct, indirect, &string);
        if (get_char_attr(indirect, "DUMMYATTR") == 'b')
        {
            rc = SUCCESS;
        } else {
            rc = FAILURE;
        }
        break;
    case 5:
        set_bool_attr(indirect, "DUMMYATTR", false);
        attr = get_attribute(indirect, "DUMMYATTR");
        value.bool_val = true;
        add_action_effect(ga, indirect, attr, value);
        do_item_item_action(ctx_test, a, direct, indirect, &string);
        if (get_bool_attr(indirect, "DUMMYATTR") == true)
        {
            rc = SUCCESS;
        } else {
            rc = FAILURE;
        }
        break;
    default:
        rc = do_item_item_action(ctx_test, a, direct, indirect, &string);
        break;
    }

    free(string);

    /*sometimes the direct and indirect items are not added to a player
     * and must be freed separately. The following if statements should
     * free them in this case */
    if (choose_condition <= NOT_ALLOWED_INDIRECT){
        item_free(direct); //For all tests before test 4 free direct
    }

    if (choose_condition != END_FAIL){
        item_free(indirect);  //For all tests expect for test 8 free indirect
    }
    game_free(ctx_test->game);
    lookup_t_free(ctx_test->cli_ctx->table);
    chiventure_ctx_free(ctx_test);

    action_type_free(a);
    game_action_free(ga);
    player_free(player);

    return rc;
}


Test(item_item_actions, wrong_kind_ITEM)
{
    int rc = execute_do_item_item_action("dummy", ITEM, "dummy", 0, 0);

    cr_assert_eq(rc, WRONG_KIND,
                 "execute_do_item_item_action returned %d for wrong kind 1, expected WRONG_KIND (2)", rc);
}


Test(item_item_actions, wrong_kind_PATH)
{

    int rc = execute_do_item_item_action("dummy", PATH, "dummy", 0, 0);

    cr_assert_eq(rc, WRONG_KIND,
                 "execute_do_item_item_action returned %d for wrong kind 2, expected WRONG_KIND (2)", rc);
}


Test(item_item_actions, correct_kind_ITEM_ITEM)
{
    int rc = execute_do_item_item_action("dummy", ITEM_ITEM, "dummy", 0, 0);

    cr_assert_eq(rc, SUCCESS,
                 "execute_do_item_item_action returned %d for correct kind 3, expected SUCCESS (0)", rc);
}


Test(item_item_actions, correct_allowed_actions)
{
    int rc = execute_do_item_item_action("dummy", ITEM_ITEM, "dummy", 0, 0);

    cr_assert_eq(rc, SUCCESS,
                 "execute_do_item_item_action returned %d for correct allowed actions in indirect and direct, expected SUCCESS (0)", rc);
}

Test(item_item_actions, wrong_allowed_actions)
{
    int rc = execute_do_item_item_action("dummy_allowed", ITEM_ITEM, "dummy", 0, 0);

    cr_assert_eq(rc, NOT_ALLOWED_DIRECT,
                 "execute_do_item_item_action returned %d for incorrect allowed actions name in indirect and direct, expected NOT_ALLOWED_DIRECT (2)", rc);
}

Test(item_item_actions, effect_set_string_direct)
{
    int rc = execute_do_item_item_action("dummy", ITEM_ITEM, "dummy", 0, 1);

    cr_assert_eq(rc, SUCCESS,
                 "string attributewas not set due to effect of direct item");
}

Test(item_item_actions, effect_set_integer_direct)
{
    int rc = execute_do_item_item_action("dummy", ITEM_ITEM, "dummy", 0, 2);

    cr_assert_eq(rc, SUCCESS,
                 "integer attribute was not set due to effect of direct item");
}

Test(item_item_actions, effect_set_double_direct)
{
    int rc = execute_do_item_item_action("dummy", ITEM_ITEM, "dummy", 0, 3);

    cr_assert_eq(rc, SUCCESS,
                 "double attribute was not set due to effect of direct item");
}

Test(item_item_actions, effect_set_character_direct)
{
    int rc = execute_do_item_item_action("dummy", ITEM_ITEM, "dummy", 0, 4);

    cr_assert_eq(rc, SUCCESS,
                 "character attribute was not set due to effect of direct item");
}

Test(item_item_actions, effect_set_boole_direct)
{
    int rc = execute_do_item_item_action("dummy", ITEM_ITEM, "dummy", 0, 5);

    cr_assert_eq(rc, SUCCESS,
                 "bool attribute was not set due to effect of direct item");
}

/* Checks if the condition is met for an item */
Test(item_item_actions, conditons_met_direct)
{
    int rc = execute_do_item_item_action("dummy", ITEM_ITEM, "dummy", 1, 0);

    cr_assert_eq(rc, SUCCESS,
                 "execute_do_item_item_action returned %d for conditons met for direct item attribute, expected SUCCESS (0)", rc);
}

/* Checks behavior when condition is not met */
Test(item_item_actions, conditons_not_met_direct)
{
    int rc = execute_do_item_item_action("dummy", ITEM_ITEM, "dummy", 2, 0);

    cr_assert_eq(rc, CONDITIONS_NOT_MET,
                 "execute_do_item_item_action returned %d for conditons not met for direct item attribute, expected CONDITIONS_NOT_MET (4)", rc);
}

/* Similar, to conditions_met_direct, but for another item */
Test(item_item_actions, conditons_met_indirect)
{
    int rc = execute_do_item_item_action("dummy", ITEM_ITEM, "dummy", 3, 0);

    cr_assert_eq(rc, SUCCESS,
                 "execute_do_item_item_action returned %d for conditons met for indirect item attribute, expected SUCCESS (0)", rc);
}

/* Check behavior when condition is not met */
Test(item_item_actions, conditons_not_met_indirect)
{
    int rc = execute_do_item_item_action("dummy", ITEM_ITEM, "dummy", 4, 0);

    cr_assert_eq(rc, CONDITIONS_NOT_MET,
                 "execute_do_item_item_action returned %d for conditons not met for indirect item attribute, expected CONDITIONS_NOT_MET (4)", rc);
}

/* Checks behavior when an inventory condition is met */
Test(item_item_actions, inv_conditions_met)
{
    int rc = execute_do_item_item_action("dummy", ITEM_ITEM, "dummy", 5, 0);

    cr_assert_eq(rc, SUCCESS,
                 "execute_do_item_item_action returned %d for conditons met for item in inventory, expected SUCCESS (0)", rc);
}

/* Checks behavior when an inventory condition is not met */
Test(item_item_actions, inv_conditions_not_met)
{
    int rc = execute_do_item_item_action("dummy", ITEM_ITEM, "dummy", 6, 0);

    cr_assert_eq(rc, CONDITIONS_NOT_MET,
                 "execute_do_item_item_action returned %d for conditons not met for item in inventory, expected CONDITIONS_NOT_MET (4)", rc);
}

/* Checks if two conditions (attribute and inventory) are able to be added and evaluated together */
Test(item_item_actions, attr_and_inv_conditions_met)
{
    int rc = execute_do_item_item_action("dummy", ITEM_ITEM, "dummy", 7, 0);

    cr_assert_eq(rc, SUCCESS,
                 "execute_do_item_item_action returned %d for attribute and inventory conditons met, expected SUCCESS (0)", rc);
}

/* Checks if two conditions (two inventory) are able to be added and evaluated together */
Test(item_item_actions, two_inv_conditions_met)
{
    int rc = execute_do_item_item_action("dummy", ITEM_ITEM, "dummy", 8, 0);

    cr_assert_eq(rc, SUCCESS,
                 "execute_do_item_item_action returned %d for two inventory conditons met, expected SUCCESS (0)", rc);
}
