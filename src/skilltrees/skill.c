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
                   effect_t effect) {
    skill_t* skill;
    int rc;

    skill = (skill_t*)malloc(sizeof(skill_t));
    if (skill == NULL) {
        fprintf(stderr, "skill_new: could not allocate memory\n");
        return NULL;
    }

    rc = skill_init(skill, sid, type, name, desc, 1, 0, effect);
    if (rc) {
        fprintf(stderr, "skill_new: could not initialize skill\n");
        return NULL;
    }

    return skill;
}

/* See skill.h */
int skill_init(skill_t* skill, sid_t sid, skill_type_t type, char* name,
               char* desc, unsigned int level, unsigned int xp,
               effect_t effect) {
    assert(skill != NULL);

    skill->sid = sid;
    skill->type = type;
    skill->name = strdup(name);
    skill->desc = strdup(desc);
    skill->level = level;
    skill->xp = xp;
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
