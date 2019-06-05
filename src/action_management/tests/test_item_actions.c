#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "actionmanagement.h"
#include "action_structs.h"
#include "item.h"
#include "game.h"
#include "player.h"

#define BUFFER_SIZE (100)

int execute_do_item_action(char *act_name, enum action_kind kind, char *allowed_act_name, enum action_kind allowed_kind)
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
    sprintf(expected_output, "Requested action %s on item %s",
            a->c_name, item->item_id);

    char *kind_error = malloc(BUFFER_SIZE);
    sprintf(kind_error, "The action type provided is not of the correct kind");

    char *allowed_error = malloc(BUFFER_SIZE);
    sprintf(allowed_error, "Action %s can't be requested on item %s",
            a->c_name, item->item_id);

    int rc;
    if (strcmp(do_item_action(g, a, item), expected_output) == 0)
    {
        rc = SUCCESS;
    }
    else if (strcmp(do_item_action(g, a, item), kind_error) == 0)
    {
        rc = FAILURE;
    }
    else if (strcmp(do_item_action(g, a, item), allowed_error) == 0)
    {
        rc = 2;
    }
    else {
        rc = 4; //Wrong string printed
    }

    free(expected_output);
    free(kind_error);
    free(allowed_error);
    item_free(item);
    action_type_free(a);
    action_type_free(allowed_a);
    game_free(g);

    return rc;
}

Test(item_actions, correct_kind_1_and_allowed_action)
{
    int rc = execute_do_item_action("dummy", ITEM, "dummy", ITEM);

    cr_assert_eq(rc, SUCCESS,
                 "execute_do_item_action returned %d for correct kind 1, expected 0", rc);
}

Test(item_actions, wrong_kind_2)
{

    int rc = execute_do_item_action("dummy", PATH, "dummy", PATH);

    cr_assert_eq(rc, FAILURE,
                 "execute_do_item_action returned %d for wrong kind 2, expected 1", rc);
}

Test(item_actions, wrong_kind_3)
{
    int rc = execute_do_item_action("dummy", ITEM_ITEM, "dummy", ITEM_ITEM);

    cr_assert_eq(rc, FAILURE,
                 "execute_do_item_action returned %d for wrong kind 3, expected 1", rc);
}

Test(item_actions, action_not_allowed_name)
{
    int rc = execute_do_item_action("dummy", ITEM, "dummy_allow", ITEM);

    cr_assert_eq(rc, 2,
                 "execute_do_item_action returned %d for action name that is not allowed, expected 2", rc);
}

Test(item_actions, action_not_allowed_struct)
{
    int rc = execute_do_item_action("dummy", ITEM, "dummy_allow", ITEM_ITEM);

    cr_assert_eq(rc, 2,
                 "execute_do_item_action returned %d for action struct that is not allowed, expected 2", rc);
}
