/*
 * Tests for skilltree.ch
 */

#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "skilltrees/skill.h"
#include "skilltrees/inventory.h"
#include "skilltrees/skilltree.h"
#include "effect_t.h"

Test(skilltree, branch_new) {
    branch_t* branch;

    branch = branch_new(UNLOCK_DOOR, 0, 10, 100);

    cr_assert_not_null(branch, "branch_new() failed to allocate memory");

    cr_assert_eq(branch->sid, UNLOCK_DOOR, "branch_new() didn't set sid");
    cr_assert_not_null(branch->prereqs, "branch_new() didn't allocate prereqs array");
    cr_assert_eq(branch->nprereqs, 0, "branch_new() didn't set nprereqs");
    cr_assert_eq(branch->max_level, 10, "branch_new() didn't set max_level");
    cr_assert_eq(branch->min_xp, 100, "branch_new() didn't set min_xp");
}

Test(skilltree, branch_free) {
    branch_t* branch;
    int rc;

    branch = branch_new(UNLOCK_DOOR, 0, 10, 100);

    cr_assert_not_null(branch, "branch_new() failed to allocate memory");

    rc = branch_free(branch);

    cr_assert_eq(rc, SUCCESS, "branch_free() failed");
}

Test(skilltree, branch_prereq_add) {
    skill_t skill1, skill2, skill3;
    int init1, init2, init3;
    branch_t* branch;
    int add1, add2, add3;

    // Initialize the skills
    init1 = skill_init(&skill1, UNLOCK_DOOR, ACTIVE, "Unlock door",
                       "A skill that allows a player to unlock a locked door",
                       1, 0, &effect_unlock_door);
    cr_assert_eq(init1, SUCCESS, "skill_init() failed to initialize skill");

    init2 = skill_init(&skill2, DEFUSE_BOMB, ACTIVE, "Defuse bomb",
                       "A skill that allows a player to defuse a bomb",
                       1, 0, &effect_defuse_bomb);
    cr_assert_eq(init2, SUCCESS, "skill_init() failed to initialize skill");

    init3 = skill_init(&skill3, INNER_PEACE, PASSIVE, "Inner peace",
                       "A skill that allows a player to maintain inner peace",
                       1, 0, &effect_inner_peace);
    cr_assert_eq(init3, SUCCESS, "skill_init() failed to initialize skill");

    // Initialize the skill branch
    branch = branch_new(CHOP_TREE, 2, 10, 100);
    cr_assert_not_null(branch, "branch_new() failed to allocate memory");

    // Add the prerequisites to the skill branch
    add1 = branch_prereq_add(branch, &skill1);
    cr_assert_eq(add1, SUCCESS, "branch_prereq_add() failed");
    cr_assert_eq(branch->prereqs[0]->sid, UNLOCK_DOOR, "branch_prereq_add() failed to add prereq");

    add2 = branch_prereq_add(branch, &skill2);
    cr_assert_eq(add2, SUCCESS, "branch_prereq_add() failed");
    cr_assert_eq(branch->prereqs[1]->sid, DEFUSE_BOMB, "branch_prereq_add() failed to add prereq");

    add3 = branch_prereq_add(branch, &skill3);
    cr_assert_eq(add3, FAILURE, "branch_prereq_add() surpassed nprereqs");
}

