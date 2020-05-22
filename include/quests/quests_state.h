#ifndef QUESTS_STATE_H
#define QUESTS_STATE_H

#include <stdbool.h>
#include <string.h>
#include "quests_structs.h"

/* Creates a new quest struct (allocates memory)
 * 
 * Parameters:
 * - hh: UT_hash_handle
 * - quest_id: string for the specific quest_id 
 * - achievement_list:  linked list struct holding a list of achievements that make up a quest
 * - reward: reward of the quest is an item
 * 
 * Returns: a pointer to the newly allocated quest, with default status of 2 (not started.
 */
quest_t *quest_new(UT_hash_handle hh, char *quest_id, 
                   achievement_llist_t achievement_list, item_t *reward);


/* Initialize an already allocated quest struct
 *
 * Parameters:
 * - q: an already allocated quest_t
 * - hh: UT_hash_handle
 * - quest_id: string for the specific quest_id 
 * - achievement_llist_t:  inked list struct holding a list of achievements that make up a quest
 * - reward: reward of the quest is an item
 * - status: int indicating the status of the quest
 * 
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 */
int quest_init(quest_t *q, UT_hash_handle hh, char *quest_id, 
               achievement_llist_t *achievement_list, item_t *reward, int status);


/* 
 * Frees a quest struct from memory, does not free associated pointers
 * 
 * Parameter:
 * - quest: the quest_t to be freed
 * 
 * Returns:
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */
int quest_free(quest_t * quest);

#endif