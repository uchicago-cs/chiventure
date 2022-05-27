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


/* Tests skill_node_new. */

Test(skilltree_test, skill_node_new_test)
{   
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);

    skill_t* skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect, NULL);

    char** classes = (char**)malloc(sizeof(char*)*3);
    classes[0] = "bard";
    classes[1] = "beserker";
    classes[2] = "mage";

    skill_node_t* node = skill_node_new(skill, 0, 24, classes, 3, 76);
    cr_assert_eq(node->prereqs,NULL,
        "Error: failed test skill_node_new on node->prereqs\n");
    cr_assert_eq(node->num_prereq_skills, 0,
        "Error: failed test skill_node_new on node->num_prereq_skills\n");

    cr_assert_eq(node->prereq_level, 24,
        "Error: failed test skill_node_new on node->prereq_level\n");
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
        "Error: failed test on node->skill->max_level\n");
    cr_assert_eq(node->skill->min_xp, 5,
        "Error: failed test skill_node_new_test on node->skill->min_xp\n");
}
/* Tests skill_node_free. */

Test(skilltree_test, skill_node_free_test)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);

    skill_t* skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect, NULL);
    skill_node_t* node = skill_node_new(skill, 4, 76, NULL, 0, 38);
    int ret = skill_node_free(node);
    cr_assert_eq(ret, 0, "Error: failed test skill_node_free_test\n");
}


/* Tests skill_tree_new. */
Test(skilltree_test, skill_tree_new_test)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);

    skill_tree_t* tree = skill_tree_new(1002, "this tree", 0);
    cr_assert_eq(tree->tid, 1002,
      "Error: failed test skill_tree_new_test on tree->tid\n");
    cr_assert_str_eq(tree->name, "this tree",
      "Error: failed test skill_tree_new_test on tree->name\n");
    cr_assert_eq(tree->num_nodes, 0,
      "Error: failed test skill_tree_new_test on tree->num_nodes\n");
}

/* Tests skill_tree_free. */
Test(skilltree_test, skill_tree_free_test)
{
    skill_tree_t* tree = skill_tree_new(1002, "this tree", 3);
    int ret = skill_tree_free(tree);
    cr_assert_eq(ret, SUCCESS, "Error: failed test skill_tree_free_test\n");
}

/* Tests node_prereq_add on a valid case. */

Test(skilltree_test, node_prereq_add_safe)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);
    effect_t* innerpeace = make_innerpeace_effect(ctx);
    
    skill_t* bomb_skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect, NULL);
    skill_t* peace = skill_new(1001, ACTIVE, "inner peace", "maintains inner peace",
        4, 7, innerpeace, NULL);
    skill_node_t* bomb_node = skill_node_new(bomb_skill, 0, 76, NULL, 0, 33);
    skill_node_t* peace_node = skill_node_new(peace, 1, 76, NULL, 0, 29);
    int ret = node_prereq_add(peace_node,bomb_node, 5);
    cr_assert_eq(ret, SUCCESS, "Error: failed test node_prereq_add_safe\n");
}

/* Tests node_prereq_add when the prereq list is full. */

Test(skilltree_test, node_prereq_add_full)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);
    effect_t* innerpeace = make_innerpeace_effect(ctx);
    item_t* tree = add_chop_item(ctx);
    effect_t* choptreeeffect = make_choptree_effect(tree);

    skill_t* bomb_skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect, NULL);
    skill_t* tree_skill = skill_new(1001, ACTIVE, "chop tree", "chops a bomb",
        3, 6, choptreeeffect, NULL);
    skill_t* peace = skill_new(1002, ACTIVE, "inner peace", "maintains inner peace",
        4, 7, innerpeace, NULL);
    skill_node_t* bomb_node = skill_node_new(bomb_skill, 0, 76, NULL, 0, 34);
    skill_node_t* tree_node = skill_node_new(tree_skill, 0, 76, NULL, 0, 22);
    skill_node_t* peace_node = skill_node_new(peace, 1, 76, NULL, 0, 12);
    node_prereq_add(peace_node,bomb_node, 12);
    int ret = node_prereq_add(peace_node,tree_node, 12);
    cr_assert_eq(ret, SUCCESS, "Error: failed test node_prereq_add_full\n");
}

