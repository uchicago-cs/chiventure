/*
 * Skill implementation for chiventure
 */

#ifndef INCLUDE_SKILL_H_
#define INCLUDE_SKILL_H_

#include "skilltrees/skilltrees_common.h"

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
 *  - skill_effects: Pointer to the head of a linked list of effects that a skill has
 *
 * Returns:
 *  - A pointer to the skill, or NULL if a skill cannot be allocated
 */
skill_t* skill_new(sid_t sid, skill_type_t type, char* name, char* desc,
                   unsigned int max_level, unsigned int min_xp,
                   effects_linked_list_t*  skill_effects);

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
 *  - skill_effects: Pointer to the head of a linked list of effects that a skill has.
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int skill_init(skill_t* skill, sid_t sid, skill_type_t type, char* name,
               char* desc, unsigned int level, unsigned int xp,
               unsigned int max_level, unsigned int min_xp,
               effects_linked_list_t* skill_effects);

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
 * Executes the effects of a skill.
 *
 * Parameters:
 *  - skill: A skill
 *
 * Returns:
 *  - SUCCESS if the skill effects were applied succesfull
 */
int skill_execute(skill_t* skill);

/*
 * Levels up a skill
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
