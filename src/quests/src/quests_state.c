#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quests_state.h"

/* Refer to quests_state.h */
bool completed_mission(mission_t *mission, player_t *player) {
    assert(player != NULL);
    if(mission == NULL) {
        return true;
    }
    switch(mission->type) {
        case VISIT_ROOM:
            return !(strcmp(mission->target_name, player->crnt_room));
            break;
        case COLLECT_ITEM:
            for(item_list_t *cur = get_all_items_in_inventory(player); cur != NULL; cur = cur->next) {
                if(!strcmp(mission->target_name, cur->item->item_id)) {
                    return true;
                }
            }
            return false;
            break;
    }
    return true;
}

/* Refer to quests_state.h */
bool is_task_completed(task_t *task, player_t *player)
{
    assert(task != NULL);
    assert(player != NULL);

    player_task_t *ptask = get_player_task_from_hash(task->id, player->player_tasks);
    if(!ptask) {
        return false;
    }
    if(ptask->completed) {
        return true;
    }
    return completed_mission(task->mission, player) && meets_prereqs(player, task->prereq);
}

/* Refer to quests_state.h */
bool get_player_task_status(task_t *task, player_t *player)
{
    player_task_t *ptask = get_player_task_from_hash(task->id, player->player_tasks);
    return ptask->completed;
}

/* Refer to quest_state.h */
int accept_reward(reward_t *reward, player_t *player) {
    assert(player != NULL);
    if(reward == NULL) {
        return FAILURE;
    }

    player->xp += reward->xp;
    add_item_to_hash(&player->inventory, reward->item);
    return SUCCESS;
}

/* Refer to quests_state.h */
bool meets_prereqs(player_t *player, prereq_t *prereq) {
    if(player == NULL) {
        return false;
    }
    if(prereq == NULL) {
        return true;
    }
    stats_hash_t *stats_hash = player->player_stats;
    double health = get_stat_current(stats_hash, "health");
    
    if (health < prereq->hp || player->level < prereq->level) {
        return false;
    }
    id_list_t *quest_list = prereq->quest_list;
    id_list_t *task_list = prereq->task_list;
    for(id_list_node_t *cur = quest_list->head; cur != NULL; cur = cur->next) {
        player_quest_t *pquest = get_player_quest_from_hash(cur->id, player->player_quests);
        // 2 is the quest status, should be changed if status is switched to an enum
        if(pquest->completion != 2) {
            return false;
        }
    }
    for(id_list_node_t *cur = task_list->head; cur != NULL; cur = cur->next) {
        player_task_t *ptask = get_player_task_from_hash(cur->id, player->player_tasks);
        if(!ptask->completed) {
            return false;
        }
    }
    return true;
}

/* Refer to quests_state.h */
int add_task_to_quest(quest_t *quest, task_t *task_to_add, char *parent_id)
{
    assert(quest != NULL);

    task_tree_t *tree = malloc(sizeof(task_tree_t));
    if (quest->task_tree == NULL)
    {
        tree->task = task_to_add;
        tree->parent = NULL;
        tree->rsibling = NULL;
        tree->lmostchild = NULL;
        quest->task_tree = tree;
        return SUCCESS;
    }
    tree = find_task_tree_of_task_in_tree(quest->task_tree, parent_id);
    assert(tree != NULL);

    if (tree->lmostchild == NULL)
    {
        tree->lmostchild = malloc(sizeof(task_tree_t));
        tree->lmostchild->task = task_to_add;
        tree->lmostchild->parent = find_task_tree_of_task_in_tree(quest->task_tree, parent_id);
    }
    else
    {
        while (tree->rsibling != NULL)
        {
            tree = tree->rsibling;
        }
        tree->rsibling = malloc(sizeof(task_tree_t));
        tree->rsibling->task = task_to_add;
        tree->rsibling->parent = find_task_tree_of_task_in_tree(quest->task_tree, parent_id);
    }

    return SUCCESS;
}

