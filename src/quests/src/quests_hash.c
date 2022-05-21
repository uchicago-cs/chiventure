#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quests_hash.h"

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
task_t *get_task_from_hash(char *id, quest_hash_t *hash_table) {
    return get_task_tree_from_hash(id, hash_table)->task;
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
            strnlen(id, MAX_ID_LEN), t);

    return t;
}

/* Refer to quests_hash.h */
int add_quest_to_player(quest_t *quest, player_t *player, int completion, quest_hash_t *quest_hash)
{
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
            add_task_to_player_hash(new_task, task_hash, quest_hash);
            temp = temp->next;
        }
    }
    return SUCCESS;
}

/* Refer to quests_hash.h */
int add_task_to_player_hash(task_t *task, player_task_hash_t **hash_table, quest_hash_t *quest_hash)
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

    if(task->prereq) {
        id_list_node_t *temp = task->prereq->task_list->head;
        while (temp != NULL) {
            task_t *new_task = get_task_from_hash(temp->id, quest_hash);
            add_task_to_player_hash(new_task, hash_table, quest_hash);
            temp = temp->next;
        }
    }
  
    return SUCCESS;
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

