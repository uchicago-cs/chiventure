#ifndef SAMPLES_H
#define SAMPLES_H

#include "quests_state.h"

/* samples for testing */

/* A function that creates a task and all parameters associated with it for testing 
 *
 * Parameters: 
 * - task_id: The id of the task getting created
 * - create_mission: Whether to create a mission for the task
 * - mission_target_name: The target name of the new mission (ignored if not creating a mission)
 * - mission_type: The type of the new mission (ignored if not creating a mission)
 * - create_reward: Whether to create a reward for the task
 * - reward_xp: The xp for the reward (ignored if not creating a reward)
 * - reward_item: A pointer to a preexisting item for the reward (ignored if not creating a reward)
 * - create_prereq: Whether to create a prereq for the task
 * - prereq_hp: The hp for the prereq (ignored if not creating a prereq)
 * - prereq_level: The level for the prereq (ignored if not creating a prereq)
 * 
 * Returns: 
 * - A pointer to the new task struct or NULL if there was an error
*/
task_t *create_sample_task(char *task_id, 
    bool create_mission, char *mission_target_name, mission_types_t mission_type,
    bool create_reward, int reward_xp, item_t *reward_item, 
    bool create_prereq, int prereq_hp, int prereq_level);

/* A function that creates a quest and all parameters associated with it for testing 
 *
 * Parameters: 
 * - quest_id: The id of the quest getting created
 * - create_reward: Whether to create a reward for the quest
 * - reward_xp: The xp for the reward (ignored if not creating a reward)
 * - reward_item: A pointer to a preexisting item for the reward (ignored if not creating a reward)
 * - create_prereq: Whether to create a prereq for the quest
 * - prereq_hp: The hp for the prereq (ignored if not creating a prereq)
 * - prereq_level: The level for the prereq (ignored if not creating a prereq)
 * 
 * Returns: 
 * - A pointer to the new quest struct or NULL if there was an error
*/
quest_t *create_sample_quest(char *quest_id,
    bool create_reward, int reward_xp, item_t *reward_item,
    bool create_prereq, int prereq_hp, int prereq_level);

/* A function that creates a player and all parameters associated with it for testing 
 *
 * Parameters: 
 * - player_id: The id of the player getting created
 * - health: The health of the player
 * - level: The level of the player
 * 
 * Returns: 
 * - A pointer to the new player struct or NULL if there was an error
*/
player_t *create_sample_player(char *player_id, int health, int level);

/* A function that creates a quest ctx with a default player (hp: 50, level: 5) and an 
 * empty quest hash table
 * 
 * Returns: 
 * - A pointer to the new quest_ctx struct or NULL if there was an error
*/
quest_ctx_t *create_sample_ctx();

#endif /* SAMPLES_H */
