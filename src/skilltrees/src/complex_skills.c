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
        fprintf(stderr, "skill_new: max_level is invalid\n");
        return NULL;
    }

    complex = (complex_skill_t*)malloc(sizeof(complex_skill_t));

    if (skill == NULL) {
        fprintf(stderr, "complex_skill_new: memory allocation failed\n");
        return NULL;
    }

    skill_t** list = (skill_t**)malloc(sizeof(skill_t*)*num_skills);
    complex->skills = list; 

    if (list == NULL) {
        fprintf(stderr, "complex_skill_new: memory allocation for skills failed\n");
        return NULL;
    }

    int rc = complex_skill_init(complex, skills, num_skills);

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

    for(int i = 0; i < num_skills; i++){
        free(complex_skill->skills[i]);
    }
    free(complex_skill->skills);
    free(complex_skill);

    return SUCCESS;
}

/*See complex_skills.h */
int complex_skill_execute(complex_skill_t* complex_skill, chiventure_ctx_t* ctx){
    return FAILURE;
}

/*See complex_skills.h */
int sequential_complex_skill_execute(complex_skill_t* complex_skill, chiventure_ctx_t* ctx){
    return FAILURE;
}