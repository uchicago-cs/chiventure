#ifndef QUESTS_STATE_H
#define QUESTS_STATE_H

#include <stdbool.h>
#include <string.h>
#include "quests_structs.h"

/* Creates a new passive mission struct (allocates memory)
 * 
 * Parameters:
 * - xp: integer experience milestone to reach
 * - levels: integer level milestone to reach
 * - health: integer health milestone to reach
 *
 * Returns: a pointer to the newly allocated passive mission, that is not completed
 */
passive_mission_t *passive_mission_new(int xp, int levels, int health);

/* Creates a new active mission struct (allocates memory)
 * 
 * Parameters:
 * - item_to_collect: the item to be collected for the mission
 * - npc_to_meet: the npc to be met for the mission
 * - npc_to_kill: the npc to kill for the mission
 * - room_to_visit: the room to visit for the mission 
 *
 * Returns: a pointer to the newly allocated passive mission, that is not completed
 */
active_mission_t *active_mission_new(item_t *item_to_collect, npc_t *npc_to_meet, 
                              npc_t *npc_to_kill, room_t *room_to_visit);

/* Creates a new reward struct for completing a quest 
 * 
 * Parameters:
 * - xp: xp reward
 * - item: item reward
 *
 * Returns: a pointer to the newly allocated reward struct
 */
reward_t *reward_new(int xp, item_t *item);

/* 
 * Creates a new prereq object on the heap
 *
 * Parameters:
 * - hp: health points required to begin quest
 * - level: level required to begin quest
 *
 * Returns: a pointer to the newly allocated prereq, or NULL if there was an error
 */
prereq_t *prereq_new(int hp, int level);

/* 
 * Creates a new id_list object on the heap
 *
 * Returns: a pointer to the newly allocated id_list, or NULL if there was an error
 * 
*/
id_list_t *id_list_new();


/* Creates a new task struct (allocates memory)
 * 
 * Parameters:
 * - mission: the mission to be completed for the quest
 * - id: the id of the task
 * - reward: the reward of the task
 *
 * Returns: a pointer to the newly allocated task that is not completed
 */
task_t *task_new(mission_t *mission, char *id, reward_t *reward);

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
                    reward_t *reward, prereq_t *stat_req);

/* Initialize an already allocated passive mission struct 
 *
 * Parameters:
 * - mission: an already allocated mission_t (of passive type)
 * - item_to_collect: the item to be collected for the mission
 * - npc_to_meet: the npc to be met for the mission
 * 
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 */
int passive_mission_init(passive_mission_t *mission, int xp, int level, int health);

/* Initialize an already allocated active mission struct 
 *
 * Parameters:
 * - mission: an already allocated mission_t (of active type)
 * - item_to_collect: the item to be collected for the mission
 * - npc_to_meet: the npc to be met for the mission
 * 
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 */
int active_mission_init(active_mission_t *mission, item_t *item_to_collect, npc_t *npc_to_meet,
                        npc_t *npc_to_kill, room_t *room_to_visit);

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

/* 
 * Initialize an already allocated task struct
 *
 * Parameters:
 * - task: an already allocated task
 * - mission: the mission to be completed for the task
 * - id: the id of the task
 * - reward: the reward of the task
 * 
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 */
int task_init(task_t *task, mission_t *mission, char *id, reward_t *reward);

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
               reward_t *reward, prereq_t *stat_req, int status);

/* 
 * Initializes a prereq object with the given parameters
 *
 * Parameters:
 * - prereq: The prereq getting initialized
 * - hp: health points required to begin quest
 * - level: level required to begin quest
 *
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 */
int prereq_init(prereq_t * prereq, int hp, int level);

/* 
 * Initializes an id_list as an empty list
 *
 * Parameters:
 * - id_list: The id_list getting initialized
 * 
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
*/
int id_list_init(id_list_t *id_list);

/* 
 * Frees a passive mission struct from memory
 * 
 * Parameter:
 * - mission: the mission to be freed
 * 
 * Returns:
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */
int passive_mission_free(passive_mission_t *mission);

/* 
 * Frees an active mission struct from memory
 * 
 * Parameter:
 * - mission: the mission to be freed
 * 
 * Returns:
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */
int active_mission_free(active_mission_t *mission);

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

/*
 * Frees a prereq struct from memory including the task list and quest list.
 *
 * Parameter:
 * - prereq: the prereq to be freed
 *
 * Returns:
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */
int prereq_free(prereq_t *prereq);

/*
 * Frees an id_list from memory
 * 
 * Parameter:
 * - id_list: the id_list to be freed
 * 
 * Returns:
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
*/
int id_list_free(id_list_t *id_list);


/* 
 * Determines whether a player meets a set of prerequisites
 * 
 * Parameter:
 * - prereq: a prerequisite object
 * - player: a player
 * 
 * Returns:
 * - true if the player meets the prerequisites, false if the player does not
 */
bool meets_prereqs(player_t *player, prereq_t *prereq);

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

/* Gets a quest from the given hash table
 *
 * Parameters:
 *  quest id string
 *  pointer to quest hash table
 *
 * Returns:
 *  quest struct if successful, NULL if quest is not found
 */
quest_t *get_quest_from_hash(char *quest_id, quest_hash_t *hash_table);

/* Adds a quest to the given hash table
 *
 * Parameters:
 *  pointer to quest struct
 *  pointer to quest hash table
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_quest_to_hash(quest_t *quest, quest_hash_t *hash_table);

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

/*
 * Traverses the task tree to find the task with the
 * given string identifier along a valid quest path.
 *
 * Parameters:
 * - tree: pointer to the task tree to be traversed
 * - id: pointer to a string identifier for the desired task
 *
 * Returns:
 * - pointer to the desired task, OR
 * - NULL if task cannot be found along a valid path
 *
 * Note: tasks must be completed in order according to this
 *       traversal. Only one task on each level can be completed,
 *       so this "locks" a user into a path once they've begun
 *       completing tasks.
 */
task_t *find_task_in_quest(task_tree_t *tree, char *id);

/*
 * Adds an id to an id_list
 *
 * Parameters:
 * - id_list: The id_list getting added to
 * - id: A pointer to a string id getting added
 * 
 * Returns:
 * - SUCCESS if successfully added
 * - FAILURE if something went wrong
*/
int id_list_add(id_list_t *id_list, char *id);

/*
 * Traverses all quests in the player struct and searches for a task with a given id
 *
 * Parameters:
 * - player: A player
 * - id: A pointer to a string identifier for the desired task
 * 
 * Returns:
 * - pointer to the desired task, OR
 * - NULL if task cannot be found along in any of the player's quests
 * 
 * Note:
 * - This function is EXTREMELY SLOW, as it requires searching through all of the player's
 *   quest trees. If the task isn't present and the player has many quests, this will be 
 *   quite inefficient, so try to call this function sparringly.
*/
task_t *find_task(player_t *player, char *id);

/*
 * Finds a quest in a player's list of quests
 *
 * Parameters:
 * - player: A player
 * - id: A pointer to a string identifier for the desired quest
 * 
 * Returns:
 * - pointer to the desired quest, OR
 * - NULL if quest cannot be found in the list
*/
quest_t *find_quest(player_t *player, char *id);

#endif /* QUESTS_STATE_H */
