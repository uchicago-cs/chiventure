#ifndef QUESTS_STATE_H
#define QUESTS_STATE_H

#include <stdbool.h>
#include <string.h>
#include "quests_structs.h"
#include "game-state/player.h"

/* Creates a new mission struct (allocates memory)
 * 
 * Parameters:
 * - item_to_collect: the item to be collected for the mission
 * - npc_to_meet: the npc to be met for the mission
 * - npc_to_kill: the npc to kill for the mission
 * - room_to_visit: the room to visit for the mission 
 *
 * Returns: a pointer to the newly allocated mission, that is not completed
 */
mission_t *mission_new(item_t *item_to_collect, npc_t *npc_to_meet, 
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
 * - prereq: the prerequisite of the task
 *
 * Returns: a pointer to the newly allocated task that is not completed
 */
task_t *task_new(mission_t *mission, char *id, reward_t *reward, prereq_t *prereq);

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

/* Initialize an already allocated mission struct
 *
 * Parameters:
 * - mission: an already allocated mission_t 
 * - item_to_collect: the item to be collected for the mission
 * - npc_to_meet: the npc to be met for the mission
 * 
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 * 
 * Note: Also ensures that the mission only includes a single thing to do. If
 *       there is more than one pointer that is not NULL (excluding mission),
 *       this function will return FAILURE.
 */
int mission_init(mission_t *mission, item_t *item_to_collect, npc_t *npc_to_meet,
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

/* Gets a task tree who's immediate task has a given id from the given hash table
 *
 * Parameters:
 *  id: the task tree's immediate task's id string
 *  hash_table: a hashtable of quests, ideally from game_state
 *
 * Returns:
 *  task_tree struct if successful, NULL if task is not found
 */
task_tree_t *get_task_tree_from_hash(char *id, quest_hash_t *hash_table);

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

/*
 * Adds a task id to a prereq's task id list
 *
 * Parameters:
 * - prereq: The prereq getting added to
 * - task_id: A pointer to a string id getting added
 * 
 * Returns:
 * - SUCCESS if successfully added
 * - FAILURE if something went wrong
*/
int prereq_add_task(prereq_t *prereq, char *task_id);

/* Checks if a task's prereqs are met and if they are, completes the task, 
 * returning the task's reward on success. After completing the task, checks 
 * if the task completion also completed the task's quest.
 *
 * Parameter:
 * - tree: pointer to a task tree who's immediate task is getting completed
 * - player: pointer to player completing the task
 * 
 * Returns:
 * - the task's reward item
 * - NULL if the task is incomplete
 */
reward_t *complete_task(char *task_id, player_t *player, quest_hash_t *quest_hash);


/* returns the hash after deleting one or all quest.
 *
 * Parameter:
 * - pointer to a hash table
 * - quest ID, 
 * 
 * Returns:
 * - 0 if the removal was failure, 1 if successful 
 */
int remove_quest_in_hash(quest_hash_t *hash_table, char *quest_id);


/* returns the hash after deleting one or all quest.
 *
 * Parameter:
 * - pointer to a hash table
 * 
 * Returns:
 * - 0 if the removal was failure, 1 if successful 
 */
int remove_quest_all(quest_hash_t *hash_table);


#endif /* QUESTS_STATE_H */
