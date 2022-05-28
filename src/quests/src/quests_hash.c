#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quests_hash.h"

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
    assert(tree->task != NULL && tree->task->id != NULL);
    if (strcmp(tree->task->id, id) == 0)
    {
        return tree;
    }
    task_tree_t * newTree;
    newTree = find_task_tree_of_task_in_tree(tree->rsibling, id);
    return (newTree != NULL) ? newTree : find_task_tree_of_task_in_tree(tree->lmostchild, id);
}

/* Refer to quests_hash.h */
quest_t *get_quest_from_hash(char *quest_id, quest_hash_t *hash_table)
{
    quest_t *q;
    HASH_FIND_STR(hash_table, quest_id, q);
    return q;
}

/* Refer to quests_hash.h */
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

/* Refer to quests_hash.h */
task_t *get_task_from_quest_hash(char *id, quest_hash_t *hash_table) {
    task_tree_t *task_tree = get_task_tree_from_hash(id, hash_table);
    return task_tree != NULL ? task_tree->task : NULL;
}

/* Refer to quests_hash.h */
task_hash_t *search_task_hash(char *id, task_hash_t *hash_table)
{
    task_hash_t *t;
    HASH_FIND_STR(hash_table, id, t);
    return t;
}

/* Refer to quests_hash.h */
task_t *get_task_from_task_hash(char *id, task_hash_t *hash_table)
{
    task_hash_t *result = search_task_hash(id, hash_table);
    if(result == NULL) {
        return NULL;
    }
    return result->task;
}

/* Refer to quests_hash.h */
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

/* Refer to quests_hash.h */
int add_task_to_hash(task_t *task, task_hash_t **hash_table)
{
    if(task == NULL) {
        return FAILURE;
    }
    task_t *check;
  
    check = get_task_from_task_hash(task->id, *hash_table);

    if (check != NULL) 
    {
        return FAILURE; //quest id is already in the hash table
    }

    task_hash_t *thash = malloc(sizeof(task_hash_t));
    assert(thash != NULL);
    thash->task = task;
    thash->id = task->id;

    HASH_ADD_KEYPTR(hh, *hash_table, task->id,
                    strnlen(task->id, QUEST_NAME_MAX_LEN), thash);
    return SUCCESS;
}

/* Refer to quests_hash.h */
player_quest_t *get_player_quest_from_hash(char *quest_id, player_quest_hash_t *hash_table)
{
    player_quest_t *q;
    HASH_FIND_STR(hash_table, quest_id, q);
    return q;
}

/* Refer to quests_hash.h */
player_task_t *get_player_task_from_hash(char *id, player_task_hash_t *hash_table)
{
    player_task_t *t;
    HASH_FIND(hh, hash_table, id,  
            strnlen(id, QUEST_NAME_MAX_LEN), t);

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
                    strnlen(quest->quest_id, QUEST_NAME_MAX_LEN), player_quest);

    player_task_hash_t **task_hash = &player->player_tasks;
    if(quest->prereq) {
        id_list_node_t *temp = quest->prereq->task_list->head;
        while (temp != NULL) {
            task_t *new_task = get_task_from_quest_hash(temp->id, quest_hash);
            add_task_to_player_hash(new_task, qctx);
            temp = temp->next;
        }
    }
    return SUCCESS;
}

/* Refer to quests_hash.h */
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
                    strnlen(task->id, QUEST_NAME_MAX_LEN), player_task);

    if(task->prereq) {
        id_list_node_t *temp = task->prereq->task_list->head;
        while (temp != NULL) {
            task_t *new_task = get_task_from_quest_hash(temp->id, quest_hash);
            add_task_to_player_hash(new_task, qctx);
            temp = temp->next;
        }
    }
  
    return SUCCESS;
}

/* refer to quests_hash.h */
int remove_quest_in_hash(quest_hash_t *hash_table, char *quest_id) 
{
    quest_t *check; 
    check = get_quest_from_hash(quest_id, hash_table);

    if (check == NULL){ 
        return FAILURE; /* quest is not in hash_table) */
    } 

    HASH_DEL(hash_table, check); 
    quest_free(check); 
    if (get_quest_from_hash(quest_id, hash_table) != NULL){
        return FAILURE;
    }
    return SUCCESS;
}

/* refer to quests_hash.h */
int remove_quest_all(quest_hash_t **hash_table)
{ 
    quest_hash_t *original = *hash_table;
    quest_t *current_quest, *temp; 
    HASH_ITER(hh, *hash_table, current_quest, temp) 
    { 
        HASH_DEL(*hash_table, current_quest);
        quest_free(current_quest);
    }
    original = NULL;
    return SUCCESS; 
}

/* refer to quests_hash.h */
int remove_task_in_hash(task_hash_t *hash_table, char *id) 
{
    task_hash_t *check; 
    check = search_task_hash(id, hash_table);

    if (check == NULL){ 
        return FAILURE; /* quest is not in hash_table) */
    } 

    HASH_DEL(hash_table, check); 
    task_free(check->task);
    free(check);

    if (get_task_from_task_hash(id, hash_table) != NULL){
        return FAILURE;
    }
    return SUCCESS;
}

/* refer to quests_hash.h */
int remove_task_all(task_hash_t **hash_table)
{ 
    task_hash_t *original = *hash_table;
    task_hash_t *current_task, *temp; 
    HASH_ITER(hh, *hash_table, current_task, temp) 
    { 
        HASH_DEL(*hash_table, current_task);
        free(current_task);
    }
    original = NULL;
    return SUCCESS; 
}

/* Refer to quests_hash.h */
int remove_task_in_player_hash(player_task_hash_t *ptasks, char *task_id) {
    player_task_t *check; 
    check = get_player_task_from_hash(task_id, ptasks);

    if (check == NULL){ 
        return FAILURE; /* quest is not in hash_table) */
    } 

    HASH_DEL(ptasks, check); 
    player_task_free(check); 
    if (get_player_task_from_hash(task_id, ptasks) != NULL){
        return FAILURE;
    }
    return SUCCESS;
}