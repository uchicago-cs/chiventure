/*
 * Data structures and standard functions for chiventure's skill tree library
 */

#ifndef INCLUDE_STDST_H_
#define INCLUDE_STDST_H_

#include "common/common.h"

/* ============================= */
/* === SKILL DATA STRUCTURES === */
/* ============================= */
/* Unique skill IDs for each skill */
typedef enum sid {
    // Example 1
    UNLOCK_DOOR,

    // Example 2
    DEFUSE_BOMB,

    // Example 3
    CHOP_TREE,

    // Example 4
    INNER_PEACE,

} sid_t;

/* Skill type */
typedef enum skill_type {
    // Denotes active skill
    ACTIVE,

    // Denotes passive skill
    PASSIVE,

} skill_type_t;

/*
 * Skill effect function type
 *
 * Parameters:
 *  - Contained within a string for function pointer uniformity. Each skill
 *    effect function can read the string for parameters using sscanf.
 *
 * Returns:
 *  - A string describing the consequence of the skill execution, for the CLI
 */
typedef char* (*skill_effect_t)(char*);

/* An INDIVIDUAL skill, belonging to a player */
typedef struct skill {
    // The skill ID that uniquely identifies the skill
    sid_t sid;

    // The skill type
    skill_type_t type;

    // The name of the skill
    char* name;

    // The description of the skill
    char* desc;

    // The player's current level of the skill
    unsigned int level;

    // The player's current experience points associated with the skill
    unsigned int xp;

    // The pointer to the function that will execute the skill effect
    skill_effect_t effect;

} skill_t;

/* ================================= */
/* === INVENTORY DATA STRUCTURES === */
/* ================================= */
/* ALL the skills belonging to a player */
typedef struct inventory {
    // An array of active skills belonging to a player
    skill_t** active;

    // The number of active skills belonging to a player
    unsigned int nactive;

    // The maximum number of active skills a player can possess
    // (This field helps to enforce skill tree balancing)
    unsigned int max_active;

    // An array of passive skills belonging to a player
    skill_t** passive;

    // The number of passive skills belonging to a player
    unsigned int npassive;

    // The maximum number of passive skills a player can possess
    // (This field helps to enforce skill tree balancing)
    unsigned int max_passive;

} inventory_t;

/* ================================== */
/* === SKILL TREE DATA STRUCTURES === */
/* ================================== */
/* Unique tree IDs for each tree */
typedef enum tid {
    // Example 1
    HEALTH,

    // Example 2
    COMBAT,

    // Example 3
    CHARMS,

    // Example 4
    POTIONS,

} tid_t;

/* Skill branch, contains general information about an acquirable skill in a
 * game
 */
typedef struct branch {
    // The skill ID that uniquely identifies the skill
    sid_t sid;

    // The list of prerequisite skills to acquire skill `sid`
    skill_t** prereqs;

    // The number of prerequisite skills
    unsigned int nprereqs;

    // The maximum level to which the skill can be upgraded
    unsigned int max_level;

    // The number of experience points needed to level up
    unsigned int min_xp;

} branch_t;

/* Skill tree, contains all skill branches in a game */
typedef struct tree {
    // The tree ID that uniquely identifies the tree
    tid_t tid;

    // The list of tree branches
    branch_t** branches;

    // The number of tree branches
    unsigned int nbranches;

} tree_t;

/* ======================== */
/* === COMMON FUNCTIONS === */
/* ======================== */
/*
 *
 */
 // COMMENT NEEDS TO BE ADDED - What does this function do?
int array_element_add(void** array, unsigned int alen, void* element);

/*
 *
 */
 // COMMENT NEEDS TO BE ADDED - What does this function do?
int list_has_skill(skill_t** list, unsigned int llen, sid_t sid);

#endif /* INCLUDE_STDST_H_ */
