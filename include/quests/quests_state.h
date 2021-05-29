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
 * Returns: a pointer to the newly allocated mission that is not completed
 */
mission_t *mission_new(item_t *item_to_collect, npc_t *npc_to_meet);

/* Creates a new achievement struct (allocates memory)
 * 
 * Parameters:
 * - mission: the mission to be completed for the quest
 * 
 * Returns: a pointer to the newly allocated achievement that is not completed
 */
achievement_t *achievement_new(mission_t *mission);

/* Creates a new quest struct (allocates memory)
 * 
 * Parameters:
 * - quest_id: long integer for the specific quest_id 
 * - achievement_list: linked list struct holding a list of achievements that
 *                     make up a quest
 * - reward: reward of the quest is an item
 * 
 * Returns: a pointer to the newly allocated quest, with default status of 0
 *         (not started)
 */
quest_t *quest_new(long int quest_id, achievement_llist_t *achievement_list,
                    item_t *reward);

/* Initialize an already allocated mission struct
 *
 * Parameters:
 * - mission: an already allocated mission
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
 * - achievement: an already allocated achievement
 * - mission: the mission to be completed for the achievement
 * 
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 */
int achievement_init(achievement_t *achievement, mission_t *mission);


/* Initialize an already allocated quest struct
 *
 * Parameters:
 * - q: an already allocated quest
 * - quest_id: long int for the specific quest_id 
 * - achievement_llist_t: linked list struct holding a list of 
 *                        achievements that make up a quest
 * - reward: reward of the quest is an item
 * - status: int indicating the status of the quest (refer to
 *           quests_structs.h for all possible statuses)
 * 
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 * 
 */
int quest_init(quest_t *q, long int quest_id, achievement_llist_t *achievement_list, 
               item_t *reward, int status);

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

/* 
 * Frees an achievement struct from memory but does not free 
 * its associated pointers
 * 
 * Parameter:
 * - achievement: the achievement to be freed
 * 
 * Returns:
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */
int achievement_free(achievement_t *achievement);

/* 
 * Frees a quest struct from memory including the achievement list
 * and reward, but otherwise does not free associated pointers
 * 
 * Parameter:
 * - quest: the quest to be freed
 * 
 * Returns:
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */
int quest_free(quest_t * quest);

/* Adds an achievement to the end of a quest's achievement list
 *
 * Parameters:
 * - quest: pointer to a quest 
 * - achievement_to_add: pointer to an achievement to add to the list
 * 
 * Returns:
 * - SUCCESS 
 * - FAILURE
 */
int add_achievement_to_quest(quest_t *quest, achievement_t *achievement_to_add);

/* Updates a quest's status to started
 *
 * Parameter:
 * - quest: pointer to quest to be marked started
 * 
 * Returns:
 * - SUCCESS 
 * - FAILURE
 */
int start_quest(quest_t *quest);

/* Updates a quest's status to failed
 *
 * Parameter:
 * - quest: pointer to quest to be marked failed
 * 
 * Returns:
 * - SUCCESS 
 * - FAILURE
 */
int fail_quest(quest_t *quest);

/* Completes an achievement in a quest by checking if the item and npc match
 * the first incomplete achievement in the quest's achievement list
 * 
 * Parameters:
 * - quest: pointer to the quest
 * - item_collected: the item that has been collected
 * - npc_met: the npc that was met
 *
 * Returns:
 * - SUCCESS
 * - FAILURE
 */
int complete_achievement(quest_t *quest, item_t *item_collected, npc_t *npc_met);

/* Checks if a quest is completed
 * 
 * Parameter:
 * - quest: pointer to the quest
 *
 * Returns:
 * - 0 if quest is incomplete
 * - 1 if quest is complete
 */
int is_quest_completed(quest_t *quest);

/* Gets a quest from the given hash table
 *
 * Parameters:
 *  quest id string
 *  pointer to quest hash table
 *
 * Returns:
 *  quest struct if successful, NULL if quest is not found
 */
quest_t *get_quest_from_hash(char *quest_id, quest_hash_t *hash_table);

/* Adds a quest to the given hash table
 *
 * Parameters:
 *  pointer to quest struct
 *  pointer to quest hash table
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_quest_to_hash(quest_t *quest, quest_hash_t *hash_table);

/* Checks a quest's status.
 *
 * Parameter:
 * - quest: pointer to a quest
 * 
 * Returns: 
 * - the quest's status code, as described in quests_structs.h
 */
int get_quest_status(quest_t *quest);

/* Returns the quest's reward item if the quest has been completed.
 *
 * Parameter:
 * - quest: pointer to a quest
 * 
 * Returns:
 * - the quest's reward item
 * - NULL if the quest is incomplete
 * 
 * Note:
 * The status of the quest should first be checked before this function is called
 */
item_t *complete_quest(quest_t *quest);


#endif /* QUESTS_STATE_H */