/* Tests node_prereq_remove on a valid case. */

Test(skilltree_test, node_prereq_remove_safe)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);
    effect_t* innerpeace = make_innerpeace_effect(ctx);
    item_t* tree = add_chop_item(ctx);
    effect_t* choptreeeffect = make_choptree_effect(tree);

    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect, NULL);
    skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
        3, 6, choptreeeffect, NULL);
    skill_t* skill3 = skill_new(1002, PASSIVE, "inner peace", "maintains inner peace",
        4, 7, innerpeace, NULL);
    skill_node_t* bomb_node = skill_node_new(skill1, 0, 75, NULL, 0, 1);
    skill_node_t* chop_node = skill_node_new(skill2, 0, 76, NULL, 0, 23);
    skill_node_t* inner_node = skill_node_new(skill3, 2, 76, NULL, 0, 9182);

    node_prereq_add(inner_node, bomb_node, 14);
    node_prereq_add(inner_node, chop_node, 14);

    int ret = node_prereq_remove(inner_node, bomb_node);
    cr_assert_eq(ret, SUCCESS, "Error: failed test node_prereq_remove_safe\n");
}

/* Tests node_prereq_remove on a prereq that doesn't exist. */

Test(skilltree_test, node_prereq_remove_missing)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);
    effect_t* innerpeace = make_innerpeace_effect(ctx);
    item_t* tree = add_chop_item(ctx);
    effect_t* choptreeeffect = make_choptree_effect(tree);

    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect, NULL);
    skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
        3, 6, choptreeeffect, NULL);
    skill_t* skill3 = skill_new(1002, PASSIVE, "inner peace", "maintains inner peace",
        4, 7, innerpeace, NULL);
    skill_node_t* bomb_node = skill_node_new(skill1, 0, 75, NULL, 0, 33);
    skill_node_t* chop_node = skill_node_new(skill2, 0, 76, NULL, 0, 72);
    skill_node_t* inner_node = skill_node_new(skill3, 2, 76, NULL, 0, 91);

    node_prereq_add(inner_node, chop_node, 15);

    int ret = node_prereq_remove(inner_node, bomb_node);
    cr_assert_eq(ret, 1, "Error: failed test node_prereq_remove_missing\n");
}


/* Tests skill_tree_node_add on a valid case. */

Test(skilltree_test, skill_tree_node_add_safe)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);
    effect_t* innerpeace = make_innerpeace_effect(ctx);
    item_t* tree = add_chop_item(ctx);
    effect_t* choptreeeffect = make_choptree_effect(tree);

    skill_tree_t* skilltree = skill_tree_new(1002, "this tree", 2);
    skill_t* bomb_skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect, NULL);
    skill_node_t* bomb_node = skill_node_new(bomb_skill, 0, 76, NULL, 0, 21);
    cr_assert_eq(skilltree->num_nodes, 0, "Error: Failed getting tree->num_nodes\n");
    int ret = skill_tree_node_add(skilltree, bomb_node);
    cr_assert_eq(ret, SUCCESS, "Error: failed test skill_tree_node_add_safe\n");
    cr_assert_eq(bomb_node->skill->sid, 1000, "Error: Failed getting sid\n");
    cr_assert_eq(skilltree->nodes[0]->skill->sid, 1000,
                 "Error: failed test skill_tree_node_add_safe\n");
}

/* Tests skill_tree_node_add when the skill tree is full. */

Test(skilltree_test, skill_tree_node_add_full)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);
    effect_t* innerpeace = make_innerpeace_effect(ctx);
    item_t* tree = add_chop_item(ctx);
    effect_t* choptreeeffect = make_choptree_effect(tree);

    skill_tree_t* skilltree = skill_tree_new(1002, "this tree", 1);
    skill_t* bomb_skill = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect, NULL);
    skill_t* peace = skill_new(1001, ACTIVE, "inner peace", "maintains inner peace",
        4, 7, innerpeace, NULL);
    skill_node_t* bomb_node = skill_node_new(bomb_skill, 0, 76, NULL, 0, 22);
    skill_node_t* peace_node = skill_node_new(peace, 0, 76, NULL, 0,5);
    skill_tree_node_add(skilltree,bomb_node);
    int ret = skill_tree_node_add(skilltree,peace_node);
    cr_assert_eq(ret, SUCCESS, "Error: failed test skill_tree_node_add_full\n");
}

