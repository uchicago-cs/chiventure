#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quests_state.h"

/* Refer to quests_state.h */
passive_mission_t *passive_mission_new(int *xp, int *levels, int *health)
{
    passive_mission_t *mission = malloc(sizeof(pasive_mission_t));
    int rc;

    rc = passive_mission_init(xp, levels, health);

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
    mission_t *mission = malloc(sizeof(mission_t));
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
achievement_t *achievement_new(mission_t *mission, char *id)
{
    achievement_t *achievement;
    int rc;
    achievement = malloc(sizeof(achievement_t));

    rc = achievement_init(achievement,mission, id);
    if (rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not initialize achievement struct!\n");
    }

    return achievement;
}

/* Refer to quests_state.h */
quest_t *quest_new(long quest_id, achievement_tree_t *achievement_tree,
                   reward_t *reward, stat_req_t *stat_req) 
{
    quest_t *q;
    int rc;
    q = calloc(1, sizeof(quest_t));

    if(q == NULL){
        fprintf(stderr, "\nCould not allocate memory for quest!\n");
        return NULL;
    }

    rc = quest_init(q, quest_id, achievement_tree, reward, stat_req, 0);
    if(rc != SUCCESS){
        fprintf(stderr, "\nCould not initialize quest struct!\n");
        return NULL;
    }

    return q;
}

/* Refer to quests_state.h */
int passive_mission_init(passive_mission_t *mission, int *xp, int *levels, int *health)
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
int achievement_init(achievement_t *achievement, mission_t *mission, char *id)
{
    assert(achievement != NULL);

    achievement->mission = mission;
    achievement->completed = 0;
    achievement->id = id;

    return SUCCESS;
}

/* Refer to quests_state.h */
int quest_init(quest_t *q, long quest_id, achievement_tree_t *achievement_tree,
                reward_t *reward, stat_req_t *stat_req, int status)
{
    assert(q != NULL);

    q->quest_id = quest_id;
    q->achievement_tree = achievement_tree;
    q->reward = reward;
    q->stat_req = stat_req;
    q->status = status;

    return SUCCESS;
}

/* Refer to quests_state.h */
int passive_mission_free(passive_mission_t *mission)
{
    assert(mission != NULL);

    free(mission->xp);
    free(mission->levels);
    free(mission->health);

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
int achievement_free(achievement_t *achievement)
{
    assert(achievement != NULL);

    free(achievement);

    return SUCCESS;
}

/* Refer to quests_state.h */
int quest_free(quest_t *q)
{
    assert(q != NULL);

    free(q->achievement_tree);
    free(q->reward);
    free(q->stat_req);
    free(q);

    return SUCCESS;
}

/* Refer to quests_state.h */
int compare_quests(quest_t *quest1, quest_t *quest2)
{
    if (strcmp(quest1->id, quest2->id) == 0)
    {
        return 0;
    } 
    return 1;
}

/* Refer to quests_state.h */
achievement_tree_t *get_bottom_node(achievement_tree_t *t){
    assert(t != NULL);
    achievement_tree_t *tmp = t;
    if(tmp->lmostchild != NULL){
        get_bottom_node(tmp->lmostchild);
    }
    return tmp;
} 

/* Refer to quests_state.h */
achievement_tree_t *find_parent(achievement_tree_t *tree, char *id) {

    assert(tree != NULL);

    achievment_tree_t *cur = malloc(sizeof(achievement_tree_t));
    cur = quest->achievement_tree_t;

    while(cur = get_bottom_node(cur)){
        if(!(strcmp(cur->achievement->id, id))){
            return cur;
        } else if(cur->rsibling != NULL){
            cur = cur->rsibling; 
        } else if(cur->parent->rsibling != NULL){
            cur = cur->parent->rsibling;
        }
        else
        {
            return NULL; //error printing??
        }
    }
} 

/* Refer to quests_state.h */
int add_achievement_to_quest(quest_t *quest, achievement_t *achievement_to_add, char *parent_id)
{
    assert(quest != NULL);

    achievement_tree_t *tree = malloc(sizeof(achievement_tree_t));
    if (quest->achievement_tree == NULL) {
        tree->achievement = achievement_to_add;
	tree->parent = NULL;
	tree->rsibling = NULL;
	tree->lmostchild = NULL;
	quest->achievement_tree = tree;
	return SUCCESS;
    }
    tree = find_achievement_tree(quest->achievement_tree, parent_id);
    assert(tree != NULL);

    if (tree->lmostchild->achievement == NULL)
    {
        tree->lmostchild = malloc(sizeof(achievement_tree_t));
        tree->lmostchild->achievement = achievement_to_add;
        tree->lmostchild->parent = find_achievement_tree(quest->achievement_tree, parent_id);
    }
    else
    {
        while (tree->rsibling != NULL)
        {
            tree = tree->rsibling;
        }
        tree->rsibling = malloc(sizeof(achievement_tree_t));
        tree->rsibling->achievement = achievement_to_add;
        tree->rsibling->parent = find_achievement_tree(quest->achievement_tree, parent_id);
    }

    return SUCCESS;
}

/* Refer to quests_state.h */
int start_quest(quest_t *quest)
{
    assert(quest != NULL);

    quest->status = 1;

    return SUCCESS;
}

/* Refer to quests_state.h */
int fail_quest(quest_t *quest)
{
    assert(quest != NULL);

    quest->status = -1;

    return SUCCESS;
}

/* Refer to quests_state.h */
achievement_t *find_achievement(achievement_tree_t *tree, char *id) {
    achievement_t *achievement = tree->achievement;

    assert(achievement != NULL);

    if (strcmp(achievement->id, id) == 0) {
        if (achievement->completed == 1) return NULL;
        return achievement;
    } else if (achievement->completed == 1) {
        if (tree->lmostchild != NULL) {
            return find_achievement(tree->lmostchild, id);
	}
	return NULL;
    } else if (tree->rsibling != NULL) {
        return find_achievement(tree->rsibling, id);
    }
    return NULL;
}

/* Refer to quests_state.h */
int complete_achievement(quest_t *quest, char *id)
{
    achievement_tree_t *tree = quest->achievement_tree;

    achievement_t *achievement = find_achievement(tree, id);

    if (((strcmp(achievement->id,id)) == 0) &&
        (achievement->completed == 0))
    {
        quest->achievement_tree->achievement->completed = 1;
        return SUCCESS;
    }
    else
    {
        return FAILURE;
    }
}

/* Refer to quests_state.h */
int is_quest_completed(quest_t *quest)
{
    assert (quest != NULL);
    achievment_tree_t *tmp = malloc(sizeof(achievement_tree_t));
    tmp = quest->achievement_tree_t;
    
    while(tmp = get_bottom_node(tmp)){
        if(tmp->achievement->completed == 1){
            quest->status = 2;
            return 1;
        } else if(tmp->rsibling != NULL){
            tmp = tmp->rsibling; 
        } else if(tmp->parent->rsibling != NULL){
            tmp = tmp->parent->rsibling;
        } else{
            return 0;
        }
    }
}

/* Refer to quests_state.h */
int get_quest_status(quest_t *quest)
{
    return quest->status;
}

/* Refer quests_state.h */
item_t *complete_quest(quest_t *quest)
{
    if (get_quest_status(quest) == 2)
        return quest->reward;
    else
        return NULL;
}
