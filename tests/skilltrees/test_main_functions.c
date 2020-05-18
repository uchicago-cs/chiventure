#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "skilltrees/skilltrees.h"

// Checks that create_skill_list correctly creates an empty list of active
// and passive skills.
Test(skilltrees_main_functions, create_skill_list)
{
    allskills_t* skill_list = create_skill_list();
    cr_assert_not_null(skill_list,
                       "create_skill_list() failed: null skill_list");

    cr_assert_eq(skill_list->cur_num_active, 0,
                 "create_skill_list didn't set cur_num_active correctly.");
    cr_assert_eq(skill_list->cur_num_passive, 0,
              "create_skill_list didn't set cur_num_passive correctly.");
    cr_assert_eq(skill_list->max_num_active, 5,
               "create_skill_list didn't set max_num_active correctly.");
    cr_assert_eq(skill_list->max_num_active, 5,
                "create_skill_list didn't set max_num_passive correctly.");


    for (int i = 0; i < 5; i++) {
        cr_assert_null(skill_list->active_skills[i],
                       "Active skill %d is not null", i);
        cr_assert_null(skill_list->passive_skills[i],
                       "Passive skill %d is not null", i);
    }
}


// This is a dummy skill used to test pointer functions for skills.
int test_skill(int param1, int param2) {
    return param1 + param2;
}


// This is a helper function which creates a dummy skill for tests.
skill_t* create_dummy_skill()
{
    // Abstract parameters going into new_skill
    char name[50] = "fireball";
    char description[100] = "shoots fire but, like, super fast.";
    unsigned int cur_level = 0;
    unsigned int experience = 10;
    int (*skill_func)(int param1, int param2) = &test_skill;

    skill_t* skill = new_skill(name, cur_level, experience,
                               description, skill_func);
    return skill;
}


// Checks that new_skill correctly creates a new skill struct.
Test(skilltrees_main_functions, new_skill)
{
    skill_t* skill = create_dummy_skill();
    cr_assert_not_null(skill, "new_skill() failed: null skill");

    cr_assert_str_eq("fireball", skill->name,
                     "new_skill() failed at creating the name.");
    cr_assert_str_eq("shoots fire but, like, super fast.", skill->description,
                     "new_skill() failed at creating the description.");
    cr_assert_eq(0, skill->cur_level,
                 "new_skill() failed at creating the current level.");
    cr_assert_eq(10, skill->experience,
                 "new_skill() failed at creating the experience parameter.");
    cr_assert_eq(6, skill->execute_skill(2, 4),
                 "new_skill() failed when testing the function pointer.");
}

// Checks that free_skill correctly frees a skill struct.
Test(skilltrees_main_functions, free_skill)
{
    skill_t* skill = create_dummy_skill();

    cr_assert_not_null(skill, "new_skill() failed");

    int rc = free_skill(skill);

    cr_assert_eq(rc, 0, "free_skill() failed");
}

// Checks that allskills_t can be freed correctly, but through the
// individual functions free_passive_skills and free_active_skills().
Test(skilltrees_main_functions, free_skill_lists_manually)
{
    allskills_t* skill_list = create_skill_list();
    cr_assert_not_null(skill_list, "create_skill_list() failed");

    int rc = free_passive_skills(skill_list);
    int rc2 = free_active_skills(skill_list);

    cr_assert_eq(rc, 0, "free_passive_skills() failed.");
    cr_assert_eq(rc2, 0, "free_active_skills() failed.");
}


// Checks that allskills_t can be freed correctly, now with the function
// free_all_skills.
Test(skilltrees_main_functions, free_all_skills)
{
    allskills_t* skill_list = create_skill_list();
    cr_assert_not_null(skill_list, "create_skill_list() failed");

    int rc = free_all_skills(skill_list);

    cr_assert_eq(rc, 0, "free_all_skills() failed.");
}
