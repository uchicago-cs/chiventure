#ifndef QUESTS_STRUCTS_H
#define QUESTS_STRUCTS_H

// REMEMBER TO INCLUDE ANY ADDITIONAL RELEVANT FILES (NPC)
#include "game-state/item.h"
#include "common/common.h"
#include "common/utlist.h"

/* 
 * This union represents the mission.
 * 
 * Note: Although this is currently a union, it might be formed into
 *       a struct in future implementations.
 *
 */
typedef union mission {
    item_t *item_to_collect;
    npc_t *npc_to_meet;
} mission_u;


/* 
 * This union represents an achievement.
 */
typedef struct achievement {
    mission_u mission;
    bool completed;
} achievement_t;


/* 
 * This is a linked list struct of achievements.
 */
typedef struct achievement_llist {
    achievement_t *achievement;
    struct achievement_llist *next;
} achievement_llist_t;


/* 
 * This is the hashable struct for a quest 
 */
typedef struct quest  {
    UT_hash_handle hh;
    char* quest_id;
    achievement_llist_t *achievement_list;    //linked list struct holding a list of achievements that make up a quest
    item_t *reward;    //reward of the quest is an item
    int status;    /* 0: quest has been completed
                    * 1: quest has been started but not completed
                    * 2: quest has not been started
                    */
 } quest_t;

typedef struct quest quest_hash_t;


#endif