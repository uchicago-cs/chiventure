#ifndef QUESTS_STRUCTS_H
#define QUESTS_STRUCTS_H

// REMEMBER TO INCLUDE ANY ADDITIONAL RELEVANT FILES (NPC)
#include "game-state/item.h"
#include "common/common.h"
#include "common/utlist.h"
#include "npc/npc.h"

/* Forward declaration */
typedef struct npc npc_t;

/*
 * This struct represents the mission.
 * 
 * Components:
 *  item_to_collect: item to be collected in order to complete the mission
 *  npc_to_meet: npc to meet in order to complete the mission
 */
typedef struct mission {
    item_t *item_to_collect;
    npc_t *npc_to_meet;
} mission_t;


/* 
 * This struct represents an achievement.
 * 
 * Components:
 *  mission: mission to be completed
 *  id: string identifier for the achievement
 *  completed: bool for if achievement is completed
 */
typedef struct achievement {
    mission_t *mission;
    char *id;
    bool completed;     //0 is not completed, 1 is completed
} achievement_t;

/*
 * This is a non-binary tree struct of achievements (to replace linked list)
 *
 * Components:
 *  achievement: achievement in tree
 *  parent: parent node of achievement
 *  rsibling: the nearest right-hand sibling of the achievement node
 *  lmostchild: the leftmost child of the achievement node
 */
typedef struct achievement_tree {
    achievement_t *achievement;
    struct achievement_tree *parent;
    struct achievement_tree *rsibling;
    struct achievement_tree *lmostchild;
} achievement_tree_t;


/* 
 * This is the hashable struct for a quest 
 * Elements:
 * hh: used for hashtable, as provided in uthash.h
 * quest_id: the id of the quest
 * achievement_tree: non-binary tree struct holding a
 *                   tree of achievements that make up 
 *                   a quest
 * reward: reward of the quest is an item
 * status: -1: failed quest
 *         0: quest has not been started
 *         1: quest has been started but not completed
 *         2: quest has been completed
 */
typedef struct quest {
    UT_hash_handle hh;
    long int quest_id;
    achievement_tree_t *achievement_tree;
    item_t *reward;
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
