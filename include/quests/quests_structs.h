#ifndef QUESTS_STRUCTS_H
#define QUESTS_STRUCTS_H

// REMEMBER TO INCLUDE ANY ADDITIONAL RELEVANT FILES (NPC)
#include "game-state/item.h"
#include "common/common.h"
#include "common/utlist.h"
#include "npc/npc.h"
#include "game-state/player.h"

/* Forward declaration */
typedef struct npc npc_t;

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
    prereq_t *prereq;
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
 * A single quest/task id node for the linked list
*/
typedef struct id_list_node {
    char *id;
    struct id_list_node *next;
} id_list_node_t;

/* 
 * This is the hashable struct for a quest 
 * Elements:
 * quest_id: the id of the quest
 * task_tree: non-binary tree struct holding a tree of
 *                   tasks that make up a quest
 * reward: reward of the quest is either experience, an item, or both
 * stat_req: stat requirement for the quest
 * status: -1: failed quest
 *          0: quest has not been started
 *          1: quest has been started but not completed
 *          2: quest has been completed
 */
typedef struct quest  {
    UT_hash_handle hh;
    char *quest_id;
    task_tree_t *task_tree;
    reward_t *reward;
    prereq_t *prereq;
    int status;  
} quest_t;

/*
 * This typedef distinguishes between quest_t pointers
 * which are used to point to quest_t structs in the 
 * traditional sense and those which are used to hash
 * quest_t structs with the UTHASH macros as specified
 * in include/common
 */
typedef struct quest quest_hash_t;


#endif 
