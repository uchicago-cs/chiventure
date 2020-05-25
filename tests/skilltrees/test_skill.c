/*
 * Tests for skill.ch
 */

#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "skilltrees/skill.h"
#include "effect_t.h"

/* Checks the allocation and initialization of a skill */
Test(skill, new) {
    skill_t* skill;

    skill = skill_new(UNLOCK_DOOR, ACTIVE, "Unlock door",
                      "A skill that allows a player to unlock a locked door",
                      &effect_unlock_door);

    cr_assert_not_null(skill, "skill_new() failed to allocate memory");

    cr_assert_eq(skill->sid, UNLOCK_DOOR, "skill_new() didn't set sid");
    cr_assert_eq(skill->type, ACTIVE, "skill_new() didn't set type");
    cr_assert_str_eq(skill->name, "Unlock door", "skill_new() didn't set name");
    cr_assert_str_eq(skill->desc, "A skill that allows a player to unlock a locked door",
                     "skill_new() didn't set description");
    cr_assert_eq(skill->level, 1, "skill_new() didn't set level");
    cr_assert_eq(skill->xp, 0, "skill_new() didn't set xp");
    cr_assert_not_null(skill->effect, "skill_new() didn't set effect");
}

/* Checks the initialization of a skill */
Test(skill, init) {
    skill_t skill;
    int rc;

    rc = skill_init(&skill, UNLOCK_DOOR, ACTIVE, "Unlock door",
                    "A skill that allows a player to unlock a locked door",
                    1, 0, &effect_unlock_door);

    cr_assert_eq(rc, SUCCESS, "skill_init() failed to initialize skill");

    cr_assert_eq(skill.sid, UNLOCK_DOOR, "skill_init() didn't set sid");
    cr_assert_eq(skill.type, ACTIVE, "skill_init() didn't set type");
    cr_assert_str_eq(skill.name, "Unlock door", "skill_init() didn't set name");
    cr_assert_str_eq(skill.desc, "A skill that allows a player to unlock a locked door",
                     "skill_init() didn't set description");
    cr_assert_eq(skill.level, 1, "skill_init() didn't set level");
    cr_assert_eq(skill.xp, 0, "skill_init() didn't set xp");
    cr_assert_not_null(skill.effect, "skill_init() didn't set effect");
}

/* Checks the freeing of a skill */
Test(skill, free) {
    skill_t* skill;
    int rc;

    skill = skill_new(UNLOCK_DOOR, ACTIVE, "Unlock door",
                      "A skill that allows a player to unlock a locked door",
                      &effect_unlock_door);

    cr_assert_not_null(skill, "skill_new() failed");

    rc = skill_free(skill);

    cr_assert_eq(rc, SUCCESS, "skill_free() failed");
}

/* Checks the execution of a skill */
Test(skill, execute) {
    skill_t skill;
    int rc;
    char* consequence;

    rc = skill_init(&skill, UNLOCK_DOOR, ACTIVE, "Unlock door",
                    "A skill that allows a player to unlock a locked door",
                    1, 0, &effect_unlock_door);

    cr_assert_eq(rc, SUCCESS, "skill_init() failed");

    consequence = skill_execute(&skill, "Jackie");

    cr_assert_str_eq(consequence, "Jackie unlocked the door!", "skill_execute() failed");
}
