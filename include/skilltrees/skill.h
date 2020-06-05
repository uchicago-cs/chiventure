/*
 * Skill implementation for chiventure
 */

#ifndef INCLUDE_SKILL_H_
#define INCLUDE_SKILL_H_

#include "skilltrees/stdst.h"

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

/*
 * Allocates a new skill in the heap.
 *
 * Parameters:
 *  - sid: The skill ID that uniquely identifies the skill
 *  - type: The skill type, ACTIVE or PASSIVE
 *  - name: The name of the skill
 *  - desc: The description of the skill
 *  - max_level: The maximum level to which the skill can be upgraded
 *  - min_xp: The minimum number of experience points needed to level up
 *  - effect: The skill effect
 *
 * Returns:
 *  - A pointer to the skill, or NULL if a skill cannot be allocated
 */
skill_t* skill_new(sid_t sid, skill_type_t type, char* name, char* desc,
                   unsigned int max_level, unsigned int min_xp,
                   skill_effect_t effect);

/*
 * Initializes a skill.
 *
 * Parameters:
 *  - skill: A skill. Must pointer to skill allocated with skill_new
 *  - sid: The skill ID that uniquely identifies the skill
 *  - type: The skill type, ACTIVE or PASSIVE
 *  - name: The name of the skill
 *  - desc: The description of the skill
 *  - level: The player's current level of the skill
 *  - xp: The player's current experience points associated with the skill
 *  - max_level: The maximum level to which the skill can be upgraded
 *  - min_xp: The minimum number of experience points needed to level up
 *  - effect: The skill effect
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int skill_init(skill_t* skill, sid_t sid, skill_type_t type, char* name,
               char* desc, unsigned int level, unsigned int xp,
               unsigned int max_level, unsigned int min_xp,
               skill_effect_t effect);

/*
 * Frees the resources associated with a skill.
 *
 * Parameters:
 *  - skill: A skill. Must point to skill allocated with skill_new
 *
 * Returns:
 *  - Always returns 0
 */
int skill_free(skill_t* skill);

/*
 * Executes the effect of a skill.
 *
 * Parameters:
 *  - skill: A skill
 *  - args: Arguments for the skill effect function, contained in a
 *          space-separated string
 *
 * Returns:
 *  - A string that describes the consequence(s) of the skill execution for the
 *    CLI
 */
char* skill_execute(skill_t* skill, char* args);

#endif /* INCLUDE_SKILL_H_ */
