#include "wdl/load_quests.h"

// NOTE: We need to add validation functions to validate.c 
//       to make sure quest objects are inputted correctly.
//       Headers are already in validate.h.
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
 * - task_hash: A hash table of all tasks
 * 
 * Returns:
 * - A pointer to a quest specified according to the WDL object
*/
quest_t *load_quest(obj_t *quest_obj, task_hash_t *task_hash) {
    /* TODO */
    return NULL;
}

/* See load_quests.h */
int load_quests(obj_t *doc, game_t *game) {
    assert(game != NULL);
    assert(doc != NULL);
    obj_t *quests_obj = obj_get(doc, "QUESTS");
    if(quests_obj == NULL) {
        quests_obj = obj_get(doc, "QUEST");
        if(quests_obj != NULL) {
            fprintf(stderr, "QUESTS is misspelled as QUEST!");
            return FAILURE;
        }
        fprintf(stderr, "Warning: The game has no quests! \n");
        return SUCCESS;
    }
    else if(quests_type_check(quests_obj) == FAILURE) {
        fprintf(stderr, "items fail type checking\n");
        return FAILURE;
    }

    // Load the task hash table
    task_hash_t *task_hash = load_task_hash(quests_obj);

    // iterate through the hash table of quests
    // Code shamelessly stolen from load_npc.c
    obj_t *cur, *tmp;
    HASH_ITER (hh, quests_obj->data.obj.attr, cur, tmp)
    {
        add_quest_to_game(game, load_quest(cur, task_hash));
    }

    // Creates placeholder quests for prereq tasks that aren't a part of any quest's task tree
    for(task_hash_t *cur_task = task_hash; cur_task != NULL; cur_task = cur_task->hh.next) {
        if(get_task_from_quest_hash(cur_task->id, game->all_quests) == NULL) {
            quest_t *prereq_quest = quest_new(cur_task->id, NULL, NULL);
            add_task_to_quest(prereq_quest, cur_task->task, NULL);
            add_quest_to_game(game, prereq_quest);
        }
    }
    return SUCCESS;
}