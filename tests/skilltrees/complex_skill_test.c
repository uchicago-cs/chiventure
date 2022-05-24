#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "skilltrees/skilltree.h"
#include "skilltrees/skill.h"
#include "skilltrees/complex_skills.h"
#include "skilltrees/skilltrees_common.h"
#include "test_init.h"

/* Test complex_skill_new */
Test(skill_test, complex_skill_new_test)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);

    skill_t** skills = malloc(sizeof(skill_t)*2);
    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect, NULL);
    skill_t* skill2 = skill_new(1001, ACTIVE, "defuse bomb 2", "defuses a bomb 2",
        2, 5, defusebombeffect, NULL);
    skills[0] = skill1;
    skills[1] = skill2;

    complex_skill_t* complex = complex_skill_new(COMBINED, skills, 2, NULL);

    cr_assert_eq(complex->type, COMBINED,
        "Error: failed test complex_skill_new_test on complex->type\n");
    cr_assert_eq(complex->num_skills, 2,
        "Error: failed test complex_skill_new_test on complex->num_skills\n");
}

/* Test complex_skill_init */
Test(skill_test, complex_skill_init_test)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);

    skill_t** skills = malloc(sizeof(skill_t)*2);
    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect, NULL);
    skill_t* skill2 = skill_new(1001, ACTIVE, "defuse bomb 2", "defuses a bomb 2",
        2, 5, defusebombeffect, NULL);
    skills[0] = skill1;
    skills[1] = skill2;

    complex_skill_t* complex = malloc(sizeof(complex_skill_t));
    complex_skill_init(complex, COMBINED, skills, 2, NULL);

    cr_assert_eq(complex->type, COMBINED,
        "Error: failed test complex_skill_new_test on complex->type\n");
    cr_assert_eq(complex->num_skills, 2,
        "Error: failed test complex_skill_new_test on complex->num_skills\n");
    cr_assert_eq(complex->skills[0], skill1,
        "Error: failed test complex_skill_new_test on complex->skills[0]\n");
    cr_assert_eq(complex->skills[1], skill2,
        "Error: failed test complex_skill_new_test on complex->skills[1]\n");
}


/* Test complex_skill_free */
Test(skill_test, complex_skill_free_test)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);

    skill_t** skills = malloc(sizeof(skill_t)*2);
    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect, NULL);
    skill_t* skill2 = skill_new(1001, ACTIVE, "defuse bomb 2", "defuses a bomb 2",
        2, 5, defusebombeffect, NULL);
    skills[0] = skill1;
    skills[1] = skill2;

    complex_skill_t* complex = complex_skill_new(COMBINED, skills, 2, NULL);
    int ret = complex_skill_free(complex);

    cr_assert_eq(ret, 0, "Error: failed test complex_skill_free_test\n");
}

Test(skill_test, complex_skill_execute){
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);

    skill_t** skills = malloc(sizeof(skill_t)*2);
    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect, NULL);
    skill_t* skill2 = skill_new(1001, ACTIVE, "defuse bomb 2", "defuses a bomb 2",
        2, 5, defusebombeffect, NULL);
    skills[0] = skill1;
    skills[1] = skill2;

    complex_skill_t* complex = complex_skill_new(COMBINED, skills, 2, NULL);

    cr_assert_eq(complex_skill_execute(complex, ctx), 0,
    "Error: failed test skill_new_test on skill->effect\n");
}

/* Test combined_complex_skill_execute */
Test(skill_test, combined_complex_skill_execute){
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);

    skill_t** skills = malloc(sizeof(skill_t)*2);
    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect, NULL);
    skill_t* skill2 = skill_new(1001, ACTIVE, "defuse bomb 2", "defuses a bomb 2",
        2, 5, defusebombeffect, NULL);
    skills[0] = skill1;
    skills[1] = skill2;

    complex_skill_t* complex = complex_skill_new(COMBINED, skills, 2, NULL);

    cr_assert_eq(combined_complex_skill_execute(complex, ctx), 0,
    "Error: failed test skill_new_test on skill->effect\n");
}

/*Test sequential_skill_execute*/
Test(skill_test, sequential_complex_skill_execute){
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);

    skill_t** skills = malloc(sizeof(skill_t)*2);
    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect, NULL);
    skill_t* skill2 = skill_new(1001, ACTIVE, "defuse bomb 2", "defuses a bomb 2",
        2, 5, defusebombeffect, NULL);
    skills[0] = skill1;
    skills[1] = skill2;

    complex_skill_t* complex = complex_skill_new(SEQUENTIAL, skills, 2, NULL);

    cr_assert_eq(sequential_complex_skill_execute(complex, ctx), 0,
    "Error: failed test skill_new_test on skill->effect\n");
}

//Following tests won't work until reader is implemented

/*Test conditional_skill_execute*/
// Test(skill_test, conditonal_skill_execute){
//     int xp = 2;
//     complex_skill_t* complex = complex_skill_new(SEQUENTIAL, skills, 2);
//     int x = complex_skill_xp_up(complex, xp);
//     cr_assert_eq(x, 1, "Error: failed test complex_skill_xp_up_success");
//     cr_assert_eq(complex->skills[0]->xp, 7, "Error: failed test complex_skill_xp_up_success for skill 0 incrementing");
//     cr_assert_eq(complex->skills[1]->xp, 7, "Error: failed test complex_skill_xp_up_success for skill 1 incrementing");
// }

//Crash occuring with these tests related to the list of skills, task for future sprint

// /* Tests complex_skill_level_up when the return value is success */
// Test(skill_test, complex_skill_level_up_success){
//     chiventure_ctx_t* ctx = create_player_and_stats();
//     item_t* bomb = add_bomb_item(ctx);
//     effect_t* defusebombeffect = make_bomb_effect(bomb);

//     skill_t** skills = malloc(sizeof(skill_t*)*2);
//     skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
//         2, 5, defusebombeffect, NULL);
//     skill_t* skill2 = skill_new(1001, ACTIVE, "defuse bomb 2", "defuses a bomb 2",
//         2, 5, defusebombeffect, NULL);
//     skills[0] = skill1;
//     skills[1] = skill2;

//     complex_skill_t* complex = complex_skill_new(SEQUENTIAL, skills, 2, NULL);
//     int x = complex_skill_level_up(complex);
//     cr_assert_eq(x, 0, "Error: failed test complex_skill_level_up_test");
// }

// /* Tests skill_level_up when return value is failure */
// Test(skill_tests, complex_skill_level_up_failure)
// {
//     chiventure_ctx_t* ctx = create_player_and_stats();
//     item_t* bomb = add_bomb_item(ctx);
//     effect_t* defusebombeffect = make_bomb_effect(bomb);

//     skill_t** skills = malloc(sizeof(skill_t*)*2);
//     skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
//         1, 5, defusebombeffect, NULL);
//     skill_t* skill2 = skill_new(1001, ACTIVE, "defuse bomb 2", "defuses a bomb 2",
//         1, 5, defusebombeffect, NULL);
//     skills[0] = skill1;
//     skills[1] = skill2;

//     complex_skill_t* complex = complex_skill_new(SEQUENTIAL, skills, 2, NULL);
//     int x = complex_skill_level_up(complex);
//     cr_assert_eq(x, 0, "Error: failed test complex_skill_level_up_test");
// }
