#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/task.h"

/* Refer to task.h */
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

/* Refer to task.h */
int mission_init(mission_t *mission, char *target_name, mission_types_t type)
{
    assert(mission != NULL);
    assert(target_name != NULL);

    mission->target_name = target_name;
    mission->type = type;

    return SUCCESS;
}

/* Refer to task.h */
int mission_free(mission_t *mission)
{
    assert(mission != NULL);
    free(mission);

    return SUCCESS;
}

/* Refer to task.h */
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

/* Refer to task.h */
int reward_init(reward_t *rewards, int xp, item_t *item)
{
    assert(rewards != NULL);

    rewards->xp = xp;
    rewards->item = item;

    return SUCCESS;
}

/* Refer to task.h */
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

/* Refer to task.h */
int task_init(task_t *task, char *id, mission_t *mission, reward_t *reward, prereq_t *prereq)
{
    assert(task != NULL);
    task->mission = mission;
    task->reward = reward;
    task->id = id;
    task->prereq = prereq;

    return SUCCESS;
}

/* Refer to task.h */
int task_free(task_t *task)
{
    assert(task != NULL);

    free(task);

    return SUCCESS;
}

/* Refer to task.h */
int task_tree_free(task_tree_t *task_tree)
{
    if (task_tree == NULL){
        return SUCCESS;
    } else {
    task_free(task_tree->task);
    task_tree_free(task_tree->parent);
    task_tree_free(task_tree->rsibling);
    task_tree_free(task_tree->lmostchild);
    free(task_tree);
    }
}

