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
    skill_node_t* node = skill_node_new(skill, 0, 76);
    cr_assert_eq(node->prereqs,NULL,
        "Error: failed test skill_node_new on node->prereqs\n");
    cr_assert_eq(node->num_prereq_skills, 0,
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
    skill_tree_t* tree = skill_tree_new(1002, "this tree", 0);
    cr_assert_eq(tree->tid, 1002,
      "Error: failed test skill_tree_new_test on tree->tid\n");
    cr_assert_str_eq(tree->name, "this tree",
      "Error: failed test skill_tree_new_test on tree->name\n");
    cr_assert_eq(tree->num_nodes, 0,
      "Error: failed test skill_tree_new_test on tree->num_nodes\n");
}

/* Tests skill_tree_free. */
Test(skilltree_tests, skill_tree_free_test)
{
    skill_tree_t* tree = skill_tree_new(1002, "this tree", 3);
    int ret = skill_tree_free(tree);
    cr_assert_eq(ret, SUCCESS, "Error: failed test skill_tree_free_test\n");
}

/*Tests after this line fail and are skipped.*/

/* Tests node_prereq_add on a valid case. */
Test(skilltree_tests, node_prereq_add_safe)
{
    skill_t* bomb = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, effect_defuse_bomb);
    skill_t* peace = skill_new(1001, ACTIVE, "inner peace", "maintains inner peace",
        4, 7, effect_inner_peace);
    skill_node_t* bomb_node = skill_node_new(bomb, 0, 76);
    skill_node_t* peace_node = skill_node_new(peace, 1, 76);
    int ret = node_prereq_add(peace_node,bomb_node);
    cr_assert_eq(ret, SUCCESS, "Error: failed test node_prereq_add_safe\n");
}

/* Tests node_prereq_add when the prereq list is full. */
Test(skilltree_tests, node_prereq_add_full)
{
    skill_t* bomb = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, effect_defuse_bomb);
    skill_t* tree = skill_new(1001, ACTIVE, "chop tree", "chops a bomb",
        3, 6, effect_chop_tree);
    skill_t* peace = skill_new(1002, ACTIVE, "inner peace", "maintains inner peace",
        4, 7, effect_inner_peace);
    skill_node_t* bomb_node = skill_node_new(bomb, 0, 76);
    skill_node_t* tree_node = skill_node_new(tree, 0, 76);
    skill_node_t* peace_node = skill_node_new(peace, 1, 76);
    node_prereq_add(peace_node,bomb_node);
    int ret = node_prereq_add(peace_node,tree_node);
    cr_assert_eq(ret, SUCCESS, "Error: failed test node_prereq_add_full\n");
}

// /* Tests node_prereq_remove on a valid case. */
// Test(skilltree_tests, node_prereq_remove_safe)
// {
//     skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
//         2, 5, effect_defuse_bomb);
//     skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
//         3, 6, effect_chop_tree);
//     skill_t* skill3 = skill_new(1002, PASSIVE, "inner peace", "maintains inner peace",
//         4, 7, effect_inner_peace);
//     skill_node_t* bomb_node = skill_node_new(skill1, 0, 75);
//     skill_node_t* chop_node = skill_node_new(skill2, 0, 76);
//     skill_node_t* inner_node = skill_node_new(skill3, 2, 76);
//
//     node_prereq_add(inner_node, bomb_node);
//     node_prereq_add(inner_node, chop_node);
//
//     int ret = node_prereq_remove(inner_node, bomb_node);
//     cr_assert_eq(ret, SUCCESS, "Error: failed test node_prereq_remove_safe\n");
// }

// /* Tests node_prereq_remove on a prereq that doesn't exist. */
// Test(skilltree_tests, node_prereq_remove_missing)
// {
//     skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
//         2, 5, effect_defuse_bomb);
//     skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
//         3, 6, effect_chop_tree);
//     skill_t* skill3 = skill_new(1002, PASSIVE, "inner peace", "maintains inner peace",
//         4, 7, effect_inner_peace);
//     skill_node_t* bomb_node = skill_node_new(skill1, 0, 75);
//     skill_node_t* chop_node = skill_node_new(skill2, 0, 76);
//     skill_node_t* inner_node = skill_node_new(skill3, 2, 76);
//
//     node_prereq_add(inner_node, chop_node);
//
//     int ret = node_prereq_remove(inner_node, bomb_node);
//     cr_assert_eq(ret, 1, "Error: failed test node_prereq_remove_missing\n");
// }


