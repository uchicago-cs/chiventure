#ifndef QUESTS_STATE_H
#define QUESTS_STATE_H

#include <stdbool.h>
#include <string.h>
#include "quests_structs.h"


/* Creates a new passive mission struct (allocates memory)
 * 
 * Parameters:
 * - xp: integer list of experience milestones to reach
 * - levels: integer list of level milestones to reach
 * - health: integer list of health milestones to reach
 *
 * Returns: a pointer to the newly allocated passive mission, that is not completed
 */
mission_t *passive_mission_new(int *xp, int *levels, int *health);

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
mission_t *active_mission_new(item_t *item_to_collect, npc_t *npc_to_meet, 
                              npc_t *npc_to_kill, room_t *room_to_visit);

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
 * - stat_req: base stat requirement to begin the quest
 * 
 * Returns: a pointer to the newly allocated quest, with default status of 0
 *         (not started.
 */
quest_t *quest_new(long int quest_id, achievement_llist_t *achievement_list,
                    reward_t *reward, stat_req_t *stat_req);


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
int passive_mission_init(mission_t *mission, int *xp, int *levels, int *health);

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
int active_mission_init(mission_t *mission, item_t *item_to_collect, npc_t *npc_to_meet,
                        npc_t *npc_to_kill, room_t *room_to_visit);

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


/* New Functions below */

/* Initialize an already allocated quest struct
 *
 * Parameters:
 * - q: an already allocated quest_t
 * - quest_id: long int for the specific quest_id 
 * - achievement_llist_t: linked list struct holding a list of achievements that make up a quest
 * - reward: reward of the quest is an item
 * - stat_req: base stat requirement to begin the quest
 * - status: int indicating the status of the quest
 * 
 * Returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 * 
 * Notes: Adds achievement to the front of the list
 */
int quest_init(quest_t *q, long int quest_id, 
               achievement_llist_t *achievement_list, reward_t *reward, 
               stat_req_t *stat_req, int status);

/* 
 * Frees a mission struct from memory (passive or active)
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
int quest_free(quest_t *quest);

/* Adds an achievement to a quest
 *
 * Parameter:
 * - quest: pointer to quest_t 
 * - achievement_to_add: pointer to achievement_t to add to list
 * 
 * Returns:
 * - SUCCESS 
 * - FAILURE
 */
int add_achievement_to_quest(quest_t *quest, achievement_t *achievement_to_add);

/* Starts a quest
 *
 * Parameter:
 * - quest: pointer to quest_t to be started
 * 
 * Returns:
 * - SUCCESS 
 * - FAILURE
 */
int start_quest(quest_t *quest);

/* Updates the status to a failed quest
 *
 * Parameter:
 * - quest: pointer to quest_t to be started
 * 
 * Returns:
 * - SUCCESS 
 * - FAILURE
 */
int fail_quest(quest_t *quest);

/* Completes an achievement in a quest by checking if the item and npc matches
 * 
 * Paramter:
 * - quest: pointer to the quest
 * - item_collected: the item that has been collected
 * - npc_met: the npc that was met
 *
 * Returns:
 * - SUCCESS
 * - FAILURE
 */
int complete_achievement(quest_t *quest, item_t *item_collected, npc_t *npc_met);

/* Checks if the quest is completed
 * 
 * Paramter:
 * - pointer to the quest
 *
 * Returns:
 * 0 if quest is incomplete, 1 if it is complete
 */
int is_quest_completed(quest_t *quest);

/* Checks the status of a quest
 *
 * Parameter:
 * - quest: pointer to quest_t
 * 
 * Returns: status code for various status in the quest:
 * -1: failed quest
 * 0: quest has not been started
 * 1: quest has been started but not completed
 * 2: quest has been completed
 */
int get_quest_status(quest_t *quest);

/* Rewards the prize to the player once the quest has been completed
 * This also checks for completion, and does nothing if not completed
 *
 * Parameter:
 * - quest: pointer to quest_t
 * 
 * Returns:
 * - item_t: an item (possible to be added into the inventory of the player)
 *           If the quest is not completed the function will return a null pointer
 * 
 * Note:
 * The status of the quest should first be checked before this function is called
 */
item_t *complete_quest(quest_t *quest);


#endif