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
#define CONDITIONS_NOT_MET (6)
#define EFFECT_NOT_APPLIED (7)

int execute_do_item_action(char *act_name, enum action_kind kind, char *allowed_act_name, int choose_condition, int choose_effect)
{
    chiventure_ctx_t *ctx_test = chiventure_ctx_new(NULL);
  
    action_type_t *a = action_type_new(act_name, kind);
    item_t *item = item_new("item", "The item item", "The itemmost object of interest");
    agent_t *agent = malloc(sizeof(agent_t));
    agent->item = item;
    agent->npc = NULL;
    add_action(agent, allowed_act_name, "success1", "fail1");
    char *string = malloc(BUFFER_SIZE);
    game_action_t *ga;
    if (strcmp(act_name, allowed_act_name) == 0)
    {
        ga = get_action(agent, act_name);
    }
    else
    {
        ga = get_action(agent, allowed_act_name);
    }
    int rc;
    attribute_value_t *value = malloc(sizeof(attribute_value_t));
    attribute_t *attr;

    switch (choose_condition)
    {
    case 1:
        set_int_attr(agent->item, "DUMMYCONDITON", 0);
        attr = get_attribute(agent->item, "DUMMYCONDITON");
        value->int_val = 0;
        add_action_attribute_condition(ga, agent->item, attr, value);
        break;
    case 2:
        set_int_attr(agent->item, "DUMMYCONDITON", 1);
        attr = get_attribute(agent->item, "DUMMYCONDITON");
        value->int_val = 0;
        add_action_attribute_condition(ga, agent->item, attr, value);
        break;
    default:
        break;
    }

    switch (choose_effect)
    {
    case 0:
        rc = do_item_action(ctx_test, a, agent->item, &string);
        break;
    case 1:
        set_str_attr(agent->item, "DUMMYATTR", "old");
        attr = get_attribute(agent->item, "DUMMYATTR");
        value->str_val = "new";
        add_action_effect(ga, agent->item, attr, value);
        do_item_action(ctx_test, a, agent->item, &string);
        if (strcmp(get_str_attr(agent->item, "DUMMYATTR"), "new") == 0)
        {
            rc = SUCCESS;
        }
        else
        {
            rc = FAILURE;
        }
        break;
    case 2:
        set_int_attr(agent->item, "DUMMYATTR", 0);
        attr = get_attribute(agent->item, "DUMMYATTR");
        value->int_val = 1;
        add_action_effect(ga, agent->item, attr, value);
        do_item_action(ctx_test, a, agent->item, &string);
        if (get_int_attr(agent->item, "DUMMYATTR") == 1)
        {
            rc = SUCCESS;
        }
        else
        {
            rc = FAILURE;
        }
        break;
    case 3:
        set_double_attr(agent->item, "DUMMYATTR", 0.0);
        attr = get_attribute(agent->item, "DUMMYATTR");
        value->double_val = 1.0;
        add_action_effect(ga, agent->item, attr, value);
        do_item_action(ctx_test, a, agent->item, &string);
        if (get_double_attr(agent->item, "DUMMYATTR") == 1.0)
        {
            rc = SUCCESS;
        }
        else
        {
            rc = FAILURE;
        }
        break;
    case 4:
        set_char_attr(agent->item, "DUMMYATTR", 'a');
        attr = get_attribute(agent->item, "DUMMYATTR");
        value->char_val = 'b';
        add_action_effect(ga, agent->item, attr, value);
        do_item_action(ctx_test, a, agent->item, &string);
        if (get_char_attr(agent->item, "DUMMYATTR") == 'b')
        {
            rc = SUCCESS;
        }
        else
        {
            rc = FAILURE;
        }
        break;
    case 5:
        set_bool_attr(agent->item, "DUMMYATTR", false);
        attr = get_attribute(agent->item, "DUMMYATTR");
        value->bool_val = true;
        add_action_effect(ga, agent->item, attr, value);
        do_item_action(ctx_test, a, agent->item, &string);
        if (get_bool_attr(agent->item, "DUMMYATTR") == true)
        {
            rc = SUCCESS;
        }
        else
        {
            rc = FAILURE;
        }
        break;
    default:
        rc = do_item_action(ctx_test, a, agent->item, &string);
        break;
    }
    
    
    game_free(ctx_test->game);
    lookup_t_free(ctx_test->cli_ctx->table);
    free(ctx_test->cli_ctx->table);
    chiventure_ctx_free(ctx_test);
    free(string);
    item_free(agent->item);
    free(agent);
    action_type_free(a);
    free(value);

    return rc;
}

