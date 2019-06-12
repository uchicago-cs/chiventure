#include <stdio.h>
#include <criterion/criterion.h>
#include "common-game-action.h"
#include "game_action.h"
#include "item.h"
#include "common-item.h"

// EFFECT TESTS ------------------------------------------------------------

/* checks adding a single effect to an item's action */
Test(game_action_effects, add_act_effect) {
    //setting up
    item_t *door = item_new("door", "door for testing",
        "item for testing add_action_condition");

    int set_attr = set_bool_attr(door, "open", false);
    cr_assert_eq(set_attr, SUCCESS, "add_act_cond: failed to set attribute");

    int add_action_check = add_action(door, "open", "door opened!", "door did not open!");
    cr_assert_eq(add_action_check, SUCCESS, "add_act_cond: failed to retrieve action from item");

    //checking
    game_action_t *open_action = get_action(door, "open");

    attribute_t* attr_to_affect = get_attribute(door, "open");
    cr_assert_not_null(attr_to_affect, "add_act_cond: could not retrieve the attribute to check from item");

    attribute_value_t effect_value;
    effect_value.bool_val = true;

    int add_effect_check = add_action_effect(open_action, door, door, attr_to_affect, effect_value);

    cr_assert_eq(add_effect_check, SUCCESS, "add_act_cond: adding the condition failed");
}
 /* test for add_action_effect */
 /* test for function add_action_effect() */
Test(game_action_effects, add_multiple_effects) {
    //setting up
    item_t *door = item_new("door", "door for testing",
        "item1 for testing add_action_condition");

    int set_attr1 = set_bool_attr(door, "locked", true);
    cr_assert_eq(set_attr1, SUCCESS, "add_multiple_act_cond: failed to set attribute");

    item_t* sconce = item_new("sconce", "sconce for testing",
        "item2 for testing add_action_condition");

    int set_attr2 = set_bool_attr(sconce, "pulled", false);
    cr_assert_eq(set_attr2, SUCCESS, "add_multiple_act_cond: failed to set attribute");


    int add_action_check = add_action(sconce, "pull", "door opened!", "door did not open!");
    cr_assert_eq(add_action_check, SUCCESS, "add_multiple_act_cond: failed to retrieve action");

    //checking
    game_action_t *open_action = get_action(sconce, "pull");

    attribute_t* attr_to_affect1 = get_attribute(door, "locked");
    cr_assert_not_null(attr_to_affect1, "add_multiple_act_cond: could not retrieve the attribute to check from item");

    attribute_value_t effect_value1;
    effect_value1.bool_val = false;

    attribute_t* attr_to_affect2 = get_attribute(sconce, "pulled");
    cr_assert_not_null(attr_to_affect2, "add_multiple_act_cond: could not retrieve the attribute to check from item");

    attribute_value_t effect_value2;
    effect_value2.bool_val = true;

    int add_effect_check1 = add_action_effect(open_action, sconce, door, attr_to_affect1, effect_value1);

    cr_assert_eq(add_effect_check1, SUCCESS, "add_multiple_act_cond: adding the condition failed");

    int add_effect_check2 = add_action_effect(open_action, sconce, sconce , attr_to_affect2, effect_value2);

    cr_assert_eq(add_effect_check2, SUCCESS, "add_multiple_act_cond: adding the condition failed");
}

Test(game_action_effects, new) {

    item_t *test_item = item_new("door", "door for testing",
    "door for testing effect_new()");

    attribute_t *test_attr = malloc(sizeof(attribute_t));
    test_attr->attribute_key = (char*)malloc(100);
    test_attr->attribute_key = "unlock";
    test_attr->attribute_tag = INTEGER;
    test_attr->attribute_value.int_val = 0;

    attribute_value_t value;
    value.int_val = 1;

    game_action_effect_t *test_effect = effect_new(test_item, test_attr,
        value);

    cr_assert_not_null(test_effect, "effect_new() test failed to create effect!");
    cr_assert_eq(test_effect->new_value.int_val, 1,
        "effect_new() test failed!");
}

Test(game_action_effects, do) {

    item_t *test_item = item_new("door", "door for testing",
    "door for testing do_effect()");
    attribute_t *test_attr = malloc(sizeof(attribute_t));
    test_attr->attribute_key = (char*)malloc(100);
    test_attr->attribute_key = "open";
    test_attr->attribute_tag = INTEGER;
    test_attr->attribute_value.int_val = 0;

    attribute_value_t value;
    value.int_val = 1;

    game_action_effect_t *test_effect = effect_new(test_item, test_attr, value);

    int check = do_effect(test_effect);

    cr_assert_eq(check, SUCCESS, "do_effect() test failed!");
}

Test(game_action_effects, do_all) {

    // create item
    item_t *door = item_new("door", "door for testing", "door for testing do_all_effects()");

    item_t *handle = item_new("handle", "handle for testing", "handle for testing do_all_effects");

    item_t *lock = item_new("lock", "lock for testing", "lock for testing");

    set_bool_attr(door, "opened", false);
    attribute_t *opened = get_attribute(door, "opened");
    set_bool_attr(handle, "turned", true);
    attribute_t *turned = get_attribute(handle, "turned");
    set_bool_attr(lock, "unlocked", true);
    attribute_t *unlocked = get_attribute(lock, "unlocked");

    // add action "open"
    int added_action = add_action(door, "open", "success", "failure");
    game_action_t *open = get_action(door, "open");

    // add conditions
    attribute_value_t value;
    value.bool_val = true;
    add_action_condition(door, open, handle, turned, value);
    add_action_condition(door, open, lock, unlocked, value);

    // do all effects
    int check = do_all_effects(door, "open");
    cr_assert_eq(check, SUCCESS, "do_all_effects test failed!");

    bool check_opened = get_bool_attr(door, "opened");
    bool check_turned = get_bool_attr(handle, "turned");
    bool check_unlocked = get_bool_attr(lock, "unlocked");

    cr_assert_eq(check_turned, true, "do_all_effects test failed!");
    cr_assert_eq(check_unlocked, true, "do_all_effects test failed!");


}
