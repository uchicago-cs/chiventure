/*
 * Skill inventory implementation for chiventure
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    inventory->num_active = 0;
    inventory->max_active = max_active;
    inventory->num_passive = 0;
    inventory->max_passive = max_passive;

    // Initially malloc for just one skill.
    inventory->active = (skill_t**)malloc(sizeof(skill_t*));
    inventory->passive = (skill_t**)malloc((sizeof(skill_t*)));

    return inventory;
}

/* See inventory.h */
int inventory_free(skill_inventory_t* inventory) {
    assert(inventory != NULL);

    /* Free the arrays of skills */
    free(inventory->active);
    free(inventory->passive);

    /* Free the pointer to the skill_inventory itself */
    free(inventory);

    return SUCCESS;
}

/* See inventory.h */
int inventory_skill_add(skill_inventory_t* inventory, skill_t* skill) {
    assert(inventory != NULL && skill != NULL);

    switch (skill->type) {
        case ACTIVE:
            if (inventory->num_active >= inventory->max_active) {
                fprintf(stderr, "inventory_skill_add: at max active skills\n");
                return FAILURE;
            }
            inventory->active[inventory->num_active] = skill;
            inventory->num_active += 1;
            inventory->active = (skill_t**)realloc(inventory->active, sizeof(skill_t*) * (inventory->num_active + 1));
            return SUCCESS;
        case PASSIVE:
            if (inventory->num_passive >= inventory->max_passive) {
                fprintf(stderr, "inventory_skill_add: at max passive skills\n");
                return FAILURE;
            }
            inventory->passive[inventory->num_passive] = skill;
            inventory->num_passive += 1;
            inventory->passive = (skill_t**)realloc(inventory->passive, sizeof(skill_t*) * (inventory->num_passive + 1));
            return SUCCESS;
        default:
            fprintf(stderr, "inventory_skill_add: invalid skill type\n");
            return FAILURE;
    }
}



/* See inventory.h */
skill_inventory_t* copy_inventory(skill_inventory_t* original)
{
    assert(original != NULL);

    skill_inventory_t* copy = inventory_new(original->max_active, original->max_passive);
    if (copy == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for skill inventory copy");
        return NULL;
    }

    /* Fill Array of Active Skills */
    for (int i = 0; i < original->num_active; i++)
    {
        skill_t* tmp = original->active[i];
        inventory_skill_add(copy, tmp);
    }

    /* Fill Array of Passive Skills */
    for (int i = 0; i < original->num_passive; i++)
    {
        skill_t* tmp = original->passive[i];
        inventory_skill_add(copy, tmp);
    }

    return copy;
}

/* See inventory.h */
int inventory_has_skill(skill_inventory_t* inventory, sid_t sid,
                        skill_type_t type) {
    assert(inventory != NULL);

    switch (type) {
        case ACTIVE:
            return list_has_skill(inventory->active, inventory->num_active, sid);
        case PASSIVE:
            return list_has_skill(inventory->passive, inventory->num_passive, sid);
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

    skill_t** a = inventory->active;
    skill_t** p = inventory->passive;

    switch (skill->type) {
        case ACTIVE:
            a[pos] = NULL;
            inventory->num_active -= 1;
            a[pos] = a[inventory->num_active];
            a[inventory->num_active] = NULL;
            a = (skill_t**)realloc(a, sizeof(skill_t*) * inventory->num_active);
            return SUCCESS;
        case PASSIVE:
            p[pos] = NULL;
            inventory->num_passive -= 1;
            p[pos] = p[inventory->num_passive];
            p[inventory->num_passive] = NULL;
            p = (skill_t**)realloc(p, sizeof(skill_t*) * inventory->num_passive);
            return SUCCESS;
        default:
            fprintf(stderr, "inventory_skill_remove: invalid skill type\n");
            return FAILURE;
    }
}
