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
reward_t *load_reward(obj_t *reward_obj, game_t *game) {
    if (reward_obj == NULL)
    {
        fprintf(stderr, "reward is null\n");
        return FAILURE;
    }

    int xp = obj_get_int(reward_obj, "XP");
    char *item_id = obj_get_str(reward_obj, "Item");
    item_t *reward_item = get_item_in_hash(game->all_items, item_id);
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
    reward_t *reward = load_reward(reward_obj, game);
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
int load_task_tree(obj_t *task_tree_obj, quest_t *quest, task_hash_t *task_hash) {
    assert(task_tree_obj != NULL);
    assert(quest != NULL);
    
    // obj_t *cur, *tmp;
    // HASH_ITER(hh)
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
int *load_quest(obj_t *quest_obj, game_t *game) {
    assert(quest_obj != NULL);
    task_hash_t *task_hash = NULL;
    
    load_task_hash(quest_obj, &task_hash);
    char *quest_id = obj_get_str(quest_obj, "Quest Name");
    obj_t *reward_obj = obj_get(quest_obj, "Rewards");
    reward_t *reward = NULL;
    if(reward_obj != NULL) {
        reward = load_reward(reward_obj, game);
    } 
    obj_t *prereq_obj = obj_get(quest_obj, "Prerequisites");
    prereq_t *prereq = NULL;
    if(prereq_obj != NULL) {
        prereq = load_prereq(prereq_obj);
    }
    quest_t *q = quest_new(quest_id, reward, prereq);
    obj_t *task_tree_obj = obj_get(quest_obj, "Task Tree");
    load_task_tree(task_tree_obj, q, task_hash);
    add_quest_to_game(q, game);
    // Creates placeholder quests for prereq tasks that aren't a part of the task tree
    for(task_hash_t *cur_task = task_hash; cur_task != NULL; cur_task = cur_task->hh.next) {
        if(get_task_from_quest_hash(cur_task->id, game->all_quests) == NULL) {
            quest_t *prereq_quest = quest_new(cur_task->id, NULL, NULL);
            add_task_to_quest(prereq_quest, cur_task->task, NULL);
            add_quest_to_game(game, prereq_quest);
        }
    }
    remove_task_all(&task_hash);
    return SUCCESS;
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
    remove_task_all(task_hash);
    return SUCCESS;
}