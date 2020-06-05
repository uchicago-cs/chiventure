/*
 * Skill implementation for chiventure
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "skilltrees/skill.h"

/* See skill.h */
skill_t* skill_new(sid_t sid, skill_type_t type, char* name, char* desc,
                   unsigned int max_level, unsigned int min_xp,
                   skill_effect_t effect) {
    skill_t* skill;
    int rc;

    skill = (skill_t*)malloc(sizeof(skill_t));
    if (skill == NULL) {
        fprintf(stderr, "skill_new: memory allocation failed\n");
        return NULL;
    }

    rc = skill_init(skill, sid, type, name, desc, 1, 0, max_level, min_xp, effect);
    if (rc) {
        fprintf(stderr, "skill_new: initialization failed\n");
        return NULL;
    }

    return skill;
}

/* See skill.h */
int skill_init(skill_t* skill, sid_t sid, skill_type_t type, char* name,
               char* desc, unsigned int level, unsigned int xp,
               unsigned int max_level, unsigned int min_xp,
               skill_effect_t effect) {
    assert(skill != NULL);

    skill->sid = sid;
    skill->type = type;
    skill->name = strdup(name);
    if (skill->name == NULL) {
        fprintf(stderr, "skill_init: name copy failed\n");
        return FAILURE;
    }
    skill->desc = strdup(desc);
    if (skill->desc == NULL) {
        fprintf(stderr, "skill_init: description copy failed\n");
        return FAILURE;
    }
    skill->level = level;
    skill->xp = xp;
    skill->max_level = max_level;
    skill->min_xp = min_xp;
    skill->effect = effect;

    return SUCCESS;
}

/* See skill.h */
int skill_free(skill_t* skill) {
    assert(skill != NULL);

    free(skill->name);
    free(skill->desc);
    free(skill);

    return SUCCESS;
}

/* See skill.h */
char* skill_execute(skill_t* skill, char* args) {
    assert(skill != NULL && args != NULL);

    return (*(skill->effect))(args);
}
