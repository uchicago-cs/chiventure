#include <stdio.h>
#include <criterion/criterion.h>
#include "common-game-action.h"
#include "game_action.h"
#include "item.h"
#include "common-item.h"

// CONDITION TESTS ------------------------------------------------------------

/* checks new condition created correctly */
Test(game_action_conditions, new)
{
    item_t *test_item = item_new("door", "door for testing",
    "door for testing condition_new()");

    // set_int_attr(test_item, "locked", 1);
    attribute_t *test_attr = malloc(sizeof(attribute_t));
    test_attr->attribute_key = (char*)malloc(100);
    test_attr->attribute_key = "locked";
    test_attr->attribute_tag = INTEGER;
    test_attr->attribute_value.int_val = 1;

    attribute_value_t value;
    value.int_val = 0;

    game_action_condition_t *test_cond = condition_new(test_item, test_attr,
        value);

    cr_assert_eq(test_cond->expected_value.int_val, 0,
        "condition_new() test failed!");
}

/* checks adding a single condition to an item's action*/
Test(game_action_cond, add_act_cond) {
    //setting up
    item_t *door = item_new("door", "door for testing",
        "item for testing add_action_condition");

    int set_attr = set_bool_attr(door, "locked", true);
    cr_assert_eq(set_attr, SUCCESS, "add_act_cond: failed to set attribute");

    int add_action_check = add_action(door, "open", "door opened!",
    "door did not open!");
    cr_assert_eq(add_action_check, SUCCESS,
        "add_act_cond: failed to retrieve action from item");

    //checking
    game_action_t *open_action = get_action(door, "open");

    attribute_t* attr_to_check = get_attribute(door, "locked");
    cr_assert_not_null(attr_to_check,
        "add_act_cond: could not retrieve the attribute to check from item");

    attribute_value_t cond_value;
    cond_value.bool_val = false;

    int add_cond_check = add_action_condition(door, open_action, door,
        attr_to_check, cond_value);

    cr_assert_eq(add_cond_check, SUCCESS,
        "add_act_cond: adding the condition failed");
}

/* checks adding multiple conditions to an item's action*/
Test(game_action_cond, add_multiple_cond) {
    //setting up
    item_t *door = item_new("door", "door for testing",
        "item1 for testing add_action_condition");

    int set_attr1 = set_bool_attr(door, "locked", true);
    cr_assert_eq(set_attr1, SUCCESS,
        "add_multiple_act_cond: failed to set attribute");

    item_t* sconce = item_new("sconce", "sconce for testing",
        "item2 for testing add_action_condition");

    int set_attr2 = set_bool_attr(sconce, "pulled", false);
    cr_assert_eq(set_attr2, SUCCESS,
        "add_multiple_act_cond: failed to set attribute");


    int add_action_check = add_action(door,
        "open", "door opened!", "door did not open!");
    cr_assert_eq(add_action_check, SUCCESS,
        "add_multiple_act_cond: failed to retrieve action");

    //checking
    game_action_t *open_action = get_action(door, "open");

    attribute_t* attr_to_check1 = get_attribute(door, "locked");
    cr_assert_not_null(attr_to_check1,
        "add_multiple_act_cond: could not retrieve attr to check from item");

    attribute_value_t cond_value1;
    cond_value1.bool_val = false;

    attribute_t* attr_to_check2 = get_attribute(sconce, "pulled");
    cr_assert_not_null(attr_to_check2,
        "add_multiple_act_cond: could not retrieve attr to check from item");

    attribute_value_t cond_value2;
    cond_value2.bool_val = false;

    int add_cond_check1 = add_action_condition(door, open_action, door,
        attr_to_check1, cond_value1);

    cr_assert_eq(add_cond_check1, SUCCESS,
        "add_multiple_act_cond: adding the condition failed");

    int add_cond_check2 = add_action_condition(door, open_action, sconce,
        attr_to_check2, cond_value2);

    cr_assert_eq(add_cond_check2, SUCCESS,
        "add_multiple_act_cond: adding the condition failed");
}


