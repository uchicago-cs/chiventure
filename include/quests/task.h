#ifndef TASK_H
#define TASK_H

#include "game-state/item.h"
#include "common/common.h"
#include "common/utlist.h"
#include "game-state/player.h"

/* structs related to tasks */

/* An enum representing the possible mission types currently supported */
typedef enum mission_types {
    MEET_NPC,
    KILL_NPC,
    COLLECT_ITEM,
    VISIT_ROOM,
} mission_types_t;

/*
 * This struct represents a mission.
 *
 * Components:
 * - target_name: The name of the mission's target (ie the NPC's name, the item's name, etc)
 * - type: The type of 
 */
typedef struct mission {
    char *target_name;
    mission_types_t type;
} mission_t;

/* 
 * This struct represents a reward for completing a quest or task.
 *
 * Components:
 *  xp: an xp amount gained
 *  item: an item gained
 */
typedef struct reward {
   int xp;
   item_t *item;
} reward_t;

/*
 * A linked list of quest/task ids
 */
typedef struct id_list {
    id_list_node_t *head;
    int length;
} id_list_t;

/*
 * This struct represents a prerequisite for a quest or task.
 *
 * Components:
 *  hp: health points 
 *  level: a number of levels gained
 *  task_list: a list of task ids that will all be checked for completion
 *  quest_list: a list of quest ids that will all be checked for completion
 */
typedef struct prereq {
    int hp;
    int level;
    id_list_t *task_list;
    id_list_t *quest_list;
} prereq_t;

/* 
 * This struct represents a task.
 * 
 * Components:
 *  mission: mission to be completed
 *  id: string identifier for the task
 *  reward: reward for completing the task.
 *  prereq: prerequisite for beginning a task
 */
typedef struct task {
    mission_t *mission;
    char *id;
    reward_t *reward;
    prereq_t *prereq;
} task_t;

/*
 * This is a non-binary tree struct of tasks (to replace linked list)
 *
 * Components:
 *  task: task in tree
 *  parent: parent node of task
 *  rsibling: the nearest right-hand sibling of the task node
 *  lmostchild: the leftmost child of the task node
 */
typedef struct task_tree {
    task_t *task;
    struct task_tree *parent;
    struct task_tree *rsibling;
    struct task_tree *lmostchild;
} task_tree_t;

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
 * Creates a new id_list object on the heap
 *
 * Returns: a pointer to the newly allocated id_list, or NULL if there was an error
 * 
*/
id_list_t *id_list_new();

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


// OTHER STUFF

/*
 * Find the bottom node on the left side of a tree
 *
 * Parameters:
 * - t: a pointer to a tree
 *
 * Returns:
 * - a pointer to the tree with no children on the left side of the tree
 */
task_tree_t *get_bottom_node(task_tree_t *t)

/*
 * Function that finds an task tree given its string ID.
 * It's called find_parent() because of its use to find parent nodes
 * in add_task_to_quest() in quest.h
 *
 * Parameters:
 * - tree: a pointer to an task tree
 * - id: the string identifier of the task being searched for
 *
 * Returns:
 * - NULL if task cannot be found
 * - The task tree being searched for
 */ 
task_tree_t *find_parent(task_tree_t *tree, char *id)

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
task_t *find_task(task_tree_t *tree, char *id)

#endif /* TASK_H */