#include <stdio.h>
#include <criterion/criterion.h>
#include "common-game-action.h"
#include "game_action.h"
#include "item.h"
#include "common-item.h"

// BASIC GAME ACTION UNIT TESTS -----------------------------------------------

/* Checks creation of new game action */
Test(game_action, new)
{
    game_action_t *new_action = game_action_new("test_action", "success",
    "null");

    cr_assert_not_null(new_action, "game_action_new() test 1 has failed!");

}

/* Checks if creation of new game action fails */
Test(game_action, new_fail)
{
    game_action_t *new_action = NULL;

    cr_assert_null(new_action, "game_action_new() null test 1 has failed!");

}

/* checks correct initialization of new game action */
Test(game_action, init)
{
    game_action_t *new_action = game_action_new("test_action", "success",
    "failure");

    int check = game_action_init(new_action, "test_action", "success",
    "failure");

    cr_assert_eq(check, SUCCESS, "game_action_init() test 1 has failed!");

}

// ----------------------------------------------------------------------------


/* checks that action is retrieved correctly */
Test(game_action, get_existent_action)
{
    item_t *test_item = item_new("test_item", "item for testing",
    "item for testing get_action");

    int test_act1 = add_action(test_item, "push", "success", "failure");
    int test_act2 = add_action(test_item, "pull", "success", "failure");

    cr_assert_eq(test_act1, SUCCESS, "get_action(): adding act1 failed!");
    cr_assert_eq(test_act2, SUCCESS, "get_action(): adding act2 failed!");

    game_action_t *my_act = get_action(test_item, "push");

    cr_assert_str_eq(my_act->action_name, "push",
    "get_action(): wrong action!");

}

/* checks that nonexistent action is rnot retrieved */
Test(game_action, get_nonexistent_action)
{
    item_t *test_item = item_new("test_item", "item for testing",
    "item for testing get_action");

    int test_act1 = add_action(test_item, "push", "success", "failure");

    cr_assert_eq(test_act1, SUCCESS, "get_action(): adding act1 failed!");

    game_action_t *my_act = get_action(test_item, "pull");

    cr_assert_null(my_act,
        "get_action: returned a non-NULL pointer but expected NULL");

}

/* checks that action is correctly added to item */
Test(game_action, add_action)
{
    item_t *test_item = item_new("test_item", "item for testing",
    "item for testing add_action");

    int check = add_action(test_item, "push", "success", "failure");

    cr_assert_eq(check, SUCCESS, "add_action() test has failed!");

}

/* checks that desired action is possible on item */
 Test(game_action, possible_action)
 {
     item_t *test_item = item_new("test_item", "item for testing",
     "item for testing possible_action");

     add_action(test_item, "push", "success", "failure");

     int is_allowed = possible_action(test_item, "push");

     cr_assert_eq(is_allowed, SUCCESS, "possible_action() test failed!");
 }

 /* checks that desired action is correctly found to be not possible */
 Test(game_action, possible_action_fail)
 {
     item_t *test_item = item_new("test_item", "item for testing",
     "item for testing possible_action");

     add_action(test_item, "push", "success", "failure");

     int is_allowed = possible_action(test_item, "pull");

     cr_assert_eq(is_allowed, FAILURE,
         "possible_action() failure test failed!");
 }
