/* 
 * Defines a player class struct to store base class information.
 */ 

#ifndef CLASS_STRUCTS_H
#define CLASS_STRUCTS_H

#include "libobj/obj.h"
#include "common/utlist.h"

// max name length
#define MAX_NAME_LEN (20)

// max short description length
#define MAX_SHORT_DESC_LEN (150)

// max long description length
#define MAX_LONG_DESC_LEN (300)

// playerstats stub
typedef struct stats {
    obj_t* stat;
} stats_t;

// skilltrees stub
typedef struct skilltree {
    obj_t* skilltree;
} skilltree_t;

// actions stub
typedef struct skill {
    obj_t* skill;
} skill_t;

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
    stats_t* stats;

    // Class skilltree
    skilltree_t* skilltree;

    // Class combat actions
    skill_t* combat;

    // Class noncombat actions
    skill_t* noncombat;

} class_t;

#endif /* CLASS_STRUCTS_H */
