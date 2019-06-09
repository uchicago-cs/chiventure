#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "actionmanagement.h"
#include "action_structs.h"
#include "item.h"
#include "game.h"
#include "player.h"

#define BUFFER_SIZE (100)
#define WRONG_KIND (1)
#define NOT_ALLOWED_DIRECT (2)
#define NOT_ALLOWED_INDIRECT (3)
#define CONDITIONS_NOT_MET (4)
#define ATTRIBUTE_TYPE_DNE (5)
#define ATTRIBUTE_NOT_SET (6)

int execute_do_item_item_action(char *act_name, enum action_kind kind, char *allowed_act_name1, enum action_kind allowed_kind1, char *allowed_act_name2, enum action_kind allowed_kind2, int choose_item, int choose_attribute)
{
    action_type_t *a = action_type_new(act_name, kind);
    item_t *direct = item_new("direct", "The direct item", "The directmost object of interest");
    item_t *indirect = item_new("indirect", "The indirect item", "The indirectmost object of interest");
    add_action(direct, allowed_act_name1, "success1", "fail1");
    add_action(indirect, allowed_act_name2, "success2", "fail2");
    char *string = malloc(BUFFER_SIZE);

    item_t **chosen_item;
    switch (choose_item)
    {
    case 1:
        chosen_item = &direct;
        break;
    case 2:
        chosen_item = &indirect;
        break;
    default:
        break;
    }

    int n;
    switch (choose_attribute)
    {
    case 1:
        n = set_str_attr(*chosen_item, "DUMMYATTR", "old");
        game_action_t *ga = get_action(*chosen_item, act_name);
        n = add_action_effect(ga, *chosen_item, "DUMMYATTR", "new");
        n = do_item_item_action(a, direct, indirect, &string);
        if (strcmp(get_str_attr(*chosen_item, "DUMMYATTR"), "new") == 0)
        {
            rc = SUCCESS;
        }
        else
        {
            rc = FAILURE;
        }
        break;
    case 2:
        n = set_int_attr(*chosen_item, "DUMMYATTR", 0);
        game_action_t *ga = get_action(*chosen_item, act_name);
        n = add_action_effect(ga, *chosen_item, "DUMMYATTR", 1);
        n = do_item_item_action(a, direct, indirect, &string);
        if (get_int_attr(*chosen_item, "DUMMYATTR") == 1)
        {
            rc = SUCCESS;
        }
        else
        {
            rc = FAILURE;
        }
        break;
    case 3:
        n = set_double_attr(*chosen_item, "DUMMYATTR", 0.0);
        game_action_t *ga = get_action(*chosen_item, act_name);
        n = add_action_effect(ga, *chosen_item, "DUMMYATTR", 1.0);
        n = do_item_item_action(a, direct, indirect, &string);
        if (get_double_attr(*chosen_item, "DUMMYATTR") == 1.0)
        {
            rc = SUCCESS;
        }
        else
        {
            rc = FAILURE;
        }
        break;
    case 4:
        n = set_char_attr(*chosen_item, "DUMMYATTR", 'a');
        game_action_t *ga = get_action(*chosen_item, act_name);
        n = add_action_effect(ga, *chosen_item, "DUMMYATTR", 'b');
        n = do_item_item_action(a, direct, indirect, &string);
        if (get_char_attr(*chosen_item, "DUMMYATTR") == 'b')
        {
            rc = SUCCESS;
        }
        else
        {
            rc = FAILURE;
        }
        break;
    case 5:
        n = set_bool_attr(*chosen_item, "DUMMYATTR", false);
        game_action_t *ga = get_action(*chosen_item, act_name);
        n = add_action_effect(ga, *chosen_item, "DUMMYATTR", true);
        n = do_item_item_action(a, direct, indirect, &string);
        if (get_bool_attr(*chosen_item, "DUMMYATTR") == true)
        {
            rc = SUCCESS;
        }
        else
        {
            rc = FAILURE;
        }
        break;
    default:
        rc = do_item_item_action(a, direct, indirect, &string);
        break;
    }


    free(string);
    item_free(direct);
    item_free(indirect);
    action_type_free(a);

    return rc;
}


Test(item_item_actions, wrong_kind_ITEM)
{
    int rc = execute_do_item_item_action(ITEM, "dummy", ITEM, "dummy", ITEM, 1, 0);

    cr_assert_eq(rc, WRONG_KIND,
                 "execute_do_item_item_action returned %d for wrong kind 1, expected WRONG_KIND (1)", rc);
}


