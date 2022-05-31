/*
 * Complex Skill implementation for chiventure
 *
 * Types of complex skills:
 * - Combined: Executes multiple subskills in order
 * - Conditional: Executes a subskill if a given condition is met
 * - Random: Executes subskills either based on chance (random chance)
 *           on an all or nothing basis,
 *          to a variable extent (random range), or as one of several
 *          potential outcomes (random switch).
 */

#ifndef INCLUDE_COMPLEX_SKILL_H_
#define INCLUDE_COMPLEX_SKILL_H_

#include "skilltrees/skilltrees_common.h"
#include "skilltrees/effect.h"
#include "skilltrees/reader.h"
#include "skilltrees/skill.h"

/*
 * Allocates a new complex skill in the heap.
 *
 * Parameters:
 *  - type: The complex skill type
 *  - skills: An array of the sub-skills to be stored within complex_skill
 *  - num_skills: The number of sub-skills the complex skill will use
 *  - reader: Optional reader if skill is conditional
 *
 * Returns:
 *  - A pointer to the complex skill, or NULL if a complex skill cannot be allocated
 */
complex_skill_t* complex_skill_new(complex_skill_type_t type, skill_t** skills, int num_skills, 
                                   reader_effect_t* reader);

/*
 * Initializes a complex skill.
 *
 * Parameters:
 *  - complex_skill: A complex skill. Must pointer to skill allocated with complex_skill_new
 *  - type: Type of complex skill 
 *  - skills: An array of the sub-skills to be stored within complex_skill
 *  - num_skills: number of sub-skills in skills array
 *  - reader: Optional reader if skill is conditional
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int complex_skill_init(complex_skill_t* complex_skill, complex_skill_type_t type, 
                       skill_t** skills, int num_skills, reader_effect_t* reader);

/*
 * Frees the resources associated with a complex skill.
 *
 * Parameters:
 *  - complex_skill: A complex skill. Must point to skill allocated with complex_skill_new
 *
 * Returns:
 *  - Always returns 0
 */
int complex_skill_free(complex_skill_t* complex_skill);

/*
 * Executes each subskill in order. Behavior will vary depending on the type of skill.
 * Ex: Combined skills will run skill_execute on each subskill regardless of success or failure
 *     Sequential skills will stop execution once a sub_skill fails
 * 
 * Note: Random complex skills are executed via a different function
 *
 *
 * Parameters:
 *  - complex_skill: A complex skill
 *  - chiventure_ctx_t* ctx - A context object to pull data from to execute the skill
 *
 * Returns:
 * 0 if success
 * 1 if failure
 */
int complex_skill_execute(complex_skill_t* complex_skill, chiventure_ctx_t* ctx);

/*
 * Executes 1 of 2 skills stored in a conditional skill depending on reader conditon. 
 *
 * Parameters:
 *  - skill: A conditional skill
 *  - chiventure_ctx_t* ctx - A context object to pull data from to execute the skill
 *
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
int conditional_skill_execute(complex_skill_t* skill, chiventure_ctx_t* ctx);

/*********************************************************************************************/
/* NOTICE
 * The following 2 functions may not be necessary in final implementation, by changing the
 * skill_level_up and skill_xp_up functions to just check for the presence of a complex skill
 * And increment each sub-skill respectfully.
 * These are included depending on that future decision
*/
/*********************************************************************************************/
int sequential_complex_skill_execute(complex_skill_t* complex_skill, chiventure_ctx_t* ctx);

/*
 * Levels each skill within complex_skill using skill_level_up.
 *
 * Parameters:
 *  - complex_skill: A complex skill.
 *
 * Returns:
 * SUCCESS if leveling up worked.
 * FAILURE if the maximum level was already achieved, so levelling up won't happen 
 * or if leveling up failed, such as invalid parameters for instance, or if 
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
 * SUCCESS if incrementing experience worked.
 * FAILURE if the maximum level was already reached and you tried to level up again
 * or if incrementing xp failed, such as giving invalid parameters, or if 
 *  not every subskill was able to be incremented. 
 */
int complex_skill_xp_up(complex_skill_t* complex_skill, unsigned int xp_gained);

/*
 * Allocates a random chance type in the heap.
 *
 * Parameters:
 *  - chance_failure: A float representing the chance of failure
 *  - complex_skill: the associated complex skill
 *
 * Returns:
 *  - A pointer to the random chance type, or NULL if one cannot be 
 *    allocated
 */
