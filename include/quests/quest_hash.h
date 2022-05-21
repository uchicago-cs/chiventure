#ifndef QUEST_HASH_H
#define QUEST_HASH_H

#include "prereq.h"

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