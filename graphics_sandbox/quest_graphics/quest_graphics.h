#ifndef QUEST_GRAPHICS_H
#define QUEST_GRAPHICS_H

#include "raylib.h"
#include "uthash.h"

/*Later we should include the following structs
  instead of manually defining them*/


typedef struct passive_mission{
    int xp;
    int levels;
    int health;
} passive_mission_t;

typedef struct active_mission {
    item_t *item_to_collect;
    npc_t *npc_to_meet;
    npc_t *npc_to_kill;
    room_t *room_to_visit;
} active_mission_t;

typedef union mission {
    active_mission_t *a_mission;
    passive_mission_t *p_mission;
} mission_t;


typedef struct task {
    mission_t *mission;
    char *id;
    bool completed;     //0 is not completed, 1 is completed
} task_t;

typedef struct task_tree {
    task_t *task;
    struct task_tree *parent;     //parent node of task
    struct task_tree *rsibling;     //the nearest right-hand sibling of the task node
    struct task_tree *lmostchild;     //the leftmost child of the task node
} task_tree_t;

typedef struct quest  {
    UT_hash_handle hh;
    long int quest_id;
    task_tree_t *task_tree;
    reward_t *reward;
    stat_req_t *stat_req;
    int status;  
} quest_t;

typedef struct quest quest_hash_t;



#endif