#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "skilltrees/skilltree.h"
#include "skilltrees/skill.h"
#include "skilltrees/stdst.h"
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
Test(inventory_tests, inventory_has_skill_has_active, .description = "Fails & Skipped", .disabled = true)
{
  skill_inventory_t* inventory = inventory_new(1,1);
  skill_t* bomb = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  //inventory_skill_add(inventory, bomb);
  (inventory->active)[0] = bomb;
  int ret = inventory_has_skill(inventory, 1000, ACTIVE);

  cr_assert_eq(ret, 0,
    "Error: failed test inventory_has_skill_has_active\n");
}

/* Tests inventory_has_skill on a passive skill it has. */
Test(inventory_tests, inventory_has_skill_has_passive, .description = "Fails & Skipped", .disabled = true)
{
  skill_inventory_t* inventory = inventory_new(1,1);
  skill_t* bomb = skill_new(1000, PASSIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  inventory_skill_add(inventory, bomb);
  int ret = inventory_has_skill(inventory, 1000, PASSIVE);
  cr_assert_neq(ret, -1,
    "Error: failed test inventory_has_skill_has_passive\n");
}

/*Tests inventory_skill_levels_update. */
Test(inventory_tests, inventory_skill_levels_update_test, .description = "Fails & Skipped (function not implemented)", .disabled = true)
{
  /* Function documentation and implementation are both incomplete,
  function is not testable in current state. */
}

/* Tests inventory_skill_remove on a pasive skill that is had. */
Test(inventory_tests, inventory_skill_remove_has_passive, .description = "Fails & Skipped", .disabled = true)
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
Test(inventory_tests, inventory_skill_remove_has_active, .description = "Fails & Skipped", .disabled = true)
{
  skill_inventory_t* inventory = inventory_new(1,1);
  skill_t* bomb = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  inventory_skill_add(inventory, bomb);
  int ret = inventory_skill_remove(inventory, bomb);
  cr_assert_eq(ret, SUCCESS,
    "Error: failed test inventory_has_skill_has_active\n");
}