Test(skilltree, branch_prereq_remove) {
    skill_t skill1, skill2, skill3;
    int init1, init2, init3;
    branch_t* branch;
    int add1, add2, add3;
    int rem1, rem2, rem3;

    // Initialize the skills
    init1 = skill_init(&skill1, UNLOCK_DOOR, ACTIVE, "Unlock door",
                       "A skill that allows a player to unlock a locked door",
                       1, 0, &effect_unlock_door);
    cr_assert_eq(init1, SUCCESS, "skill_init() failed to initialize skill");

    init2 = skill_init(&skill2, DEFUSE_BOMB, ACTIVE, "Defuse bomb",
                       "A skill that allows a player to defuse a bomb",
                       1, 0, &effect_defuse_bomb);
    cr_assert_eq(init2, SUCCESS, "skill_init() failed to initialize skill");

    init3 = skill_init(&skill3, INNER_PEACE, PASSIVE, "Inner peace",
                       "A skill that allows a player to maintain inner peace",
                       1, 0, &effect_inner_peace);
    cr_assert_eq(init3, SUCCESS, "skill_init() failed to initialize skill");

    // Initialize the skill branch
    branch = branch_new(CHOP_TREE, 2, 10, 100);
    cr_assert_not_null(branch, "branch_new() failed to allocate memory");

    // Add the prerequisites to the skill branch
    add1 = branch_prereq_add(branch, &skill1);
    cr_assert_eq(add1, SUCCESS, "branch_prereq_add() failed");

    add2 = branch_prereq_add(branch, &skill2);
    cr_assert_eq(add2, SUCCESS, "branch_prereq_add() failed");

    // Remove the prerequisites from the skill branch
    rem1 = branch_prereq_remove(branch, &skill1);
    cr_assert_eq(rem1, SUCCESS, "branch_prereq_remove() failed");
    cr_assert_null(branch->prereqs[0], "branch_prereq_remove() failed to remove prereq");

    rem2 = branch_prereq_remove(branch, &skill2);
    cr_assert_eq(rem2, SUCCESS, "branch_prereq_remove() failed");
    cr_assert_null(branch->prereqs[1], "branch_prereq_remove() failed to remove prereq");

    rem3 = branch_prereq_remove(branch, &skill3);
    cr_assert_eq(rem3, FAILURE, "branch_prereq_remove() returned a false success");
}

Test(skilltree, tree_new) {
    tree_t* tree;

    tree = tree_new(HEALTH, 5);

    cr_assert_not_null(tree, "tree_new() failed to allocate memory");

    cr_assert_eq(tree->tid, HEALTH, "tree_new() didn't set tid");
    cr_assert_not_null(tree->branches, "tree_new() didn't allocate branches array");
    cr_assert_eq(tree->nbranches, 5, "tree_new() didn't set nbranches");
}

Test(skilltree, tree_free) {
    tree_t* tree;
    int rc;

    tree = tree_new(HEALTH, 5);

    cr_assert_not_null(tree, "tree_new() failed to allocate memory");

    rc = tree_free(tree);

    cr_assert_eq(rc, SUCCESS, "tree_free() failed");
}

Test(skilltree, tree_branch_add) {
    branch_t *branch1, *branch2, *branch3;
    tree_t* tree;
    int add1, add2, add3;

    // Initialize the branches
    branch1 = branch_new(UNLOCK_DOOR, 0, 10, 100);
    cr_assert_not_null(branch1, "branch_new() failed to allocate memory");

    branch2 = branch_new(DEFUSE_BOMB, 0, 10, 100);
    cr_assert_not_null(branch2, "branch_new() failed to allocate memory");

    branch3 = branch_new(CHOP_TREE, 0, 10, 100);
    cr_assert_not_null(branch3, "branch_new() failed to allocate memory");

    // Initialize the tree
    tree = tree_new(HEALTH, 2);
    cr_assert_not_null(tree, "tree_new() failed to allocate memory");

    // Add the branches to the tree
    add1 = tree_branch_add(tree, branch1);
    cr_assert_eq(add1, SUCCESS, "tree_branch_add() failed");
    cr_assert_eq(tree->branches[0]->sid, UNLOCK_DOOR, "tree_branch_add() failed to add branch");

    add2 = tree_branch_add(tree, branch2);
    cr_assert_eq(add2, SUCCESS, "tree_branch_add() failed");
    cr_assert_eq(tree->branches[1]->sid, DEFUSE_BOMB, "tree_branch_add() failed to add branch");

    add3 = tree_branch_add(tree, branch3);
    cr_assert_eq(add3, FAILURE, "tree_branch_add() failed");
}

