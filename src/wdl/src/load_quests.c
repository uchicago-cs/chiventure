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
        return NULL;
    }

    if(prereq_type_check(prereq_obj) == FAILURE) {
        fprintf(stderr, "prereq is not in the correct format");
        return NULL;
    }

    int hp = obj_get_int(prereq_obj, "Health");
    int level = obj_get_int(prereq_obj, "Level");
    obj_list_t *quest_list = obj_get_list(prereq_obj, "Quests");
    obj_list_t *task_list = obj_get_list(prereq_obj, "Tasks");

    prereq_t *prereq = prereq_new(hp, level);

    obj_t *cur;
    if(quest_list != NULL) {
        DL_FOREACH(quest_list, cur)
        {
            prereq_add_quest(prereq, cur->data.s);
        }
    }
    if(task_list != NULL) {
        DL_FOREACH(task_list, cur)
        {
            prereq_add_task(prereq, cur->data.s);
        }
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
        return NULL;
    }

    if(rewards_type_check(reward_obj) == FAILURE) {
        fprintf(stderr, "reward is not in the correct format");
        return NULL;
    }

    int xp = obj_get_int(reward_obj, "XP");
    char *item_id = obj_get_str(reward_obj, "Item");
    item_t *reward_item = NULL;
    if(obj_get(reward_obj, "Item") != NULL) {
        char *item_id = obj_get_str(reward_obj, "Item");
        reward_item = get_item_from_game(game, item_id);
    }
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
        return NULL;
    }

    if(mission_type_check(mission_obj) == FAILURE) {
        fprintf(stderr, "mission is not in the correct format");
        return NULL;
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

/* Creates a task from a WDL task object
 * 
 * Parameters:
 * - task_obj: A WDL task object
 * - game: A chiventure game
 * 
 * Returns:
 * - A task struct defined by the WDL object
*/
task_t *load_task(obj_t *task_obj, game_t *game) {
    if (task_obj == NULL)
    {
        fprintf(stderr, "task is null\n");
        return NULL;
    }

    if(task_type_check(task_obj) == FAILURE) {
        fprintf(stderr, "task is not in the correct format");
        return NULL;
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
 * - task_list_obj: A WDL quest object
 * - hash: A task hash table
 * 
 * Returns:
 * - SUCCESS on success, FAILURE if an error occurs
*/
int load_task_hash(obj_list_t *task_list_obj, game_t *game, task_hash_t **hash) {
    assert(task_list_obj != NULL);
    assert(hash != NULL);
    
    obj_t *cur, *tmp;
    DL_FOREACH(task_list_obj, cur) {
        task_t *cur_task = load_task(cur, game);
        add_task_to_hash(cur_task, hash);
    }
    return SUCCESS;
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
int load_task_tree(obj_list_t *task_tree_obj, quest_t *quest, task_hash_t *task_hash, char *parent_id) {
    assert(quest != NULL);
    
    if(task_tree_obj == NULL) {
        return SUCCESS;
    }

    obj_t *cur, *tmp;
    DL_FOREACH(task_tree_obj, cur) {
        char *task_name = obj_get_str(cur, "Task Name");
        task_t *task = get_task_from_task_hash(task_name, task_hash);
        if(task == NULL) {
            fprintf(stderr, "Undefined task: %s!\n", task_name);
            return FAILURE;
        }
        add_task_to_quest(quest, task, parent_id);
        obj_list_t *next_obj = obj_get_list(cur, "Task Tree");
        if(next_obj != NULL) {
            load_task_tree(next_obj, quest, task_hash, task_name);
        }
    }
    return SUCCESS;
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
int load_quest(obj_t *quest_obj, game_t *game) {
    assert(quest_obj != NULL);

    if(quest_type_check(quest_obj) == FAILURE) {
        fprintf(stderr, "quest is not in the correct format");
        return FAILURE;
    }
    task_hash_t *task_hash = NULL;
    obj_list_t *task_list_obj = obj_get_list(quest_obj, "Task List");
    load_task_hash(task_list_obj, game, &task_hash);

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

    obj_list_t *task_tree_obj = obj_get_list(quest_obj, "Task Tree");
    load_task_tree(task_tree_obj, q, task_hash, NULL);
    add_quest_to_game(game, q);
    
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
    obj_list_t *quests_obj = obj_get_list(doc, "QUESTS");
    if(quests_obj == NULL) {
        quests_obj = obj_get(doc, "QUEST");
        if(quests_obj != NULL) {
            fprintf(stderr, "QUESTS is misspelled as QUEST!");
            return FAILURE;
        }
        fprintf(stderr, "Warning: The game has no quests! \n");
        return SUCCESS;
    }

    // iterate through the hash table of quests
    // Code shamelessly stolen from load_npc.c
    obj_t *cur;
    DL_FOREACH (quests_obj, cur)
    {
        load_quest(cur, game);
    }
    return SUCCESS;
}