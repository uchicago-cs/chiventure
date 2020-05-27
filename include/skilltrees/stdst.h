/*
 * Data structures and standard functions for chiventure's skill tree library
 */

#ifndef INCLUDE_STDST_H_
#define INCLUDE_STDST_H_

#include "common/common.h"

/* ============================= */
/* === SKILL DATA STRUCTURES === */
/* ============================= */

/* Unique skill IDs for each skill
/* This enum we're defining here isn't supposed to limit the possible skill
/* types, but instead is an example of how other groups would define their own
/* unique skill ids.
/* For instance, we define our example skills starting at 1001 because
/* skilltrees has access to the first 1000 skills, and another team would have
/* access to the next 1000 (so 2001, 2002, etc), to avoid overlap.
*/
// Add size_t comment.
typedef enum sid {
    // Example 1
    UNLOCK_DOOR=1001,

    // Example 2
    DEFUSE_BOMB=1002,

    // Example 3
    CHOP_TREE=1003,

    // Example 4
    INNER_PEACE=1004,

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
    unsigned int level;  // Maximum level was recently removed. Why is that?
                         // How would we figure out if a skill can level up,
                         // or if it is at its maximum and thus can't level up,
                         // unless we have it in the skill struct? Is it
                         // efficient to have to search through the entire skill
                         // tree to figure out if something can be level'd up
                         // or not?

    // The player's current experience points associated with the skill
    unsigned int xp;  // If this is an integer, how do we figure out what the
                      // required experience is until the next level? Is it
                      // 100? If so, does that mean we can't make it harder
                      // on our end to get to the next level? Implementing a
                      // total xp to next level requirement would help solve
                      // this problem.

    // The maximum level to which the skill can be upgraded
    unsigned int max_level;

    // The number of experience points needed to level up
    unsigned int min_xp;

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
/* This enum we're defining here isn't supposed to limit the possible tree
/* types, but instead is an example of how other groups would define their own
/* unique skill ids.
/* For instance, we define our example trees starting at 1001 because
/* skilltrees has access to the first 1000 trees, and another team would have
/* access to the next 1000 (so 2001, 2002, etc), to avoid overlap.
*/
// Add size_t comment.
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
    // The skill identified with the branch
    skill_t* skill;

    // Points to a list of prerequisites immediately preceeding this level in
    // the tree.
    branch_t** prereqs;

    // The number of prerequisite branches
    unsigned int nprereqs;

    // Size of the branch — for the graphics team, purely visual.
    unsigned int size;

} branch_t;

/* Skill tree, contains all skill branches in a game */
typedef struct tree {
    // The tree ID that uniquely identifies the tree
    tid_t tid;

    // Name of the tree for the graphics team.
    char* name;

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
