#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/task.h"

/* Refer to task.h */
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

/* Refer to task.h */
int passive_mission_init(passive_mission_t *mission, int xp, int levels, int health)
{
    assert(mission != NULL);

    mission->xp = xp;
    mission->levels = levels;
    mission->health = health;

    return SUCCESS;
}

/* Refer to task.h */
int passive_mission_free(passive_mission_t *mission)
{
    assert(mission != NULL);

    free(mission);

    return SUCCESS;
}

/* Refer to task.h */
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

/* Refer to task.h */
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

/* Refer to task.h */
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

/* Refer to task.h */
int task_init(task_t *task, mission_t *mission, char *id, reward_t *reward)
{
    assert(task != NULL);

    task->mission = mission;
    task->reward = reward;
    task->completed = 0;
    task->id = id;

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
task_tree_t *get_bottom_node(task_tree_t *t)
{
    assert(t != NULL);
    task_tree_t *tmp = malloc(sizeof(task_tree_t));
    tmp = t;
    if(tmp->lmostchild != NULL)
    {
        get_bottom_node(tmp->lmostchild);
    }
    return tmp;
}

/* Refer to task.h */
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

/* Refer to task.h */
task_t *find_task(task_tree_t *tree, char *id)
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
            return find_task(tree->lmostchild, id);
        }
        return NULL;
    }
    else if (tree->rsibling != NULL)
    {
        return find_task(tree->rsibling, id);
    }
    return NULL;
}