/* Tests skill_tree_node_add on a valid case. */
Test(skilltree_tests, skill_tree_node_add_safe)
{
    skill_tree_t* tree = skill_tree_new(1002, "this tree", 2);
    skill_t* bomb = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, effect_defuse_bomb);
    skill_node_t* bomb_node = skill_node_new(bomb, 0, 76);
    cr_assert_eq(tree->num_nodes, 0, "Error: Failed getting tree->num_nodes\n");
    int ret = skill_tree_node_add(tree, bomb_node);
    cr_assert_eq(ret, SUCCESS, "Error: failed test skill_tree_node_add_safe\n");
    cr_assert_eq(bomb_node->skill->sid, 1000, "Error: Failed getting sid\n");
    cr_assert_eq(tree->nodes[0]->skill->sid, 1000,
                 "Error: failed test skill_tree_node_add_safe\n");
}

/* Tests skill_tree_node_add when the skill tree is full. */
Test(skilltree_tests, skill_tree_node_add_full)
{
    skill_tree_t* tree = skill_tree_new(1002, "this tree", 1);
    skill_t* bomb = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, effect_defuse_bomb);
    skill_t* peace = skill_new(1001, ACTIVE, "inner peace", "maintains inner peace",
        4, 7, effect_inner_peace);
    skill_node_t* bomb_node = skill_node_new(bomb, 0, 76);
    skill_node_t* peace_node = skill_node_new(peace, 0, 76);
    skill_tree_node_add(tree,bomb_node);
    int ret = skill_tree_node_add(tree,peace_node);
    cr_assert_eq(ret, SUCCESS, "Error: failed test skill_tree_node_add_full\n");
}

/* Tests skill_tree_node_remove in a valid case. */
Test(skilltree_tests, skill_tree_node_remove_safe)
{
    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, effect_defuse_bomb);
    skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
        3, 6, effect_chop_tree);
    skill_t* skill3 = skill_new(1002, PASSIVE, "inner peace", "maintains inner peace",
        4, 7, effect_inner_peace);
    skill_node_t* bomb_node = skill_node_new(skill1, 0, 75);
    skill_node_t* chop_node = skill_node_new(skill2, 0, 76);
    skill_node_t* inner_node = skill_node_new(skill3, 0, 77);

    skill_tree_t* tree = skill_tree_new(1001, "this tree", 3);
    skill_tree_node_add(tree, bomb_node);
    skill_tree_node_add(tree, chop_node);
    skill_tree_node_add(tree, inner_node);

    int ret = skill_tree_node_remove(tree, chop_node);
    cr_assert_eq(ret, SUCCESS, "Error: failed test skill_tree_node_remove_safe\n");
}

/* Tests skill_tree_node_remove on a node that is missing. */
Test(skilltree_tests, skill_tree_node_remove_missing)
{
    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, effect_defuse_bomb);
    skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
        3, 6, effect_chop_tree);
    skill_t* skill3 = skill_new(1002, PASSIVE, "inner peace", "maintains inner peace",
        4, 7, effect_inner_peace);
    skill_node_t* bomb_node = skill_node_new(skill1, 0, 75);
    skill_node_t* chop_node = skill_node_new(skill2, 0, 76);
    skill_node_t* inner_node = skill_node_new(skill3, 0, 77);

    skill_tree_t* tree = skill_tree_new(1001, "this tree", 3);
    skill_tree_node_add(tree, bomb_node);
    skill_tree_node_add(tree, chop_node);

    int ret = skill_tree_node_remove(tree, inner_node);
    cr_assert_eq(ret, 1, "Error: failed test skill_tree_node_remove_missing\n");
}

/* Tests skill_tree_has_node with a node that exists. */
Test(skilltree_tests, skill_tree_has_node_has)
{
  skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
      3, 6, effect_chop_tree);
  skill_t* skill3 = skill_new(1002, PASSIVE, "inner peace", "maintains inner peace",
      4, 7, effect_inner_peace);
  skill_node_t* bomb_node = skill_node_new(skill1, 0, 75);
  skill_node_t* chop_node = skill_node_new(skill2, 0, 76);
  skill_node_t* inner_node = skill_node_new(skill3, 0, 77);

  skill_tree_t* tree = skill_tree_new(1001, "this tree", 3);
  skill_tree_node_add(tree, bomb_node);
  skill_tree_node_add(tree, chop_node);

  int ret = skill_tree_has_node(tree, 1000);
  cr_assert_eq(ret, 0, "Error: failed test skill_tree_has_node_has\n");
}