/* Tests skill_tree_node_remove in a valid case. */

Test(skilltree_test, skill_tree_node_remove_safe)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);
    effect_t* innerpeace = make_innerpeace_effect(ctx);
    item_t* tree = add_chop_item(ctx);
    effect_t* choptreeeffect = make_choptree_effect(tree);

    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect, NULL);
    skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
        3, 6, choptreeeffect, NULL);
    skill_t* skill3 = skill_new(1002, PASSIVE, "inner peace", "maintains inner peace",
        4, 7, innerpeace, NULL);
    skill_node_t* bomb_node = skill_node_new(skill1, 0, 75, NULL, 0, 74);
    skill_node_t* chop_node = skill_node_new(skill2, 0, 76, NULL, 0, 33);
    skill_node_t* inner_node = skill_node_new(skill3, 0, 77, NULL, 0, 5);

    skill_tree_t* skilltree = skill_tree_new(1001, "this tree", 3);
    skill_tree_node_add(skilltree, bomb_node);
    skill_tree_node_add(skilltree, chop_node);
    skill_tree_node_add(skilltree, inner_node);

    int ret = skill_tree_node_remove(skilltree, chop_node);
    cr_assert_eq(ret, SUCCESS, "Error: failed test skill_tree_node_remove_safe\n");
}

/* Tests skill_tree_node_remove on a node that is missing. */

Test(skilltree_test, skill_tree_node_remove_missing)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);
    effect_t* innerpeace = make_innerpeace_effect(ctx);
    item_t* tree = add_chop_item(ctx);
    effect_t* choptreeeffect = make_choptree_effect(tree);

    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect, NULL);
    skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
        3, 6, choptreeeffect, NULL);
    skill_t* skill3 = skill_new(1002, PASSIVE, "inner peace", "maintains inner peace",
        4, 7, innerpeace, NULL);
    skill_node_t* bomb_node = skill_node_new(skill1, 0, 75, NULL, 0, 22);
    skill_node_t* chop_node = skill_node_new(skill2, 0, 76, NULL, 0, 9);
    skill_node_t* inner_node = skill_node_new(skill3, 0, 77, NULL, 0, 738);

    skill_tree_t* skilltree = skill_tree_new(1001, "this tree", 3);
    skill_tree_node_add(skilltree, bomb_node);
    skill_tree_node_add(skilltree, chop_node);

    int ret = skill_tree_node_remove(skilltree, inner_node);
    cr_assert_eq(ret, 1, "Error: failed test skill_tree_node_remove_missing\n");
}

/* Tests skill_tree_has_node with a node that exists. */

Test(skilltree_test, skill_tree_has_node_has)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);
    effect_t* innerpeace = make_innerpeace_effect(ctx);
    item_t* tree = add_chop_item(ctx);
    effect_t* choptreeeffect = make_choptree_effect(tree);

    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, defusebombeffect, NULL);
    skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
      3, 6, choptreeeffect, NULL);
    skill_t* skill3 = skill_new(1002, PASSIVE, "inner peace", "maintains inner peace",
      4, 7, innerpeace, NULL);
    skill_node_t* bomb_node = skill_node_new(skill1, 0, 75, NULL, 0, 32); 
    skill_node_t* chop_node = skill_node_new(skill2, 0, 76, NULL, 0, 11);
    skill_node_t* inner_node = skill_node_new(skill3, 0, 77, NULL, 0, 40);

    skill_tree_t* skilltree = skill_tree_new(1001, "this tree", 3);
    skill_tree_node_add(skilltree, bomb_node);
    skill_tree_node_add(skilltree, chop_node);

    int ret = skill_tree_has_node(skilltree, 1000);
    cr_assert_eq(ret, 0, "Error: failed test skill_tree_has_node_has\n");
}

/* Tests skill_tree_has_node on a node that it doesn't have. */

