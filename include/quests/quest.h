#ifndef QUEST_H
#define QUEST_H

#include "task.h"

/* structs for completion of quest */

/* 
 * This is the hashable struct for a quest 
 * Elements:
 * quest_id: the id of the quest
 * task_tree: non-binary tree struct holding a tree of
 *                   tasks that make up a quest
 * reward: reward of the quest is either experience, an item, or both
 * stat_req: stat requirement for the quest
 */
typedef struct quest  {
    char *quest_id;
    task_tree_t *task_tree;
    reward_t *reward;
    prereq_t *prereq;
    UT_hash_handle hh;
} quest_t;

/*
 * This typedef distinguishes between quest_t pointers
 * which are used to point to quest_t structs in the 
 * traditional sense and those which are used to hash
 * quest_t structs with the UTHASH macros as specified
 * in include/common
 */
typedef struct quest quest_hash_t;

/* Creates a new quest struct (allocates memory)
 * 
 * Parameters:
 * - quest_id: string representing the specific quest_id 
 * - task_tree: non-binary tree  struct holding a tree of 
 *                     tasks that make up a quest
 * - reward: reward of the quest is an item
 * 
 * Returns: a pointer to the newly allocated quest, with default status of 0
 *         (not started)
 */
quest_t *quest_new(char *quest_id, task_tree_t *task_tree,
                    reward_t *reward, prereq_t *prereq);

/* Initialize an already allocated quest struct
 *
 * Parameters:
 * - q: an already allocated quest
 * - quest_id: string representing the specific quest_id 
 * - task_tree: non-binary tree struct holding a tree of 
 *                     tasks that make up a quest
 * - reward: reward of the quest is an item
 * 
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 * 
 */
int quest_init(quest_t *q, char *quest_id, task_tree_t *task_tree, 
               reward_t *reward, prereq_t *stat_req);

/* 
 * Frees a quest struct from memory including the task list
 * and reward, but otherwise does not free associated pointers
 * 
 * Parameter:
 * - quest: the quest to be freed
 * 
 * Returns:
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */
int quest_free(quest_t *quest);


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

/*
 * Adds a quest id to a prereq's quest id list
 *
 * Parameters:
 * - prereq: The prereq getting added to
 * - quest_id: A pointer to a string id getting added
 * 
 * Returns:
 * - SUCCESS if successfully added
 * - FAILURE if something went wrong
*/
int prereq_add_quest(prereq_t *prereq, char *quest_id);

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


#endif /* QUEST_H */
