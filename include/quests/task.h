#ifndef TASK_H
#define TASK_H

#include "game-state/item.h"
#include "prereq.h"

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

/* Creates a new task struct (allocates memory)
 * 
 * Parameters:
 * - id: the id of the task
 * - mission: the mission to be completed for the quest
 * - reward: the reward of the task
 * - prereq: the prerequisite of the task
 *
 * Returns: a pointer to the newly allocated task that is not completed
 */
task_t *task_new(char *id, mission_t *mission, reward_t *reward, prereq_t *prereq);

/* 
 * Initialize an already allocated task struct
 *
 * Parameters:
 * - task: an already allocated task
 * - id: the id of the task
 * - mission: the mission to be completed for the task
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
int task_init(task_t *task, char *id, mission_t *mission, reward_t *reward, prereq_t *prereq);

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
 * Frees a task tree struct from memory b
 * 
 * Parameter:
 * - task_tree: the task to be freed
 * 
 * Returns:
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */

 int task_tree_free(task_tree_t *task_tree); 


#endif /* TASK_H */