Test(skilltree_test, skill_tree_has_node_has_not)
{
  chiventure_ctx_t* ctx = create_player_and_stats();
  item_t* bomb = add_bomb_item(ctx);
  effect_t* defusebombeffect = make_bomb_effect(bomb);
  effect_t* innerpeace = make_innerpeace_effect(ctx);
  item_t* tree = add_chop_item(ctx);
  effect_t* choptreeeffect = make_choptree_effect(tree);

  skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, defusebombeffect, NULL);
  skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
      3, 6, choptreeeffect, NULL);
  skill_t* skill3 = skill_new(1002, PASSIVE, "inner peace", "maintains inner peace",
      4, 7, innerpeace, NULL);
  skill_node_t* bomb_node = skill_node_new(skill1, 0, 75, NULL, 0, 33);
  skill_node_t* chop_node = skill_node_new(skill2, 0, 76, NULL, 0,11);
  skill_node_t* inner_node = skill_node_new(skill3, 0, 77, NULL, 0,88);

  skill_tree_t* skilltree = skill_tree_new(1001, "this tree", 3);
  skill_tree_node_add(skilltree, bomb_node);
  skill_tree_node_add(skilltree, chop_node);

  int ret = skill_tree_has_node(skilltree, 1002);
  cr_assert_eq(ret, -1, "Error: failed test skill_tree_has_node_has_not\n");
}

/* Tests get_all_skill_prereqs on a valid case. */

Test(skilltree_test, get_all_skill_prereqs_safe)
{ 
  chiventure_ctx_t* ctx = create_player_and_stats();
  item_t* bomb = add_bomb_item(ctx);
  effect_t* defusebombeffect = make_bomb_effect(bomb);
  effect_t* innerpeace = make_innerpeace_effect(ctx);
  item_t* tree = add_chop_item(ctx);
  effect_t* choptreeeffect = make_choptree_effect(tree);
    
  skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, defusebombeffect, NULL);
  skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
      3, 6, choptreeeffect, NULL);
  skill_t* skill3 = skill_new(1002, PASSIVE, "inner peace", "maintains inner peace",
      4, 7, innerpeace, NULL);
  skill_node_t* bomb_node = skill_node_new(skill1, 0, 75, NULL, 0,22);
  skill_node_t* chop_node = skill_node_new(skill2, 0, 76, NULL, 0,19);
  skill_node_t* inner_node = skill_node_new(skill3, 2, 77, NULL, 0,4);

  node_prereq_add(inner_node, bomb_node, 19);
  node_prereq_add(inner_node, chop_node, 14);

  skill_tree_t* skilltree = skill_tree_new(1001, "this tree", 3);
  skill_tree_node_add(skilltree, bomb_node);
  skill_tree_node_add(skilltree, chop_node);
  skill_tree_node_add(skilltree, inner_node);



  skill_node_t** ret = get_all_skill_prereqs(skilltree, 1002);
  cr_assert_eq(ret, inner_node->prereqs,
    "Error: failed test get_all_skill_prereqs_safe\n");
}

/* Tests get_all_skill_prereqs for empty prereq list. */

Test(skilltree_test, get_all_skill_prereqs_empty)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);
    effect_t* innerpeace = make_innerpeace_effect(ctx);
    item_t* tree = add_chop_item(ctx);
    effect_t* choptreeeffect = make_choptree_effect(tree);

    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect, NULL);
    skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
        3, 6, choptreeeffect, NULL);
    skill_t* skill3 = skill_new(1002, PASSIVE, "inner peace", "maintains inner peace",
        4, 7, innerpeace, NULL);
    skill_node_t* bomb_node = skill_node_new(skill1, 0, 75, NULL, 0,59);
    skill_node_t* chop_node = skill_node_new(skill2, 0, 76, NULL, 0,66);
    skill_node_t* inner_node = skill_node_new(skill3, 0, 77, NULL, 0,37);
    skill_tree_t* skilltree = skill_tree_new(1001, "this tree", 3);
    skill_tree_node_add(skilltree, bomb_node);
    skill_tree_node_add(skilltree, chop_node);
    skill_tree_node_add(skilltree, inner_node);

    skill_node_t** ret = get_all_skill_prereqs(skilltree, 1002);
    cr_assert_null(ret,
      "Error: failed test get_all_skill_prereqs_empty\n");
}

/* Tests get_acquired_skill_prereqs with no prereqs. */

