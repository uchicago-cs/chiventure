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

    if (num_skills == 0) {
        fprintf(stderr, "complex_skill_new: max_level is invalid\n");
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
    reader_effect_free(complex_skill->reader);
    free(complex_skill);

    return SUCCESS;
}

/*See complex_skills.h */
int complex_skill_execute(complex_skill_t* complex_skill, chiventure_ctx_t* ctx){
    // if(complex_skill->type == COMBINED){
    //     return combined_skill_execute(complex_skill, ctx);
    // }
    // if(complex_skill->type == SEQUENTIAL){
    //     return sequential_skill_execute(complex_skill, ctx);
    // }
    if(complex_skill->type == COMPLEX_CONDITIONAL){
        return conditional_skill_execute(complex_skill,ctx);
    }
    return FAILURE;
}

/*See complex_skills.h */
reader_effect_t* reader_effect_new(char* condition, int str_len, reader_type_t type)
{

    reader_effect_t* reader;
    int rc;

    if (condition == NULL)
    {
        fprintf(stderr, "reader_effect_new: condition invalid");
        return NULL;
    }

    if (str_len == 0)
    {
        fprintf(stderr, "reader_effect_new: condition invalid");
        return NULL;
    }

    reader = (reader_effect_t*)malloc(sizeof(reader_effect_t));
    rc = reader_effect_init(reader, condition, str_len, type);

    if (rc)
    {
        fprintf(stderr, "reader_effect_new: initialization failed");
        return NULL;
    }

    return reader;
}

/* See complex_hills.h */
int reader_effect_init(reader_effect_t* reader, char* condition, int str_len, reader_type_t type)
{

    assert (reader != NULL);

    reader->condition = condition;
    reader->str_len = str_len;
    reader->type = type;

    return SUCCESS;
}

/* See complex_skills.h */
int reader_effect_free(reader_effect_t* reader)
{
    free(reader);
    return 0;
}

/* See complex_skills.h */
int conditional_skill_execute(complex_skill_t* skill, chiventure_ctx_t* ctx)
{
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