/* checks if all_cond_met() correctly evaluates a single failed condition for an action*/
Test(game_action_cond, check_failed_act_cond) {
    //setting up
    item_t *door = item_new("door", "door for testing",
        "item for testing add_action_condition");

    int set_attr = set_bool_attr(door, "locked", true);
    cr_assert_eq(set_attr, SUCCESS, "failed to set attribute");

    int add_action_check = add_action(door, "open", "door opened!",
    "door did not open!");
    cr_assert_eq(add_action_check, SUCCESS, "failed to add the action");

    //checking
    game_action_t *open_action = get_action(door, "open");

    attribute_t* attr_to_check = get_attribute(door, "locked");
    cr_assert_not_null(attr_to_check,
        "could not retrieve the attribute to check from item");

    attribute_value_t cond_value;
    cond_value.bool_val = false;

    int add_cond_check = add_action_condition(door, open_action, door,
        attr_to_check, cond_value);

    cr_assert_eq(add_cond_check, SUCCESS, "adding the condition failed");

    int checking_conditon = all_conditions_met(door, "open");

    cr_assert_eq(checking_conditon, FAILURE,
        "returned that all conditions were met when they were not");
}

/* checks if all_cond_met() correctly evaluates a single successful condition for an action*/
Test(game_action_cond, check_success_act_cond) {
    //setting up
    item_t *door = item_new("door", "door for testing",
        "item for testing add_action_condition");

    int set_attr = set_bool_attr(door, "locked", false);
    cr_assert_eq(set_attr, SUCCESS,
        "check_success_act_cond: failed to set attribute");

    int add_action_check = add_action(door, "open", "door opened!",
    "door did not open!");
    cr_assert_eq(add_action_check, SUCCESS,
        "check_success_act_cond: failed to add the action");

    //checking
    game_action_t *open_action = get_action(door, "open");

    attribute_t* attr_to_check = get_attribute(door, "locked");
    cr_assert_not_null(attr_to_check,
        "check_success_act_cond: could not retrieve attr to check from item");

    attribute_value_t cond_value;
    cond_value.bool_val = false;

    int add_cond_check = add_action_condition(door, open_action, door,
        attr_to_check, cond_value);

    cr_assert_eq(add_cond_check, SUCCESS,
        "check_success_act_cond: adding the condition failed");

    int checking_conditon = all_conditions_met(door, "open");

    cr_assert_eq(checking_conditon, SUCCESS,
        "check_success_act_cond: returns that all conds were met when they were not");
}

/* checks multiple conditions of an item's action where all should fail*/
Test(game_action_cond, check_all_failed_multiple_act_cond) {
    //setting up
    item_t *door = item_new("door", "door for testing",
        "item1 for testing add_action_condition");

    int set_attr1 = set_bool_attr(door, "locked", true);
    cr_assert_eq(set_attr1, SUCCESS,
        "check_all_failed_multiple_act_cond: failed to set attribute");

    item_t* sconce = item_new("sconce", "sconce for testing",
        "item2 for testing add_action_condition");

    int set_attr2 = set_bool_attr(sconce, "pulled", false);
    cr_assert_eq(set_attr2, SUCCESS,
        "check_all_failed_multiple_act_cond: failed to set attribute");


    int add_action_check = add_action(door, "open", "door opened!",
    "door did not open!");
    cr_assert_eq(add_action_check, SUCCESS,
        "check_all_failed_multiple_act_cond: failed to retrieve action");

    //checking
    game_action_t *open_action = get_action(door, "open");

    attribute_t* attr_to_check1 = get_attribute(door, "locked");
    cr_assert_not_null(attr_to_check1,
        "check_all_failed_multiple_act_cond: could not retrieve the attribute to check from item");

    attribute_value_t cond_value1;
    cond_value1.bool_val = false;

    attribute_t* attr_to_check2 = get_attribute(sconce, "pulled");
    cr_assert_not_null(attr_to_check2,
        "check_all_failed_multiple_act_cond: could not retrieve the attribute to check from item");

    attribute_value_t cond_value2;
    cond_value2.bool_val = true;

    int add_cond_check1 = add_action_condition(door, open_action, door, attr_to_check1, cond_value1);

    cr_assert_eq(add_cond_check1, SUCCESS,
        "check_all_failed_multiple_act_cond: adding the condition failed");

    int add_cond_check2 = add_action_condition(door, open_action, sconce , attr_to_check2, cond_value2);

    cr_assert_eq(add_cond_check2, SUCCESS,
        "check_all_failed_multiple_act_cond: adding the condition failed");

    int checking_conditon = all_conditions_met(door, "open");

    cr_assert_eq(checking_conditon, FAILURE,
        "check_all_failed_multiple_act_cond: returned that all conditions were met when they were not");
}

