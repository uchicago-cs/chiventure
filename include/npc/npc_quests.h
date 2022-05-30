#ifndef _NPC_QUESTS_H
#define _NPC_QUESTS_H

#include "game-state/game_state_common.h"
#include "npc/dialogue.h"
#include "cli/util.h"
#include "quests/quests_hash.h"
#include "quests/quests_state.h"

/* Forward Declaration */
typedef struct npc_quest npc_quest_t;

/* 
 * A singular quest node for npc_quest_list_t 
 * (provided by the Quest team)
*/ 
typedef struct npc_quest {
   char *id;
   convo_t *dialogue;
   npc_quest_t *next;
} npc_quest_t;

/* 
 * A linked list of npc_quest structs
 * (provided by the Quest team)
*/ 
typedef struct npc_quest_list {
   npc_quest_t *head;
   int length;
} npc_quest_list_t;

/* 
 * tasks and task lists have the same format as quest lists
 * (provided by the Quest team)
*/
typedef npc_quest_t npc_task_t;
typedef npc_quest_list_t npc_task_list_t;

/*
 * Initializes a npc_quest struct
 * 
 * Parameters:
 * - quest_id: the quest id
 * - quest_dialogue: a conversation unique to this quest
 * 
 * Returns:
 * - SUCCESS upon successful initialization, FAILURE upon failed initialization
*/
int npc_quest_init(npc_quest_t *npc_quest, char *quest_id, 
                   convo_t *quest_dialogue);

/*
 * Creates a new npc_quest struct (allocated memory)
 * 
 * Parameters:
 * - id: the quest id
 * - quest_dialogue: a conversation unique to this quest
 * 
 * Returns:
 * - a pointer to the npc_quest struct
*/
npc_quest_t *npc_quest_new(char *quest_id, convo_t *quest_dialogue);

/*
 * Frees an npc_quest struct
 *
 * Parameters:
 * - npc_quest: the quest to be freed
 *
 * Returns:
 * - SUCCESS upon successful free, FAILURE upon failed free
*/
int npc_quest_free(npc_quest_t *npc_quest);

/*
 * Initializes a npc_task struct
 * 
 * Parameters:
 * - id: the task id
 * - task_dialogue: a conversation unique to this task
 * 
 * Returns:
 * - SUCCESS upon successful initialization, FAILURE upon failed initialization
*/
int npc_task_init(npc_task_t *npc_task, char *task_id, convo_t *task_dialogue);

/*
 * Creates a new npc_task struct (allocated memory)
 * 
 * Parameters:
 * - id: the task id
 * - task_dialogue: a conversation unique to this task
 * 
 * Returns:
 * - a pointer to the npc_quest struct
*/
npc_task_t *npc_task_new(char *task_id, convo_t *task_dialogue);

/*
 * Frees an npc_task struct
 *
 * Parameters:
 * - npc_task: the task to be freed
 *
 * Returns:
 * - SUCCESS upon successful free, FAILURE upon failed free
*/
int npc_task_free(npc_task_t *npc_task);

/*
 * Initializes a npc_quest_list struct
 * 
 * Parameters:
 * - quest_list: an uninitialized list of quests
 * 
 * Returns:
 * - SUCCESS upon successful initialization, FAILURE upon failed initialization
*/
int npc_quest_list_init(npc_quest_list_t *quest_list);

/*
 * Creates a new linked list of npc_quest structs
*/
npc_quest_list_t *npc_quest_list_new();

/*
 * Frees a npc_quest_list struct
 * 
 * Parameters:
 * - quest_list: a list of quests
 * 
 * Returns:
 * - SUCCESS upon successful free, FAILURE upon failed free
*/
int npc_quest_list_free(npc_quest_list_t *quest_list);

/*
 * Initializes a npc_task_list struct
 * 
 * Parameters:
 * - task_list: an uninitialized list of tasks
 * 
 * Returns:
 * - SUCCESS upon successful initialization, FAILURE upon failed initialization
*/
int npc_task_list_init(npc_task_list_t *task_list);

/*
 * Creates a new linked list of npc_task structs
*/
npc_task_list_t *npc_task_list_new();

/*
 * Frees a new linked list of npc_task structs
 *
 * Parameters:
 * - task_list: an uninitialized list of tasks
 * 
 * Returns:
 * - SUCCESS on successful free, FAILIURE on failure
*/
int npc_task_list_free(npc_task_list_t *npc_task_list);

/*
 * Appends an npc_quest_t to an npc_quest_list_t
 *
 * Parameters:
 * - list: the npc_quest_list
 * - next: the quest_t struct to add
 * 
 * Returns:
 * - SUCCESS following successful append, FAILURE upon failed append
*/
int npc_quest_list_add(npc_quest_list_t *list, npc_quest_t *quest);

/*
 * Appends an npc_task_t to an npc_task_list_t
 *
 * Parameters:
 * - list: the npc_task_list
 * - task: the task_t struct to add
 * 
 * Returns:
 * - SUCCESS following successful append, FAILURE upon failed append
*/
int npc_task_list_add(npc_task_list_t *list, npc_task_t *task);

/* Adds a conversation to a quest.
 * 
 * Parameters:
 * - quest: the npc's quest
 * - c: the quest-specific dialogue
 * 
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 */
int add_convo_to_quest(npc_quest_t *quest, convo_t *c);

/* Adds a conversation to a task.
 * 
 * Parameters:
 * - task: the npc's task
 * - c: the task-specific dialogue
 * 
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 */
int add_convo_to_task(npc_task_t *task, convo_t *c);

#endif /* NPC_QUESTS_H */
