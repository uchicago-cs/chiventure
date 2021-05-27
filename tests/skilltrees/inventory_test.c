#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "skilltrees/skilltree.h"
#include "skilltrees/skill.h"
#include "skilltrees/skilltrees_common.h"
#include "skilltrees/inventory.h"
#include "effect_t.h"

/* Tests inventory_new. */
Test(inventory_tests, inventory_new_test)
{
    skill_inventory_t* inventory = inventory_new(3,4);
    cr_assert_eq(inventory->num_active, 0,
        "Error: failed test inventory_new_test on inventory->num_active\n");
    cr_assert_eq(inventory->max_active, 3,
        "Error: failed test inventory_new_test on inventory->max_active\n");
    cr_assert_eq(inventory->num_passive, 0,
        "Error: failed test inventory_new_test on inventory->num_passive\n");
    cr_assert_eq(inventory->max_passive, 4,
        "Error: failed test inventory_new_test on inventory->max_passive\n");
}

/* Tests inventory_free. */
Test(inventory_tests, inventory_free_test)
{
    skill_inventory_t* inventory = inventory_new(3,4);
    int ret = inventory_free(inventory);
    cr_assert_eq(ret, SUCCESS, "Error: failed test inventory_free\n");
}

Test(inventory_test, deep_copy_inventory_no_skills)
{
    int ret_val;
    skill_inventory_t* inventory = inventory_new(3,4);
    cr_assert_not_null(inventory, "inventory_new() failed to create inventory struct");

    skill_inventory_t* copy = copy_inventory(inventory);
    cr_assert_not_null(copy, "copy_inventory() failed to create copy");

    /* Check that fields where set correctly */
    cr_assert_eq(copy->num_active, inventory->num_active, 
                 "number of active skills differ between copy and original");
    cr_assert_eq(copy->num_passive, inventory->num_passive, 
                 "number of passive skills differ between copy and original");
    cr_assert_eq(copy->max_active, inventory->max_active,
                 "maximum number of active skills differ between copy and original");
    cr_assert_eq(copy->max_passive, inventory->max_passive,
                 "maximum number of passive skills differ between copy and original");

    /* Check that array pointers for active & passive skills are different */
    if (copy->active == inventory->active)
        cr_assert_fail("copy_inventory results in active array pointer still being shared between original and copy");
    if (copy->passive == inventory->passive)
        cr_assert_fail("copy_inventory results in passive array pointer still being shared between original and copy");

    /* Free the original inventory */
    ret_val = inventory_free(inventory);
    cr_assert_eq(ret_val, SUCCESS, "inventory_free failed to free original inventory");

    /* Free the copied inventory */
    ret_val = inventory_free(copy);
    cr_assert_eq(ret_val, SUCCESS, "inventory_free failed to free deep copy inventory");
}

