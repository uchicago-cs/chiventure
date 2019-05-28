#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "actionmanagement.h"
#include "action_structs.h"
#include "item.h"
#include "game.h"

bool execute_do_item_item_action(char *c_name, enum action_kind kind)
{
    game_t *g = game_new;
    action_type_t *a = action_type_new(c_name, kind);
    item_t *direct = item_new("direct", "The direct item", "The directmost object of interest");
    item_t *indirect = item_new("indirect", "The indirect item", "The indirectmost object of interest");

    char *expected_output = malloc(100); // buffer
    expected_output[0] = '\0';
    strcat(expected_output, "Requested action ");
    strcat(expected_output, c_name);
    strcat(expected_output, " with ");
    strcat(expected_output, "direct");
    strcat(expected_output, " on ");
    strcat(expected_output, "indirect");

    bool rc;
    if (strcmp(do_item_item_action(g, a, direct, indirect), expected_output) == 0) 
    {
        rc = true;
    }
    else 
    {
        rc = false;
    }

    free(expected_output);
    item_free(direct);
    item_free(indirect);
    action_type_free(a);
    game_free(g);

    return rc;
}

Test(item_item_actions, wrong_kind_1)
{
    bool rc = execute_do_item_item_action("dummy", ITEM);

    cr_assert_eq(rc, false,
                  "execute_do_item_item_action returned true for wrong kind 1");
}

Test(item_item_actions, wrong_kind_2)
{

    bool rc = execute_do_item_item_action("dummy", PATH);

    cr_assert_eq(rc, false,
                 "execute_do_item_item_action returned true for wrong kind 2");
    ;
}

Test(item_item_actions, correct_kind_3)
{
    bool rc = execute_do_item_item_action("dummy", ITEM_ITEM);

    cr_assert_eq(rc, true,
                 "execute_do_item_item_action returned false for correct kind 3");
}