/*
 * Skill inventory implementation for chiventure
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "skilltrees/inventory.h"

/* See inventory.h */
inventory_t* inventory_new(unsigned int max_active, unsigned int max_passive) {
    inventory_t* inventory;
    skill_t** active;
    skill_t** passive;
    unsigned int i;

    inventory = (inventory_t*)malloc(sizeof(inventory_t));
    if (inventory == NULL) {
        fprintf(stderr, "inventory_new: could not allocate memory\n");
        return NULL;
    }
    active = (skill_t**)malloc(sizeof(skill_t*) * max_active);
    if (active == NULL) {
        fprintf(stderr, "inventory_new: could not allocate memory\n");
        return NULL;
    }
    passive = (skill_t**)malloc(sizeof(skill_t*) * max_passive);
    if (passive == NULL) {
        fprintf(stderr, "inventory_new: could not allocate memory\n");
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

/* See inventory.h */
int inventory_free(inventory_t* inventory) {
    assert(inventory != NULL);

    free(inventory->active);
    free(inventory->passive);
    free(inventory);

    return SUCCESS;
}

/* See inventory.h */
int inventory_skill_add(inventory_t* inventory, skill_t* skill) {
    assert(inventory != NULL && skill != NULL);

    switch (skill->type) {
        case ACTIVE:
            if (inventory->nactive >= inventory->max_active) {
                fprintf(stderr, "inventory_skill_add: at max active skills\n");
                return FAILURE;
            }
            inventory->active[inventory->nactive] = skill;
            inventory->nactive += 1;
            return SUCCESS;
        case PASSIVE:
            if (inventory->npassive >= inventory->max_passive) {
                fprintf(stderr, "inventory_skill_add: at max passive skills\n");
                return FAILURE;
            }
            inventory->passive[inventory->npassive] = skill;
            inventory->npassive += 1;
            return SUCCESS;
        default:
            fprintf(stderr, "inventory_skill_add: not a valid skill type\n");
            return FAILURE;
    }
}

/* See inventory.h */
int inventory_skill_remove(inventory_t* inventory, skill_t* skill) {
    assert(inventory != NULL && skill != NULL);

    int pos = inventory_has_skill(inventory, skill->sid, skill->type);
    if (pos == -1) {
        fprintf(stderr, "inventory_skill_remove: skill is not in inventory\n");
        return FAILURE;
    }

    switch (skill->type) {
        case ACTIVE:
            inventory->active[pos] = NULL;
            inventory->nactive -= 1;
            inventory->active[pos] = inventory->active[inventory->nactive];
            inventory->active[inventory->nactive] = NULL;
            return SUCCESS;
        case PASSIVE:
            inventory->passive[pos] = NULL;
            inventory->npassive -= 1;
            inventory->passive[pos] = inventory->passive[inventory->npassive];
            inventory->passive[inventory->npassive] = NULL;
            return SUCCESS;
        default:
            fprintf(stderr, "inventory_skill_remove: not a valid skill type\n");
            return FAILURE;
    }
}

int list_has_skill(skill_t** list, unsigned int llen, sid_t sid) {
    assert(list != NULL);

    unsigned int i;

    for (i = 0; i < llen; i++) {
        if (list[i]) {
            if (list[i]->sid == sid) {
                return i;
            }
        }
    }

    return -1;
}

/* See inventory.h */
int inventory_has_skill(inventory_t* inventory, sid_t sid, skill_type_t type) {
    assert(inventory != NULL);

    switch (type) {
        case ACTIVE:
            return list_has_skill(inventory->active, inventory->nactive, sid);
        case PASSIVE:
            return list_has_skill(inventory->passive, inventory->npassive, sid);
        default:
            fprintf(stderr, "inventory_has_skill: not a valid skill type\n");
            return -1;
    }
}