/* Tests skill_tree_has_node on a node that it doesn't have. */
Test(skilltree_tests, skill_tree_has_node_has_not)
{
  skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
      3, 6, effect_chop_tree);
  skill_t* skill3 = skill_new(1002, PASSIVE, "inner peace", "maintains inner peace",
      4, 7, effect_inner_peace);
  skill_node_t* bomb_node = skill_node_new(skill1, 0, 75);
  skill_node_t* chop_node = skill_node_new(skill2, 0, 76);
  skill_node_t* inner_node = skill_node_new(skill3, 0, 77);

  skill_tree_t* tree = skill_tree_new(1001, "this tree", 3);
  skill_tree_node_add(tree, bomb_node);
  skill_tree_node_add(tree, chop_node);

  int ret = skill_tree_has_node(tree, 1002);
  cr_assert_eq(ret, -1, "Error: failed test skill_tree_has_node_has_not\n");
}

/* Tests get_all_skill_prereqs on a valid case. */
Test(skilltree_tests, get_all_skill_prereqs_safe)
{
  skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
      3, 6, effect_chop_tree);
  skill_t* skill3 = skill_new(1002, PASSIVE, "inner peace", "maintains inner peace",
      4, 7, effect_inner_peace);
  skill_node_t* bomb_node = skill_node_new(skill1, 0, 75);
  skill_node_t* chop_node = skill_node_new(skill2, 0, 76);
  skill_node_t* inner_node = skill_node_new(skill3, 2, 77);

  node_prereq_add(inner_node, bomb_node);
  node_prereq_add(inner_node, chop_node);

  skill_tree_t* tree = skill_tree_new(1001, "this tree", 3);
  skill_tree_node_add(tree, bomb_node);
  skill_tree_node_add(tree, chop_node);
  skill_tree_node_add(tree, inner_node);
  int* out = malloc(sizeof(int));


  skill_node_t** ret = get_all_skill_prereqs(tree, 1002, out);
  cr_assert_eq(ret, inner_node->prereqs,
    "Error: failed test get_all_skill_prereqs_safe\n");
}

/* Tests get_all_skill_prereqs for empty prereq list. */
Test(skilltree_tests, get_all_skill_prereqs_empty)
{
    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, effect_defuse_bomb);
    skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
        3, 6, effect_chop_tree);
    skill_t* skill3 = skill_new(1002, PASSIVE, "inner peace", "maintains inner peace",
        4, 7, effect_inner_peace);
    skill_node_t* bomb_node = skill_node_new(skill1, 0, 75);
    skill_node_t* chop_node = skill_node_new(skill2, 0, 76);
    skill_node_t* inner_node = skill_node_new(skill3, 0, 77);
    skill_tree_t* tree = skill_tree_new(1001, "this tree", 3);
    skill_tree_node_add(tree, bomb_node);
    skill_tree_node_add(tree, chop_node);
    skill_tree_node_add(tree, inner_node);
    int* out = malloc(sizeof(int));

    skill_node_t** ret = get_all_skill_prereqs(tree, 1002, out);
    cr_assert_null(ret,
      "Error: failed test get_all_skill_prereqs_empty\n");
    cr_assert_eq(*out, 0,
      "Error: failed test get_all_skill_prereqs_empty\n");
}

/* Tests get_acquired_skill_prereqs with no prereqs. */
Test(skilltree_tests, get_acquired_skill_prereqs_no_prereqs)
{
    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, effect_defuse_bomb);
    skill_node_t* bomb_node = skill_node_new(skill1, 0, 75);

    skill_tree_t* tree = skill_tree_new(1001, "this tree", 1);
    skill_tree_node_add(tree, bomb_node);

    int* out = malloc(sizeof(int));

    skill_inventory_t* inventory = inventory_new(3,4);
    inventory_skill_add(inventory, skill1);

    get_acquired_skill_prereqs(tree, inventory, 1000, out);

    cr_assert_eq(*out, 0,
      "Error: failed test get_acquired_skill_prereqs_no_prereqs\n");
}

