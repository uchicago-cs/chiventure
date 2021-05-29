#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "skilltrees/skilltree.h"
#include "skilltrees/skill.h"
#include "skilltrees/skilltrees_common.h"
#include "skilltrees/inventory.h"
#include "skilltrees/effect.h"
#include "skilltrees/sampleeffects.c"

/* Rewrote the test with new effect implementation */


/* Test skill_new. */
Test(skill_tests, skill_new_test)
{
    skill_t* skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect);
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

/* Test skill_init. */

Test(skill_tests, skill_init_test)
{
  skill_t* skill = malloc(sizeof(skill_t));
  skill_init(skill, 1000, ACTIVE, "defuse bomb", "defuses a bomb",
      1, 0, 2, 5, defusebombeffect);
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
  cr_assert_eq((skill->skill_effect->effecttype, ITEM_ATTRIBUTE_MOD,
      "Error: failed test skill_new_test on skill->effect\n");
}

/* Tests skill_free. */

Test(skill_tests, skill_free_test)
{
  skill_t* skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, defusebombeffect);
  int ret = skill_free(skill);
  cr_assert_eq(ret, 0, "Error: failed test skill_free_test\n");
}
*/
/* Tests skill_execute. */

Test(skill_tests, skill_execute_test)
{
  skill_t* skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, defusebombeffect);
  cr_assert_eq(skill_execute(skill, ctx), 0,
      "Error: failed test skill_new_test on skill->effect\n");
}
*/