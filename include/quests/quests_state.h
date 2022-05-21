#ifndef QUESTS_STATE_H
#define QUESTS_STATE_H

#include <stdbool.h>
#include <string.h>
#include "quests_hash.h"

typedef struct item_wrapped_for_llist item_list_t; // Forward declaration

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

/* 
 * Determines whether a player meets a set of prerequisites
 * 
 * Parameters:
 * - prereq: a prerequisite object
 * - player: a player
 * 
 * Returns:
 * - true if the player meets the prerequisites, false if the player does not
 */
bool meets_prereqs(player_t *player, prereq_t *prereq);

/* quest functionality */

/* Adds a task to the tree given an parent tree id
 *
 * Parameters:
 * - quest: pointer to a quest 
 * - task_to_add: pointer to a task to add to the list
 * - parent_id: string that is parent task's id
 * 
 * Returns:
 * - SUCCESS 
 * - FAILURE 
 */
int add_task_to_quest(quest_t *quest, task_t *task_to_add, char *parent_id);

/* Updates a quest's status to started
 *
 * Parameter:
 * - quest: pointer to quest to be started
 * - player: pointer to player starting the quest
 * - quest_hash: pointer to hash table of all quests
 *
 * Returns:
 * - SUCCESS 
 * - FAILURE
 */
int start_quest(quest_t *quest, player_t *player, quest_hash_t *quest_hash);

/* Updates a quest's status to failed
 *
 * Parameter:
 * - quest: pointer to quest to be marked failed
 * - player: pointer to player failing the quest
 * 
 * Returns:
 * - SUCCESS 
 * - FAILURE
 */
int fail_quest(quest_t *quest, player_t *player);

/* Checks if a player completed a given quest and updates the 
 * reference to the quest in the player's quest table accordingly
 * 
 * Parameter:
 * - quest: pointer to the quest
 * - player: pointer to player with the quest
 *
 * Returns:
 * - false if quest is incomplete
 * - true if quest is complete
 */
bool is_quest_completed(quest_t *quest, player_t *player);

/* Gets the quest that has the given task as one of its tasks
 *
 * Parameters:
 *  task_id: the task tree's immediate task's id string
 *  hash_table: a hashtable of quests, ideally from game_state
 *
 * Returns:
 *  quest struct if successful, NULL if task is not found
 */
quest_t *get_quest_of_task(char *task_id, quest_hash_t *hash_table);

/* Checks a quest's status.
 *
 * Parameter:
 * - quest: pointer to a quest
 * - player: pointer to player with the quest
 * 
 * Returns: 
 * - the quest's completion for the given player
 */
int get_player_quest_status(quest_t *quest, player_t *player);

/* Checks if a task's prereqs are met and if they are, completes the task, 
 * returning the task's reward on success. After completing the task, checks 
 * if the task completion also completed the task's quest, adds any new tasks
 * from the tree if not and accepts the quest's rewards if so.
 *
 * Parameter:
 * - task_id: the stringid of the task getting completed
 * - player: the player completing the task
 * - quest_hash: A hash table of all quests, ideally game->all_quests
 * 
 * Returns:
 * - the task's reward item
 * - NULL if the task is incomplete
 */
reward_t *complete_task(char *task_id, player_t *player, quest_hash_t *quest_hash);

/* Returns the quest's reward item if the quest has been completed.
 *
 * Parameter:
 * - quest: pointer to a quest
 * - player: pointer to player completing the quest
 * 
 * Returns:
 * - the quest's reward item
 * - NULL if the quest is incomplete
 * 
 * Note:
 * The status of the quest should first be checked before this function is called
 */
reward_t *complete_quest(quest_t *quest, player_t *player);

/* Checks if all of the player's tasks are complete and updates them accordingly
 * 
 * Parameter:
 * - player: the player getting checked
 * - quest_hash: a hash table of all of the quests in the game
 * 
 * Returns:
 * - SUCCESS if tasks are checked successfully, FAILURE if an error occured
*/
int update_player_quests(player_t *player, quest_hash_t *quest_hash);

#endif /* QUESTS_STATE_H */