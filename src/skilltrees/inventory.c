/*
 * Skill inventory implementation for chiventure
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "skilltrees/inventory.h"

/* See inventory.h */
skill_inventory_t* inventory_new(unsigned int max_active,
                                 unsigned int max_passive) {
    assert(!(max_active == 0 && max_passive == 0));

    skill_inventory_t* inventory;
    inventory = (skill_inventory_t*)malloc(sizeof(skill_inventory_t));
    if (inventory == NULL) {
        fprintf(stderr, "inventory_new: memory allocation failed\n");
        return NULL;
    }

    inventory->active = NULL;
    inventory->nactive = 0;
    inventory->max_active = max_active;
    inventory->passive = NULL;
    inventory->npassive = 0;
    inventory->max_passive = max_passive;

    return inventory;
}

/* See inventory.h */
int inventory_free(skill_inventory_t* inventory) {
    assert(inventory != NULL);

    if (inventory->nactive > 0) {
        free(inventory->active);
    }

    if (inventory->npassive > 0) {
        free(inventory->passive);
    }

    free(inventory);

    return SUCCESS;
}

/* See inventory.h */
int inventory_skill_add(skill_inventory_t* inventory, skill_t* skill) {
    assert(inventory != NULL && skill != NULL);

    skill_t** a = inventory->active, p = inventory->passive;

    switch (skill->type) {
        case ACTIVE:
            if (inventory->nactive >= inventory->max_active) {
                fprintf(stderr, "inventory_skill_add: at max active skills\n");
                return FAILURE;
            }
            inventory->nactive += 1;
            a = (skill_t**)realloc(a, sizeof(skill_t*) * inventory->nactive);
            a[inventory->nactive] = skill;
            return SUCCESS;
        case PASSIVE:
            if (inventory->npassive >= inventory->max_passive) {
                fprintf(stderr, "inventory_skill_add: at max passive skills\n");
                return FAILURE;
            }
            inventory->npassive += 1;
            p = (skill_t**)realloc(p, sizeof(skill_t*) * inventory->npassive);
            p[inventory->npassive] = skill;
            return SUCCESS;
        default:
            fprintf(stderr, "inventory_skill_add: invalid skill type\n");
            return FAILURE;
    }
}

/* See inventory.h */
int inventory_has_skill(skill_inventory_t* inventory, sid_t sid,
                        skill_type_t type) {
    assert(inventory != NULL);

    switch (type) {
        case ACTIVE:
            return list_has_skill(inventory->active, inventory->nactive, sid);
        case PASSIVE:
            return list_has_skill(inventory->passive, inventory->npassive, sid);
        default:
            fprintf(stderr, "inventory_has_skill: invalid skill type\n");
            return -1;
    }
}

/* See inventory.h */
int inventory_skill_remove(skill_inventory_t* inventory, skill_t* skill) {
    assert(inventory != NULL && skill != NULL);

    int pos = inventory_has_skill(inventory, skill->sid, skill->type);
    if (pos == -1) {
        fprintf(stderr, "inventory_skill_remove: skill not in inventory\n");
        return FAILURE;
    }

    skill_t** a = inventory->active, p = inventory->passive;

    switch (skill->type) {
        case ACTIVE:
            a[pos] = NULL;
            inventory->nactive -= 1;
            a[pos] = a[inventory->nactive];
            a[inventory->nactive] = NULL;
            a = (skill_t**)realloc(a, sizeof(skill_t*) * inventory->nactive);
            return SUCCESS;
        case PASSIVE:
            p[pos] = NULL;
            inventory->npassive -= 1;
            p[pos] = p[inventory->npassive];
            p[inventory->npassive] = NULL;
            p = (skill_t**)realloc(p, sizeof(skill_t*) * inventory->npassive);
            return SUCCESS;
        default:
            fprintf(stderr, "inventory_skill_remove: invalid skill type\n");
            return FAILURE;
    }
}

/* See inventory.h */
void skill_levels_update(skill_inventory_t* inventory) {
    assert(inventory != NULL);
}
