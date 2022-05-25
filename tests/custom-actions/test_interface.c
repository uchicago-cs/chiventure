#include <criterion/criterion.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "interface.h"

Test(custom_action_t, add_actions)
{
    // creates a single custom action

    block_t *block1 = malloc(sizeof(block_t));
    block_type_t block_type1 = CONDITIONAL;
    AST_block_t *head1 = AST_block_new(block1, block_type1);
    char *action_name1 = "act_PUSH";
    char *context1 = "chair";
    char *item1 = "obj_SPINACH";
    char *type1 = "druid";
    custom_action_t *new_action1 = custom_action_new(action_name1, context1,
                                                     item1, type1, head1);

    cr_assert_not_null(new_action1, "custom_action_new failed");

    // adds first custom action to the game and checks for success

    int rc = add_custom_action_to_game(new_action1);
    cr_assert_eq(rc, SUCCESS, "add_custom_action_to_game failed");

    // creates another custom action

    block_t *block2 = malloc(sizeof(block_t));
    block_type_t block_type2 = CONDITIONAL;
    AST_block_t *head2 = AST_block_new(block2, block_type2);
    char *action_name2 = "act_PUSH";
    char *context2 = "chair";
    char *item2 = "obj_SPINACH";
    char *type2 = "warlock";
    custom_action_t *new_action2 = custom_action_new(action_name2, context2,
                                                     item2, type2, head2);

    cr_assert_not_null(new_action2, "custom_action_new failed");

    // adds second custom action to the game and checks for success

    rc = add_custom_action_to_game(new_action2);
    cr_assert_eq(rc, SUCCESS, "add_custom_action_to_game failed");
}

Test(custom_action_t, find_existing)
{
    // creates a single custom action

    block_t *block1 = malloc(sizeof(block_t));
    block_type_t block_type1 = ACTION;

    AST_block_t *head1 = AST_block_new(block1, block_type1);
    char *action_name1 = "act_PUSH";
    char *context1 = "chair";
    char *item1 = "obj_SPINACH";
    char *type1 = "mage";

    custom_action_t *new_action1 = custom_action_new(action_name1, context1,
                                                     item1, type1, head1);

    cr_assert_not_null(new_action1, "custom_action_new failed");

    // adds custom action to the game

    int rc = add_custom_action_to_game(new_action1);
    cr_assert_eq(rc, SUCCESS, "add_custom_action_to_game failed");

    // searches for custom action

    custom_action_t *found = search_for_custom_action(action_name1);

    cr_assert_not_null(found, "search_for_custom_action did not find a custom "
                              "action it was expected to find");

    cr_assert_eq(found->action_name, action_name1, "search_for_custom_action "
                                                   "returned the wrong result");
}

Test(custom_action_t, find_empty_list)
{
    // tries to find an action in an empty list

    char *action_name1 = "act_PUSH";

    custom_action_t *found = search_for_custom_action(action_name1);

    cr_assert_null(found, "search_for_custom_action returned the wrong "
                          "result");
}

Test(custom_action_t, find_multiple)
{
    // creates multiple different custom actions

    block_t *block1 = malloc(sizeof(block_t));
    block_type_t block_type1 = ACTION;
    AST_block_t *head1 = AST_block_new(block1, block_type1);
    char *action_name1 = "act_PUSH";
    char *context1 = "chair";
    char *item1 = "obj_SPINACH";
    char *type1 = "wizard";
    custom_action_t *new_action1 = custom_action_new(action_name1, context1,
                                                     item1, type1, head1);
    cr_assert_not_null(new_action1, "custom_action_new failed");

    block_t *block2 = malloc(sizeof(block_t));
    block_type_t block_type2 = CONDITIONAL;
    AST_block_t *head2 = AST_block_new(block2, block_type2);
    char *action_name2 = "act_THROW";
    char *context2 = "chair";
    char *item2 = "obj_SPADE";
    char *type2 = "druid";
    custom_action_t *new_action2 = custom_action_new(action_name2, context2,
                                                     item2, type2, head2);
    cr_assert_not_null(new_action2, "custom_action_new failed");

    block_t *block3 = malloc(sizeof(block_t));
    block_type_t block_type3 = BRANCH;
    AST_block_t *head3 = AST_block_new(block3, block_type3);
    char *action_name3 = "act_PLANT";
    char *context3 = "soil";
    char *item3 = "obj_ORANGE_SEED";
    char *type3 = "ranger";
    custom_action_t *new_action3 = custom_action_new(action_name3, context3,
                                                     item3, type3, head3);
    cr_assert_not_null(new_action3, "custom_action_new failed");

    // adds all 3 custom actions to the game

    int rc = add_custom_action_to_game(new_action1);
    cr_assert_eq(rc, SUCCESS, "add_custom_action_to_game failed");

    rc = add_custom_action_to_game(new_action2);
    cr_assert_eq(rc, SUCCESS, "add_custom_action_to_game failed");

    rc = add_custom_action_to_game(new_action3);
    cr_assert_eq(rc, SUCCESS, "add_custom_action_to_game failed");

    // tries finding the 3 custom actions, one by one
    // (in a different order than they were added to the game)

    custom_action_t *found = search_for_custom_action(action_name1);
    cr_assert_not_null(found, "search_for_custom_action did not find a custom"
                              " action it was expcted to find");
    cr_assert_eq(found->action_name, action_name1, "search_for_custom_action"
                                                   " returned the wrong result");

    found = search_for_custom_action(action_name3);
    cr_assert_not_null(found, "search_for_custom_action did not find a custom"
                              " action it was expcted to find");
    cr_assert_eq(found->action_name, action_name3, "search_for_custom_action"
                                                   " returned the wrong result");

    found = search_for_custom_action(action_name2);
    cr_assert_not_null(found, "search_for_custom_action did not find a custom"
                              " action it was expcted to find");
    cr_assert_eq(found->action_name, action_name2, "search_for_custom_action"
                                                   " returned the wrong result");

    // now tries to find an action that is NOT in the list

    char *action_name4 = "act_EAT";
    found = search_for_custom_action(action_name4);
    cr_assert_null(found, "search_for_custom_action returned the wrong "
                          "result");
}