Test(item_actions, correct_kind_1_and_allowed_action)
{
    int rc = execute_do_item_action("dummy", ITEM, "dummy", 0, 0);

    cr_assert_eq(rc, SUCCESS,
                 "execute_do_item_action returned %d for correct kind 1, expected SUCCESS (0)", rc);
}

Test(item_actions, wrong_kind_2)
{

    int rc = execute_do_item_action("dummy", PATH, "dummy", 0, 0);

    cr_assert_eq(rc, WRONG_KIND,
                 "execute_do_item_action returned %d for wrong kind 2, expected WRONG_KIND (2)", rc);
}

Test(item_actions, wrong_kind_3)
{
    int rc = execute_do_item_action("dummy", ITEM_ITEM, "dummy", 0, 0);

    cr_assert_eq(rc, WRONG_KIND,
                 "execute_do_item_action returned %d for wrong kind 3, expected WRONG_KIND (2)", rc);
}

Test(item_actions, correct_allowed_action)
{
    int rc = execute_do_item_action("dummy", ITEM, "dummy", 0, 0);

    cr_assert_eq(rc, SUCCESS,
                 "execute_do_item_action returned %d for correct allowed action, expected SUCCESS (0)", rc);
}

Test(item_actions, wrong_allowed_action)
{
    int rc = execute_do_item_action("dummy", ITEM, "dummy_allowed", 0, 0);

    cr_assert_eq(rc, NOT_ALLOWED_DIRECT,
                 "execute_do_item_action returned %d for incorrect allowed action, expected NOT_ALLOWED (2)", rc);
}

Test(item_actions, effect_set_string)
{
    int rc = execute_do_item_action("dummy", ITEM, "dummy", 0, 1);

    cr_assert_eq(rc, SUCCESS,
                 "string attribute was not set");
}

Test(item_actions, effect_set_integer)
{
    int rc = execute_do_item_action("dummy", ITEM, "dummy", 0, 2);

    cr_assert_eq(rc, SUCCESS,
                 "integer attribute was not set");
}

Test(item_actions, effect_set_double)
{
    int rc = execute_do_item_action("dummy", ITEM, "dummy", 0, 3);

    cr_assert_eq(rc, SUCCESS,
                 "double attribute was not set");
}

Test(item_actions, effect_set_character)
{
    int rc = execute_do_item_action("dummy", ITEM, "dummy", 0, 4);

    cr_assert_eq(rc, SUCCESS,
                 "character attribute was not set");
}

Test(item_actions, effect_set_boole)
{
    int rc = execute_do_item_action("dummy", ITEM, "dummy", 0, 5);

    cr_assert_eq(rc, SUCCESS,
                 "bool attribute was not set");
}

Test(item_actions, conditons_met)
{
    int rc = execute_do_item_action("dummy", ITEM, "dummy", 1, 0);

    cr_assert_eq(rc, SUCCESS,
                 "execute_do_item_action returned %d for conditons met, expected SUCCESS (0)", rc);
}

Test(item_actions, conditons_not_met)
{
    int rc = execute_do_item_action("dummy", ITEM, "dummy", 2, 0);

    cr_assert_eq(rc, CONDITIONS_NOT_MET,
                 "execute_do_item_action returned %d for conditons not met, expected CONDITIONS_NOT_MET (4)", rc);
}
