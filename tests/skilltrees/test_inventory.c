/*
 * Tests for inventory.ch
 */

#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "skilltrees/inventory.h"

/* Example skill effect function */
char* effect_unlock_door(char* args) {
    char* s = strdup(args);
    char* msg = "unlocked the door!";
    unsigned int rlen = strlen(s) + strlen(msg) + 2;
    char* res = (char*)malloc(sizeof(char) * rlen);
    sprintf(res, "%s %s", s, msg);
    return res;
}

char* effect_defuse_bomb(char* args) {
    return "Bomb defused!";
}

char* effect_chop_tree(char* args) {
    return "Tree chopped!";
}

char* effect_inner_peace(char* args) {
    return "Maintaining inner peace.";
}

Test(inventory, new) {
    inventory_t* inventory;

    inventory = inventory_new(5, 5);

    cr_assert_not_null(inventory, "inventory_new() failed");
}

Test(inventory, free) {
    inventory_t* inventory;
    int rc;

    inventory = inventory_new(5, 5);

    cr_assert_not_null(inventory, "inventory_new() failed");

    rc = inventory_free(inventory);

    cr_assert_eq(rc, SUCCESS, "inventory_free() failed");
}

Test(inventory, add_has_remove) {
    skill_t skill1, skill2, skill3, skill4;
    int init1, init2, init3, init4;
    int add1, add2, add3, add4;
    int has1, has2, has3;
    int rem1, rem2, rem3, rem4;

    init1 = skill_init(&skill1, UNLOCK_DOOR, ACTIVE, "Unlock door",
                    "A skill that allows a player to unlock a locked door",
                    1, 0, &effect_unlock_door);
    cr_assert_eq(init1, SUCCESS, "skill_init() failed");
    init2 = skill_init(&skill2, DEFUSE_BOMB, ACTIVE, "Defuse bomb",
                    "A skill that allows a player to defuse a bomb",
                    1, 0, &effect_defuse_bomb);
    cr_assert_eq(init2, SUCCESS, "skill_init() failed");
    init3 = skill_init(&skill3, CHOP_TREE, ACTIVE, "Chop tree",
                    "A skill that allows a player to chop a tree down",
                    1, 0, &effect_chop_tree);
    cr_assert_eq(init3, SUCCESS, "skill_init() failed");
    init4 = skill_init(&skill4, INNER_PEACE, PASSIVE, "Inner peace",
                    "A skill that allows a player to maintain inner peace",
                    1, 0, &effect_inner_peace);
    cr_assert_eq(init4, SUCCESS, "skill_init() failed");

    inventory* inventory = inventory_new(2, 5);
    cr_assert_not_null(inventory, "inventory_new() failed");

    add1 = inventory_skill_add(inventory, &skill1);
    cr_assert_eq(add1, SUCCESS, "inventory_skill_add() failed");
    cr_assert_eq(inventory->active[0].sid, UNLOCK_DOOR, "inventory_skill_add() failed");

    add2 = inventory_skill_add(inventory, &skill2);
    cr_assert_eq(add2, SUCCESS, "inventory_skill_add() failed");
    cr_assert_eq(inventory->active[1].sid, DEFUSE_BOMB, "inventory_skill_add() failed");

    add3 = inventory_skill_add(inventory, &skill3);
    cr_assert_eq(add3, FAILURE, "inventory_skill_add() failed");

    add4 = inventory_skill_add(inventory, &skill4);
    cr_assert_eq(add4, SUCCESS, "inventory_skill_add() failed");
    cr_assert_eq(inventory->passive[0].sid, INNER_PEACE, "inventory_skill_add() failed");

    has1 = inventory_has_skill(inventory, &skill4);
    cr_assert_eq(has1, 0, "inventory_has_skill() failed");

    has2 = inventory_has_skill(inventory, &skill3);
    cr_assert_eq(has2, -1, "inventory_has_skill() failed");

    has3 = inventory_has_skill(inventory, &skill2);
    cr_assert_eq(has3, 1, "inventory_has_skill() failed");

    rem1 = inventory_skill_remove(inventory, &skill1);
    cr_assert_eq(rem1, SUCCESS, "inventory_skill_remove() failed");

    rem2 = inventory_skill_remove(inventory, &skill2);
    cr_assert_eq(rem2, SUCCESS, "inventory_skill_remove() failed");

    rem3 = inventory_skill_remove(inventory, &skill3);
    cr_assert_eq(rem3, FAILURE, "inventory_skill_remove() failed");

    rem4 = inventory_skill_remove(inventory, &skill4);
    cr_assert_eq(rem4, SUCCESS, "inventory_skill_remove() failed");
}
