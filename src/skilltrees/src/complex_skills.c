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

/*See complex_skills.h */
random_chance_type_t* random_chance_new(complex_skill_t* complex_skill, float chance_failure)
{
    random_chance_type_t* random_chance;

    if (chance_failure < 0 || chance_failure > 1)
    {
        fprintf(stderr, "random_chance_new: chance_failure invalid, must be between 0 and 1, inclusive\0");
        return NULL;
    }

    if (complex_skill == NULL)
    {
        fprintf(stderr, "random_chance_new: complex_skill invalid");
        return NULL;
    }

    random_chance = (random_chance_type_t*)malloc(sizeof(random_chance_type_t));

    if (random_chance == NULL) 
    {
        fprintf(stderr, "random_chance_new: memory allocation failed\0");
        return NULL;
    }

    int rc = random_chance_init(random_chance, complex_skill, chance_failure);

    if (rc)
    {
        fprintf(stderr, "random_chance_new: initialization failed\0");
        return NULL;
    }

    return random_chance;
}

/*See complex_skills.h */
int random_chance_init(random_chance_type_t* random_chance_skill, complex_skill_t* complex_skill, float chance_failure)
{
    assert (random_chance_skill != NULL);

    random_chance_skill->complex_skill = complex_skill;
    random_chance_skill->chance_failure = chance_failure;

    return SUCCESS;
}

/*See complex_skills.h */
int random_chance_free(random_chance_type_t* random_chance_skill){
    
    complex_skill_free(random_chance_skill->complex_skill);

    free(random_chance_skill);

    return SUCCESS;
}

/*See complex_skills.h */
random_range_type_t* random_range_new(complex_skill_t* complex_skill, int lower_bound, int upper_bound){
    random_range_type_t* random;

    random = (random_range_type_t*)malloc(sizeof(random_range_type_t));

    if (random == NULL) {
        fprintf(stderr, "random_range_new: memory allocation failed\n");
        return NULL;
    }

    int rc = random_range_init(random, complex_skill, lower_bound, upper_bound);

    if (rc) {
        fprintf(stderr, "random_range_new: initialization failed\n");
        return NULL;
    }

    return random;
}

/*See complex_skills.h */
int random_range_init(random_range_type_t* random_range_skill, complex_skill_t* complex_skill, int lower_bound, int upper_bound){
    assert(random_range_skill != NULL);
    assert(complex_skill != NULL);

    random_range_skill->complex_skill = complex_skill;
    random_range_skill->lower_bound = lower_bound;   
    random_range_skill->upper_bound = upper_bound;

    return SUCCESS;
}

/*See complex_skills.h */
int random_range_free(random_range_type_t* random_range_skill){
    int x = complex_skill_free(random_range_skill->complex_skill);
    if (x != 0){
        fprintf(stderr, "random_range_free: Complex skill freeing failed\n");
        return FAILURE;
    }

    free(random_range_skill);

    return SUCCESS;
}

/*See complex_skills.h */
random_switch_type_t* random_switch_new(complex_skill_t* complex_skill, float* chances){
    random_switch_type_t* random;

   random = (random_switch_type_t*)malloc(sizeof(random_switch_type_t));

    if (random == NULL) {
        fprintf(stderr, "random_switch_new: memory allocation failed for random\n");
        return NULL;
    }

    float* list = (float*)malloc(sizeof(float)*complex_skill->num_skills);
    if (list == NULL) {
        fprintf(stderr, "random_switch_new: memory allocation for chances failed\n");
        return NULL;
    }
    list = chances;
    random->chances = list; 

    int rc = random_switch_init(random, complex_skill, list);

    if (rc != 0) {
        fprintf(stderr, "random_switch_new: initialization failed\n");
        return NULL;
    }

    return random;
}

/*See complex_skills.h */
int random_switch_init(random_switch_type_t* random_switch_skill, complex_skill_t* complex_skill, float* chances){
    assert(random_switch_skill != NULL);
    assert(complex_skill != NULL);
    assert(chances != NULL);

    random_switch_skill->complex_skill = complex_skill;
    random_switch_skill->chances = chances;   

    return SUCCESS;
}

/*See complex_skills.h */
int random_switch_free(random_switch_type_t* random_switch_skill){
    free(random_switch_skill->chances);

    int x = complex_skill_free(random_switch_skill->complex_skill);
    if (x != 0){
        fprintf(stderr, "random_switch_free: Complex skill freeing failed\n");
        return FAILURE;
    }

    free(random_switch_skill);

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
