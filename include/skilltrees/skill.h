/*
 * Skill implementation for chiventure
 */

#ifndef INCLUDE_SKILL_H_
#define INCLUDE_SKILL_H_

#include "skilltrees/skilltrees_common.h"
#include "skilltrees/effect.h"

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
 *  - effect: The skill effect; no skill means put NULL
 *  - complex_skill: designates the type of complex skill the skill is; 
 *                   if it's not one, then NULL
 * 
 * Returns:
 *  - A pointer to the skill, or NULL if a skill cannot be allocated
 */
skill_t* skill_new(sid_t sid, skill_type_t type, char* name, char* desc,
                   unsigned int max_level, unsigned int min_xp,
                   effect_t*  skill_effect, complex_skill_t* complex_skill);

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
               effect_t* skill_effect, complex_skill_t* complex_skill);

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
 *  - chiventure_ctx_t* ctx - A context object to pull data from to execute the skill
 * Returns:
 * 0 if success
 * 1 if failure
 */
int skill_execute(skill_t* skill, chiventure_ctx_t* ctx);

/*
 * Levels up a skill and exponentially increments the min_xp required for 
 * the next level
 *
 * Parameters:
 *  - skill: A skill.
 *
 * Returns:
 * 0 if leveling up worked.
 * 1 if the maximum level was already achieved, so levelling up won't happen.
 * -1 if leveling up failed, such as invalid parameters for instance.
 */
int skill_level_up(skill_t* skill);


/*
 * Increments a skill's xp, leveling up when necessary.
 *
 * Parameters:
 *  - skill: A skill.
 *  - xp_gained: Amount of xp to add onto a skill.
 *
 * Returns:
 * 0 if incrementing experience worked.
 * 1 if the maximum level was already reached and you tried to level up again.
 * -1 if incrementing xp failed, such as giving invalid parameters.
 */
int skill_xp_up(skill_t* skill, unsigned int xp_gained);

#endif /* INCLUDE_SKILL_H_ */
