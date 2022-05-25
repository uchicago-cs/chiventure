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

    complex_skill_t* complex = complex_skill_new(COMBINED, skills, 2);

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

    complex_skill_type_t type = COMBINED;

    complex_skill_t* complex = malloc(sizeof(complex_skill_t));
    complex_skill_init(complex, type, skills, 2);

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

    complex_skill_t* complex = complex_skill_new(COMBINED, skills, 2);
    int ret = complex_skill_free(complex);

    cr_assert_eq(ret, 0, "Error: failed test complex_skill_free_test\n");
}

/*Test complex_skill_execute*/
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

    complex_skill_t* complex = complex_skill_new(COMBINED, skills, 2);

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

    complex_skill_t* complex = complex_skill_new(COMBINED, skills, 2);

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

    complex_skill_t* complex = complex_skill_new(SEQUENTIAL, skills, 2);

    cr_assert_eq(sequential_complex_skill_execute(complex, ctx), 0,
    "Error: failed test skill_new_test on skill->effect\n");
}

//Crash occuring with these tests related to the list of skills, task for future sprint

// /* Tests complex_skill_xp_up when the return value is success */
// Test(skill_test, complex_skill_xp_up_success){
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

//     int xp = 2;
//     complex_skill_t* complex = complex_skill_new(SEQUENTIAL, skills, 2);
//     int x = complex_skill_xp_up(complex, xp);
//     cr_assert_eq(x, 1, "Error: failed test complex_skill_xp_up_success");
//     cr_assert_eq(complex->skills[0]->xp, 7, "Error: failed test complex_skill_xp_up_success for skill 0 incrementing");
//     cr_assert_eq(complex->skills[1]->xp, 7, "Error: failed test complex_skill_xp_up_success for skill 1 incrementing");
// }

// /* Tests complex_skill_xp_up when the return value is failure */
// Test(skill_test, complex_skill_xp_up_failure){
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

//     int xp = 0;

//     complex_skill_t* complex = complex_skill_new(SEQUENTIAL, skills, 2);
//     int x = complex_skill_xp_up(complex, xp);
//     cr_assert_eq(x, 0, "Error: failed test complex_skill_xp_up_failure");
// }



/* Tests complex_skill_level_up when the return value is success */
Test(skill_test, complex_skill_level_up_success){
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);

    skill_t** skills = malloc(sizeof(skill_t*)*2);
    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        2, 5, defusebombeffect, NULL);
    skill_t* skill2 = skill_new(1001, ACTIVE, "defuse bomb 2", "defuses a bomb 2",
        2, 5, defusebombeffect, NULL);
    skills[0] = skill1;
    skills[1] = skill2;

    complex_skill_t* complex = complex_skill_new(SEQUENTIAL, skills, 2);
    int x = complex_skill_level_up(complex);
    cr_assert_eq(x, 0, "Error: failed test complex_skill_level_up_test");
}

/* Tests skill_level_up when return value is failure */
Test(skill_tests, complex_skill_level_up_failure)
{
    chiventure_ctx_t* ctx = create_player_and_stats();
    item_t* bomb = add_bomb_item(ctx);
    effect_t* defusebombeffect = make_bomb_effect(bomb);

    skill_t** skills = malloc(sizeof(skill_t*)*2);
    skill_t* skill1 = skill_new(1000, ACTIVE, "defuse bomb", "defuses a bomb",
        1, 5, defusebombeffect, NULL);
    skill_t* skill2 = skill_new(1001, ACTIVE, "defuse bomb 2", "defuses a bomb 2",
        1, 5, defusebombeffect, NULL);
    skills[0] = skill1;
    skills[1] = skill2;

    complex_skill_t* complex = complex_skill_new(SEQUENTIAL, skills, 2);
    int x = complex_skill_level_up(complex);
    cr_assert_eq(x, 0, "Error: failed test complex_skill_level_up_test");
}

/* Test(random_skills, execute_random_range_failure)
{
    chiventure_ctx_t* ctx = create_player_and_stats();

}
*/


//RANDOM RANGE TESTS

