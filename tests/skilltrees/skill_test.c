#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "skilltrees/skilltree.h"
#include "skilltrees/skill.h"
#include "skilltrees/skilltrees_common.h"
#include "test_init.h"


/* Some of the tests are currently commented out because they need to be modified according to
the modified parameters of the respective functions that they're testing. */

/* Test skill_new. */
/*
Test(skill_tests, skill_new_test)
{
    skill_t* skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, effect_defuse_bomb);
    cr_assert_eq(skill->sid,1000,
        "Error: failed test skill_new_test on skill->sid\n");
    cr_assert_eq(skill->type,ACTIVE,
        "Error: failed test skill_new_test on skill->type\n");
    cr_assert_str_eq(skill->name, "defuse bomb",
        "Error: failed test skill_new_test on skill->name\n");
    cr_assert_str_eq(skill->desc, "defuses a bomb",
        "Error: failed test skill_new_test on skill->desc\n");
    cr_assert_eq(skill->level, 1,
        "Error: failed test skill_new_test on skill->level\n");
    cr_assert_eq(skill->xp, 0,
        "Error: failed test skill_new_test on skill->xp\n");
    cr_assert_eq(skill->max_level, 2,
        "Error: failed test skill_new_test on skill->max_level\n");
    cr_assert_eq(skill->min_xp, 5,
        "Error: failed test skill_new_test on skill->min_xp\n");
    cr_assert_str_eq((skill->effect)("haha"),"Bomb defused!",
        "Error: failed test skill_new_test on skill->effect\n");
}

*/
/* Test skill_init. */
/*
Test(skill_tests, skill_init_test)
{
  skill_t* skill = malloc(sizeof(skill_t));
  skill_init(skill, 1000, ACTIVE, "defuse bomb", "defuses a bomb",
      1, 0, 2, 5, effect_defuse_bomb);
  cr_assert_eq(skill->sid,1000,
      "Error: failed test skill_new_test on skill->sid\n");
  cr_assert_eq(skill->type,ACTIVE,
      "Error: failed test skill_new_test on skill->type\n");
  cr_assert_str_eq(skill->name, "defuse bomb",
      "Error: failed test skill_new_test on skill->name\n");
  cr_assert_str_eq(skill->desc, "defuses a bomb",
      "Error: failed test skill_new_test on skill->desc\n");
  cr_assert_eq(skill->level, 1,
      "Error: failed test skill_new_test on skill->level\n");
  cr_assert_eq(skill->xp, 0,
      "Error: failed test skill_new_test on skill->xp\n");
  cr_assert_eq(skill->max_level, 2,
      "Error: failed test skill_new_test on skill->max_level\n");
  cr_assert_eq(skill->min_xp, 5,
      "Error: failed test skill_new_test on skill->min_xp\n");
  cr_assert_str_eq((skill->effect)("haha"),"Bomb defused!",
      "Error: failed test skill_new_test on skill->effect\n");
}
*/
/* Tests skill_free. */
/*
Test(skill_tests, skill_free_test)
{
  skill_t* skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  int ret = skill_free(skill);
  cr_assert_eq(ret, 0, "Error: failed test skill_free_test\n");
}
*/
/* Tests skill_execute. */
/*
Test(skill_tests, skill_execute_test)
{
  skill_t* skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  cr_assert_str_eq(skill_execute(skill, "haha"),"Bomb defused!",
      "Error: failed test skill_new_test on skill->effect\n");
}
*/

/* Main function to test skill_level_up. */
void check_level_up(skill_t* skill, int expected) 
{
  cr_assert_eq(skill_level_up(skill), expected, "Error: failed test skill_level_up_test");
}

/* Tests skill_level_up when return value is 0 */

Test(skill_tests, skill_level_up_0)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_item(ctx);
    attribute_value_t mod;
    mod.bool_val = false;
    enum attribute_tag att_tag = BOOLE;

    item_attr_effect_t* disarm_bomb = define_item_attr_effect(bomb, "ARMED", att_tag, mod);
    effect_t* effect_defuse_bomb = make_item_attr_effect(disarm_bomb);

    skill_t* skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
    2, 5, effect_defuse_bomb);
    check_level_up(skill, 0);
}

/* Tests skill_level_up when return value is 1 */

Test(skill_tests, skill_level_up_1)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_item(ctx);
    attribute_value_t mod;
    mod.bool_val = false;
    enum attribute_tag att_tag = BOOLE;

    item_attr_effect_t* disarm_bomb = define_item_attr_effect(bomb, "ARMED", att_tag, mod);
    effect_t* effect_defuse_bomb = make_item_attr_effect(disarm_bomb);

    skill_t* skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
    1, 5, effect_defuse_bomb);
    check_level_up(skill, 1);
}

/* Tests skill_level_up when return value is -1 */

Test(skill_tests, skill_level_up_minus_1)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_item(ctx);
    attribute_value_t mod;
    mod.bool_val = false;
    enum attribute_tag att_tag = BOOLE;

    item_attr_effect_t* disarm_bomb = define_item_attr_effect(bomb, "ARMED", att_tag, mod);
    effect_t* effect_defuse_bomb = make_item_attr_effect(disarm_bomb);

    skill_t* skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
    0, 5, effect_defuse_bomb);
    check_level_up(skill, -1);
}

