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
    if (prereq_obj == NULL)
    {
        fprintf(stderr, "prereqs list is null\n");
        return FAILURE;
    }

    int hp = obj_get_int(prereq_obj, "Health");
    int level = obj_get_int(prereq_obj, "Level");
    obj_t *quest_list = obj_get(prereq_obj, "Quests");
    obj_t *task_list = obj_get(prereq_obj, "Tasks");

    prereq_t *prereq = prereq_new(hp, level);

    obj_t *curr, *tmp;
    HASH_ITER(hh, quest_list->data.obj.attr, curr, tmp)
    {
        prereq_add_quest(prereq, curr->id);
    }
    HASH_ITER(hh, task_list->data.obj.attr, curr, tmp)
    {
        prereq_add_task(prereq, curr->id);
    }

    return prereq;
}

/* Creates a reward from a WDL reward object
 *
 * Parameters:
 * - reward_obj: A WDL reward object
 * 
 * Returns:
 * - A pointer to a reward specified according to the WDL object
*/
reward_t *load_reward(obj_t *reward_obj, item_hash_t *all_items) {
    if (reward_obj == NULL)
    {
        fprintf(stderr, "reward is null\n");
        return FAILURE;
    }

    int xp = obj_get_int(reward_obj, "XP");
    char *item_id = obj_get_str(reward_obj, "Item");
    item_t *reward_item = get_item_in_hash(all_items, item_id);
    reward_t *reward = reward_new(xp, reward_item);
    return reward;
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
    if (mission_obj == NULL)
    {
        fprintf(stderr, "mission is null\n");
        return FAILURE;
    }

    char *target = obj_get_str(mission_obj, "Target Name");
    char *mission_type = obj_get_str(mission_obj, "Type");
    int type;
    if (strcmp(mission_type, "Meet NPC") == 0)
        type = 0;
    else if (strcmp(mission_type, "Kill NPC") == 0)
        type = 1;
    else if (strcmp(mission_type, "Collect Item") == 0)
        type = 2;
    else if (strcmp(mission_type, "Visit Room") == 0)
        type = 3;

    mission_t *mission = mission_new(target, type);
    return mission;
}

task_t *load_task(obj_t *task_obj, game_t *game) {
    if (task_obj == NULL)
    {
        fprintf(stderr, "task is null\n");
        return FAILURE;
    }

    char *name = obj_get_str(task_obj, "Task Name");
    obj_t *mission_obj = obj_get(task_obj, "Mission");
    mission_t *mission = load_mission(mission_obj);
    obj_t *reward_obj = obj_get(task_obj, "Rewards");
    reward_t *reward = load_reward(reward_obj, game->all_items);
    obj_t *prereq_obj = obj_get(task_obj, "Prerequisites");
    prereq_t *prereq = load_prereq(prereq_obj);
    
    task_t *task = task_new(name, mission, reward, prereq);
    return task;
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