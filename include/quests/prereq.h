#ifndef PREREQ_H
#define PREREQ_H

#include "game-state/item.h"
#include "common/common.h"
#include "common/utlist.h"
#include "game-state/player.h"

/* structs related to prereqs */

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
int prereq_init(prereq_t *prereq, int hp, int level);

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

#endif