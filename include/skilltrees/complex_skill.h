/*
 * Complex Skill implementation for chiventure
 */

#ifndef INCLUDE_COMPLEX_SKILL_H_
#define INCLUDE_COMPLEX_SKILL_H_

#include "skilltrees/skilltrees_common.h"
#include "skilltrees/effect.h"
#include "skilltrees/skill.h"

/*
 * Allocates a new complex skill in the heap.
 *
 * Parameters:
 *  - type: The complex skill type
 *  - skills: A list of the sub-skills to be stored within complex_skill
 *  - num_skills: The number of sub-skills the complex skill will use
 *
 * Returns:
 *  - A pointer to the complex skill, or NULL if a complex skill cannot be 
 *    allocated
 */
complex_skill_t* complex_skill_new(complex_skill_type_t type, skill_t** skills, int num_skills);

/*
 * Initializes a complex skill.
 *
 * Parameters:
 *  - complex_skill: A complex skill. Must pointer to skill allocated with 
 *    complex_skill_new
 *  - skills: A list of the sub-skills to be stored within complex_skill
 * 
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int complex_skill_init(complex_skill_t* complex_skill, skill_t** skills);

/*
 * Frees the resources associated with a complex skill.
 *
 * Parameters:
 *  - complex_skill: A complex skill. Must point to skill allocated with 
 *    complex_skill_new
 *
 * Returns:
 *  - Always returns 0
 */
int complex_skill_free(complex_skill_t* complex_skill);

/*
 * Executes each subskill in order. Behavior will vary depending on the type of 
 * skill.
 * Ex: Combined skills will run skill_execute on each subskill regardless of 
 *     success or failure
 *     Sequential skills will stop execution once a sub_skill fails
 *
 * Parameters:
 *  - complex_skill: A complex skill
 *  - chiventure_ctx_t* ctx - A context object to pull data from to execute the 
 *    skill
 * Returns:
 * 0 if success
 * 1 if failure
 */
int complex_skill_execute(complex_skill_t* complex_skill, chiventure_ctx_t* ctx);

/*
 * Executes a combined skill, executing each subskill regardless of success or 
 * failure
 *
 * Parameters:
 *  - complex_skill: A complex skill
 *  - chiventure_ctx_t* ctx - A context object to pull data from to execute the 
 *    skill
 * 
 * Returns:
 * 0 if success
 * 1 if failure
 */
int combined_complex_skill_execute(complex_skill_t* complex_skill, chiventure_ctx_t* ctx);

/*
 * Executes a sequential skill, stopping execution once a sub_skill fails
 *
 * Parameters:
 *  - complex_skill: A complex skill
 *  - chiventure_ctx_t* ctx - A context object to pull data from to execute the 
 *    skill
 * 
 * Returns:
 * 0 if success
 * 1 if failure
 */
int sequential_complex_skill_execute(complex_skill_t* complex_skill, chiventure_ctx_t* ctx);

/* NOTICE
 * The following 2 functions may not be necessary in final implementation, by 
 * changing the skill_level_up and skill_xp_up functions to just check for the 
 * presence of a complex skill
 * And increment each sub-skill respectfully.
 * These are included depending on that future decision
*/

/*
 * Levels each skill within complex_skill using skill_level_up.
 *
 * Parameters:
 *  - complex_skill: A complex skill.
 *
 * Returns:
 * 0 if leveling up worked.
 * 1 if the maximum level was already achieved, so levelling up won't happen.
 * -1 if leveling up failed, such as invalid parameters for instance, or if 
 *  not every subskill was able to be leveled up
 */
int complex_skill_level_up(complex_skill_t* complex_skill);

/*
 * Increments each sub-skill's exp
 *
 * Parameters:
 *  - complex_skill: A complex skill.
 *  - xp_gained: Amount of xp to add onto a skill.
 *
 * Returns:
 * 0 if incrementing experience worked.
 * 1 if the maximum level was already reached and you tried to level up again.
 * -1 if incrementing xp failed, such as giving invalid parameters, or if 
 *  not every subskill was able to be incremented. 
 */
int complex_skill_xp_up(complex_skill_t* complex_skill, unsigned int xp_gained);