/* checks multiple conditions of an item's action where some fail and some pass*/
Test(game_action_cond, check_some_failed_multiple_act_cond) {
    //setting up
    item_t *door = item_new("door", "door for testing",
        "item1 for testing add_action_condition");

    int set_attr1 = set_bool_attr(door, "locked", true);
    cr_assert_eq(set_attr1, SUCCESS,
        "check_some_failed_multiple_act_cond: failed to set attribute");

    item_t* sconce = item_new("sconce", "sconce for testing",
        "item2 for testing add_action_condition");

    int set_attr2 = set_bool_attr(sconce, "pulled", true);
    cr_assert_eq(set_attr2, SUCCESS,
        "check_some_failed_multiple_act_cond: failed to set attribute");


    int add_action_check = add_action(door, "open", "door opened!",
    "door did not open!");
    cr_assert_eq(add_action_check, SUCCESS,
        "check_some_failed_multiple_act_cond: failed to retrieve action");

    //checking
    game_action_t *open_action = get_action(door, "open");

    attribute_t* attr_to_check1 = get_attribute(door, "locked");
    cr_assert_not_null(attr_to_check1,
        "check_some_failed_multiple_act_cond: could not retrieve the attribute to check from item");

    attribute_value_t cond_value1;
    cond_value1.bool_val = false;

    attribute_t* attr_to_check2 = get_attribute(sconce, "pulled");
    cr_assert_not_null(attr_to_check2, "check_some_failed_multiple_act_cond: could not retrieve the attribute to check from item");

    attribute_value_t cond_value2;
    cond_value2.bool_val = false;

    int add_cond_check1 = add_action_condition(door, open_action, door,
        attr_to_check1, cond_value1);

    cr_assert_eq(add_cond_check1, SUCCESS,
        "check_some_failed_multiple_act_cond: adding the condition failed");

    int add_cond_check2 = add_action_condition(door, open_action, sconce,
        attr_to_check2, cond_value2);

    cr_assert_eq(add_cond_check2, SUCCESS,
        "check_some_failed_multiple_act_cond: adding the condition failed");

    int checking_conditon = all_conditions_met(door, "open");

    cr_assert_eq(checking_conditon, FAILURE,
        "check_some_failed_multiple_act_cond: returned that all conditions were met when they were not");
}

/* checks multiple conditions of an item's action where all pass */
/* test for function all_conditions_met() */
Test(game_action_cond, check_all_pass_multiple_act_cond) {
    //setting up
    item_t *door = item_new("door", "door for testing",
        "item1 for testing add_action_condition");

    int set_attr1 = set_bool_attr(door, "locked", false);
    cr_assert_eq(set_attr1, SUCCESS, "check_all_pass_multiple_act_cond: add_multiple_act_cond: failed to set attribute");

    item_t* sconce = item_new("sconce", "sconce for testing",
        "item2 for testing add_action_condition");

    int set_attr2 = set_bool_attr(sconce, "pulled", true);
    cr_assert_eq(set_attr2, SUCCESS, "check_all_pass_multiple_act_cond: failed to set attribute");


    int add_action_check = add_action(door, "open", "door opened!", "door did not open!");
    cr_assert_eq(add_action_check, SUCCESS, "check_all_pass_multiple_act_cond: failed to retrieve action");

    //checking
    game_action_t *open_action = get_action(door, "open");

    attribute_t* attr_to_check1 = get_attribute(door, "locked");
    cr_assert_not_null(attr_to_check1, "check_all_pass_multiple_act_cond: could not retrieve the attribute to check from item");

    attribute_value_t cond_value1;
    cond_value1.bool_val = false;

    attribute_t* attr_to_check2 = get_attribute(sconce, "pulled");
    cr_assert_not_null(attr_to_check2, "check_all_pass_multiple_act_cond: could not retrieve the attribute to check from item");

    attribute_value_t cond_value2;
    cond_value2.bool_val = false;

    int add_cond_check1 = add_action_condition(door, open_action, door, attr_to_check1, cond_value1);

    cr_assert_eq(add_cond_check1, SUCCESS, "check_all_pass_multiple_act_cond: adding the condition failed");

    int add_cond_check2 = add_action_condition(door, open_action, sconce , attr_to_check2, cond_value2);

    cr_assert_eq(add_cond_check2, SUCCESS, "check_all_pass_multiple_act_cond: adding the condition failed");

    int checking_conditon = all_conditions_met(door, "open");

    cr_assert_eq(checking_conditon, FAILURE, "check_all_pass_multiple_act_cond: returned that all conditions were met when they were not");
}
