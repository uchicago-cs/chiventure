/*
 * Skill trees library for chiventure
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "skilltrees.h"

/* See skilltrees.h */
skill_t* skill_new(sid_t sid, skill_type_t type, char* name, char* desc,
                   effect_t effect) {
    skill_t* skill;
    int rc;

    skill = (skill_t*)malloc(sizeof(skill_t));
    if (skill == NULL) {
        fprintf(stderr, "skill_new: could not allocate memory\n");
        return NULL;
    }

    rc = skill_init(skill, sid, type, name, desc, 0, 0, effect);
    if (rc) {
        fprintf(stderr, "skill_new: could not initialize skill\n");
        return NULL;
    }

    return skill;
}

/* See skilltrees.h */
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

    return 0;
}

/* See skilltrees.h */
int skill_free(skill_t* skill) {
    assert(skill != NULL);

    free(skill->name);
    free(skill->desc);
    free(skill);

    return 0;
}

/* See skilltrees.h */
char* skill_execute(skill_t* skill, char* args) {
    assert(skill != NULL && args != NULL);

    return (*(skill->effect))(args);
}

/* See skilltrees.h */
skill_inventory_t* skill_inventory_new(unsigned int max_active,
                                       unsigned int max_passive) {
    skill_inventory_t* inventory;
    skill_t** active;
    skill_t** passive;
    unsigned int i;

    inventory = (skill_inventory_t*)malloc(sizeof(skill_inventory_t));
    if (inventory == NULL) {
        fprintf(stderr, "skill_inventory_new: could not allocate memory\n");
        return NULL;
    }
    active = (skill_t**)malloc(sizeof(skill_t*) * max_active);
    if (active == NULL) {
        fprintf(stderr, "skill_inventory_new: could not allocate memory\n");
        return NULL;
    }
    passive = (skill_t**)malloc(sizeof(skill_t*) * max_passive);
    if (passive == NULL) {
        fprintf(stderr, "skill_inventory_new: could not allocate memory\n");
        return NULL;
    }

    for (i = 0; i < max_active; i++) {
        active[i] = NULL;
    }
    for (i = 0; i < max_passive; i++) {
        passive[i] = NULL;
    }

    inventory->active = active;
    inventory->nactive = 0;
    inventory->max_active = max_active;
    inventory->passive = passive;
    inventory->npassive = 0;
    inventory->max_passive = max_passive;

    return inventory;
}

/* See skilltrees.h */
int skill_inventory_free(skill_inventory_t* inventory) {
    assert(inventory != NULL);

    free(inventory->active);
    free(inventory->passive);
    free(inventory);

    return 0;
}

/* See skilltrees.h */
int skill_add(skill_inventory_t* inventory, skill_t* skill) {
    assert(inventory != NULL && skill != NULL);

    switch (skill->type) {
        case ACTIVE:
            if (inventory->nactive >= inventory->max_active) {
                fprintf(stderr, "skill_add: at max active skills\n");
                return 1;
            }
            inventory->active[inventory->nactive] = skill;
            inventory->active += 1;
            return 0;
        case PASSIVE:
            if (inventory->npassive >= inventory->max_passive) {
                fprintf(stderr, "skill_add: at max passive skills\n");
                return 1;
            }
            inventory->active[inventory->nactive] = skill;
            inventory->active += 1;
            return 0;
        default:
            fprintf(stderr, "skill_add: not a valid skill type\n");
            return 1;
    }
}

/* See skilltrees.h */
int skill_remove(skill_inventory_t* inventory, skill_t* skill) {
    assert(inventory != NULL && skill != NULL);

    int pos = has_skill(inventory, skill);
    if (pos < 0) {
        fprintf(stderr, "skill_remove: skill is not in inventory");
        return 1;
    }

    switch (skill->type) {
        case ACTIVE:
            inventory->active[pos] = NULL;
            inventory->nactive -= 1;
            inventory->active[pos] = inventory->active[inventory->nactive];
            inventory->active[inventory->nactive] = NULL;
            return 0;
        case PASSIVE:
            inventory->passive[pos] = NULL;
            inventory->npassive -= 1;
            inventory->passive[pos] = inventory->passive[inventory->npassive];
            inventory->passive[inventory->npassive] = NULL;
            return 0;
        default:
            fprintf(stderr, "skill_remove: not a valid skill type\n");
            return 1;
    }
}

/* See skilltrees.h */
int has_skill(skill_inventory_t* inventory, skill_t* skill) {
    assert(inventory != NULL && skill != NULL);

    unsigned int i;

    switch (skill->type) {
        case ACTIVE:
            for (i = 0; i < inventory->nactive; i++) {
                if (inventory->active[i]->sid == skill->sid) {
                    return i;
                }
            }
            return -1;
        case PASSIVE:
            for (i = 0; i < inventory->npassive; i++) {
                if (inventory->passive[i]->sid == skill->sid) {
                    return i;
                }
            }
            return -1;
        default:
            fprintf(stderr, "has_skill: not a valid skill type\n");
            return -1;
    }
}