/* Refer to quests_state.h */
int start_quest(quest_t *quest, player_t *player, quest_hash_t *quest_hash)
{
    assert(quest != NULL);
    assert(player != NULL);
    int rc = add_quest_to_player(quest, player, 1, quest_hash); // 1 means the quest started, should be replaced when completion status is replaced with enums
    assert(rc == SUCCESS);
    player_quest_t *test = get_player_quest_from_hash(quest->quest_id, player->player_quests);
    task_tree_t *cur = quest->task_tree;
    while(cur) {
        add_task_to_player_hash(cur->task, &player->player_tasks, quest_hash);
        if(is_task_completed(cur->task, player)) {
            accept_reward(complete_task(cur->task->id, player, quest), player);
            break;
        }
        cur = cur->rsibling;
    }   

    return SUCCESS;
}

/* Refer to quests_state.h */
int fail_quest(quest_t *quest, player_t *player)
{
    assert(quest != NULL);
    player_quest_t *pquest = get_player_quest_from_hash(quest->quest_id,
                             player->player_quests);
    pquest->completion = -1;

    return SUCCESS;
}

/* Refer to quests_state.h */
bool is_quest_completed(quest_t *quest, player_t *player)
{
    assert(quest != NULL);
    assert(player != NULL);
    task_tree_t *cur = quest->task_tree;

    player_quest_t *pquest = get_player_quest_from_hash(quest->quest_id, player->player_quests);
    if(!pquest || pquest->completion == -1) {
        return false;
    }

    bool crntStatus = true;
    player_task_t *temp;
    while(cur) {
        temp = get_player_task_from_hash(cur->task->id, player->player_tasks);
        if(temp && temp->completed) {
            cur = cur->lmostchild;
            crntStatus = true;
            continue;
        }
        cur = cur->rsibling;
        crntStatus = false;
    }
    pquest->completion = crntStatus ? 2 : 1;
    return crntStatus;
}

/* Refer to quests_state.h */
quest_t *get_quest_of_task(char *task_id, quest_hash_t *hash_table) {
    task_tree_t *tree = NULL;
    quest_t *cur;
    for(cur = hash_table; cur != NULL; cur = cur->hh.next) {
        tree = find_task_tree_of_task_in_tree(cur->task_tree, task_id);
        if(tree != NULL) {
            break;
        }
    }
    return cur;
}

/* Refer to quests_state.h */
int get_player_quest_status(quest_t *quest, player_t *player)
{
    player_quest_t *pquest = get_player_quest_from_hash(quest->quest_id, player->player_quests);
    if(!pquest) {
        return 0;
    }
    return pquest->completion;
}

/* Refer quests_state.h */
reward_t *complete_task(char *task_id, player_t *player, quest_hash_t *quest_hash)
{
    assert(player != NULL);

    task_tree_t *tree = get_task_tree_from_hash(task_id, quest_hash);
    assert(tree != NULL);
    
    quest_t *quest_of_task = get_quest_of_task(tree->task->id, quest_hash);
    int pquest_exists = !!get_player_quest_from_hash(quest_of_task->quest_id, player->player_quests);

    if (is_task_completed(tree->task, player)) 
    {
        player_task_t *ptask = get_player_task_from_hash(tree->task->id, player->player_tasks);
        if(ptask->completed == true) {
            return NULL;
        }
        ptask->completed = true;
        if(pquest_exists) {
            for(task_tree_t *cur = tree->lmostchild; cur != NULL; cur = cur->rsibling) {
                add_task_to_player_hash(cur->task, &player->player_tasks, quest_hash);
                if(is_task_completed(cur->task, player)) {
                    accept_reward(complete_task(cur->task->id, player, quest_hash), player);
                    break;
                }
            }
        }
        
        if(is_quest_completed(quest_of_task, player)) {
            accept_reward(complete_quest(quest_of_task, player), player);
        }
        return tree->task->reward;
    } 
    else
    {
        return NULL;
    }
}

/* Refer quests_state.h */
reward_t *complete_quest(quest_t *quest, player_t *player)
{
    if (get_player_quest_status(quest, player) == 2)
        return quest->reward;
    else
        return NULL;
}

/* Refer to quest_state.h */
int update_player_quests(player_t *player, quest_hash_t *quest_hash) {
    assert(player != NULL);

    for(player_task_hash_t *cur = player->player_tasks; cur!= NULL; cur = cur->hh.next) {
        accept_reward(complete_task(cur->task_id, player, quest_hash), player);
    }
}
    

