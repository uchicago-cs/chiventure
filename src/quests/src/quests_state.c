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

/*
 * Traverses the task tree to find the task with the
 * given string identifier along a valid quest path.
 *
 * Parameters:
 * - tree: pointer to the task tree to be traversed
 * - id: pointer to a string identifier for the desired task
 *
 * Returns:
 * - pointer to the tree immediately containing the task, OR
 * - NULL if task cannot be found along a valid path
 *
 * Note: Traversal no longer relies on task completion, so 
 *       runtime is now O(T) where T is the number of tasks
 *       in the game
 */
task_tree_t *find_task_tree_of_task_in_tree(task_tree_t *tree, char *id)
{
    if(tree == NULL) {
        return NULL;
    }
    assert(tree->task != NULL);

    if (strcmp(tree->task->id, id) == 0)
    {
        return tree;
    }
    task_tree_t * newTree;
    newTree = find_task_tree_of_task_in_tree(tree->rsibling, id);
    return (newTree != NULL) ? newTree : find_task_tree_of_task_in_tree(tree->lmostchild, id);
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