Test(skilltree_test, get_acquired_skill_prereqs_no_prereqs)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);
    effect_t* innerpeace = make_innerpeace_effect(ctx);
    item_t* tree = add_chop_item(ctx);
    effect_t* choptreeeffect = make_choptree_effect(tree);

    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect, NULL);
    skill_node_t* bomb_node = skill_node_new(skill1, 0, 3, NULL, 0, 75);

    skill_tree_t* skilltree = skill_tree_new(1001, "this tree", 1);
    skill_tree_node_add(skilltree, bomb_node);

    int* out = malloc(sizeof(int));

    skill_inventory_t* inventory = inventory_new(3,4);
    inventory_skill_add(inventory, skill1);

    unsigned int* prereq;
    get_acquired_skill_prereqs(skilltree, inventory, 1000, prereq, out);

    cr_assert_eq(*out, 0,
      "Error: failed test get_acquired_skill_prereqs_no_prereqs\n");
}

/* Tests get_acquired_skill_prereqs on a valid case. */

Test(skilltree_test, get_acquired_skill_prereqs_safe)
{
  chiventure_ctx_t* ctx = create_player_and_stats();
  item_t* bomb = add_bomb_item(ctx);
  effect_t* defusebombeffect = make_bomb_effect(bomb);
  effect_t* innerpeace = make_innerpeace_effect(ctx);
  item_t* tree = add_chop_item(ctx);
  effect_t* choptreeeffect = make_choptree_effect(tree);

  skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, defusebombeffect, NULL);
  skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
      3, 6, choptreeeffect, NULL);
  skill_node_t* bomb_node = skill_node_new(skill1, 1, 23, NULL, 0, 75);
  skill_node_t* chop_node = skill_node_new(skill2, 0, 82, NULL, 0, 76);

  node_prereq_add(bomb_node, chop_node, 7);

  skill_tree_t* skilltree = skill_tree_new(1001, "this tree", 1);
  skill_tree_node_add(skilltree, bomb_node);
  skill_tree_node_add(skilltree, chop_node);

  int* out = malloc(sizeof(int));

  skill_inventory_t* inventory = inventory_new(3,4);
  inventory_skill_add(inventory, skill2);

  unsigned int* prereq; 
  skill_t** acqed = get_acquired_skill_prereqs(skilltree, inventory, 1000, prereq, out);
  int ret = (acqed[0] == skill2);
  cr_assert_eq(acqed[0]->sid, 1001,
   "Error: failed test get_acquired_skill_prereqs_safe\n");
  cr_assert_eq(ret, true,
   "Error: failed test get_acquired_skill_prereqs_safe\n");
}


/* The following tests crash due to issues with skill_has_prereqs 
 * method, which is left as an issue to resolve.
 */ 



/* Tests skill_prereqs_missing on a case with no missing prereqs. */
/* TEST CRASHES  (See Line 488)*/
/*
Test(skilltree_test, skill_prereqs_missing_none)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);
    item_t* tree = add_chop_item(ctx);
    effect_t* choptreeeffect = make_choptree_effect(tree);
    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect);
    skill_node_t* bomb_node = skill_node_new(skill1, 0, 75, NULL, 0, 11);

    skill_tree_t* skilltree = skill_tree_new(1001, "this tree", 1);
    skill_tree_node_add(skilltree, bomb_node);
    int* out = malloc(sizeof(int));
    skill_inventory_t* inventory = inventory_new(3,4);
    inventory_skill_add(inventory, skill1);
    unsigned int* prereq_level = (unsigned int*)malloc(sizeof(unsigned int*));
    skill_prereqs_missing(skilltree, inventory, 1000, prereq_level, out);
    cr_assert_eq(*out, 0,
      "Error: failed test skill_prereqs_missing_none\n");
}
*/