Test(inventory_test, deep_copy_inventory_with_skills)
{
    int ret_val;
    skill_inventory_t* inventory = inventory_new(3,4);
    cr_assert_not_null(inventory, "inventory_new() failed to create inventory struct");

    /* Add two skills for both Passive and Active field */
    skill_t* activ1 = (skill_t*)malloc(sizeof(skill_t));
    skill_t* activ2 = (skill_t*)malloc(sizeof(skill_t));
    skill_t* pass1 = (skill_t*)malloc(sizeof(skill_t));
    skill_t* pass2 = (skill_t*)malloc(sizeof(skill_t));

    activ1->type = ACTIVE;
    activ2->type = ACTIVE;
    pass1->type = PASSIVE;
    pass2->type = PASSIVE;

    ret_val = inventory_skill_add(inventory, activ1);
    cr_assert_eq(ret_val, SUCCESS, "inventory_skill_add() failed to add activ1");

    ret_val = inventory_skill_add(inventory, activ2);
    cr_assert_eq(ret_val, SUCCESS, "inventory_skill_add() failed to add activ2");

    ret_val = inventory_skill_add(inventory, pass1);
    cr_assert_eq(ret_val, SUCCESS, "inventory_skill_add() failed to add pass1");

    ret_val = inventory_skill_add(inventory, pass2);
    cr_assert_eq(ret_val, SUCCESS, "inventory_skill_add() failed to add pass2");

    /* Create Deep memory copy of inventory WITH skills */
    skill_inventory_t* copy = copy_inventory(inventory);
    cr_assert_not_null(copy, "copy_inventory() failed to create copy");

    /* Check that fields where set correctly */
    cr_assert_eq(copy->num_active, inventory->num_active, 
                 "number of active skills differ between copy and original");
    cr_assert_eq(copy->num_passive, inventory->num_passive, 
                 "number of passive skills differ between copy and original");
    cr_assert_eq(copy->max_active, inventory->max_active,
                 "maximum number of active skills differ between copy and original");
    cr_assert_eq(copy->max_passive, inventory->max_passive,
                 "maximum number of passive skills differ between copy and original");

    /* Check that the skills in the copy and skills in original inventory are
     * found in the same spots of the array */
    if (copy->active[0] != inventory->active[0])
        cr_assert_fail("First active stat in copy has different stat_t*");
    if (copy->active[1] != inventory->active[1])
        cr_assert_fail("Second active stat in copy has different stat_t*");
    if (copy->passive[0] != inventory->passive[0])
        cr_assert_fail("First passive stat in copy has different stat_t*");
    if (copy->passive[1] != inventory->passive[1])
        cr_assert_fail("Second passive stat in copy has different stat_t*");

    /* Free the original inventory */
    ret_val = inventory_free(inventory);
    cr_assert_eq(ret_val, SUCCESS, "inventory_free failed to free original inventory");

    /* Free the copied inventory */
    ret_val = inventory_free(copy);
    cr_assert_eq(ret_val, SUCCESS, "inventory_free failed to free deep copy inventory");

    free(activ1);
    free(activ2);
    free(pass1);
    free(pass2);
}

/* Tests inventory_skill_add for an active skill, that is valid. */
Test(inventory_tests, inventory_skill_add_active_safe)
{
    skill_inventory_t* inventory = inventory_new(1,1);
    skill_t* bomb = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, effect_defuse_bomb);
    skill_t* tree = skill_new(1001, ACTIVE, "chop tree", "chops a bomb",
        3, 6, effect_chop_tree);
    int ret = inventory_skill_add(inventory, bomb);
    cr_assert_eq(ret,SUCCESS,"Error: failed test inventory_skill_add_active_safe");
    cr_assert_eq(inventory->active[0]->sid,1000,
        "Error: failed test inventory_skill_add_active_safe");
}

/*Tests inventory_skill_add for an active skill, when active inventory full. */
Test(inventory_tests, inventory_skill_add_active_full)
{
    skill_inventory_t* inventory = inventory_new(1,1);
    skill_t* bomb = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, effect_defuse_bomb);
    skill_t* tree = skill_new(1001, ACTIVE, "chop tree", "chops a bomb",
        3, 6, effect_chop_tree);
    inventory_skill_add(inventory, bomb);
    int ret = inventory_skill_add(inventory, tree);
    cr_assert_eq(ret,FAILURE,"Error: failed test inventory_skill_add_active_full");
}

/* Tests inventory_skill_add on a passive skill, that is valid. */
Test(inventory_tests, inventory_skill_add_passive_safe)
{
    skill_inventory_t* inventory = inventory_new(1,1);
    skill_t* bomb = skill_new(1000, PASSIVE, "defuse bomb", "defuses a bomb",
        2, 5, effect_defuse_bomb);
    skill_t* tree = skill_new(1001, PASSIVE, "chop tree", "chops a bomb",
        3, 6, effect_chop_tree);
    int ret = inventory_skill_add(inventory, bomb);
    cr_assert_eq(ret,SUCCESS,"Error: failed test inventory_skill_add_passive_safe");
}

/*Tests inventory_skill_add on a passive skill, when passive inventory full.*/
Test(inventory_tests, inventory_skill_add_passive_full)
{
    skill_inventory_t* inventory = inventory_new(1,1);
    skill_t* bomb = skill_new(1000, PASSIVE, "defuse bomb", "defuses a bomb",
        2, 5, effect_defuse_bomb);
    skill_t* tree = skill_new(1001, PASSIVE, "chop tree", "chops a bomb",
        3, 6, effect_chop_tree);
    inventory_skill_add(inventory, bomb);
    int ret = inventory_skill_add(inventory, tree);
    cr_assert_eq(ret,FAILURE,"Error: failed test inventory_skill_add_passive_full");
}

