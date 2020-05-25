/*
 * Tests for inventory.ch
 */

#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "skilltrees/skill.h"
#include "skilltrees/inventory.h"
#include "effect_t.h"

/* Checks the allocation and initialization of a skill inventory */
Test(inventory, new) {
    inventory_t* inventory;

    inventory = inventory_new(5, 7);

    cr_assert_not_null(inventory, "inventory_new() failed to allocate memory");

    cr_assert_not_null(inventory->active, "inventory_new() failed to allocate active skills array");
    cr_assert_eq(inventory->nactive, 0, "inventory_new() failed to set nactive");
    cr_assert_eq(inventory->max_active, 5, "inventory_new() failed to set max_active");
    cr_assert_not_null(inventory->passive, "inventory_new() failed to allocate passive skills array");
    cr_assert_eq(inventory->npassive, 0, "inventory_new() failed to set npassive");
    cr_assert_eq(inventory->max_passive, 7, "inventory_new() failed to set max_passive");
}

/* Checks the freeing of a skill inventory */
Test(inventory, free) {
    inventory_t* inventory;
    int rc;

    inventory = inventory_new(5, 7);

    cr_assert_not_null(inventory, "inventory_new() failed");

    rc = inventory_free(inventory);

    cr_assert_eq(rc, SUCCESS, "inventory_free() failed");
}

/* Checks the addition of a skill to a skill inventory */
Test(inventory, skill_add) {
    skill_t skill1, skill2, skill3, skill4;
    int init1, init2, init3, init4;
    inventory_t* inventory;
    int add1, add2, add3, add4;

    // Initialize the skills
    init1 = skill_init(&skill1, UNLOCK_DOOR, ACTIVE, "Unlock door",
                       "A skill that allows a player to unlock a locked door",
                       1, 0, &effect_unlock_door);
    cr_assert_eq(init1, SUCCESS, "skill_init() failed to initialize skill");

    init2 = skill_init(&skill2, DEFUSE_BOMB, ACTIVE, "Defuse bomb",
                       "A skill that allows a player to defuse a bomb",
                       1, 0, &effect_defuse_bomb);
    cr_assert_eq(init2, SUCCESS, "skill_init() failed to initialize skill");

    init3 = skill_init(&skill3, CHOP_TREE, ACTIVE, "Chop tree",
                       "A skill that allows a player to chop down a tree",
                       1, 0, &effect_chop_tree);
    cr_assert_eq(init3, SUCCESS, "skill_init() failed to initialize skill");

    init4 = skill_init(&skill4, INNER_PEACE, PASSIVE, "Inner peace",
                       "A skill that allows a player to maintain inner peace",
                       1, 0, &effect_inner_peace);
    cr_assert_eq(init4, SUCCESS, "skill_init() failed to initialize skill");

    // Initialize the inventory
    inventory = inventory_new(2, 5);
    cr_assert_not_null(inventory, "inventory_new() failed");

    // Add the skills to the inventory
    add1 = inventory_skill_add(inventory, &skill1);
    cr_assert_eq(add1, SUCCESS, "inventory_skill_add() failed");
    cr_assert_eq(inventory->active[0]->sid, UNLOCK_DOOR, "inventory_skill_add() failed to add active skill");
    cr_assert_eq(inventory->nactive, 1, "inventory_skill_add() failed to update active skill count");

    add2 = inventory_skill_add(inventory, &skill2);
    cr_assert_eq(add2, SUCCESS, "inventory_skill_add() failed");
    cr_assert_eq(inventory->active[1]->sid, DEFUSE_BOMB, "inventory_skill_add() failed to add active skill");
    cr_assert_eq(inventory->nactive, 2, "inventory_skill_add() failed to update active skill count");

    add3 = inventory_skill_add(inventory, &skill3);
    cr_assert_eq(add3, FAILURE, "inventory_skill_add() surpassed max active skills");

    add4 = inventory_skill_add(inventory, &skill4);
    cr_assert_eq(add4, SUCCESS, "inventory_skill_add() failed");
    cr_assert_eq(inventory->passive[0]->sid, INNER_PEACE, "inventory_skill_add() failed to add passive skill");
    cr_assert_eq(inventory->npassive, 1, "inventory_skill_add() failed to update passive skill count");
}

