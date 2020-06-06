#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "skilltrees/skilltree.h"
#include "skilltrees/skill.h"
#include "skilltrees/stdst.h"
#include "skilltrees/inventory.h"
#include "effect_t.h"

/* Tests skill_node_new. */
Test(skilltree_tests, skill_node_new_test)
{
    skill_t* skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, effect_defuse_bomb);
    skill_node_t* node = skill_node_new(skill, 4, 76);
    cr_assert_eq(node->prereqs,NULL,
        "Error: failed test skill_node_new on node->prereqs\n");
    cr_assert_eq(node->num_prereq_skills, 4,
        "Error: failed test skill_node_new on node->num_prereq_skills\n");
    cr_assert_eq(node->size, 76,
        "Error: failed test skill_node_new on node->size\n");
    cr_assert_eq(node->skill->sid,1000,
        "Error: failed test skill_node_new_test on node->skill->sid\n");
    cr_assert_eq(node->skill->type,ACTIVE,
        "Error: failed test skill_node_new_test on node->skill->type\n");
    cr_assert_str_eq(node->skill->name, "defuse bomb",
        "Error: failed test skill_node_new_test on node->skill->name\n");
    cr_assert_str_eq(node->skill->desc, "defuses a bomb",
        "Error: failed test skill_node_new_test on node->skill->desc\n");
    cr_assert_eq(node->skill->level, 1,
        "Error: failed test skill_node_new_test on node->skill->level\n");
    cr_assert_eq(node->skill->xp, 0,
        "Error: failed test skill_node_new_test on node->skill->xp\n");
    cr_assert_eq(node->skill->max_level, 2,
        "Error: failed test skill_node_new_test on node->skill->max_level\n");
    cr_assert_eq(node->skill->min_xp, 5,
        "Error: failed test skill_node_new_test on node->skill->min_xp\n");
    cr_assert_str_eq((node->skill->effect)("haha"),"Bomb defused!",
        "Error: failed test skill_node_new_test on node->skill->effect\n");}

/* Tests skill_node_free. */
Test(skilltree_tests, skill_node_free_test)
{
    skill_t* skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, effect_defuse_bomb);
    skill_node_t* node = skill_node_new(skill, 4, 76);
    int ret = skill_node_free(node);
    cr_assert_eq(ret, 0, "Error: failed test skill_node_free_test\n");
}


/* Tests skill_tree_new. */
Test(skilltree_tests, skill_tree_new_test)
{
    skill_tree_t* tree = skill_tree_new(1002, "this tree", 3);
    cr_assert_eq(tree->tid, 1002,
      "Error: failed test skill_tree_new_test on tree->tid\n");
    cr_assert_str_eq(tree->name, "this tree",
      "Error: failed test skill_tree_new_test on tree->name\n");
    cr_assert_eq(tree->num_nodes, 3,
      "Error: failed test skill_tree_new_test on tree->num_nodes\n");
}

/* Tests skill_tree_free. */
Test(skilltree_tests, skill_tree_free_test)
{
    skill_tree_t* tree = skill_tree_new(1002, "this tree", 3);
    int ret = skill_tree_free(tree);
    cr_assert_eq(ret, SUCCESS, "Error: failed test skill_tree_free_test\n");
}
