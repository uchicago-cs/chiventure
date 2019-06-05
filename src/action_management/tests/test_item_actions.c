#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "actionmanagement.h"
#include "action_structs.h"
#include "item.h"
#include "game.h"
#include "player.h"

#define BUFFER_SIZE (100)

bool execute_do_item_action(char *act_name, enum action_kind kind, char *allowed_act_name, enum action_kind allowed_kind)
{
    player_t *player = player_new("player", 1);
    game_t *g = game_new("this is a dummy game");
    add_player_to_game(g, player);
    set_curr_player(g, player);
    action_type_t *a = action_type_new(act_name, kind);
    action_type_t *allowed_a = action_type_new(allowed_act_name, allowed_kind);
    item_t *item = item_new("dummy", "The dummy item", "The dummy object of interest");
    add_allowed_action(item, allowed_act_name, allowed_a);

    char *expected_output = malloc(BUFFER_SIZE);
    expected_output[0] = '\0';
    strcat(expected_output, "Requested action ");
    strcat(expected_output, a->c_name);
    strcat(expected_output, " on item ");
    strcat(expected_output, item->item_id);

    bool rc;
    if (strcmp(do_item_action(g, a, item), expected_output) == 0)
    {
        rc = true;
    }
    else
    {
        rc = false;
    }

    free(expected_output);
    item_free(item);
    action_type_free(a);
    action_type_free(allowed_a);
    game_free(g);

    return rc;
}

Test(item_actions, correct_kind_1_and_allowed_action)
{
    bool rc = execute_do_item_action("dummy", ITEM, "dummy", ITEM);

    cr_assert_eq(rc, true,
                  "execute_do_item_action returned false for correct kind 1");
}

Test(item_actions, wrong_kind_2)
{

    bool rc = execute_do_item_action("dummy", PATH, "dummy", PATH);

    cr_assert_eq(rc, false,
                 "execute_do_item_action returned true for wrong kind 2");
}

Test(item_actions, wrong_kind_3)
{
    bool rc = execute_do_item_action("dummy", ITEM_ITEM, "dummy", ITEM_ITEM);

    cr_assert_eq(rc, false,
                 "execute_do_item_action returned true for wrong kind 3");
}

Test(item_actions, action_not_allowed_name)
{
    bool rc = execute_do_item_action("dummy", ITEM, "dummy_allow", ITEM);

    cr_assert_eq(rc, false,
                 "execute_do_item_action returned true for action name that is not allowed");
}

Test(item_actions, action_not_allowed_struct)
{
    bool rc = execute_do_item_action("dummy", ITEM, "dummy_allow", ITEM_ITEM);

    cr_assert_eq(rc, false,
                 "execute_do_item_action returned true for action struct that is not allowed");
}