/* Checks the removal of a skill from a skill inventory */
Test(inventory, skill_remove) {
    skill_t skill1, skill2, skill3, skill4;
    int init1, init2, init3, init4;
    inventory_t* inventory;
    int add1, add2, add3, add4;
    int rem1, rem2, rem3, rem4;

    // Initialize the skills
    init1 = skill_init(&skill1, UNLOCK_DOOR, ACTIVE, "Unlock door",
                       "A skill that allows a player to unlock a locked door",
                       1, 0, &effect_unlock_door);
    cr_assert_eq(init1, SUCCESS, "skill_init() failed to initialize skill");

    init2 = skill_init(&skill2, DEFUSE_BOMB, ACTIVE, "Defuse bomb",
                       "A skill that allows a player to defuse a bomb",
                       1, 0, &effect_defuse_bomb);
    cr_assert_eq(init2, SUCCESS, "skill_init() failed to initialize skill");

    init3 = skill_init(&skill3, CHOP_TREE, ACTIVE, "Chop tree",
                       "A skill that allows a player to chop down a tree",
                       1, 0, &effect_chop_tree);
    cr_assert_eq(init3, SUCCESS, "skill_init() failed to initialize skill");

    init4 = skill_init(&skill4, INNER_PEACE, PASSIVE, "Inner peace",
                       "A skill that allows a player to maintain inner peace",
                       1, 0, &effect_inner_peace);
    cr_assert_eq(init4, SUCCESS, "skill_init() failed to initialize skill");

    // Initialize the inventory
    inventory = inventory_new(2, 5);
    cr_assert_not_null(inventory, "inventory_new() failed");

    // Add the skills to the inventory
    add1 = inventory_skill_add(inventory, &skill1);
    cr_assert_eq(add1, SUCCESS, "inventory_skill_add() failed");

    add2 = inventory_skill_add(inventory, &skill2);
    cr_assert_eq(add2, SUCCESS, "inventory_skill_add() failed");

    add4 = inventory_skill_add(inventory, &skill4);
    cr_assert_eq(add4, SUCCESS, "inventory_skill_add() failed");

    // Remove the skills from the inventory
    rem1 = inventory_skill_remove(inventory, &skill1);
    cr_assert_eq(rem1, SUCCESS, "inventory_skill_remove() failed");
    cr_assert_null(inventory->active[1], "inventory_skill_remove() failed to remove active skill");
    cr_assert_eq(inventory->nactive, 1, "inventory_skill_add() failed to update active skill count");

    rem2 = inventory_skill_remove(inventory, &skill2);
    cr_assert_eq(rem2, SUCCESS, "inventory_skill_remove() failed");
    cr_assert_null(inventory->active[0], "inventory_skill_remove() failed to remove active skill");
    cr_assert_eq(inventory->nactive, 0, "inventory_skill_add() failed to update active skill count");

    rem3 = inventory_skill_remove(inventory, &skill3);
    cr_assert_eq(rem3, FAILURE, "inventory_skill_remove() returned a false succcess");

    rem4 = inventory_skill_remove(inventory, &skill4);
    cr_assert_eq(rem4, SUCCESS, "inventory_skill_remove() failed");
    cr_assert_null(inventory->passive[0], "inventory_skill_remove() failed to remove passive skill");
    cr_assert_eq(inventory->npassive, 0, "inventory_skill_add() failed to update passive skill count");
}

/* Checks the search for a skill in a skill inventory */
Test(inventory, has_skill) {
    skill_t skill1, skill2, skill3, skill4;
    int init1, init2, init3, init4;
    inventory_t* inventory;
    int add1, add2, add3, add4;
    int has1, has2, has3;

    // Initialize the skills
    init1 = skill_init(&skill1, UNLOCK_DOOR, ACTIVE, "Unlock door",
                       "A skill that allows a player to unlock a locked door",
                       1, 0, &effect_unlock_door);
    cr_assert_eq(init1, SUCCESS, "skill_init() failed to initialize skill");

    init2 = skill_init(&skill2, DEFUSE_BOMB, ACTIVE, "Defuse bomb",
                       "A skill that allows a player to defuse a bomb",
                       1, 0, &effect_defuse_bomb);
    cr_assert_eq(init2, SUCCESS, "skill_init() failed to initialize skill");

    init3 = skill_init(&skill3, CHOP_TREE, ACTIVE, "Chop tree",
                       "A skill that allows a player to chop down a tree",
                       1, 0, &effect_chop_tree);
    cr_assert_eq(init3, SUCCESS, "skill_init() failed to initialize skill");

    init4 = skill_init(&skill4, INNER_PEACE, PASSIVE, "Inner peace",
                       "A skill that allows a player to maintain inner peace",
                       1, 0, &effect_inner_peace);
    cr_assert_eq(init4, SUCCESS, "skill_init() failed to initialize skill");

    // Initialize the inventory
    inventory = inventory_new(2, 5);
    cr_assert_not_null(inventory, "inventory_new() failed");

    // Add the skills to the inventory
    add1 = inventory_skill_add(inventory, &skill1);
    cr_assert_eq(add1, SUCCESS, "inventory_skill_add() failed");

    add2 = inventory_skill_add(inventory, &skill2);
    cr_assert_eq(add2, SUCCESS, "inventory_skill_add() failed");

    add4 = inventory_skill_add(inventory, &skill4);
    cr_assert_eq(add4, SUCCESS, "inventory_skill_add() failed");

    // Search the inventory for skills
    has1 = inventory_has_skill(inventory, skill4.sid, skill4.type);
    cr_assert_eq(has1, 0, "inventory_has_skill() failed");

    has2 = inventory_has_skill(inventory, skill3.sid, skill3.type);
    cr_assert_eq(has2, -1, "inventory_has_skill() failed");

    has3 = inventory_has_skill(inventory, skill2.sid, skill2.type);
    cr_assert_eq(has3, 1, "inventory_has_skill() failed");
}
