#ifndef QUESTS_STATE_H
#define QUESTS_STATE_H

#include <stdbool.h>
#include <string.h>
#include "quests_structs.h"

/* Creates a new mission struct (allocates memory)
 * 
 * Parameters:
 * - item_to_collect: the item to be collected for the mission
 * - npc_to_meet: the npc to be met for the mission
 * 
 * Returns: a pointer to the newly allocated mission, that is not completed
 */
mission_t *mission_new(item_t *item_to_collect, npc_t *npc_to_meet);

/* Creates a new achievement struct (allocates memory)
 * 
 * Parameters:
 * - mission: the mission to be completed for the quest
 * 
 * Returns: a pointer to the newly allocated achievement, that is not completed
 */
achievement_t *achievement_new(mission_t *mission);

/* Creates a new quest struct (allocates memory)
 * 
 * Parameters:
 * - quest_id: integer for the specific quest_id 
 * - achievement_list:  linked list struct holding a list of achievements that
 *                       make up a quest
 * - reward: reward of the quest is an item
 * 
 * Returns: a pointer to the newly allocated quest, with default status of 0
 *         (not started.
 */
quest_t *quest_new(long int quest_id, achievement_llist_t *achievement_list,
                    item_t *reward);

/* Initialize an already allocated mission struct
 *
 * Parameters:
 * - mission: an already allocated mission_t
 * - item_to_collect: the item to be collected for the mission
 * - npc_to_meet: the npc to be met for the mission
 * 
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 */
int mission_init(mission_t *mission, item_t *item_to_collect, npc_t *npc_to_meet);

/* Initialize an already allocated achievement struct
 *
 * Parameters:
 * - achievement: an already allocated achievement_t
 * - mission: the mission to be completed for the quest
 * 
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 */
int achievement_init(achievement_t *achievement, mission_t *mission);

/* Initialize an already allocated quest struct
 *
 * Parameters:
 * - q: an already allocated quest_t
 * - quest_id: long int for the specific quest_id 
 * - achievement_llist_t:  inked list struct holding a list of achievements that make up a quest
 * - reward: reward of the quest is an item
 * - status: int indicating the status of the quest
 * 
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 */
int quest_init(quest_t *q, long int quest_id, 
               achievement_llist_t *achievement_list, item_t *reward, int status);

/* 
 * Frees a mission struct from memory
 * 
 * Parameter:
 * - mission: the mission_t to be freed
 * 
 * Returns:
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */
int mission_free(mission_t *mission);

/* 
 * Frees a achievement struct from memory, does not free associated pointers
 * 
 * Parameter:
 * - achievement: the achievement_t to be freed
 * 
 * Returns:
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */
int achievement_free(achievement_t *achievement);

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