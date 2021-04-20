/*
 * Defines a player class struct to store base class information.
 */

#ifndef CLASS_STRUCTS_H
#define CLASS_STRUCTS_H

#include "common/utlist.h"
#include "skilltrees/inventory.h"
#include "skilltrees/skilltree.h"
#include "game-state/stats.h"
#include "libobj/obj.h"

// max name length
#define MAX_NAME_LEN (20)

// max short description length
#define MAX_SHORT_DESC_LEN (150)

// max long description length
#define MAX_LONG_DESC_LEN (300)

/* define constants for how many skills a class can have
 * in their current active and passive skill lists
 * numbers are utterly arbitrary */
#define MAX_ACTIVE_SKILLS (10)
#define MAX_PASSIVE_SKILLS (10)

/* max number of skills in a class' skilltree
 * number is utterly arbitrary */
#define MAX_SKILLS_IN_TREE (5)


/* A player class struct storing the name, descriptions, attributes,
 * and stats */
typedef struct class {
    // Name of the class
    char* name;

    // A short description of the class
    char* shortdesc;

    // A long description of the class
    char* longdesc;

    // An object containing all the attributes of the class
    obj_t* attributes;

    // All the stats of the class
    stats_hash_t* stats;

    // Effects/temporary status on the class
    effects_hash_t* effects;

    // Class skilltree
    skill_tree_t* skilltree;

    // Class combat actions
    skill_inventory_t* combat;

    // Class noncombat actions
    skill_inventory_t* noncombat;

} class_t;

#endif /* CLASS_STRUCTS_H */
