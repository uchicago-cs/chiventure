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

    if (max_level == 0) {
        fprintf(stderr, "skill_new: max_level is invalid\n");
        return NULL;
    }

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

/* See skill.h */
int skill_level_up(skill_t* skill) {
    if (skill == NULL) {
        return -1;
    }
    unsigned int level = skill->level;
    unsigned int min_xp = skill->min_xp;
    if (skill->max_level == level) {
        // Maximum level already achieved.
        return 1;
    }
    level += 1;
    min_xp = min_xp^level; 
    skill->min_xp = min_xp;
    return 0;
}

/* See skill.h */
int skill_xp_up(skill_t* skill, unsigned int xp_gained) {
    assert(skill != NULL);
    while (1) {
        int xp_to_next_level = skill->min_xp - skill->xp;
        if (xp_to_next_level > xp_gained) {
            skill->xp += xp_gained;
            return 0;
        } else {
            xp_gained -= xp_to_next_level;
            skill->xp = 0;
            int res = skill_level_up(skill);
            if (res != 0) {
                return res;
            }
        }
    }
}
