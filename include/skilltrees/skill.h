/*
 * Skill implementation for chiventure
 */

#ifndef INCLUDE_SKILL_H_
#define INCLUDE_SKILL_H_

#include "skilltrees/stdst.h"

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
