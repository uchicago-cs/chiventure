/*
 * Complex Skill implementation for chiventure
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "skilltrees/skill.h"
#include "skilltrees/complex_skills.h"

/*See complex_skills.h */
complex_skill_t* complex_skill_new(complex_skill_type_t type, skill_t** skills, int num_skills){
    complex_skill_t* complex;

    if (num_skills == 0) {
        fprintf(stderr, "skill_new: num_skills is invalid (given 0)\n");
        return NULL;
    }

    complex = (complex_skill_t*)malloc(sizeof(complex_skill_t));

    if (complex == NULL) {
        fprintf(stderr, "complex_skill_new: memory allocation failed\n");
        return NULL;
    }

    skill_t** list = (skill_t**)malloc(sizeof(skill_t*)*num_skills);
    complex->skills = list; 

    if (list == NULL) {
        fprintf(stderr, "complex_skill_new: memory allocation for skills failed\n");
        return NULL;
    }

    int rc = complex_skill_init(complex, type, list, num_skills);

    if (rc) {
        fprintf(stderr, "complex_skill_new: initialization failed\n");
        return NULL;
    }

    return complex;
}

/*See complex_skills.h */
int complex_skill_init(complex_skill_t* complex_skill, complex_skill_type_t type, skill_t** skills, int num_skills){
    assert(complex_skill != NULL);

    complex_skill->type = type;
    complex_skill->num_skills = num_skills;
    complex_skill->skills = skills;

    return SUCCESS;
}

/*See complex_skills.h */
int complex_skill_free(complex_skill_t* complex_skill){

    for(int i = 0; i < complex_skill->num_skills; i++){
        free(complex_skill->skills[i]);
    }
    free(complex_skill->skills);
    free(complex_skill);

    return SUCCESS;
}

/*See complex_skills.h */
int complex_skill_execute(complex_skill_t* complex_skill, chiventure_ctx_t* ctx){
    if (complex_skill->type == COMBINED){
        return combined_complex_skill_execute(complex_skill, ctx);
    }
    if (complex_skill->type == SEQUENTIAL){
        return sequential_complex_skill_execute(complex_skill, ctx);
    }
    return FAILURE;
}

/*See complex_skills.h */
int combined_complex_skill_execute(complex_skill_t* complex_skill, chiventure_ctx_t* ctx){
    if(complex_skill->type != COMBINED){
        return FAILURE;
    }
    
    //Attempt to execute each skill, regardless of failure or not.
    for(int i = 0; i < complex_skill->num_skills; i++){
        skill_execute(complex_skill->skills[i], ctx);
    }
    return SUCCESS;
}

/*See complex_skills.h */
int sequential_complex_skill_execute(complex_skill_t* complex_skill, chiventure_ctx_t* ctx){
    if(complex_skill->type != SEQUENTIAL){
        return FAILURE;
    }

    // Stop execution once a sub_skill fails
    for(int i = 0; i < complex_skill->num_skills; i++){
        if (skill_execute(complex_skill->skills[i], ctx) == FAILURE){
            break;
        }
        skill_execute(complex_skill->skills[i], ctx);
    }
    return SUCCESS;
}

/*See complex_skills.h */
int complex_skill_level_up(complex_skill_t* complex_skill){
    assert(complex_skill != NULL);
    
    int x;
    for (int i = 0; i < complex_skill->num_skills; i++){
        x = skill_level_up(complex_skill->skills[i]);
        if (x == FAILURE){
            return FAILURE;
        }
    }
    return SUCCESS;
}

/*See complex_skills.h */
int complex_skill_xp_up(complex_skill_t* complex_skill, unsigned int xp_gained){
    assert(complex_skill != NULL);
    int x;

    for (int i = 0; i < complex_skill->num_skills; i++){
        x = skill_xp_up(complex_skill->skills[i], xp_gained);
        if(x == FAILURE){
            return FAILURE;
        }
    }
    return SUCCESS;
}

/* Takes in a lower and upper value and generates random number within that 
*  range, helper function for the range execution function
*  Written with help of https://www.geeksforgeeks.org/generating-random-number-range-c/
*  
*  Please note that while the rand() function will work for now, this function 
*  could be improved in the future by using a third-party library for random 
*  number generation
*
*  Parameters:
* - lower_bound: the lower bound of the possible generated value
* - upper_bound: the upper bound of the possible generated value
*
* Returns;
* - int: the number randomly generated between the given bounds.
*        must be an integer since it is used to execute skill a certain amount 
*        of times.
*/
int random_int_generator(int lower_bound, int upper_bound){
    return ((rand() % (upper_bound - lower_bound + 1)) + lower_bound);
}

/* Takes in an upper value and generates random float within the range of 0 to 
*  the upper value, helper function for the chance and switch execution functions
*  Written with help of https://stackoverflow.com/questions/13408990/how-to-generate-random-float-number-in-c
*  
*  Please note that while the rand() function will work for now, this function 
*  could be improved in the future by using a third-party library for random 
*  number generation
*
*  Parameters:
* - upper_bound: the upper bound of the possible generated value
*
* Returns;
* - float: the float randomly generated between 0 and the given bound inclusive
*/
float random_float_generator(float upper_bound){
    return (float)rand()/(float)(RAND_MAX/upper_bound);
}

/*See complex_skills.h */
int execute_random_chance_complex_skill(random_chance_type_t* chance_skill, chiventure_ctx_t* ctx){
    if (chance_skill->complex_skill->type != RANDOM_CHANCE){
        return FAILURE;
    }

    int value = random_float_generator(100.0);
    if (value < (chance_skill->chance_failure * 100)){
        for (int i= 0; i < chance_skill->complex_skill->num_skills; i++){
            skill_execute(chance_skill->complex_skill->skills[i], ctx);
        }
    }
    return SUCCESS;
}

/*See complex_skills.h */
int execute_random_range_complex_skill(random_range_type_t* range_skill, chiventure_ctx_t* ctx){
    if (range_skill->complex_skill->type != RANDOM_RANGE){
        return FAILURE;
    }

    int value = random_int_generator(range_skill->lower_bound, range_skill->upper_bound);
    for (int j = 0; j < value; j++){
        for (int i= 0; i < range_skill->complex_skill->num_skills; i++){
            skill_execute(range_skill->complex_skill->skills[i], ctx);
        }
    }

    return SUCCESS;
}

/*See complex_skills.h */
int execute_random_switch_complex_skill(random_switch_type_t* switch_skill, chiventure_ctx_t* ctx){
    if (switch_skill->complex_skill->type != RANDOM_SWITCH){
        return FAILURE;
    }

    if (switch_skill->chances != NULL){
        return FAILURE;
    }

    float total = 0;
    for (int i = 0; i < switch_skill->complex_skill->num_skills; i++){
        total += switch_skill->chances[i];
    }

    int value = random_float_generator(total);

    // Check for first skill
    if (value < switch_skill->chances[0]){
        skill_execute(switch_skill->complex_skill->skills[0], ctx);
        return SUCCESS;
    }

    // Check subsequent skills
    float running_total = switch_skill->chances[0];
    for (int i = 1; i < switch_skill->complex_skill->num_skills; i++){
        if ((value >= running_total) && (value < (running_total + switch_skill->chances[i]))){
            skill_execute(switch_skill->complex_skill->skills[i], ctx);
            return SUCCESS;
        }
        running_total += switch_skill->chances[i];
    }

    return SUCCESS;
}
