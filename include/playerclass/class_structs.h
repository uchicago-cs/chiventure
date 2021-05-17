/*
 * Defines a player class struct to store base class information.
 */

#ifndef CLASS_STRUCTS_H
#define CLASS_STRUCTS_H

#include "common/utlist.h"
#include "skilltrees/skilltree.h"
#include "game-state/stats.h"
#include "libobj/obj.h"

// max name length
#define MAX_NAME_LEN (20)

// max short description length
#define MAX_SHORT_DESC_LEN (150)

// max long description length
#define MAX_LONG_DESC_LEN (300)

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

    /* 
     * Note: There is a concern here about the combat vs noncombat distinction,
     * since the skilltrees code divides between passive and active skills.
     * 
     * Should we adjust the division below so that we track passive vs active
     * skills?
     */

    // Class combat actions
    skill_inventory_t* combat;

    // Class noncombat actions
    skill_inventory_t* noncombat;

} class_t;

#endif /* CLASS_STRUCTS_H */

