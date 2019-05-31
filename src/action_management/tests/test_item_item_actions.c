#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "actionmanagement.h"
#include "action_structs.h"
#include "item.h"
#include "game.h"

bool execute_do_item_item_action(char *act_name, enum action_kind kind, char *allowed_act_name1, enum action_kind allowed_kind1, char *allowed_act_name2, enum action_kind allowed_kind2)
{
    game_t *g = game_new;
    action_type_t *a = action_type_new(c_name, kind);
    action_type_t *allowed_a1 = action_type_new(allowed_act_name1, allowed_kind1);
    action_type_t *allowed_a2 = action_type_new(allowed_act_name2, allowed_kind2);
    item_t *direct = item_new("direct", "The direct item", "The directmost object of interest");
    item_t *indirect = item_new("indirect", "The indirect item", "The indirectmost object of interest");
    add_allowed_action(direct, allowed_act_name1, allowed_a1);
    add_allowed_action(indirect, allowed_act_name2, allowed_a2);

    char *expected_output = malloc(100); // buffer
    expected_output[0] = '\0';
    strcat(expected_output, "Requested action ");
    strcat(expected_output, c_name);
    strcat(expected_output, " with ");
    strcat(expected_output, direct->item_id);
    strcat(expected_output, " on ");
    strcat(expected_output, indirect->item_id);

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

Test(item_item_actions, kind_ITEM)
{
    bool rc = execute_do_item_item_action("dummy", ITEM);

    cr_assert_eq(rc, false,
                  "execute_do_item_item_action returned true for wrong kind 1");
}

Test(item_item_actions, kind_PATH)
{

    bool rc = execute_do_item_item_action("dummy", PATH);

    cr_assert_eq(rc, false,
                 "execute_do_item_item_action returned true for wrong kind 2");
    ;
}

Test(item_item_actions, kind_ITEM_ITEM)
{
    bool rc = execute_do_item_item_action("dummy", ITEM_ITEM);

    cr_assert_eq(rc, true,
                 "execute_do_item_item_action returned false for correct kind 3");
}