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
complex_skill_t* complex_skill_new(complex_skill_type_t type, skill_t** skills, int num_skills, reader_effect_t* reader){
    complex_skill_t* complex;

    if (num_skills <= 0) {
        fprintf(stderr, "complex_skill_new: subskill length of <= 0 given\n");
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

    int rc = complex_skill_init(complex, type, skills, num_skills, reader);

    if (rc) {
        fprintf(stderr, "complex_skill_new: initialization failed\n");
        return NULL;
    }

    return complex;
}

/*See complex_skills.h */
int complex_skill_init(complex_skill_t* complex_skill, complex_skill_type_t type, 
                       skill_t** skills, int num_skills, reader_effect_t* reader){
    assert(complex_skill != NULL);

    complex_skill->type = type;
    complex_skill->num_skills = num_skills;
    complex_skill->skills = skills;
    complex_skill->reader = reader;

    return SUCCESS;
}

/*See complex_skills.h */
int complex_skill_free(complex_skill_t* complex_skill){
    for(int i = 0; i < complex_skill->num_skills; i++){
        free(complex_skill->skills[i]);
    }
    free(complex_skill->skills);

    //If statement is present to prevent crash from reading NULL reader, which is often
    //used for non-conditional skills
    if(complex_skill->reader != NULL){
        reader_effect_free(complex_skill->reader);
    }
    
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
    if(complex_skill->type == COMPLEX_CONDITIONAL){
        return conditional_skill_execute(complex_skill,ctx);
    }
    return FAILURE;
}


/* See complex_skills.h */
int conditional_skill_execute(complex_skill_t* skill, chiventure_ctx_t* ctx){
    if(skill->type != COMPLEX_CONDITIONAL) {
        return FAILURE; 
    }

    int rc = 1;

    //Following will be implemented when reader_effect_execute is written in sperate issue

    // if(reader_effect_execute(skill->reader, ctx)) {
    //     rc = skill_execute(skill->skills[0], ctx);
    // }
    // else {
    //     rc = skill_execute(skill->skills[1], ctx);
    // }

    return rc;
}

/* See complex_skills.h */
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

//Crashes occuring with tests related to these two functions. To be fixed in later sprint.

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