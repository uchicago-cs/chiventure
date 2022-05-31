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
    return false;
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

/* Refer to quests_state.h */
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

    rc = quest_init(q, quest_id, task_tree, reward, stat_req);
    if(rc != SUCCESS)
    {

        fprintf(stderr, "\nCould not initialize quest struct!\n");
        return NULL;
    }

    return q;
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
int stat_req_init(stat_req_t *stat_req, int hp, int level)
{
    assert(stat_req != NULL);

    stat_req->hp = hp;
    stat_req->level = level;

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
               reward_t *reward, stat_req_t *stat_req)

{
    assert(q != NULL);


    q->quest_id = strndup(quest_id, QUEST_NAME_MAX_LEN);
    q->task_tree = task_tree;
    q->reward = reward;
    q->stat_req = stat_req;

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
    free(q->stat_req);
    free(q);

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
bool can_start_quest(quest_t *quest, player_t *player)
{
    stats_hash_t *stats_hash = player->player_stats;
    double health = get_stat_current(stats_hash, "health");

    if (health >= quest->stat_req->hp &&
            player->level >= quest->stat_req->level)
    {
        return true;
    }
    return false;
}

/* Refer to quests_state.h */
int start_quest(quest_t *quest, player_t *player)
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
    while(cur)
    {
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
    pquest->completion = Q_FAILED;

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
    if(!pquest || pquest->completion == -1)
    {
        return false;
    }

    bool crntStatus = true;
    player_task_t *temp;
    while(cur)
    {
        temp = get_player_task_from_hash(cur->task->id, player->player_tasks);
        if(temp && temp->completed)
        {
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
bool is_task_completed(task_t *task, player_t *player)
{
    assert(task != NULL);
    assert(player != NULL);

    player_task_t *ptask = get_player_task_from_hash(task->id, player->player_tasks);
    if(!ptask)
    {
        return false;
    }
    ptask->completed = true;
    return true;

}

/* Refer to quests_state.h */
int get_player_quest_status(quest_t *quest, player_t *player)
{
    quest_t *q;
    HASH_FIND(hh, hash_table, quest_id,
              strnlen(quest_id, MAX_ID_LEN), q);

    HASH_FIND_STR(hash_table, quest_id, q);
    return q;
}

/* Refer quests_state.h */
reward_t *complete_task(char *task_id, quest_ctx_t *qctx)
{
    quest_t *check;

    check = get_quest_from_hash(quest->quest_id, *hash_table);

    if (check != NULL)
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
            task_tree_t *lmost_sibling;
            if(tree->parent == NULL) {
                lmost_sibling = quest_of_task->task_tree;
            }
            else {
                lmost_sibling = tree->parent->lmostchild;
            }
            for(task_tree_t *cur = lmost_sibling; cur != NULL; cur = cur->rsibling) {
                if(!get_player_task_status(cur->task, player)) {
                    remove_task_in_player_hash(&(qctx->player->player_tasks), cur->task->id);
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

/* Refer to quests_state.h */
task_t *get_task_from_hash(char *id, quest_hash_t *hash_table)
{
    task_t *task = NULL;
    for(quest_t *cur = hash_table; cur != NULL; cur = cur->hh.next)
    {
        task = find_task_in_tree(cur->task_tree, id);
        if(task != NULL)
        {
            break;
        }
    }
}

/* Refer to quests_state.h */
void update_task(char *task_id, quest_ctx_t *qctx) {
    accept_reward(complete_task(task_id, qctx), qctx);
}

/* Refer to quests_state.h */
bool can_player_start_quest(quest_ctx_t *qctx, char *quest_id)
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

    return (meets_prereqs(player, prereq));
}

/* Refer to quests_state.h */
bool can_player_complete_task(quest_ctx_t *qctx, char *task_id)
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
    if(!pquest)
    {
        return 0;
    }

    return (meets_prereqs(player, prereq));
}
