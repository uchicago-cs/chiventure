#ifndef QUEST_HASH_H
#define QUEST_HASH_H

#include "quest.h"
#include "game-state/player.h"

/*
 * Helper function to compare two tasks.
 *
 * Parameters:
 * - a1, a2: the two tasks to be compared
 *
 * Returns:
 * - 0 if the tasks are the same
 * - 1 otherwise
 */
int compare_tasks(task_t *a1, task_t *a2);

/*
 * Traverses the task tree to find the task with the
 * given string identifier along a valid quest path.
 *
 * Parameters:
 * - tree: pointer to the task tree to be traversed
 * - id: pointer to a string identifier for the desired task
 *
 * Returns:
 * - pointer to the tree immediately containing the task, OR
 * - NULL if task cannot be found along a valid path
 *
 * Note: Traversal no longer relies on task completion, so 
 *       runtime is now O(T) where T is the number of tasks
 *       in the game
 */
task_tree_t *find_task_tree_of_task_in_tree(task_tree_t *tree, char *id);

/*
 * This typedef distinguishes between quest_t pointers
 * which are used to point to quest_t structs in the 
 * traditional sense and those which are used to hash
 * quest_t structs with the UTHASH macros as specified
 * in include/common
 */
typedef struct quest quest_hash_t;

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

/* Adds a player quest to the given player's player quest table
 *
 * Parameters:
 * - quest: pointer to quest struct
 * - pointer: pointer to player
 * - completion: the completion status of the quest
 * - quest_hash: pointer to hash table of all quests
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_quest_to_player(quest_t *quest, player_t *player, int completion, quest_hash_t *quest_hash);

/* Adds a player task to the given hash table
 *
 * Parameters:
 *  task: pointer to task struct
 *  hash_table: pointer to player task hash table
 *  quest_hash: pointer to hash table of all quests
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_task_to_player_hash(task_t *task, player_task_hash_t **hash_table, quest_hash_t *quest_hash);

/* Returns the hash after deleting one or all quest.
 *
 * Parameter:
 * - pointer to a hash table
 * - quest ID, 
 * 
 * Returns:
 * - 0 if the removal was failure, 1 if successful 
 */
int remove_quest_in_hash(quest_hash_t *hash_table, char *quest_id);


/* Returns the hash after deleting one or all quest.
 *
 * Parameter:
 * - pointer to a hash table
 * 
 * Returns:
 * - 0 if the removal was failure, 1 if successful 
 */
int remove_quest_all(quest_hash_t *hash_table);

#endif /* QUEST_HASH_H */