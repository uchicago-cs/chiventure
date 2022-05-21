#ifndef TASK_H
#define TASK_H

#include "quest_hash.h"

typedef struct item_wrapped_for_llist item_list_t; // Forward declaration

/* task functionality */

/* Creates a new mission struct (allocates memory)
 * 
 * Parameters:
 * - target_name: The name of the mission's target (the NPC's name, the item's name, etc)
 * 
 *
 * Returns: a pointer to the newly allocated mission, that is not completed
 */
mission_t *mission_new(char *target_name, mission_types_t type);

/* Initialize an already allocated mission struct
 *
 * Parameters:
 * - mission: an already allocated mission_t 
 * - target_name: the name of the mission's target (NPC, item, etc)
 * - type: The type of mission
 * 
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 * 
 * Note: Also ensures that the mission only includes a single thing to do. If
 *       there is more than one pointer that is not NULL (excluding mission),
 *       this function will return FAILURE.
 */
int mission_init(mission_t *mission, char *target_name, mission_types_t type);

/* 
 * Frees a mission struct from memory
 * 
 * Parameter:
 * - mission: the mission to be freed
 * 
 * Returns:
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */
int mission_free(mission_t *mission);


/* Creates a new reward struct for completing a quest 
 * 
 * Parameters:
 * - xp: xp reward
 * - item: item reward
 *
 * Returns: a pointer to the newly allocated reward struct
 */
reward_t *reward_new(int xp, item_t *item);

/* Initializes an already allocated reward struct
 * 
 * Parameters:
 * - xp: xp reward
 * - item: item reward
 *
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 */
int reward_init(reward_t *rewards, int xp, item_t *item);

/* Creates a new task struct (allocates memory)
 * 
 * Parameters:
 * - mission: the mission to be completed for the quest
 * - id: the id of the task
 * - reward: the reward of the task
 * - prereq: the prerequisite of the task
 *
 * Returns: a pointer to the newly allocated task that is not completed
 */
task_t *task_new(mission_t *mission, char *id, reward_t *reward, prereq_t *prereq);

/* 
 * Initialize an already allocated task struct
 *
 * Parameters:
 * - task: an already allocated task
 * - mission: the mission to be completed for the task
 * - id: the id of the task
 * - reward: the reward of the task
 * - prereq: the prerequisite of the task
 * 
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 * 
 * Note: Also returns FAILURE if there is both a mission and prereqs. Missions should all be in their own tasks.
 *       If you want a task to have a mission and a prereq, make the mission's tasks a prereq for the actual task
 *       that has the prereqs.
 */
int task_init(task_t *task, mission_t *mission, char *id, reward_t *reward, prereq_t *prereq);

/* 
 * Frees a task struct from memory but does not free 
 * its associated pointers
 * 
 * Parameter:
 * - task: the task to be freed
 * 
 * Returns:
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */
int task_free(task_t *task);

/* Determines whether a player completed a mission (if possible for that mission type)
 *
 * Parameters:
 *  - mission: a mission object
 *  - player: a player
 * 
 * Returns:
 * - true if the player completed the mission, false if not
*/
bool completed_mission(mission_t *mission, player_t *player);

/* Checks if a player completed a given task
 * - Always returns false if the task has a mission and checks the 
 *  prerequisite if it does not
 * 
 * Parameter:
 * - task: pointer to the task
 * - player: pointer to player with the task
 *
 * Returns:
 * - false if task is incomplete
 * - true if task is complete
 */
bool is_task_completed(task_t *task, player_t *player);

/* Checks a task's status.
 *
 * Parameter:
 * - task: pointer to a task
 * - player: pointer to player with the task
 * 
 * Returns: 
 * - the task's completion for the given player (true = complete, false = incomplete)
 */
bool get_player_task_status(task_t *task, player_t *player);

/* Adds the contents of a reward struct to the player struct
 * 
 * Parameters:
 * - reward: the reward getting accepted
 * - player: the player accepting the reward
 * 
 * Returns:
 * - SUCCESS if added successfully, FAILURE if an error occured
*/
int accept_reward(reward_t *reward, player_t *player);


#endif /* TASK_H */