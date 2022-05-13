#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quests_state.h"

/* Refer to quests_state.h */
passive_mission_t *passive_mission_new(int xp, int levels, int health)
{
    passive_mission_t *mission = malloc(sizeof(passive_mission_t));
    int rc;

    rc = passive_mission_init(mission, xp, levels, health);

    if (rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not initialize  mission struct!\n");
    }

    return mission;
}

/* Refer to quests_state.h */
active_mission_t *active_mission_new(item_t *item_to_collect, npc_t *npc_to_meet, 
                              npc_t *npc_to_kill, room_t *room_to_visit)
{
    active_mission_t *mission = malloc(sizeof(active_mission_t));
    int rc;

    rc = active_mission_init(mission, item_to_collect, npc_to_meet, npc_to_kill,
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
task_t *task_new(mission_t *mission, char *id, reward_t *reward)
{
    task_t *task;
    int rc;
    task = malloc(sizeof(task_t));

    rc = task_init(task, mission, id, reward);
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
int passive_mission_init(passive_mission_t *mission, int xp, int levels, int health)
{
    assert(mission != NULL);

    mission->xp = xp;
    mission->levels = levels;
    mission->health = health;

    return SUCCESS;
}

/* Refer to quests_state.h */
int active_mission_init(active_mission_t *mission, item_t *item_to_collect, 
                        npc_t *npc_to_meet, npc_t *npc_to_kill, room_t *room_to_visit)
{
    assert(mission != NULL);

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
int task_init(task_t *task, mission_t *mission, char *id, reward_t *reward)
{
    assert(task != NULL);

    task->mission = mission;
    task->reward = reward;
    task->id = id;

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
int passive_mission_free(passive_mission_t *mission)
{
    assert(mission != NULL);

    free(mission);

    return SUCCESS;
}

/* Refer to quests_state.h */
int active_mission_free(active_mission_t *mission)
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
 * Helper function that finds an task tree given its string ID.
 * It's called find_parent() because of its use to find parent nodes
 * in add_task_to_quest().
 *
 * Parameters:
 * - tree: a pointer to an task tree
 * - id: the string identifier of the task being searched for
 *
 * Returns:
 * - NULL if task cannot be found
 * - The task tree being searched for
 */ 
task_tree_t *find_parent(task_tree_t *tree, char *id)
{

    assert(tree != NULL);

    task_tree_t *cur = tree;

    while(cur != NULL)
    {

        if(strcmp(cur->task->id, id) == 0)
        {
            return cur;
        }
        else if(cur->rsibling != NULL)
        {
            cur = cur->rsibling;
        }
        else if(cur->parent->rsibling != NULL)
        {
            cur = cur->parent->rsibling;
        }
        else
        {
            return NULL;
        }
    }
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
    tree = find_parent(quest->task_tree, parent_id);
    assert(tree != NULL);

    if (tree->lmostchild == NULL)
    {
        tree->lmostchild = malloc(sizeof(task_tree_t));
        tree->lmostchild->task = task_to_add;
        tree->lmostchild->parent = find_parent(quest->task_tree, parent_id);
    }
    else
    {
        while (tree->rsibling != NULL)
        {
            tree = tree->rsibling;
        }
        tree->rsibling = malloc(sizeof(task_tree_t));
        tree->rsibling->task = task_to_add;
        tree->rsibling->parent = find_parent(quest->task_tree, parent_id);
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

/*
 * Traverses the task tree to find the task with the
 * given string identifier along a valid quest path.
 *
 * Parameters:
 * - tree: pointer to the task tree to be traversed
 * - id: pointer to a string identifier for the desired task
 *
 * Returns:
 * - pointer to the desired task, OR
 * - NULL if task cannot be found along a valid path
 *
 * Note: Traversal no longer relies on task completion, so 
 *       runtime is now O(T) where T is the number of tasks
 *       in the game
 */
task_t *find_task_in_tree(task_tree_t *tree, char *id)
{
    task_t *task = tree->task;

    assert(task != NULL);

    if (strcmp(task->id, id) == 0)
    {
        return task;
    }
    task = find_task_in_tree(tree->rsibling, id);
    return (task != NULL) ? task : find_task_in_tree(tree->lmostchild, id);
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
    ptask->completed = true;
    return true;
    
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
task_t *get_task_from_hash(char *id, quest_hash_t *hash_table) {
    task_t *task = NULL;
    for(quest_t *cur = hash_table; cur != NULL; cur = cur->hh.next) {
        task = find_task_in_tree(cur->task_tree, id);
        if(task != NULL) {
            break;
        }
    }
    return task;
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
/* Refer to quests_state.h */
task_t *find_task_in_quest(task_tree_t *tree, char *id)
{
    task_t *task = tree->task;

    assert(task != NULL);

    if (strcmp(task->id, id) == 0)
    {
        if (task->completed == 1) return NULL;
        return task;
    }
    else if (task->completed == 1)
    {
        if (tree->lmostchild != NULL)
        {
            return find_task_in_quest(tree->lmostchild, id);
        }
        return NULL;
    }
    else if (tree->rsibling != NULL)
    {
        return find_task_in_quest(tree->rsibling, id);
    }
    return NULL;
}

/* Refer to quests_state.h */
task_t *find_task(player_t *player, char *id){
    /* TODO */
    return NULL;
}

/* Refer to quests_state.h */
quest_t *find_quest(player_t *player, char *id) {
    /* TODO */
    return NULL;
}

/* Refer quests_state.h */
reward_t *complete_task(task_t *task, player_t *player)
{
    if (get_player_task_status(task, player) == true)
        return task->reward;
    else
        return NULL;
}