/* Tests inventory_skill_add for an invalid skill type. */
Test(inventory_tests, inventory_skill_add_invalid)
{
    skill_inventory_t* inventory = inventory_new(1,1);
    skill_t* peace = skill_new(1001, 32, "inner peace", "maintains inner peace",
        4, 7, effect_inner_peace);
    int ret = inventory_skill_add(inventory, peace);
    cr_assert_eq(ret,FAILURE,"Error: failed test inventory_skill_add_invalid");
}

/*Tests inventory_has_skill on passive skill it does not have. */
Test(inventory_tests, inventory_has_skill_has_not_passive)
{
  skill_inventory_t* inventory = inventory_new(1,1);
  skill_t* bomb = skill_new(1000, PASSIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  inventory_skill_add(inventory, bomb);
  int ret = inventory_has_skill(inventory, 1000, ACTIVE);
  cr_assert_eq(ret, -1,
    "Error: failed test inventory_has_skill_has_passive\n");
}

/* Tests inventory_has_skill when it has an active, but is checking for a passive. */
Test(inventory_tests, inventory_has_skill_has_not_active)
{
  skill_inventory_t* inventory = inventory_new(1,1);
  skill_t* bomb = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  inventory_skill_add(inventory, bomb);
  int ret = inventory_has_skill(inventory, 1000, PASSIVE);
  cr_assert_eq(ret, -1,
    "Error: failed test inventory_has_skill_has_active\n");
}

/* Tests inventory_has_skill on active skill it does not have. */
Test(inventory_tests, inventory_has_skill_has_not)
{
  skill_inventory_t* inventory = inventory_new(1,1);
  skill_t* bomb = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  int ret = inventory_has_skill(inventory, 1000, PASSIVE);
  cr_assert_eq(ret, -1,
    "Error: failed test inventory_has_skill_has_not\n");
}

/* Tests inventory_skill_remove on a skill it does not have. */
Test(inventory_tests, inventory_skill_remove_has_not)
{
  skill_inventory_t* inventory = inventory_new(1,1);
  skill_t* bomb = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  int ret = inventory_skill_remove(inventory, bomb);
  cr_assert_eq(ret, FAILURE,
    "Error: failed test inventory_has_skill_has_not\n");
}

/*Tests after this line fail and are skipped.*/

/* Tests inventory_has_skill on active skill that inventory has. */
Test(inventory_tests, inventory_has_skill_has_active)
{
  skill_inventory_t* inventory = inventory_new(1,1);
  skill_t* bomb = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  inventory_skill_add(inventory, bomb);
  int ret = inventory_has_skill(inventory, 1000, ACTIVE);

  cr_assert_eq(ret, 0, "Error: failed test inventory_has_skill_has_active\n");
}

/* Tests inventory_has_skill on a passive skill it has. */
Test(inventory_tests, inventory_has_skill_has_passive)
{
  skill_inventory_t* inventory = inventory_new(1,1);
  skill_t* bomb = skill_new(1000, PASSIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  inventory_skill_add(inventory, bomb);
  int ret = inventory_has_skill(inventory, 1000, PASSIVE);
  cr_assert_eq(ret, 0,
    "Error: failed test inventory_has_skill_has_passive\n");
}

/* Tests inventory_skill_remove on a pasive skill that is had. */
Test(inventory_tests, inventory_skill_remove_has_passive)
{
  skill_inventory_t* inventory = inventory_new(1,1);
  skill_t* bomb = skill_new(1000, PASSIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  inventory_skill_add(inventory, bomb);
  int ret = inventory_skill_remove(inventory, bomb);
  cr_assert_eq(ret, SUCCESS,
    "Error: failed test inventory_has_skill_has_passive\n");
}

/* Tests inventory_skill_remove on an active skill that is had. */
Test(inventory_tests, inventory_skill_remove_has_active)
{
  skill_inventory_t* inventory = inventory_new(1,1);
  skill_t* bomb = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  inventory_skill_add(inventory, bomb);
  int ret = inventory_skill_remove(inventory, bomb);
  cr_assert_eq(ret, SUCCESS,
    "Error: failed test inventory_has_skill_has_active\n");
}
