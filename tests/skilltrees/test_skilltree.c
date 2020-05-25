/*
 * Tests for skilltree.ch
 */

#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
    cr_assert_null(branch->prereqs[0], "branch_prereq_remove() failed to remove prereq")

    rem2 = branch_prereq_remove(branch, &skill2);
    cr_assert_eq(rem2, SUCCESS, "branch_prereq_remove() failed");
    cr_assert_null(branch->prereqs[1], "branch_prereq_remove() failed to remove prereq")

    rem3 = branch_prereq_remove(branch, &skill3);
    cr_assert_eq(rem3, FAILURE, "branch_prereq_remove() returned a false success");
}
