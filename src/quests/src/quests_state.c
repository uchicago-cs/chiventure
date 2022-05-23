#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quests_state.h"

/* Refer to quests_state.h */
mission_t *mission_new(char *target_name, mission_types_t type)
{
    mission_t *mission = malloc(sizeof(mission_t));
    int rc;

    rc = mission_init(mission, target_name, type);

    if (rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not initialize  mission struct!\n");
    }

    return mission;
}

/* Refer to quests_state.h */
reward_t *reward_new(int xp, item_t *item)
{
    reward_t *rewards = malloc(sizeof(reward_t));
    int rc;

    rc = reward_init(rewards, xp, item);

    if (rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not initialize rewards struct!\n");
    }

    return rewards;
}

/* Refer to quests_state.h */
task_t *task_new(char *id, mission_t *mission, reward_t *reward, prereq_t *prereq)
{
    task_t *task;
    int rc;
    task = malloc(sizeof(task_t));

    rc = task_init(task, id, mission, reward, prereq);
    if (rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not initialize task struct!\n");
    }

    return task;
}

/* Refer to quests_state.h */
quest_t *quest_new(char *quest_id, reward_t *reward, prereq_t *prereq) 
{
    quest_t *q;
    int rc;
    q = calloc(1, sizeof(quest_t));

    if(q == NULL)
    {
        fprintf(stderr, "\nCould not allocate memory for quest!\n");
        return NULL;
    }

    rc = quest_init(q, quest_id, reward, prereq);
    if(rc != SUCCESS){
        fprintf(stderr, "\nCould not initialize quest struct!\n");
        return NULL;
    }

    return q;
}

/* Refer to quests_state.h */
prereq_t *prereq_new(int hp, int level) {
    prereq_t *prereq = malloc(sizeof(prereq_t));

    int rc = prereq_init(prereq, hp, level);
    if(rc != SUCCESS) {
        fprintf(stderr, "\nCould not initialize prereq struct!\n");
        return NULL;
    }
    return prereq;
}

/* Refer to id_list.h */
id_list_t *id_list_new() {
    id_list_t *id_list = malloc(sizeof(id_list_t));

    int rc = id_list_init(id_list);
    if(rc != SUCCESS) {
        fprintf(stderr, "\nCould not initialize id_list struct!\n");
        return NULL;
    }
    return id_list;  
}

/* Refer to quests_state.h */
int mission_init(mission_t *mission, char *target_name, mission_types_t type)
{
    assert(mission != NULL);
    assert(target_name != NULL);

    mission->target_name = target_name;
    mission->type = type;

    return SUCCESS;
}

/* Refer to quests_state.h */
int reward_init(reward_t *rewards, int xp, item_t *item)
{
    assert(rewards != NULL);

    rewards->xp = xp;
    rewards->item = item;

    return SUCCESS;
}

/* Refer to quests_state.h */
int task_init(task_t *task, char *id, mission_t *mission, reward_t *reward, prereq_t *prereq)
{
    assert(task != NULL);
    task->mission = mission;
    task->reward = reward;
    task->id = id;
    task->prereq = prereq;

    return SUCCESS;
}

/* Refer to quests_state.h */
int quest_init(quest_t *q, char *quest_id, reward_t *reward, prereq_t *prereq)

{
    assert(q != NULL);

    q->quest_id = strndup(quest_id, QUEST_NAME_MAX_LEN);
    q->task_tree = NULL;
    q->reward = reward;
    q->prereq = prereq;
    
    return SUCCESS;
}

/* Refer to quests_state.h */
int prereq_init(prereq_t * prereq, int hp, int level) {
    assert(prereq != NULL);

    prereq->hp = hp;
    prereq->level = level;
    prereq->quest_list = id_list_new();
    prereq->task_list = id_list_new();

    return SUCCESS;
}

/* Refer to quests_state.h */
int id_list_init(id_list_t *id_list) {
    assert(id_list != NULL);

    id_list->head = NULL;
    id_list->length = 0;

    return SUCCESS;
}

/* Refer to quests_state.h */
int mission_free(mission_t *mission)
{
    assert(mission != NULL);
    free(mission);

    return SUCCESS;
}

/* Refer to quests_state.h */
int task_free(task_t *task)
{
    assert(task != NULL);

    free(task);

    return SUCCESS;
}

/* Refer to quests_state.h */
int quest_free(quest_t *q)
{
    assert(q != NULL);

    free(q->quest_id);
    free(q->task_tree);
    free(q->reward);
    free(q->prereq);
    free(q);

    return SUCCESS;
}

/* Refer to quests_state.h */
int prereq_free(prereq_t *prereq) {
    assert(prereq != NULL);
    if(prereq->quest_list) {
        id_list_free(prereq->quest_list);
    }
    if(prereq->task_list) {
        id_list_free(prereq->task_list);
    }
    free(prereq);
    return SUCCESS;
}

