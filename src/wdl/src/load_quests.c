#include "wdl/load_quests.h"

// NOTE: We need to add validation functions to validate.c/.h 
//       to make sure quest objects are inputted correctly.
///      Read through other WDL files for examples.

/* Creates a prereq from a WDL prereq object
 *
 * Parameters:
 * - prereq_obj: A WDL prereq object
 * 
 * Returns:
 * - A pointer to a prereq specified according to the WDL object
*/
prereq_t *load_prereq(obj_t *prereq_obj) {
    /* TODO */
    return NULL;
}

/* Creates a reward from a WDL reward object
 *
 * Parameters:
 * - reward_obj: A WDL reward object
 * 
 * Returns:
 * - A pointer to a reward specified according to the WDL object
*/
reward_t *load_reward(obj_t *reward_obj) {
    /* TODO */
    return NULL;
}

/* Creates a mission from a WDL mission object
 *
 * Parameters:
 * - mission_obj: A WDL mission object
 * 
 * Returns:
 * - A pointer to a mission specified according to the WDL object
*/
mission_t *load_mission(obj_t *mission_obj) {
    /* TODO */
    return NULL;
}

/* Adds all of the tasks in the task list of a single quest into a 
 * task hash
 *
 * Parameters:
 * - quest_obj: A WDL quest object
 * - hash: A task hash table
 * 
 * Returns:
 * - SUCCESS on success, FAILURE if an error occurs
*/
int load_task_hash_of_quest(obj_t *quest_obj, task_hash_t *hash) {
    /* TODO */
    return 0;
}

/* Creates a task hash table from all of the quest lists from all 
 * of the WDL quest objects in a WDL list of quests
 *
 * Parameters:
 * - quests_list_obj: A WDL quests list obj
 * 
 * Returns:
 * - A pointer to a task_hash specified according to the WDL object
*/
task_hash_t *load_task_hash(obj_t *quests_list_obj) {
    /* TODO */
    return NULL;
} 

/* Creates a quest from a WDL quest object
 *
 * Parameters:
 * - quest_obj: A WDL quest object
 * 
 * Returns:
 * - A pointer to a quest specified according to the WDL object
*/
quest_t *load_quest(obj_t *quest_obj) {
    /* TODO */
    return NULL;
}

/* See load_quests.h */
int load_quests(obj_t *doc, game_t *g) {
    /* TODO */
    return 0;
}