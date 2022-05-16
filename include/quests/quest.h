#ifndef QUEST_H
#define QUEST_H

#include "task.h"

/* structs for completion of quest */

/*
 * This struct represents a skill requirement for a quest.
 *
 * Components:
 *  hp: health points 
 *  level: a number of levels gained
 */
typedef struct stat_req {
    int hp;
    int level;
} stat_req_t;

/* 
 * This is the hashable struct for a quest 
 * Elements:
 * quest_id: the id of the quest
 * task_tree: non-binary tree struct holding a tree of
 *                   tasks that make up a quest
 * reward: reward of the quest is either experience, an item, or both
 * stat_req: stat requirement for the quest
 * status: -1: failed quest
 *          0: quest has not been started
 *          1: quest has been started but not completed
 *          2: quest has been completed
 */
typedef struct quest  {
    char *quest_id;
    task_tree_t *task_tree;
    reward_t *reward;
    stat_req_t *stat_req;
    int status;  
    UT_hash_handle hh;
} quest_t;

/* Creates a new stats requirement struct to start the quest
 * 
 * Parameters:
 * - xp: xp reward
 * - item: item reward
 *
 * Returns: a pointer to the newly allocated stats requirement struct
 */
stat_req_t *stat_req_new(int hp, int level);

/* Initializes an already allocated stats requirement struct
 * 
 * Parameters:
 * - xp: xp reward
 * - item: item reward
 *
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 */
int stat_req_init(stat_req_t *stat_req, int xp, int level);

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
                    reward_t *reward, stat_req_t *stat_req);

/* Initialize an already allocated quest struct
 *
 * Parameters:
 * - q: an already allocated quest
 * - quest_id: string representing the specific quest_id 
 * - task_tree: non-binary tree struct holding a tree of 
 *                     tasks that make up a quest
 * - reward: reward of the quest is an item
 * - status: int indicating the status of the quest (refer to
 *           quests_structs.h for all possible statuses)
 * 
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 * 
 */
int quest_init(quest_t *q, char *quest_id, task_tree_t *task_tree, 
               reward_t *reward, stat_req_t *stat_req, int status);

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

/* 
 * Determines whether a player can start a quest with their base stats
 * 
 * Parameter:
 * - quest: a quest
 * - player: a player
 * 
 * Returns:
 * - 1: a player can start the quest
 * - 0: a player cannot start the quest
 */
int can_start_quest(quest_t *quest, player_t *player);

/* Updates a quest's status to started
 *
 * Parameter:
 * - quest: pointer to quest to be marked started
 * 
 * Returns:
 * - SUCCESS 
 * - FAILURE
 */
int start_quest(quest_t *quest);

/* Updates a quest's status to failed
 *
 * Parameter:
 * - quest: pointer to quest to be marked failed
 * 
 * Returns:
 * - SUCCESS 
 * - FAILURE
 */
int fail_quest(quest_t *quest);

/* Completes a task in a quest by checking if a given
 * task ID matches any incomplete tasks in the
 * appropriate level of the task tree. Returns the reward
 * of the completed task.
 * 
 * Parameters:
 * - quest: pointer to the quest
 * - id: the string identifier of the completed task
 *  
 * Returns:
 * - the task's reward item
 * - NULL if the task is incomplete
 * 
 */
reward_t *complete_task(quest_t *quest, char *id);

/* Checks if a quest is completed
 * 
 * Parameter:
 * - quest: pointer to the quest
 *
 * Returns:
 * - 0 if quest is incomplete
 * - 1 if quest is complete
 */
int is_quest_completed(quest_t *quest);

/* Checks a quest's status.
 *
 * Parameter:
 * - quest: pointer to a quest
 * 
 * Returns: 
 * - the quest's status code, as described in quests_structs.h
 */
int get_quest_status(quest_t *quest);

/* Returns the quest's reward item if the quest has been completed.
 *
 * Parameter:
 * - quest: pointer to a quest
 * 
 * Returns:
 * - the quest's reward item
 * - NULL if the quest is incomplete
 * 
 * Note:
 * The status of the quest should first be checked before this function is called
 */
reward_t *complete_quest(quest_t *quest);

#endif /* QUEST_H */