/* Tests skill_prereqs_missing on a case with missing prereqs. */
/* TEST CRASHES (See Line 488)*/
/*
Test(skilltree_test, skill_prereqs_missing_some)
{
  chiventure_ctx_t* ctx = create_player_and_stats();
  item_t* bomb = add_bomb_item(ctx);
  effect_t* defusebombeffect = make_bomb_effect(bomb);
  effect_t* innerpeace = make_innerpeace_effect(ctx);
  item_t* tree = add_chop_item(ctx);
  effect_t* choptreeeffect = make_choptree_effect(tree);
  skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, defusebombeffect);
  skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
      3, 6, choptreeeffect);
  skill_node_t* bomb_node = skill_node_new(skill1, 1, 75, NULL, 0,2);
  skill_node_t* chop_node = skill_node_new(skill2, 0, 76, NULL, 0,88);

  node_prereq_add(bomb_node, chop_node, 59);
  cr_assert_eq(bomb_node->prereqs[0]->skill->sid, 1001,
               "Error: failed test skill_prereqs_missing_some\n");
  skill_tree_t* skilltree = skill_tree_new(1001, "this tree", 1);
  skill_tree_node_add(skilltree, bomb_node);
  int res1 = skill_tree_has_node(skilltree, 1000);
  cr_assert_eq(0, res1, "Error: failed test skill_prereqs_missing_some\n");
  skill_tree_node_add(skilltree, chop_node);
  int res2 = skill_tree_has_node(skilltree, 1001);
  cr_assert_eq(1, res2, "Error: failed test skill_prereqs_missing_some\n");
  skill_node_t** skill_list = get_all_skill_prereqs(skilltree, 1000);
  //cr_assert_eq(1, (*out_prereqs),
  //             "Error: failed test skill_prereqs_missing_some\n");
  cr_assert_neq(NULL, skill_list,
      "Error: failed test skill_prereqs_missing_some\n");
  cr_assert_eq(skill_list[0]->skill->sid, 1001,
               "Error: failed test skill_prereqs_missing_some\n");
  int* out = malloc(sizeof(int));
  skill_inventory_t* inventory = inventory_new(3,4);
  unsigned int* prereq; 
  skill_t** acqed = skill_prereqs_missing(skilltree, inventory, 1000,prereq, out);
  int ret = (acqed[0] == skill2);
  cr_assert_eq(ret, true,
    "Error: failed test skill_prereqs_missing_some\n");
}
*/

/* Tests inventory_skill_acquire on a skill with satisfied prereqs. */
/* TEST CRASHES (See Line 488)*/

/*
Test(skilltree_test, inventory_skill_acquire_has)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);
    item_t* tree = add_chop_item(ctx);
    effect_t* choptreeeffect = make_choptree_effect(tree);
    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect);
    skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
        3, 6, choptreeeffect);
    skill_node_t* bomb_node = skill_node_new(skill1, 0, 12, NULL, 0, 47);
    skill_node_t* chop_node = skill_node_new(skill2, 1,14, NULL, 0, 31);

    node_prereq_add(chop_node, bomb_node, 14);
    skill_tree_t* skilltree = skill_tree_new(1001, "this tree", 1);
    skill_tree_node_add(skilltree, bomb_node);
    skill_tree_node_add(skilltree, chop_node);
    skill_inventory_t* inventory = inventory_new(3,4);
    inventory_skill_add(inventory, skill1);
    int ret = inventory_skill_acquire(skilltree, inventory, skill2);
    cr_assert_eq(ret, 0,
      "Error: failed test inventory_skill_acquire_has on return value\n");
    cr_assert_neq(-1, inventory_has_skill(inventory, 1001, ACTIVE),
      "Error: failed test inventory_skill_acquire_has on adding to inventory\n");
}
*/

/* Tests display_tree given a skilltree with one skill and a non-limiting buf size */

Test(skilltree_test, display_tree_one_skill)
{
  chiventure_ctx_t* ctx = create_player_and_stats();
  item_t* bomb = add_bomb_item(ctx);
  effect_t* defusebombeffect = make_bomb_effect(bomb);
    
  skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, defusebombeffect, NULL);
  skill_node_t* bomb_node = skill_node_new(skill1, 0, 75, NULL, 0, 22);

  skill_tree_t* skilltree = skill_tree_new(1001, "this tree", 1);
  skill_tree_node_add(skilltree, bomb_node);

  char *display = display_tree(skilltree, 65);
  char *check = "Skill Name: defuse bomb, Prereq Level: 75, Current Level: 1\n";
  cr_assert_eq(strcmp(check, display), 0, "Error: display_tree_one_skill failed\n");
}

/* Tests display_tree given a skilltree with three skills and a non-limiting buf size */

