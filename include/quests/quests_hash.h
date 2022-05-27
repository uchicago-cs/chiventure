#ifndef QUEST_HASH_H
#define QUEST_HASH_H

#include "quest.h"
#include "game-state/player.h"

/*
 * This typedef distinguishes between quest_t pointers
 * which are used to point to quest_t structs in the 
 * traditional sense and those which are used to hash
 * quest_t structs with the UTHASH macros as specified
 * in include/common
 */
typedef struct quest quest_hash_t;

/*
 * A task hash table. Uses a wrapper instead of adding the hash
 * handle to the task struct as with quests since for some reason,
 * adding the hash handle to the task struct causes crashes and odd
 * behavior.
 */
typedef struct task_hash {
    task_t *task;
    char *id;
    UT_hash_handle hh;
} task_hash_t;

/* Stores important information necessary for the majority of quest functions */
typedef struct quest_ctx {
    player_t *player;
    quest_hash_t *quest_hash;
} quest_ctx_t;

/* Allocates memory for and initializes a new quest_ctx object
 * 
 * Parameters:
 * - player: a player
 * - quest_hash: A quest hash table, ideally game->all_quests
 * 
 * Returns:
 * - A pointer to an initialized quest_ctx_t object
*/
quest_ctx_t *quest_ctx_new(player_t *player, quest_hash_t *quest_hash);

/* Initializes a new quest_ctx object
 * 
 * Parameters:
 * - quest_ctx: An already allocated quest_ctx object
 * - player: a player
 * - quest_hash: A quest hash table, ideally game->all_quests
 * 
 * Returns:
 * - SUCCESS if initialized successfully, FAILURE if any problems occured
*/
int quest_ctx_init(quest_ctx_t *quest_ctx, player_t *player, quest_hash_t *quest_hash);

/* Frees a quest_ctx object, but does not free the player or quest hash in the obejct
 *
 * Parameter:
 * - quest_ctx: The quest_ctx to be freed
 * 
 * Returns:
 * - SUCCESS if freed successfully, FAILURE if an error occured
*/
int quest_ctx_free(quest_ctx_t *quest_ctx);

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

/* Gets a task from the given quest hash table
 *
 * Parameters:
 *  id: the task's id string
 *  hash_table: a hashtable of quests, ideally from game_state
 *
 * Returns:
 *  task struct if successful, NULL if task is not found
 */


task_t *get_task_from_quest_hash(char *id, quest_hash_t *hash_table);

/* Finds the element with the given id in the task hash
 *
 * Parameters:
 *  id: the id string searching for
 *  hash_table: a hashtable of tasks
 *
 * Returns:
 *  task hash struct if successful, NULL if id is not found
 */
task_hash_t *search_task_hash(char *id, task_hash_t *hash_table);

/* Gets a task from the given task hash table
 *
 * Parameters:
 *  id: the task's id string
 *  hash_table: a hashtable of tasks
 *
 * Returns:
 *  task struct if successful, NULL if task is not found
 */
task_t *get_task_from_task_hash(char *id, task_hash_t *hash_table);

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

/* Adds a task to the given task hash table
 *
 * Parameters:
 *  task: pointer to task struct
 *  hash_table: pointer to a hashtable of tasks
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_task_to_hash(task_t *task, task_hash_t **hash_table);

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
 * - qctx: pointer to quest context struct with info on player and all quests
 * - completion: the completion status of the quest
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_quest_to_player(quest_t *quest, quest_ctx_t *qctx, int completion);

/* Adds a player task to the given hash table
 *
 * Parameters:
 *  task: pointer to task struct
 *  qctx: pointer to quest context struct with information about player and all quests
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_task_to_player_hash(task_t *task, quest_ctx_t *qctx);

/* Removes a quest from a hash table
 *
 * Parameter:
 * - pointer to a quest hash table
 * - quest ID, 
 * 
 * Returns:
 * - FAILURE if the removal was failure, SUCESS if successful 
 */
int remove_quest_in_hash(quest_hash_t *hash_table, char *quest_id);

/* Returns the (now NULL) hash table after deleting and freeing
 *  all quests
 *
 * Parameter:
 * - pointer to a hash table
 * 
 * Returns:
 * - FAILURE if the removal was failure, SUCESS if successful 
 */
int remove_quest_all(quest_hash_t **hash_table);

/* Removes a task from a task hash table
 *
 * Parameter:
 * - pointer to a task hash table
 * - task ID, 
 * 
 * Returns:
 * - FAILURE if the removal was failure, SUCCESS if successful 
 */
int remove_task_in_hash(task_hash_t *hash_table, char *id);

/* Returns the (now NULL) hash after deleteting and freeing
 * all tasks
 *
 * Parameter:
 * - pointer to a task hash table
 * 
 * Returns:
 * - FAILURE if the removal was failure, SUCCESS if successful 
 */
int remove_task_all(task_hash_t **hash_table);

/* Removes a task from a player hash table
 *
 * Parameter:
 * - pointer to a player task hash table
 * - quest ID, 
 * 
 * Returns:
 * - FAILURE if the removal was failure, SUCESS if successful 
 */
int remove_task_in_player_hash(player_task_hash_t *ptasks, char *quest_id);

#endif /* QUEST_HASH_H */
