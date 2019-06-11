#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "actionmanagement.h"
#include "action_structs.h"
#include "item.h"
#include "game.h"
#include "player.h"

#define BUFFER_SIZE (100)
#define WRONG_KIND (1)
#define NOT_ALLOWED_DIRECT (2)

int execute_do_item_action(char *act_name, enum action_kind kind, char *allowed_act_name, enum action_kind allowed_kind)
{
    action_type_t *a = action_type_new(act_name, kind);
    action_type_t *allowed_a = action_type_new(allowed_act_name, allowed_kind);
    item_t *item = item_new("dummy", "The dummy item", "The dummy object of interest");
    add_allowed_action(item, allowed_act_name, allowed_a);
    char *string = malloc(BUFFER_SIZE);

    int rc = do_item_action(a, item, &string);

    free(string);
    item_free(item);
    action_type_free(a);
    action_type_free(allowed_a);

    return rc;
}


Test(item_actions, correct_kind_1_and_allowed_action)
{
    int rc = execute_do_item_action("dummy", ITEM, "dummy", ITEM);

    cr_assert_eq(rc, SUCCESS,
                 "execute_do_item_action returned %d for correct kind 1, expected SUCCESS (0)", rc);
}


Test(item_actions, wrong_kind_2)
{

    int rc = execute_do_item_action("dummy", PATH, "dummy", PATH);

    cr_assert_eq(rc, WRONG_KIND,
                 "execute_do_item_action returned %d for wrong kind 2, expected WRONG_KIND (1)", rc);
}


Test(item_actions, wrong_kind_3)
{
    int rc = execute_do_item_action("dummy", ITEM_ITEM, "dummy", ITEM_ITEM);

    cr_assert_eq(rc, WRONG_KIND,
                 "execute_do_item_action returned %d for wrong kind 3, expected WRONG_KIND (1)", rc);
}


Test(item_actions, action_not_allowed_name)
{
    int rc = execute_do_item_action("dummy", ITEM, "dummy_allow", ITEM);

    cr_assert_eq(rc, NOT_ALLOWED_DIRECT,
                 "execute_do_item_action returned %d for action name that is not allowed, expected NOT_ALLOWED_DIRECT (2)", rc);
}


Test(item_actions, action_not_allowed_struct)
{
    int rc = execute_do_item_action("dummy", ITEM, "dummy_allow", ITEM_ITEM);

    cr_assert_eq(rc, NOT_ALLOWED_DIRECT,
                 "execute_do_item_action returned %d for action struct that is not allowed, expected NOT_ALLOWED_DIRECT (2)", rc);
}
