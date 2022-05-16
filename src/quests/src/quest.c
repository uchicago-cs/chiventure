#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quest.h"
#define QUEST_NAME_MAX_LEN 100

/* Refer to quest.h */
stat_req_t *stat_req_new(int xp, int level)
{
    stat_req_t *stat_req = malloc(sizeof(stat_req_t));
    int rc;

    rc = stat_req_init(stat_req, xp, level);

    if (rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not initialize stats req struct!\n");
    }

    return stat_req;
}

/* Refer to quest.h */
int stat_req_init(stat_req_t *stat_req, int hp, int level)
{
    assert(stat_req != NULL);

    stat_req->hp = hp;
    stat_req->level = level;

    return SUCCESS;
}

/* Refer to quest.h */
quest_t *quest_new(char *quest_id, task_tree_t *task_tree,
                   reward_t *reward, stat_req_t *stat_req) 

{
    quest_t *q;
    int rc;
    q = calloc(1, sizeof(quest_t));

    if(q == NULL)
    {
        fprintf(stderr, "\nCould not allocate memory for quest!\n");
        return NULL;
    }

    rc = quest_init(q, quest_id, task_tree, reward, stat_req, 0);
    if(rc != SUCCESS){
        fprintf(stderr, "\nCould not initialize quest struct!\n");
        return NULL;
    }

    return q;
}

/* Refer to quest.h */
int quest_init(quest_t *q, char *quest_id, task_tree_t *task_tree,
                reward_t *reward, stat_req_t *stat_req, int status)

{
    assert(q != NULL);


    q->quest_id = strndup(quest_id, QUEST_NAME_MAX_LEN);
    q->task_tree = task_tree;
    q->reward = reward;
    q->stat_req = stat_req;
    q->status = status;

    return SUCCESS;
}

/* Refer to quest.h */
int quest_free(quest_t *q)
{
    assert(q != NULL);

    free(q->quest_id);
    free(q->task_tree);
    free(q->reward);
    free(q->stat_req);
    free(q);

    return SUCCESS;
}

/* Refer to quest.h */
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

/* Refer to quest.h */
int can_start_quest(quest_t *quest, player_t *player)
{
    stats_hash_t *stats_hash = player->player_stats;
    double health = get_stat_current(stats_hash, "health");

    if (health >= quest->stat_req->hp && 
        player->level >= quest->stat_req->level){
            return 1;
        }
    return 0;
}

/* Refer to quest.h */
int start_quest(quest_t *quest)
{
    assert(quest != NULL);

    quest->status = 1;

    return SUCCESS;
}

/* Refer to quest.h */
int fail_quest(quest_t *quest)
{
    assert(quest != NULL);

    quest->status = -1;

    return SUCCESS;
}

/* Refer to quests.h */
reward_t *complete_task(quest_t *quest, char *id)
{
    task_tree_t *tree = quest->task_tree;

    task_t *task = find_task(tree, id);

    if (((strcmp(task->id,id)) == 0) &&
            (task->completed == 0))
    {
        quest->task_tree->task->completed = 1;
        return task->reward;
    }
    else
    {
        return NULL;
    }
}

/* Refer to quest.h */
int is_quest_completed(quest_t *quest)
{
    assert (quest != NULL);
    task_tree_t *tmp = malloc(sizeof(task_tree_t));
    tmp = quest->task_tree;

    while(tmp = get_bottom_node(tmp))
    {
        if(tmp->task->completed == 1)
        {
            quest->status = 2;
            return 1;
        }
        else if(tmp->rsibling != NULL)
        {
            tmp = tmp->rsibling;
        }
        else if(tmp->parent->rsibling != NULL)
        {
            tmp = tmp->parent->rsibling;
        }
        else
        {
            return 0;
        }
    }
}

/* Refer to quest.h */
int get_quest_status(quest_t *quest)
{
    return quest->status;
}

/* Refer quest.h */
reward_t *complete_quest(quest_t *quest)
{
    if (get_quest_status(quest) == 2)
        return quest->reward;
    else
        return NULL;
}
