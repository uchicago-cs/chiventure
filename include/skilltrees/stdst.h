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
 *
 * Note: This enum does not limit the number of skill IDs possible (at least,
 * within the range of the data type int...). The sid_t type is meant to be akin
 * to the C library size_t data type that is returned when calling functions
 * like sizeof(); it is merely an integer type, but we distinguish it from an
 * integer for clarity.
 *
 * Moreover, we do not expect individual enums to be defined for each skill as
 * written below (e.g. UNLOCK_DOOR, DEFUSE_BOMB, etc.), as updating the enums as
 * such would require frequently changing the code written here. The enums that
 * are explicitly defined within sid_t below are for testing purposes.
 *
 * In order to prevent skill enumeration overlap, we envision assigning each
 * chiventure team a range of 1000 IDs (e.g. rpg-battle is entitled to sid_t
 * 2000-2999).
 */
typedef enum sid {
    // Example 1
    UNLOCK_DOOR = 1000,

    // Example 2
    DEFUSE_BOMB = 1001,

    // Example 3
    CHOP_TREE = 1002,

    // Example 4
    INNER_PEACE = 1003,

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

    // The maximum level to which the skill can be upgraded
    unsigned int max_level;

    // The minimum number of experience points needed to level up
    unsigned int min_xp;

    // The pointer to the function that will execute the skill effect
    skill_effect_t effect;

} skill_t;

/* ================================= */
/* === INVENTORY DATA STRUCTURES === */
/* ================================= */
/* ALL the skills belonging to a player */
typedef struct skill_inventory {
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

} skill_inventory_t;

/* ================================== */
/* === SKILL TREE DATA STRUCTURES === */
/* ================================== */
/* Unique tree IDs for each tree
 *
 * Note: This enum does not limit the number of tree IDs possible (at least,
 * within the range of the data type int...). The tid_t type is meant to be akin
 * to the C library size_t data type that is returned when calling functions
 * like sizeof(); it is merely an integer type, but we distinguish it from an
 * integer for clarity.
 *
 * Moreover, we do not expect individual enums to be defined for each tree as
 * written below (e.g. HEALTH, COMBAT, etc.), as updating the enums as such
 * would require frequently changing the code written here. The enums that are
 * explicitly defined within tid_t below are for testing purposes.
 *
 * In order to prevent tree enumeration overlap, we envision assigning each
 * chiventure team a range of 1000 IDs (e.g. rpg-battle is entitled to tid_t
 * 2000-2999).
 */
typedef enum tid {
    // Example 1
    HEALTH = 1000,

    // Example 2
    COMBAT = 1001,

    // Example 3
    CHARMS = 1002,

    // Example 4
    POTIONS = 1003,

} tid_t;

/* Skill node forward declaration, contains general information about an acquirable skill in a game
 */
typedef struct skill_node skill_node_t;

struct skill_node {
    // The skill represented by the skill node
    skill_t* skill;

    // Points to a list of prerequisites immediately preceeding the level in the
    // tree, in which the skill node presides
    skill_node_t** prereqs;

    // The number of prerequisite skill nodes
    unsigned int nprereqs;

    // The size of the skill node, for the graphics team
    unsigned int size;

};

/* Skill tree, contains all skill nodes in a game */
typedef struct skill_tree {
    // The tree ID that uniquely identifies the skill tree
    tid_t tid;

    // The name of the skill tree
    char* name;

    // The list of tree nodes
    skill_node_t** nodes;

    // The number of tree nodes
    unsigned int nnodes;

} skill_tree_t;

/* ======================== */
/* === COMMON FUNCTIONS === */
/* ======================== */
/*
 * A helper function. Adds an arbitrary array element to an array, by pointer.
 *
 * Parameters:
 *  - array: The array
 *  - alen: The length of the array
 *  - element: The element to add to the array
 *
 * Returns:
 *  - A pointer to the updated array, NULL if an error occurs
 */
void** array_element_add(void** array, unsigned int alen, void* element);

/*
 * A helper function. Searches a list of skills for a given skill, by sid_t.
 *
 * Parameters:
 *  - list: The skill array
 *  - llen: The length of the skill list
 *  - sid: The skill ID of the skill to search for
 *
 * Returns:
 *  - The position of the skill in the list, -1 if the skill is not in the list
 */
int list_has_skill(skill_t** list, unsigned int llen, sid_t sid);

#endif /* INCLUDE_STDST_H_ */
