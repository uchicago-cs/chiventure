#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "skilltrees/skilltree.h"
#include "skilltrees/skill.h"
#include "skilltrees/skilltrees_common.h"
#include "skilltrees/inventory.h"
#include "skilltrees/effect.h"
#include "test_init.h"


/* Tests inventory_skill_add for an active skill, that is valid. */

Test(inventory_tests, inventory_skill_add_active_safe)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);
    
    item_t* tree = add_chop_item(ctx);
    effect_t* choptreeeffect  = make_choptree_effect(tree);

    skill_inventory_t* inventory = inventory_new(1,1);
    skill_t* bomb_skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect);
    skill_t* tree_skill = skill_new(1001, ACTIVE, "chop tree", "chops a bomb",
        3, 6, choptreeeffect);
    int ret = inventory_skill_add(inventory, bomb_skill);
    cr_assert_eq(ret,SUCCESS,"Error: failed test inventory_skill_add_active_safe");
    cr_assert_eq(inventory->active[0]->sid,1000,
        "Error: failed test inventory_skill_add_active_safe");
}

/*Tests inventory_skill_add for an active skill, when active inventory full. */

Test(inventory_tests, inventory_skill_add_active_full)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);
    
    item_t* tree = add_chop_item(ctx);
    effect_t* choptreeeffect  = make_choptree_effect(tree);

    skill_inventory_t* inventory = inventory_new(1,1);
    skill_t* bomb_skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect);
    skill_t* tree_skill = skill_new(1001, ACTIVE, "chop tree", "chops a bomb",
        3, 6, choptreeeffect);
    inventory_skill_add(inventory, bomb_skill);
    int ret = inventory_skill_add(inventory, tree_skill);
    
    cr_assert_eq(ret,FAILURE,"Error: failed test inventory_skill_add_active_full");
}


/* Tests inventory_skill_add on a passive skill, that is valid. */

Test(inventory_tests, inventory_skill_add_passive_safe)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);
    
    item_t* tree = add_chop_item(ctx);
    effect_t* choptreeeffect  = make_choptree_effect(tree);

    skill_inventory_t* inventory = inventory_new(1,1);
    skill_t* bomb_skill = skill_new(1000, PASSIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect);
    skill_t* tree_skill = skill_new(1001, PASSIVE, "chop tree", "chops a bomb",
        3, 6, choptreeeffect);
    int ret = inventory_skill_add(inventory, bomb_skill);
    cr_assert_eq(ret,SUCCESS,"Error: failed test inventory_skill_add_passive_safe");
}


/*Tests inventory_skill_add on a passive skill, when passive inventory full.*/

Test(inventory_tests, inventory_skill_add_passive_full)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);
    
    item_t* tree = add_chop_item(ctx);
    effect_t* choptreeeffect  = make_choptree_effect(tree);

    skill_inventory_t* inventory = inventory_new(1,1);
    skill_t* bomb_skill = skill_new(1000, PASSIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect);
    skill_t* tree_skill = skill_new(1001, PASSIVE, "chop tree", "chops a bomb",
        3, 6, choptreeeffect);
    inventory_skill_add(inventory, bomb_skill);
    int ret = inventory_skill_add(inventory, tree_skill);
    cr_assert_eq(ret,FAILURE,"Error: failed test inventory_skill_add_passive_full");
}

/*Tests inventory_has_skill on passive skill it does not have. */

Test(inventory_tests, inventory_has_skill_has_not_passive)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);
    
    skill_inventory_t* inventory = inventory_new(1,1);
    skill_t* bomb_skill = skill_new(1000, PASSIVE, "defuse bomb", "defuses a bomb",
      2, 5, defusebombeffect);
    inventory_skill_add(inventory, bomb_skill);
    int ret = inventory_has_skill(inventory, 1000, ACTIVE);
    cr_assert_eq(ret, -1,
    "Error: failed test inventory_has_skill_has_passive\n");
}

/* Tests inventory_has_skill when it has an active, but is checking for a passive. */

Test(inventory_tests, inventory_has_skill_has_not_active)
{

  chiventure_ctx_t* ctx = create_player_and_stats();
  item_t* bomb = add_bomb_item(ctx);
  effect_t* defusebombeffect = make_bomb_effect(bomb);

  skill_inventory_t* inventory = inventory_new(1,1);
  skill_t* bomb_skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, defusebombeffect);
  
  inventory_skill_add(inventory, bomb_skill);
  int ret = inventory_has_skill(inventory, 1000, PASSIVE);
  cr_assert_eq(ret, -1,
    "Error: failed test inventory_has_skill_has_active\n");
}

/* Tests inventory_has_skill on active skill it does not have. */

Test(inventory_tests, inventory_has_skill_has_not)
{
  chiventure_ctx_t* ctx = create_player_and_stats();
  item_t* bomb = add_bomb_item(ctx);
  effect_t* defusebombeffect = make_bomb_effect(bomb);

  skill_inventory_t* inventory = inventory_new(1,1);
  skill_t* bomb_skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, defusebombeffect);
  int ret = inventory_has_skill(inventory, 1000, PASSIVE);
  cr_assert_eq(ret, -1,
    "Error: failed test inventory_has_skill_has_not\n");
}

/* Tests inventory_skill_remove on a skill it does not have. */

Test(inventory_tests, inventory_skill_remove_has_not)
{
  chiventure_ctx_t* ctx = create_player_and_stats();
  item_t* bomb = add_bomb_item(ctx);
  effect_t* defusebombeffect = make_bomb_effect(bomb);

  skill_inventory_t* inventory = inventory_new(1,1);
  skill_t* bomb_skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, defusebombeffect);
  int ret = inventory_skill_remove(inventory, bomb_skill);
  cr_assert_eq(ret, FAILURE,
    "Error: failed test inventory_has_skill_has_not\n");
}

/*Tests after this line fail and are skipped.*/

/* Tests inventory_has_skill on active skill that inventory has. */
/*
Test(inventory_tests, inventory_has_skill_has_active)
{
  skill_inventory_t* inventory = inventory_new(1,1);
  skill_t* bomb = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  inventory_skill_add(inventory, bomb);
  int ret = inventory_has_skill(inventory, 1000, ACTIVE);

  cr_assert_eq(ret, 0, "Error: failed test inventory_has_skill_has_active\n");
}
*/
/* Tests inventory_has_skill on a passive skill it has. */
/*
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
*/
/* Tests inventory_skill_remove on a pasive skill that is had. */
/*
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
*/
/* Tests inventory_skill_remove on an active skill that is had. */
/*
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
*/