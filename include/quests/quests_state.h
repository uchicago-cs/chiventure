#ifndef QUESTS_STATE_H
#define QUESTS_STATE_H

#include <stdbool.h>
#include <string.h>
#include "quests_structs.h"
#include "game-state/player.h"

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

/* Creates a new stats requirement struct to start the quest
 * 
 * Parameters:
 * - xp: xp reward
 * - item: item reward
 *
 * Returns: a pointer to the newly allocated stats requirement struct
 */
stat_req_t *stat_req_new(int hp, int level);

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
                    reward_t *reward, stat_req_t *stat_req);

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

/* Initialize an already allocated task struct
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
 * 
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 * 
 */
int quest_init(quest_t *q, char *quest_id, task_tree_t *task_tree, 
               reward_t *reward, stat_req_t *stat_req);

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
 * Determines whether a player can start a quest with their base stats
 * 
 * Parameter:
 * - quest: a quest
 * - player: a player
 * 
 * Returns:
 * - true: a player can start the quest
 * - false: a player cannot start the quest
 */
bool can_start_quest(quest_t *quest, player_t *player);

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
 * 
 * Returns:
 * - SUCCESS 
 * - FAILURE
 */
int start_quest(quest_t *quest, player_t *player);

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

/* Completes a task in a quest for a given player
 * 
 * Parameters:
 * - task: pointer to the task
 * - player: pointer to player completing the task
 *  
 * Returns:
 * - the task's reward item
 * - NULL if the task is incomplete
 * 
 */
reward_t *complete_task(task_t *task, player_t *player);

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

/* Checks if a player completed a given rask and updates the 
 * reference to the task in the player's task table accordingly
 * 
 * Parameter:
 * - task: pointer to the task
 * - player: pointer to player with the task
 *
 * Returns:
 * - false if task is incomplete
 * - true if task is complete
 * 
 * Note: Currently always returns true assuming there's no error, as the 
 *       current mission system makes checking essentially impossible.
 *       Once quest prerequisites are added, this function must be updated
 *       to add this functionality.
 */
bool is_task_completed(task_t *task, player_t *player);

/* Gets a quest from the given hash table
 *
 * Parameters:
 *  quest_id: the quest's id string
 *  hash_table: a hashtable of quests, ideally from game_state
 *
 * Returns:
 *  quest struct if successful, NULL if quest is not found
 */
quest_t *get_quest_from_hash(char *quest_id, quest_hash_t *hash_table);

/* Gets a task from the given hash table
 *
 * Parameters:
 *  id: the task's id string
 *  hash_table: a hashtable of quests, ideally from game_state
 *
 * Returns:
 *  task struct if successful, NULL if task is not found
 */
task_t *get_task_from_hash(char *id, quest_hash_t *hash_table);

/* Adds a quest to the given hash table
 *
 * Parameters:
 *  quest: pointer to quest struct
 *  hash_table: pointer to a hashtable of quests, ideally from game_state
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_quest_to_hash(quest_t *quest, quest_hash_t **hash_table);


/* Gets a player quest from the given hash table
 *
 * Parameters:
 *  quest_id: the quest's id string
 *  hash_table: a hashtable of player_quests from the player
 *
 * Returns:
 *  player_quest struct if successful, NULL if the quest is not found
 */
player_quest_t *get_player_quest_from_hash(char *quest_id, player_quest_hash_t *hash_table);

/* Gets a player task from the given hash table
 *
 * Parameters:
 *  id: the task's id string
 *  hash_table: a hashtable of player_tasks from the player
 *
 * Returns:
 *  player_task struct if successful, NULL if the task is not found
 */
player_task_t *get_player_task_from_hash(char *id, player_task_hash_t *hash_table);

/* Adds a player quest to the given hash table
 *
 * Parameters:
 *  quest: pointer to quest struct
 *  hash_table: pointer to player quest hash table
 *  completion: the completion status of the quest
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_quest_to_player_hash(quest_t *quest, player_quest_hash_t **hash_table, int completion);

/* Adds a player task to the given hash table
 *
 * Parameters:
 *  tasj: pointer to task struct
 *  hash_table: pointer to player task hash table
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_task_to_player_hash(task_t *task, player_task_hash_t **hash_table);

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

/* Returns the task's reward item if the task has been completed.
 *
 * Parameter:
 * - task: pointer to a task
 * - player: pointer to player completing the task
 * 
 * Returns:
 * - the task's reward item
 * - NULL if the task is incomplete
 * 
 * Note:
 * The status of the task should first be checked before this function is called
 */
reward_t *complete_task(task_t *task, player_t *player);

#endif /* QUESTS_STATE_H */