//test for random_range_new
Test(random_range, random_range_new_test){


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
    
    complex_skill_t* random_range_skill = complex_skill_new(RANDOM_RANGE, skills, 2);
    random_range_type_t *range = random_range_new(random_range_skill, 1, 10);

    cr_assert_eq(range->complex_skill->type, RANDOM_RANGE,
        "Error: failed test random_range_new_test on range->random_range->typ\n");
    cr_assert_eq(range->complex_skill->num_skills, 2,
        "Error: failed test random_range_new_test on range->random_range->num_skills\n");
    cr_assert_eq(range->lower_bound, 1,
        "Error: failed test random_range_new_test on lower bound\n");
    cr_assert_eq(range->upper_bound, 10,
        "Error: failed test random_range_new_test on upper bound\n");
}

//test for random_range_init
Test(random_range, random_range_init_test)
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

    complex_skill_t* random_range_skill = complex_skill_new(RANDOM_RANGE, skills, 2);
    random_range_type_t* range = malloc(sizeof(random_range_type_t));
    int lower_b = 1;
    int upper_b = 10;
    random_range_init(range, random_range_skill, lower_b, upper_b);


    cr_assert_eq(range->complex_skill->type, RANDOM_RANGE,
        "Error: failed test random_range_new_test on range->random_range->typ\n");
    cr_assert_eq(range->complex_skill->num_skills, 2,
        "Error: failed test random_range_new_test on range->random_range->num_skills\n");
    cr_assert_eq(range->lower_bound, 1,
        "Error: failed test random_range_new_test on lower bound\n");
    cr_assert_eq(range->upper_bound, 10,
        "Error: failed test random_range_new_test on upper bound\n");   
}

 /** Test complex_skill_free */
Test(random_range, random_range_free_test)
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

    complex_skill_t* random_range = complex_skill_new(RANDOM_RANGE, skills, 2);
    random_range_type_t *range = random_range_new(random_range, 1, 10);

    int ret = random_range_free(range);

    cr_assert_eq(ret, 0, "Error: failed test random_range_free_test\n");
}


//  RANDOM SWITCH TESTS 

//test for random_switch_new with 0.6/0.4
Test(random_switch, random_switch_new_test_uneq)
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
    
    complex_skill_t* random_switch_skill = complex_skill_new(RANDOM_SWITCH, skills, 2);

    float *chances = (float *)malloc(2*sizeof(float)); 
    chances[0] = 0.4;
    chances[1] = 0.6;


    random_switch_type_t *rand_switch = random_switch_new(random_switch_skill, chances);

    cr_assert_eq(rand_switch->complex_skill->type, RANDOM_SWITCH,
        "Error: failed test random_switch_new_test on range->random_range->typ\n");
    cr_assert_float_eq(rand_switch->chances[0], 0.4, 10E-4,
        "Error: failed test random_switch_new_test on first chance\n");
    cr_assert_float_eq(rand_switch->chances[1], 0.6, 10E-4,
        "Error: failed test random_switch_new_test on second chance\n");
}


//test for random_range_init with 0.6/0.4
Test(random_switch, random_switch_init_test_uneq)
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

    complex_skill_t* random_switch_skill = complex_skill_new(RANDOM_SWITCH, skills, 2);
    random_switch_type_t* rand_switch = malloc(sizeof(float) * 2 + sizeof(random_switch_skill) * 4);

    float *chances = (float *)malloc(2*sizeof(float));  
    chances[0] = 0.4;
    chances[1] = 0.6;
    
    random_switch_init(rand_switch, random_switch_skill, chances);


    cr_assert_eq(rand_switch->complex_skill->type, RANDOM_SWITCH,
        "Error: failed test random_range_new_test on range->random_range->type\n");
    cr_assert_eq(rand_switch->complex_skill->num_skills, 2,
        "Error: failed test random_range_new_test on range->random_range->num_skills\n");
    cr_assert_float_eq(rand_switch->chances[0], 0.4, 10E-4,
        "Error: failed test random_switch_new_test on first chance\n");
    cr_assert_float_eq(rand_switch->chances[1], 0.6, 10E-4,
        "Error: failed test random_switch_new_test on second chance\n");    
}