random_chance_type_t* random_chance_new(complex_skill_t* complex_skill, float chance_failure);

/*
 * Initializes a random chance type.
 *
 * Parameters:
 *  - random_chance_type_t: must point struct already allocated with 
 *    random_chance_new
 *  - chance_failure: A float representing the chance of failure
 *  - complex_skill: the associated complex skill
 * 
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int random_chance_init(random_chance_type_t* random_chance_skill, complex_skill_t* complex_skill, float chance_failure);

/*
 * Frees the resources associated with a random chance skill
 *
 * Parameters:
 *  - random_chance_skill: A random chance skill. Must point to skill allocated 
 *    with random_chance_new
 *
 * Returns:
 *  - Always returns 0
 */
int random_chance_free(random_chance_type_t* random_chance_skill);

/*
 * Allocates a new random range type in the heap.
 *
 * Parameters:
 *  - lower_bound: A lower bound of values
 *  - upper_bound: An upper bound of values
 *  - complex_skill: the associated complex skill
 *
 * Returns:
 *  - A pointer to the random range type, or NULL if one cannot be 
 *    allocated
 */
random_range_type_t* random_range_new(complex_skill_t* complex_skill, int lower_bound, int upper_bound);

 /*
 * Initializes a random range type.
 *
 * Parameters:
 *  - random_range_type_t: must point struct already allocated with 
 *    random_range_new
 *  - lower_bound: A lower bound of values
 *  - upper_bound: An upper bound of values
 *  - complex_skill: the associated complex skill
 * 
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int random_range_init(random_range_type_t* random_range_skill, complex_skill_t* complex_skill, int lower_bound, int upper_bound);

/*
 * Frees the resources associated with a random range skill
 *
 * Parameters:
 *  - random_range_skill: A random range skill. Must point to skill allocated 
 *    with random_range_new
 *
 * Returns:
 *  - Always returns 0
 */
int random_range_free(random_range_type_t* random_range_skill);

 /*
 * Allocates a new random switch type in the heap.
 *
 * Parameters:
 *  - chances: array of percentages for each subskill
 *  - chances_len: Length of chances array
 *  - complex_skill: the associated complex skill
 *
 * Returns:
 *  - A pointer to the random switch type, or NULL if one cannot be 
 *    allocated
 */
random_switch_type_t* random_switch_new(complex_skill_t* complex_skill, float* chances, int chances_len);

 /*
 * Initializes a random switch type.
 *
 * Parameters:
 *  - random_switch_type_t: must point struct already allocated with 
 *    random_switch_new
 *  - chances: array of percentages for each subskill
 *  - chances_len: Length of chances array
 *  - complex_skill: the associated complex skill
 * 
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int random_switch_init(random_switch_type_t* random_switch_skill, complex_skill_t* complex_skill, float* chances, int chances_len);

/*
 * Frees the resources associated with a random switch skill
 *
 * Parameters:
 *  - random_switch_skill: A random switch skill. Must point to skill allocated 
 *    with random_switch_new
 *
 * Returns:
 *  - Always returns 0
 */
int random_switch_free(random_switch_type_t* random_switch_skill);
 
/* 
* Executes a random skill using a chance effect
*
* Parameters:
* - chance_skill: the random_chance_type_t complex skill being used
* - ctx: A context object to pull data from to execute the
*   skill
*
* Returns:
* 0 if success
* 1 if failure
*/
int execute_random_chance_complex_skill(random_chance_type_t* chance_skill, chiventure_ctx_t* ctx);

/* 
* Executes a random skill using a range effect–executes a skill a random number 
* of times within the given range
*
* Parameters:
* - range_skill: the random_range_type_t complex skill being used
* - chiventure_ctx_t* ctx: A context object to pull data from to execute the
*   skill
*
* Returns:
* 0 if success
* 1 if failure
*/
int execute_random_range_complex_skill(random_range_type_t* range_skill, chiventure_ctx_t* ctx);

/* 
* Executes a random skill using a switch effect
*
* Parameters:
* - random_switch_type_t* switch_skill: a struct with complex skill type 
*       RANDOM_SWITCH and an array of the chances of execution of each subskill
* - chiventure_ctx_t* ctx: A context object to pull data from to execute the
*   skill
*
* Returns:
* 0 if success
* 1 if failure
*/
int execute_random_switch_complex_skill(random_switch_type_t* switch_skill, chiventure_ctx_t* ctx);

#endif /*INCLUDE_COMPLEX_SKILL_H*/