Test(item_item_actions, wrong_kind_PATH)
{

    int rc = execute_do_item_item_action(PATH, "dummy", PATH, "dummy", PATH, 1, 0);

    cr_assert_eq(rc, WRONG_KIND,
                 "execute_do_item_item_action returned %d for wrong kind 2, expected WRONG_KIND (1)", rc);
}


Test(item_item_actions, correct_kind_ITEM_ITEM)
{
    int rc = execute_do_item_item_action(ITEM_ITEM, "dummy", ITEM_ITEM, "dummy", ITEM_ITEM, 1, 0);

    cr_assert_eq(rc, SUCCESS,
                 "execute_do_item_item_action returned %d for correct kind 3, expected SUCCESS (0)", rc);
}


Test(item_item_actions, correct_allowed_actions)
{
    int rc = execute_do_item_item_action(ITEM_ITEM, "dummy", ITEM_ITEM, "dummy", ITEM_ITEM, 1, 0);

    cr_assert_eq(rc, SUCCESS,
                 "execute_do_item_item_action returned %d for correct allowed actions in indirect and direct, expected SUCCESS (0)", rc);
}


Test(item_item_actions, wrong_allowed_actions_direct)
{
    int rc = execute_do_item_item_action(ITEM_ITEM, "dummy_allowed", ITEM_ITEM, "dummy", ITEM_ITEM, 1, 0);

    cr_assert_eq(rc, NOT_ALLOWED_DIRECT,
                 "execute_do_item_item_action returned %d for incorrect allowed actions name in direct, expected NOT_ALLOWED_DIRECT (2)", rc);
}


Test(item_item_actions, wrong_allowed_actions_indirect)
{
    int rc = execute_do_item_item_action(ITEM_ITEM, "dummy", ITEM_ITEM, "dummy_allowed", ITEM_ITEM, 1, 0);

    cr_assert_eq(rc, NOT_ALLOWED_INDIRECT,
                 "execute_do_item_item_action returned %d for incorrect allowed actions name in indirect, expected NOT_ALLOWED_INDIRECT (3)", rc);
}


Test(item_item_actions, wrong_allowed_actions)
{
    int rc = execute_do_item_item_action(ITEM_ITEM, "dummy_allowed", ITEM_ITEM, "dummy_allowed", ITEM_ITEM, 1, 0);

    cr_assert_eq(rc, NOT_ALLOWED_DIRECT,
                 "execute_do_item_item_action returned %d for incorrect allowed actions name in indirect and direct, expected NOT_ALLOWED_DIRECT (2)", rc);
}

Test(item_item_actions, effect_set_string_direct)
{
    int rc = execute_do_item_item_action(ITEM_ITEM, "dummy", ITEM_ITEM, "dummy", ITEM_ITEM, 1, 1);
    
    cr_assert_eq(rc, SUCCESS,
                 "string attributewas not set due to effect of direct item");
}

Test(item_item_actions, effect_set_integer_direct)
{
    int rc = execute_do_item_item_action(ITEM_ITEM, "dummy", ITEM_ITEM, "dummy", ITEM_ITEM, 1, 2);

    cr_assert_eq(rc, SUCCESS,
                 "integer attribute was not set due to effect of direct item");
}

Test(item_item_actions, effect_set_double_direct)
{
    int rc = execute_do_item_item_action(ITEM_ITEM, "dummy", ITEM_ITEM, "dummy", ITEM_ITEM, 1, 3);

    cr_assert_eq(rc, SUCCESS,
                 "double attribute was not set due to effect of direct item");
}

Test(item_item_actions, effect_set_character_direct)
{
    int rc = execute_do_item_item_action(ITEM_ITEM, "dummy", ITEM_ITEM, "dummy", ITEM_ITEM, 1, 4);

    cr_assert_eq(rc, SUCCESS,
                 "character attribute was not set due to effect of direct item");
}

Test(item_item_actions, effect_set_boole_direct)
{
    int rc = execute_do_item_item_action(ITEM_ITEM, "dummy", ITEM_ITEM, "dummy", ITEM_ITEM, 1, 5);

    cr_assert_eq(rc, SUCCESS,
                 "bool attribute was not set due to effect of direct item");
}

Test(item_item_actions, conditons_not_met_both)
{
}

Test(item_item_actions, conditons_not_met_direct)
{
}

Test(item_item_actions, conditons_not_met_indirect)
{
}

Test(item_item_actions, conditons_met)
{
}