/* Tests get_acquired_skill_prereqs on a valid case. */
Test(skilltree_tests, get_acquired_skill_prereqs_safe)
{
  skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
      3, 6, effect_chop_tree);
  skill_node_t* bomb_node = skill_node_new(skill1, 1, 75);
  skill_node_t* chop_node = skill_node_new(skill2, 0, 76);

  node_prereq_add(bomb_node, chop_node);

  skill_tree_t* tree = skill_tree_new(1001, "this tree", 1);
  skill_tree_node_add(tree, bomb_node);
  skill_tree_node_add(tree, chop_node);

  int* out = malloc(sizeof(int));

  skill_inventory_t* inventory = inventory_new(3,4);
  inventory_skill_add(inventory, skill2);

  skill_node_t** acqed = get_acquired_skill_prereqs(tree, inventory, 1000, out);
  //int ret = (acqed[0] == skill2);
  //cr_assert_eq(ret, true,
  //  "Error: failed test get_acquired_skill_prereqs_safe\n");
}

/* Tests skill_prereqs_missing on a case with no missing prereqs. */
Test(skilltree_tests, skill_prereqs_missing_none)
{
    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, effect_defuse_bomb);
    skill_node_t* bomb_node = skill_node_new(skill1, 0, 75);

    skill_tree_t* tree = skill_tree_new(1001, "this tree", 1);
    skill_tree_node_add(tree, bomb_node);

    int* out = malloc(sizeof(int));

    skill_inventory_t* inventory = inventory_new(3,4);
    inventory_skill_add(inventory, skill1);

    skill_prereqs_missing(tree, inventory, 1000, out);

    cr_assert_eq(*out, 0,
      "Error: failed test skill_prereqs_missing_none\n");
}

/* Tests skill_prereqs_missing on a case with missing prereqs. */
Test(skilltree_tests, skill_prereqs_missing_some)
{
  skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
      3, 6, effect_chop_tree);
  skill_node_t* bomb_node = skill_node_new(skill1, 1, 75);
  skill_node_t* chop_node = skill_node_new(skill2, 0, 76);

  node_prereq_add(bomb_node, chop_node);

  skill_tree_t* tree = skill_tree_new(1001, "this tree", 1);
  skill_tree_node_add(tree, bomb_node);
  skill_tree_node_add(tree, chop_node);

  int* out = malloc(sizeof(int));

  skill_inventory_t* inventory = inventory_new(3,4);

  skill_t** acqed = skill_prereqs_missing(tree, inventory, 1000, out);
  int ret = (acqed[0] == skill2);
  cr_assert_eq(ret, true,
    "Error: failed test skill_prereqs_missing_some\n");
}

/* Tests inventory_skill_acquire on a skill with satisfied prereqs. */
Test(skilltree_tests, inventory_skill_acquire_has)
{
    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, effect_defuse_bomb);
    skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
        3, 6, effect_chop_tree);
    skill_node_t* bomb_node = skill_node_new(skill1, 0, 75);
    skill_node_t* chop_node = skill_node_new(skill2, 1, 7665);

    node_prereq_add(chop_node, bomb_node);

    skill_tree_t* tree = skill_tree_new(1001, "this tree", 1);
    skill_tree_node_add(tree, bomb_node);
    skill_tree_node_add(tree, chop_node);

    skill_inventory_t* inventory = inventory_new(3,4);
    inventory_skill_add(inventory, skill1);

    int ret = inventory_skill_acquire(tree, inventory, skill2);

    cr_assert_eq(ret, 0,
      "Error: failed test inventory_skill_acquire_has on return value\n");
    cr_assert_neq(-1, inventory_has_skill(inventory, 1001, ACTIVE),
      "Error: failed test inventory_skill_acquire_has on adding to inventory\n");
}

/* Tests inventory_skill_acquire on a skill with missing prereqs. */
Test(skilltree_tests, inventory_skill_acquire_has_not)
{
  skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, effect_defuse_bomb);
  skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
      3, 6, effect_chop_tree);
  skill_node_t* bomb_node = skill_node_new(skill1, 0, 75);
  skill_node_t* chop_node = skill_node_new(skill2, 1, 7665);

  node_prereq_add(chop_node, bomb_node);

  skill_tree_t* tree = skill_tree_new(1001, "this tree", 1);
  skill_tree_node_add(tree, bomb_node);
  skill_tree_node_add(tree, chop_node);

  skill_inventory_t* inventory = inventory_new(3,4);

  int ret = inventory_skill_acquire(tree, inventory, skill2);

  cr_assert_eq(ret, 1,
    "Error: failed test inventory_skill_acquire_has on return value\n");
  cr_assert_eq(-1, inventory_has_skill(inventory, 1001, ACTIVE),
    "Error: failed test inventory_skill_acquire_has on adding to inventory\n");
}
