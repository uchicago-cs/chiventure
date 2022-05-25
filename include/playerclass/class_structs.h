/*
 * Defines a player class struct to store base class information.
 */

#ifndef CLASS_STRUCTS_H
#define CLASS_STRUCTS_H

#include "common/utlist.h"
#include "game-state/stats.h"
#include "libobj/obj.h"

/* Forward Declarations to avoid circular dependency */
typedef struct skill_tree skill_tree_t;
typedef struct skill_inventory skill_inventory_t;

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

    // Number of parent classes
    int num_parent_class;

    // All base classes that have been multiclassed into
    char **parent_class_names;

    // A short description of the class
    char* shortdesc;

    // A long description of the class
    char* longdesc;

    // An object containing all the attributes of the class
    obj_t* attributes;

    // All the base_stats of the class
    stats_hash_t* base_stats;

    // Effects on the class
    effects_hash_t* effects;

    // Class skilltree
    skill_tree_t* skilltree;

    // Class skills
    skill_inventory_t* starting_skills;

    // Memory used internally by the UTHASH macros
    UT_hash_handle hh;
} class_t;


/* This typedef exists to differentiate between two use cases of the class struct:
 *  - class_t is meant to be used to access info about one particular class.
 *  - class_hash_t is meant to be used to access a hashtable of many classes. */
typedef struct class class_hash_t;

#endif /* CLASS_STRUCTS_H */
