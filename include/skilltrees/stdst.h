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
    sid_t sid;  // Does this limit ourselves to however many skills we create?

    // The skill type
    skill_type_t type;

    // The name of the skill
    char* name;  // Why do we need both name and unique skill ids?
                 // Wouldn't the value inside of sid_t be identical to this?

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
    unsigned int max_active;  // What do we mean by 'enforce skill tree
                              // balancing'? It is not mentioned in the design
                              // document, and this idea of enforcing skill tree
                              // balancing has overriden previous code written.
                              // If this number is very large, are we going to
                              // create a way to gradually allocate more space
                              // as the player obtains more skills, or are
                              // we going to potentially have a list of, say,
                              // 40 null skill_t pointers for the majority of
                              // an early game?

    // An array of passive skills belonging to a player
    skill_t** passive;

    // The number of passive skills belonging to a player
    unsigned int npassive;

    // The maximum number of passive skills a player can possess
    // (This field helps to enforce skill tree balancing)
    unsigned int max_passive;  // See notes to max_active

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
    sid_t sid;  // Should we have the branch point to a skill instead of
                // just holding a skill id? 

    // The list of prerequisite skills to acquire skill `sid`
    skill_t** prereqs;  // Is this a complete list of every skill required,
                        // or just one skill required beforehand? For instance,
                        // if there is a branch that is 10 skills long, does
                        // this include all 10 skills or does it include only
                        // the closest skill?

    // The number of prerequisite skills
    unsigned int nprereqs;

    // Size of the branch — for the graphics team, purely visual.
    unsigned int size;

    // The maximum level to which the skill can be upgraded
    unsigned int max_level;  // Should this be here? If so, that means we have
                             // to access the skill tree every time we level
                             // up an individual skill. If a skill is, say,
                             // 10 branches away from the center of the tree,
                             // doesn't that seem like a lot of searching
                             // for the max_level?

    // The number of experience points needed to level up
    unsigned int min_xp;  // Should this be here, or in the individual skill?
                          // If it is here, then this has the same problem as
                          // max_level where we'd need to search through
                          // the skill tree to check every single time we gain
                          // experience if we should level up or not. Why
                          // can't this be in the skill_t struct instead?

} branch_t;

/* Skill tree, contains all skill branches in a game */
typedef struct tree {
    // The tree ID that uniquely identifies the tree
    tid_t tid;  // Are we limiting ourselves here by making this an enum?
                // See comments on sid_t for more info.

    // Name of the tree for the graphics team.

    char* name; // We need to talk to decide if we need both tid_t and names
                // here, similarly to how we need to talk about whether we need
                // both for skill_t or not.

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