Test(skilltree_test, display_tree_three_skills)
{ 
  chiventure_ctx_t* ctx = create_player_and_stats();
  item_t* bomb = add_bomb_item(ctx);
  effect_t* defusebombeffect = make_bomb_effect(bomb);
  effect_t* innerpeace = make_innerpeace_effect(ctx);
  item_t* tree = add_chop_item(ctx);
  effect_t* choptreeeffect = make_choptree_effect(tree);
    
  skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, defusebombeffect, NULL);
  skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
      3, 6, choptreeeffect, NULL);
  skill_t* skill3 = skill_new(1002, PASSIVE, "inner peace", "maintains inner peace",
      4, 7, innerpeace, NULL);
  skill_node_t* bomb_node = skill_node_new(skill1, 0, 75, NULL, 0, 22);
  skill_node_t* chop_node = skill_node_new(skill2, 0, 76, NULL, 0, 19);
  skill_node_t* inner_node = skill_node_new(skill3, 2, 77, NULL, 0, 4);

  skill_tree_t* skilltree = skill_tree_new(1001, "this tree", 3);
  skill_tree_node_add(skilltree, bomb_node);
  skill_tree_node_add(skilltree, chop_node);
  skill_tree_node_add(skilltree, inner_node);

  char *display = display_tree(skilltree, 200);
  char *check = "Skill Name: defuse bomb, Prereq Level: 75, Current Level: 1\nSkill Name: chop tree, Prereq Level: 76, Current Level: 1\nSkill Name: inner peace, Prereq Level: 77, Current Level: 1\n";
  cr_assert_eq(strcmp(check, display), 0, "Error: display_tree_three_skills failed\n");
}

/* Tests display_tree given a skilltree with three skills and a limiting (too small) given buf size */

Test(skilltree_test, display_tree_three_skills_limited)
{ 
  chiventure_ctx_t* ctx = create_player_and_stats();
  item_t* bomb = add_bomb_item(ctx);
  effect_t* defusebombeffect = make_bomb_effect(bomb);
  effect_t* innerpeace = make_innerpeace_effect(ctx);
  item_t* tree = add_chop_item(ctx);
  effect_t* choptreeeffect = make_choptree_effect(tree);
    
  skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, defusebombeffect, NULL);
  skill_t* skill2 = skill_new(1001, ACTIVE, "chop tree", "chops a tree",
      3, 6, choptreeeffect, NULL);
  skill_t* skill3 = skill_new(1002, PASSIVE, "inner peace", "maintains inner peace",
      4, 7, innerpeace, NULL);
  skill_node_t* bomb_node = skill_node_new(skill1, 0, 75, NULL, 0, 22);
  skill_node_t* chop_node = skill_node_new(skill2, 0, 76, NULL, 0, 19);
  skill_node_t* inner_node = skill_node_new(skill3, 2, 77, NULL, 0, 4);

  skill_tree_t* skilltree = skill_tree_new(1001, "this tree", 3);
  skill_tree_node_add(skilltree, bomb_node);
  skill_tree_node_add(skilltree, chop_node);
  skill_tree_node_add(skilltree, inner_node);

  char *display = display_tree(skilltree, 100);
  char *check = "Skill Name: defuse bomb, Prereq Level: 75, Current Level: 1\n";
  cr_assert_eq(strcmp(check, display), 0, "Error: display_tree_three_skills_limited failed\n");
}

/* Tests display_skill_description given a typical skill */

Test(skilltree_test, display_skill_description_typical)
{ 
  chiventure_ctx_t* ctx = create_player_and_stats();
  item_t* bomb = add_bomb_item(ctx);
  effect_t* defusebombeffect = make_bomb_effect(bomb);
    
  skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
      2, 5, defusebombeffect, NULL);
  skill_node_t* bomb_node = skill_node_new(skill1, 0, 75, NULL, 0, 22);

  skill_tree_t* skilltree = skill_tree_new(1001, "this tree", 1);
  skill_tree_node_add(skilltree, bomb_node);

  char *name = "defuse bomb";

  char *display = display_skill_description(skilltree, name);
  char *check = "Skill Description: defuses a bomb\n";
  cr_assert_eq(strcmp(check, display), 0, "Error: display_skill_description_typical failed\n");
}