#ifndef TASK_H
#define TASK_H

#include "game-state/item.h"
#include "common/common.h"
#include "common/utlist.h"
#include "npc/npc.h"
#include "game-state/player.h"

/* Forward declaration */
typedef struct npc npc_t;

/* structs related to tasks */

/*
 * This struct represents a passive mission.
 * 
 * A passive mission is one that the player does not
 * manually explore chiventure to acquire.
 *
 * Components:
 *  xp: integer list of xp milestones
 *  levels: integer list of level milestones
 *  health: integer list of health milestones
 */
typedef struct passive_mission{
    int xp;
    int levels;
    int health;
} passive_mission_t;

/*
 * This struct represents an active mission.
 * 
 * An active mission is one that the player
 * has to explore chiventure to acquire. 
 *
 * Components:
 *  item_to_collect: an item to collect
 *  npc_to_meet: an npc to meet
 *  npc_to_kill: an npc to kill
 *  room_to_visit: a room to visit
 */
typedef struct active_mission {
    item_t *item_to_collect;
    npc_t *npc_to_meet;
    npc_t *npc_to_kill;
    room_t *room_to_visit;
} active_mission_t;

/*
 * This union represents a mission. Can be used to create a task.
 * 
 * Components:
 *  a_mission: an active mission
 *  p_mission: a passive mission
 *
 */
typedef union mission {
    active_mission_t *a_mission;
    passive_mission_t *p_mission;
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
 *  completed: bool for if task is completed
 */
typedef struct task {
    mission_t *mission;
    char *id;
    reward_t *reward;
    bool completed;     //0 is not completed, 1 is completed
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
 * - mission: the mission to be completed for the quest
 * - id: the id of the task
 * - reward: the reward of the task
 *
 * Returns: a pointer to the newly allocated task that is not completed
 */
task_t *task_new(mission_t *mission, char *id, reward_t *reward);

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