Test(skilltree, tree_branch_remove) {
    branch_t *branch1, *branch2, *branch3;
    tree_t* tree;
    int add1, add2, add3;
    int rem1, rem2, rem3;

    // Initialize the branches
    branch1 = branch_new(UNLOCK_DOOR, 0, 10, 100);
    cr_assert_not_null(branch1, "branch_new() failed to allocate memory");

    branch2 = branch_new(DEFUSE_BOMB, 0, 10, 100);
    cr_assert_not_null(branch2, "branch_new() failed to allocate memory");

    branch3 = branch_new(CHOP_TREE, 0, 10, 100);
    cr_assert_not_null(branch3, "branch_new() failed to allocate memory");

    // Initialize the tree
    tree = tree_new(HEALTH, 2);
    cr_assert_not_null(tree, "tree_new() failed to allocate memory");

    // Add the branches to the tree
    add1 = tree_branch_add(tree, branch1);
    cr_assert_eq(add1, SUCCESS, "tree_branch_add() failed");
    cr_assert_eq(tree->branches[0]->sid, UNLOCK_DOOR, "tree_branch_add() failed to add branch");

    add2 = tree_branch_add(tree, branch2);
    cr_assert_eq(add2, SUCCESS, "tree_branch_add() failed");
    cr_assert_eq(tree->branches[1]->sid, DEFUSE_BOMB, "tree_branch_add() failed to add branch");

    // Remove the branches from the tree
    rem1 = tree_branch_remove(tree, branch1);
    cr_assert_eq(rem1, SUCCESS, "tree_branch_remove() failed");
    cr_assert_null(tree->branches[0], "tree_branch_remove() failed to remove branch");

    rem2 = tree_branch_remove(tree, branch2);
    cr_assert_eq(rem2, SUCCESS, "tree_branch_remove() failed");
    cr_assert_null(tree->branches[1], "tree_branch_remove() failed to remove branch");

    rem3 = tree_branch_remove(tree, branch3);
    cr_assert_eq(rem3, FAILURE, "tree_branch_remove() failed");
}

Test(skilltree, tree_has_branch) {
    branch_t *branch1, *branch2, *branch3;
    tree_t* tree;
    int add1, add2, add3;
    int has1, has2, has3;

    // Initialize the branches
    branch1 = branch_new(UNLOCK_DOOR, 0, 10, 100);
    cr_assert_not_null(branch1, "branch_new() failed to allocate memory");

    branch2 = branch_new(DEFUSE_BOMB, 0, 10, 100);
    cr_assert_not_null(branch2, "branch_new() failed to allocate memory");

    branch3 = branch_new(CHOP_TREE, 0, 10, 100);
    cr_assert_not_null(branch3, "branch_new() failed to allocate memory");

    // Initialize the tree
    tree = tree_new(HEALTH, 2);
    cr_assert_not_null(tree, "tree_new() failed to allocate memory");

    // Add the branches to the tree
    add1 = tree_branch_add(tree, branch1);
    cr_assert_eq(add1, SUCCESS, "tree_branch_add() failed");
    cr_assert_eq(tree->branches[0]->sid, UNLOCK_DOOR, "tree_branch_add() failed to add branch");

    add2 = tree_branch_add(tree, branch2);
    cr_assert_eq(add2, SUCCESS, "tree_branch_add() failed");
    cr_assert_eq(tree->branches[1]->sid, DEFUSE_BOMB, "tree_branch_add() failed to add branch");

    // Search the tree for branches
    has1 = tree_has_branch(tree, branch1->sid);
    cr_assert_eq(has1, 0, "tree_has_branch() failed");

    has2 = tree_has_branch(tree, branch2->sid);
    cr_assert_eq(has2, 1, "tree_has_branch() failed");

    has3 = tree_has_branch(tree, branch3->sid);
    cr_assert_eq(has3, -1, "tree_has_branch() failed");
}