/* Refer to quests_state.h */
int id_list_free(id_list_t *id_list) {
    assert(id_list != NULL);
    id_list_node_t *next = NULL;
    for(id_list_node_t *cur = id_list->head; cur != NULL; cur = next) {
        next = cur->next;
        free(cur);
    }
    free(id_list);
    return SUCCESS;
}

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

/*
 * Helper function to compare two tasks.
 *
 * Parameters:
 * - a1, a2: the two tasks to be compared
 *
 * Returns:
 * - 0 if the tasks are the same
 * - 1 otherwise
 */
int compare_tasks(task_t *a1, task_t *a2)
{
    if (strcmp(a1->id, a2->id) == 0)
    {
        return 0;
    }
    return 1;
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
    if(!tree || !id) {
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
    tree->task = task_to_add;

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
    int rc = add_quest_to_player(quest, qctx, 1); // 1 means the quest started, should be replaced when completion status is replaced with enums
    assert(rc == SUCCESS);
    player_quest_t *test = get_player_quest_from_hash(quest->quest_id, player->player_quests);
    task_tree_t *cur = quest->task_tree;
    while(cur) {
        add_task_to_player_hash(cur->task, qctx);
        if(is_task_completed(cur->task, player)) {
            accept_reward(complete_task(cur->task->id, qctx), qctx);
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
quest_t *get_quest_from_hash(char *quest_id, quest_hash_t *hash_table)
{
    quest_t *q;
    HASH_FIND_STR(hash_table, quest_id, q);
    return q;
}

/* Refer to quests_state.h */
int add_quest_to_hash(quest_t *quest, quest_hash_t **hash_table)
{
    quest_t *check;
  
    check = get_quest_from_hash(quest->quest_id, *hash_table);

    if (check != NULL) 
    {
        return FAILURE; //quest id is already in the hash table
    }

    HASH_ADD_KEYPTR(hh, *hash_table, quest->quest_id,
                    strnlen(quest->quest_id, MAX_ID_LEN), quest);
    return SUCCESS;
}

/* Refer to quests_state.h */
task_tree_t *get_task_tree_from_hash(char *id, quest_hash_t *hash_table) {
    task_tree_t *tree = NULL;
    for(quest_t *cur = hash_table; cur != NULL; cur = cur->hh.next) {
        tree = find_task_tree_of_task_in_tree(cur->task_tree, id);
        if(tree != NULL) {
            break;
        }
    }
    return tree;
}

/* Refer to quests_state.h */
task_t *get_task_from_hash(char *id, quest_hash_t *hash_table) {
    return get_task_tree_from_hash(id, hash_table)->task;
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
player_quest_t *get_player_quest_from_hash(char *quest_id, player_quest_hash_t *hash_table)
{
    player_quest_t *q;
    HASH_FIND_STR(hash_table, quest_id, q);
    return q;
}

/* Refer to quests_state.h */
player_task_t *get_player_task_from_hash(char *id, player_task_hash_t *hash_table)
{
    player_task_t *t;
    HASH_FIND(hh, hash_table, id,  
            strnlen(id, MAX_ID_LEN), t);

    return t;
}

/* Refer to quests_state.h */
int add_quest_to_player(quest_t *quest, quest_ctx_t *qctx, int completion)
{
    assert(qctx != NULL);
    player_t *player = qctx->player;
    quest_hash_t *quest_hash = qctx->quest_hash;
    player_quest_t *check;
    player_quest_hash_t **hash_table = &player->player_quests;
    check = get_player_quest_from_hash(quest->quest_id, *hash_table);

    if (check != NULL) 
    {
        return FAILURE; //quest id is already in the hash table
    }
    player_quest_t *player_quest = player_quest_new(quest->quest_id, completion);

    HASH_ADD_KEYPTR(hh, *hash_table, quest->quest_id,
                    strnlen(quest->quest_id, MAX_ID_LEN), player_quest);

    player_task_hash_t **task_hash = &player->player_tasks;
    if(quest->prereq) {
        id_list_node_t *temp = quest->prereq->task_list->head;
        while (temp != NULL) {
            task_t *new_task = get_task_from_hash(temp->id, quest_hash);
            add_task_to_player_hash(new_task, qctx);
            temp = temp->next;
        }
    }
    return SUCCESS;
}

/* Refer to quests_state.h */
int add_task_to_player_hash(task_t *task, quest_ctx_t *qctx)
{
    assert(qctx != NULL);
    player_t *player = qctx->player;
    quest_hash_t *quest_hash = qctx->quest_hash;
    player_task_hash_t **hash_table = &player->player_tasks;
    player_task_t *check;
    
    check = get_player_task_from_hash(task->id, *hash_table);

    if (check != NULL) 
    {
        return FAILURE; //task id is already in the hash table
    }
    player_task_t *player_task = player_task_new(task->id, false);

    HASH_ADD_KEYPTR(hh, *hash_table, task->id,
                    strnlen(task->id, MAX_ID_LEN), player_task);

    if(task->prereq) {
        id_list_node_t *temp = task->prereq->task_list->head;
        while (temp != NULL) {
            task_t *new_task = get_task_from_hash(temp->id, quest_hash);
            add_task_to_player_hash(new_task, qctx);
            temp = temp->next;
        }
    }
  
    return SUCCESS;
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

/* Refer to quests_state.h */
bool get_player_task_status(task_t *task, player_t *player)
{
    player_task_t *ptask = get_player_task_from_hash(task->id, player->player_tasks);
    return ptask->completed;
}

/* Refer quests_state.h */
reward_t *complete_quest(quest_t *quest, player_t *player)
{
    if (get_player_quest_status(quest, player) == 2)
        return quest->reward;
    else
        return NULL;
}


/* Refer to quests_state.h */
int id_list_add(id_list_t *id_list, char *id) {
    assert(id_list != NULL);
    assert(id != NULL);

    id_list_node_t *node = malloc(sizeof(id_list_node_t));
    assert(node != NULL);

    node->id = id;
    node->next = NULL;
    
    if(id_list->head == NULL) {
        id_list->head = node;
    }
    else {
        id_list_node_t *cur = id_list->head;
        while(cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = node;
    }
    id_list->length++;
    return SUCCESS;
} 

/*Refer to quests_state.h */
int prereq_add_quest(prereq_t *prereq, char *quest_id) {
    assert(prereq != NULL);
    assert(quest_id != NULL);
    return id_list_add(prereq->quest_list, quest_id);
}

/*Refer to quests_state.h */
int prereq_add_task(prereq_t *prereq, char *task_id) {
    assert(prereq != NULL);
    assert(task_id != NULL);
    return id_list_add(prereq->task_list, task_id);
}



/* refer to quests_state.h */
int remove_quest_in_hash(quest_hash_t *hash_table, char *quest_id) 
{
    quest_t *check; 
    check = get_quest_from_hash(quest_id, hash_table);

    if (check == NULL){ 
        return FAILURE; /* quest is not in hash_table) */
    } 

    HASH_DEL(hash_table,check); 
    quest_free(check); 
    if (get_quest_from_hash(quest_id, hash_table) != NULL){
        return FAILURE;
    }
    return SUCCESS;

}

/* refer to quests_state.h */
int remove_quest_all(quest_hash_t **hash_table)
{ 
    quest_hash_t *original = *hash_table;
    quest_t *current_quest, *temp; 
    HASH_ITER(hh, *hash_table, current_quest, temp) 
    { 
        HASH_DEL(*hash_table, current_quest);
        free(current_quest);
    }
    original = NULL;
    return SUCCESS; 
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
            for(task_tree_t *cur = tree->lmostchild; cur != NULL; cur = cur->rsibling) {
                add_task_to_player_hash(cur->task, qctx);
                if(is_task_completed(cur->task, player)) {
                    accept_reward(complete_task(cur->task->id, qctx), qctx);
                    break;
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

/* Refer to quest_state.h */
int update_player_quests(quest_ctx_t *qctx) {
    assert(qctx != NULL);
    player_t *player = qctx->player;
    quest_hash_t *quest_hash = qctx->quest_hash;
    assert(player != NULL);
    for(player_task_hash_t *cur = player->player_tasks; cur != NULL; cur = cur->hh.next) {
        accept_reward(complete_task(cur->task_id, qctx), qctx);
    }
}

/* Refer to quests_state.h */
quest_ctx_t *quest_ctx_new(player_t *player, quest_hash_t *quest_hash) {
    quest_ctx_t *quest_ctx = malloc(sizeof(quest_ctx_t));

    int rc = quest_ctx_init(quest_ctx, player, quest_hash);
    if (rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not initialize quest_ctx struct!\n");
    }

    return quest_ctx;
}

/* Refer to quests_state.h */
int quest_ctx_init(quest_ctx_t *quest_ctx, player_t *player, quest_hash_t *quest_hash)
{
    assert(quest_ctx != NULL);
    assert(player != NULL);

    quest_ctx->player = player;
    quest_ctx->quest_hash = quest_hash;

    return SUCCESS;
}

/* Refer to quests_state.h */
int quest_ctx_free(quest_ctx_t *quest_ctx) {
    assert(quest_ctx != NULL);
    free(quest_ctx);
    return SUCCESS;
}