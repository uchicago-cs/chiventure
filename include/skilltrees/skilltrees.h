/*
 * Skill trees library for chiventure
 */

#ifndef INCLUDE_SKILLTREES_H_
#define INCLUDE_SKILLTREES_H_

/* Unique skill IDs for each skill */
typedef enum sid {
    UNLOCK_DOOR,
    DEFUSE_BOMB,
} sid_t;

/* Skill type */
typedef enum skill_type {
    ACTIVE,
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
typedef char* (*effect_t)(char*);

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
    effect_t effect;

} skill_t;

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

/*
 * Allocates a new skill in the heap.
 *
 * Parameters:
 *  - sid: The skill ID that uniquely identifies the skill
 *  - type: The skill type, ACTIVE or PASSIVE
 *  - name: The name of the skill
 *  - desc: The description of the skill
 *  - effect: The skill effect
 *
 * Returns:
 *  - A pointer to the skill, or NULL if a skill cannot be allocated
 */
skill_t* skill_new(sid_t sid, skill_type_t type, char* name, char* desc,
                   effect_t effect);

/*
 * Initializes a skill.
 *
 * Parameters:
 *  - skill: A skill. Must point to skill allocated with skill_new
 *  - sid: The skill ID that uniquely identifies the skill
 *  - type: The skill type, ACTIVE or PASSIVE
 *  - name: The name of the skill
 *  - desc: The description of the skill
 *  - level: The skill level
 *  - xp: The xp points associated with the skill
 *  - effect: The skill effect
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int skill_init(skill_t* skill, sid_t sid, skill_type_t type, char* name,
               char* desc, unsigned int level, unsigned int xp,
               effect_t effect);

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
 * Allocates a new skill inventory in the heap.
 *
 * Parameters:
 *  - max_active: The maximum number of active skills a player can possess
 *  - max_passive: The maximum number of passive skills a player can possess
 *
 * Returns:
 *  - A pointer to the skill inventory, or NULL if the skill inventory cannot be
 *    allocated
 */
skill_inventory_t* skill_inventory_new(unsigned int max_active,
                                       unsigned int max_passive);

/*
 * Frees the resources associated with a skill inventory.
 *
 * Parameters:
 *  - inventory: A skill inventory. Must point to skill inventory allocated with
 *               skill_inventory_new
 *
 * Returns:
 *  - Always returns 0
 */
int skill_inventory_free(skill_inventory_t* inventory);

/*
 * Adds a skill to a player's skill inventory.
 *
 * Parameters:
 *  - inventory: A skill inventory
 *  - skill: A skill
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int skill_add(skill_inventory_t* inventory, skill_t* skill);

/*
 * Removes a skill from a player's skill inventory.
 *
 * Parameters:
 *  - inventory: A skill inventory
 *  - skill: A skill
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int skill_remove(skill_inventory_t* inventory, skill_t* skill);

/*
 * Searches for a skill in a player's skill inventory.
 *
 * Parameters:
 *  - inventory: A skill inventory
 *  - skill: A skill
 *
 * Returns:
 *  - If in the inventory, the position of the skill in the inventory;
 *    -1 otherwise
 */
int has_skill(skill_inventory_t* inventory, skill_t* skill);

// Functions needed in regards to this:
// 5) Activate passive skills — Activates all passive skills in the inventory


// // Overall skill tree, shared by every player:
// struct tree_skill {
//     //Skill name // Name of the skill
//     //Dependencies // Which skills are required to unlock this skill
//     //Skills unlocked after// Skills that have this struct’s skill as a
//     //dependencies.
//     //Max level // Max level that this skill can be.
//
// };

// Functions needed in regards to this:
// 1) find_requirements — A player calls this when they want to know how to
// get a skill.
// 2) find_unlockables — A player calls this when they want to know
// what they can get after they unlock this skill.

#endif /* INCLUDE_SKILLTREES_H_ */
