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

/* ======================== */
/* === COMMON FUNCTIONS === */
/* ======================== */
/*
 * A helper function. Adds an arbitrary array element to an array, by pointer.
 *
 * Parameters:
 *  - array: The array
 *  - array_len: The length of the array
 *  - element: The element to add to the array
 *
 * Returns:
 *  - A pointer to the updated array, NULL if an error occurs
 */
void** array_element_add(void** array, unsigned int array_len, void* element);

/*
 * A helper function. Searches a list of skills for a given skill, by sid_t.
 *
 * Parameters:
 *  - list: The skill array
 *  - list_len: The length of the skill list
 *  - sid: The skill ID of the skill to search for
 *
 * Returns:
 *  - The position of the skill in the list, -1 if the skill is not in the list
 */
int list_has_skill(skill_t** list, unsigned int list_len, sid_t sid);

#endif /* INCLUDE_STDST_H_ */
