#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quests_state.h"

/* Refer to quests_state.h */
mission_t *mission_new(item_t *item_to_collect, npc_t *npc_to_meet, 
                              npc_t *npc_to_kill, room_t *room_to_visit)
{
    mission_t *mission = malloc(sizeof(mission_t));
    int rc;

    rc = mission_init(mission, item_to_collect, npc_to_meet, npc_to_kill,
                      room_to_visit);

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
task_t *task_new(mission_t *mission, char *id, reward_t *reward, prereq_t *prereq)
{
    task_t *task;
    int rc;
    task = malloc(sizeof(task_t));

    rc = task_init(task, mission, id, reward, prereq);
    if (rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not initialize task struct!\n");
    }

    return task;
}

/* Refer to quests_state.h */
quest_t *quest_new(char *quest_id, task_tree_t *task_tree,
                   reward_t *reward, prereq_t *prereq) 

{
    quest_t *q;
    int rc;
    q = calloc(1, sizeof(quest_t));

    if(q == NULL)
    {
        fprintf(stderr, "\nCould not allocate memory for quest!\n");
        return NULL;
    }

    rc = quest_init(q, quest_id, task_tree, reward, prereq);
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
int mission_init(mission_t *mission, item_t *item_to_collect, 
                        npc_t *npc_to_meet, npc_t *npc_to_kill, room_t *room_to_visit)
{
    assert(mission != NULL);

    int count = 0;
    if(item_to_collect != NULL) {
        count++;
    }
    if(npc_to_meet != NULL) {
        count++;
    }
    if(npc_to_kill != NULL) {
        count++;
    }
    if(room_to_visit != NULL) {
        count++;
    }
    assert(count < 2);

    mission->item_to_collect = item_to_collect;
    mission->npc_to_meet = npc_to_meet;
    mission->npc_to_kill = npc_to_kill;
    mission->room_to_visit = room_to_visit;

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
int task_init(task_t *task, mission_t *mission, char *id, reward_t *reward, prereq_t *prereq)
{
    assert(task != NULL);
    assert(mission == NULL || prereq == NULL);
    task->mission = mission;
    task->reward = reward;
    task->id = id;
    task->prereq = prereq;

    return SUCCESS;
}

/* Refer to quests_state.h */
int quest_init(quest_t *q, char *quest_id, task_tree_t *task_tree,
                reward_t *reward, prereq_t *prereq)

{
    assert(q != NULL);

    q->quest_id = strndup(quest_id, QUEST_NAME_MAX_LEN);
    q->task_tree = task_tree;
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

    free(mission->item_to_collect);
    free(mission->npc_to_meet);
    free(mission->npc_to_kill);
    free(mission->room_to_visit);
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
    tree = find_task_in_tree(quest->task_tree, parent_id);
    assert(tree != NULL);

    if (tree->lmostchild == NULL)
    {
        tree->lmostchild = malloc(sizeof(task_tree_t));
        tree->lmostchild->task = task_to_add;
        tree->lmostchild->parent = find_task_in_tree(quest->task_tree, parent_id);
    }
    else
    {
        while (tree->rsibling != NULL)
        {
            tree = tree->rsibling;
        }
        tree->rsibling = malloc(sizeof(task_tree_t));
        tree->rsibling->task = task_to_add;
        tree->rsibling->parent = find_task_in_tree(quest->task_tree, parent_id);
    }

    return SUCCESS;
}

/* Refer to quests_state.h */
int start_quest(quest_t *quest, player_t *player)
{
    assert(quest != NULL);
    assert(player != NULL);

    int rc = add_quest_to_player_hash(quest, &player->player_quests, 1); // 1 means the quest started, should be replaced when completion status is replaced with enums
    assert(rc == SUCCESS);
    player_quest_t *test = get_player_quest_from_hash(quest->quest_id, player->player_quests);
    task_tree_t *cur = quest->task_tree;
    while(cur) {
        assert(add_task_to_player_hash(cur->task, &player->player_tasks) == SUCCESS);
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
    if(task->mission != NULL) {
        return false;
    }
    return meets_prereqs(player, task->prereq);
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
task_tree_t *find_task_in_tree(task_tree_t *tree, char *id)
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
    newTree = find_task_in_tree(tree->rsibling, id);
    return (newTree != NULL) ? newTree : find_task_in_tree(tree->lmostchild, id);
}

/* Refer to quests_state.h */
task_tree_t *get_task_tree_from_hash(char *id, quest_hash_t *hash_table) {
    task_tree_t *tree = NULL;
    for(quest_t *cur = hash_table; cur != NULL; cur = cur->hh.next) {
        tree = find_task_in_tree(cur->task_tree, id);
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
        tree = find_task_in_tree(cur->task_tree, task_id);
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
int add_quest_to_player_hash(quest_t *quest, player_quest_hash_t **hash_table, int completion)
{
    player_quest_t *check;
    
    check = get_player_quest_from_hash(quest->quest_id, *hash_table);

    if (check != NULL) 
    {
        return FAILURE; //quest id is already in the hash table
    }
    player_quest_t *player_quest = player_quest_new(quest->quest_id, completion);

    HASH_ADD_KEYPTR(hh, *hash_table, quest->quest_id,
                    strnlen(quest->quest_id, MAX_ID_LEN), player_quest);
    return SUCCESS;
}

/* Refer to quests_state.h */
int add_task_to_player_hash(task_t *task, player_task_hash_t **hash_table)
{
    player_task_t *check;
    
    check = get_player_task_from_hash(task->id, *hash_table);

    if (check != NULL) 
    {
        return FAILURE; //task id is already in the hash table
    }
    player_task_t *player_task = player_task_new(task->id, false);

    HASH_ADD_KEYPTR(hh, *hash_table, task->id,
                    strnlen(task->id, MAX_ID_LEN), player_task);
  
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
int remove_quest_all(quest_hash_t *hash_table)
{ 
    quest_t *current_quest, *temp; 
    HASH_ITER(hh, hash_table, current_quest, temp) 
    { 
        HASH_DEL(hash_table, current_quest);
        free(current_quest);
    }
    return SUCCESS; 
}

/* Refer quests_state.h */
reward_t *complete_task(char *task_id, player_t *player, quest_hash_t *quest_hash)
{
    assert(player != NULL);
    task_tree_t *tree = get_task_tree_from_hash(task_id, quest_hash);
    assert(tree != NULL);

    if (meets_prereqs(player, tree->task->prereq)) 
    {
        get_player_task_from_hash(tree->task->id, player->player_tasks)->completed = true;
        
        for(task_tree_t *cur = tree->lmostchild; cur != NULL; cur = cur->rsibling) {
            add_task_to_player_hash(cur->task, player->player_tasks);
            if(is_task_completed(cur->task, player)) {
                return complete_task(cur->task->id, player, quest_hash);
                break;
            }
        }
        quest_t *quest_of_task = get_quest_of_task(tree->task, quest_hash);
        if(is_quest_completed(quest_of_task, player)) {
            complete_quest(quest_of_task, player);
        }
        return tree->task->reward;
    } 
    else
    {
        return NULL;
    }
}

int accept_reward(reward_t *reward, player_t *player) {
    assert(reward != NULL);
    assert(player != NULL);
    player->xp += reward->xp;
    // Add item
}
