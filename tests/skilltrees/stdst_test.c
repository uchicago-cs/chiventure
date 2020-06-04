#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "skilltrees/skilltree.h"
#include "skilltrees/skill.h"
#include "skilltrees/stdst.h"
#include "skilltrees/inventory.h"
#include "effect_t.h"

/* Tests array_element_add on a valid case. */
Test(stdst_tests, array_element_add_safe)
{
    void** list = malloc(sizeof(void*) * 5);
    list[0] = effect_defuse_bomb("haha");
    list[1] = effect_defuse_bomb("haha");
    list[2] = effect_defuse_bomb("haha");
    list[3] = NULL;
    list[4] = NULL;

    array_element_add(list,5, effect_defuse_bomb("haha"));
    cr_assert_str_eq(list[3],"Bomb defused!", "Error: failed test array_element_add_safe\n");
}

/* Tests array_element_add on a case where array is full. */
Test(stdst_tests, array_element_add_full)
{
    void** list = malloc(sizeof(void*) * 5);
    for(int i = 0; i < 5; i++){
        list[i] = malloc(sizeof(int));
    }
    int* ptr = malloc(sizeof(int));
    void** ret = array_element_add(list, 5, ptr);
    cr_assert_null(ret, "Error: failed test array_element_add_full\n");
}

/* Tests list_has_skill for a skill it does not have. */
Test(stdst_tests, list_has_skill_doesnt)
{
    skill_t** list = malloc(sizeof(skill_t*) * 2);
    for(int i = 0; i < 2; i++){
      skill_t* skill = malloc(sizeof(skill_t));
      if(i == 0){
        skill->sid = 1000;
      }
      else{
        skill->sid = 1001;
      }
      list[i] = skill;
    }

    cr_assert_eq(list_has_skill(list, 2, 1003), -1, "Error: failed test list_has_skill_doesnt\n");
}

/* Tests list_has_skill for a skill it has. */
Test(stdst_tests, list_has_skill_does)
{
    skill_t** list = malloc(sizeof(skill_t*) * 2);
    for(int i = 0; i < 2; i++){
      skill_t* skill = malloc(sizeof(skill_t));
      if(i == 0){
        skill->sid = 1000;
      }
      else{
        skill->sid = 1001;
      }
      list[i] = skill;
    }

    cr_assert_eq(list_has_skill(list, 2, 1000), 0, "Error: failed test list_has_skill_does\n");
    cr_assert_eq(list_has_skill(list, 2, 1001), 1, "Error: failed test list_has_skill_does\n");
}
