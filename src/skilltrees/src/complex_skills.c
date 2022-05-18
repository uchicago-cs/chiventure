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
    if(complex_skill->type == COMBINED){
        return combined_complex_skill_execute(complex_skill, ctx);
    }
    if(complex_skill->type == SEQUENTIAL){
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
            if(x == FAILURE){
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