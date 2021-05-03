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
                   effects_linked_list_t* skill_effects) {
    skill_t* skill;
    int rc;

    skill = (skill_t*)malloc(sizeof(skill_t));
    if (skill == NULL) {
        fprintf(stderr, "skill_new: memory allocation failed\n");
        return NULL;
    }

    rc = skill_init(skill, sid, type, name, desc, 1, 0, max_level, min_xp, skill_effects);
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
               effects_linked_list_t* skill_effects) {
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
    skill->skill_effects = skill_effects;

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
char* skill_execute(skill_t* skill) 
{
    //TODO
}

/* See skill.h */
int skill_level_up(skill_t* skill) {
    assert(skill != NULL);
    if (skill->max_level == skill->level) {
        // Maximum level already achieved.
        return 1;
    }
    skill->level += 1;
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
