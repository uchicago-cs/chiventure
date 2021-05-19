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

/* A player class struct storing the name, descriptions, attributes, stats, 
 * stat effects, skill inventories, and skill tree associated with a class. */
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

    // Memory used internally by the UTHASH macros
    UT_hash_handle hh;
} class_t;


/* This typedef exists to differentiate between two use cases of the class struct:
 *  - class_t is meant to be used to access info about one particular class.
 *  - class_hash_t is meant to be used to access a hashtable of many classes. */
typedef struct class class_hash_t;

#endif /* CLASS_STRUCTS_H */