//test for random_switch_new with 0.5/0.5
Test(random_switch, random_switch_new_test_half)
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
    
    complex_skill_t* random_switch_skill = complex_skill_new(RANDOM_SWITCH, skills, 2);

    float *chances = (float *)malloc(2*sizeof(float)); 
    chances[0] = 0.5;
    chances[1] = 0.5;


    random_switch_type_t *rand_switch = random_switch_new(random_switch_skill, chances);

    cr_assert_eq(rand_switch->complex_skill->type, RANDOM_SWITCH,
        "Error: failed test random_switch_new_test on range->random_range->typ\n");
    cr_assert_eq(rand_switch->chances[0], 0.5,
        "Error: failed test random_switch_new_test on first chance\n");
    cr_assert_eq(rand_switch->chances[1], 0.5,
        "Error: failed test random_switch_new_test on second chance\n");
}


//test for random_switch_init with 0.5/0.5
Test(random_switch, random_switch_init_test_half)
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

    complex_skill_t* random_switch_skill = complex_skill_new(RANDOM_SWITCH, skills, 2);
    random_switch_type_t* rand_switch = malloc(sizeof(float) * 2 + sizeof(random_switch_skill) * 4);

    float *chances = (float *)malloc(2*sizeof(float));  
    chances[0] = 0.5;
    chances[1] = 0.5;
    
    random_switch_init(rand_switch, random_switch_skill, chances);


    cr_assert_eq(rand_switch->complex_skill->type, RANDOM_SWITCH,
        "Error: failed test random_switch_new_test on rand_switch->complex_skill->type\n");
    cr_assert_eq(rand_switch->complex_skill->num_skills, 2,
        "Error: failed test random_switch_new_test on rand_switch->complex_skill->num_skills\n");
    cr_assert_eq(rand_switch->chances[0], 0.500000, 
        "Error: failed test random_switch_new_test on first chance\n");
    cr_assert_eq(rand_switch->chances[1], 0.500000,
        "Error: failed test random_switch_new_test on second chance\n");    
}


 /** Test complex_skill_free */
Test(random_switch, random_switch_free_test)
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

    float *chances = (float *)malloc(2*sizeof(float)); 
    chances[0] = 0.4;
    chances[1] = 0.6;

    complex_skill_t* random_switch = complex_skill_new(RANDOM_SWITCH, skills, 2);
    random_switch_type_t *rand_switch = random_switch_new(random_switch, chances);

    int ret = random_switch_free(rand_switch);

    cr_assert_eq(ret, 0, "Error: failed test random_switch_free_test\n");
}



//  RANDOM CHANCE TESTS 

Test(random_chance, random_chance_new_test){


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
    
    complex_skill_t* random_chance_skill = complex_skill_new(RANDOM_CHANCE, skills, 2);
    random_chance_type_t *chance = random_chance_new(random_chance_skill, 0.6);

    cr_assert_eq(chance->complex_skill->type, RANDOM_CHANCE,
        "Error: failed test random_chance_new_test on chance->complex_skill->type\n");
    cr_assert_eq(chance->complex_skill->num_skills, 2,
        "Error: failed test random_chance_new_test on chance->complex_skill->num_skills\n");
    cr_assert_float_eq(chance->chance_failure, 0.6, 10E-4,
        "Error: failed test random_chance_new_test on percentage failure\n");
}


//test for random_chance_init with 0.5
Test(random_chance, random_switch_init_test_half)
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

    complex_skill_t* random_chance_skill = complex_skill_new(RANDOM_CHANCE, skills, 2);
    random_chance_type_t* rand_chance= (random_chance_type_t *)malloc(sizeof(random_chance_type_t));

    
    random_chance_init(rand_chance, random_chance_skill, 0.50);


    cr_assert_eq(rand_chance->complex_skill->type, RANDOM_CHANCE,
        "Error: failed test random_chance_new_test on range->random_range->type\n");
    cr_assert_eq(rand_chance->complex_skill->num_skills, 2,
        "Error: failed test random_chance_new_test on range->random_range->num_skills\n");
    cr_assert_float_eq(rand_chance->chance_failure, 0.50, 10E-4,
        "Error: failed test random_chance_new_test on failure\n");   
}

/** Test complex_skill_free */
Test(random_chance, random_chance_free_test)
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

    complex_skill_t* random_chance = complex_skill_new(RANDOM_CHANCE, skills, 2);
    random_chance_type_t *chance = random_chance_new(random_chance, 0.7);

    int ret = random_chance_free(chance);

    cr_assert_eq(ret, 0, "Error: failed test random_chance_free_test\n");
}
