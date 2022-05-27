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
    if(ptask != NULL) {
        return ptask->completed;
    }
    return false;
}

/* Refer to quest_state.h */
int accept_reward(reward_t *reward, quest_ctx_t *qctx) {
    if(qctx == NULL) {
        return FAILURE;
    }
    player_t *player = qctx->player;
    if(reward == NULL) {
        return FAILURE;
    }

    player->xp += reward->xp;
    add_item_to_player_without_checks(player, reward->item);
    update_player_quests(qctx);
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
        if(pquest->completion != Q_COMPLETED) {
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
    tree->task = task_to_add;
    tree->rsibling = NULL;
    tree->lmostchild = NULL;

    task_tree_t *parent = find_task_tree_of_task_in_tree(quest->task_tree, parent_id);
    tree->parent = parent;
    task_tree_t **location;

    if(parent == NULL) {
        location = &quest->task_tree;
    }
    else {
        location = &parent->lmostchild;
    }

    while(*location != NULL) {
        location = &(*location)->rsibling;
    }
    *location = tree;
    return SUCCESS;
}

/* Refer to quests_state.h */
int start_quest(quest_t *quest, quest_ctx_t *qctx)
{
    assert(qctx != NULL);
    player_t *player = qctx->player;
    quest_hash_t *quest_hash = qctx->quest_hash;
    assert(quest != NULL);
    assert(player != NULL);
    int rc = add_quest_to_player(quest, qctx, Q_STARTED);
    assert(rc == SUCCESS);
    player_quest_t *test = get_player_quest_from_hash(quest->quest_id, player->player_quests);
    task_tree_t *cur = quest->task_tree;
    while(cur) {
        add_task_to_player_hash(cur->task, qctx);
        cur = cur->rsibling;
    }
    update_player_quests(qctx);

    return SUCCESS;
}

/* Refer to quests_state.h */
int fail_quest(quest_t *quest, player_t *player)
{
    assert(quest != NULL);
    player_quest_t *pquest = get_player_quest_from_hash(quest->quest_id,
                             player->player_quests);
    pquest->completion = Q_FAILED;

    return SUCCESS;
}

/* Refer to quests_state.h */
bool is_quest_completed(quest_t *quest, player_t *player)
{
    assert(quest != NULL);
    assert(player != NULL);
    task_tree_t *cur = quest->task_tree;

    player_quest_t *pquest = get_player_quest_from_hash(quest->quest_id, player->player_quests);
    if(!pquest || pquest->completion == Q_FAILED) {
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
    pquest->completion = crntStatus ? Q_COMPLETED : Q_STARTED;
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
reward_t *complete_task(char *task_id, quest_ctx_t *qctx)
{
    assert(qctx != NULL);
    if(task_id == NULL) {
        return NULL;
    }
    player_t *player = qctx->player;
    quest_hash_t *quest_hash = qctx->quest_hash;
    
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
            // Add next tasks from quest to player
            for(task_tree_t *cur = tree->lmostchild; cur != NULL; cur = cur->rsibling) {
                add_task_to_player_hash(cur->task, qctx);
                if(is_task_completed(cur->task, player)) {
                    update_task(cur->task->id, qctx);
                    break;
                }
            }
            // Remove tasks from other paths from player
            if(tree->parent != NULL) {
                for(task_tree_t *cur = tree->parent->lmostchild; cur != NULL; cur = cur->rsibling) {
                    if(!get_player_task_status(cur->task, player)) {
                        remove_task_in_player_hash(qctx->player->player_tasks, cur->task->id);
                    }
                }
            }
        }
        
        if(is_quest_completed(quest_of_task, player)) {
            accept_reward(complete_quest(quest_of_task, player), qctx);
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
    if (get_player_quest_status(quest, player) == Q_COMPLETED)
        return quest->reward;
    else
        return NULL;
}

/* Refer to quest_state.h */
int update_player_quests(quest_ctx_t *qctx) {
    assert(qctx != NULL);
    player_t *player = qctx->player;
    quest_hash_t *quest_hash = qctx->quest_hash;
    assert(player != NULL);
    for(player_task_hash_t *cur = player->player_tasks; cur != NULL; cur = cur->hh.next) {
        update_task(cur->task_id, qctx);
    }
}

/* Refer to quests_state.h */
void update_task(char *task_id, quest_ctx_t *qctx) {
    accept_reward(complete_task(task_id, qctx), qctx);
}

/* Refer to quests_state.h */
bool npc_can_give_quest(quest_ctx_t *qctx, char *quest_id)
{
    assert(qctx != NULL);
    quest_t *quest = get_quest_from_hash(quest_id, qctx->quest_hash);

    assert(quest != NULL);
    
    prereq_t *prereq = quest->prereq;
    player_t *player = qctx->player;

    return (meets_prereqs(player, prereq));
}

/* Refer to quests_state.h */
bool npc_can_give_task(quest_ctx_t *qctx, char *task_id)
{
    assert(qctx != NULL);
    task_t *task = get_task_from_quest_hash(task_id, qctx->quest_hash);

    assert(task != NULL);
    
    prereq_t *prereq = task->prereq;
    player_t *player = qctx->player;

    return (meets_prereqs(player, prereq));
}
