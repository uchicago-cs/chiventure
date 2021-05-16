#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quests_state.h"


/* Refer to quests_state.h */
mission_t *mission_new(item_t *item_to_collect, npc_t *npc_to_meet)
{
    mission_t *mission = malloc(sizeof(mission_t));
    int rc;

    rc = mission_init(mission, item_to_collect, npc_to_meet);

    if (rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not initialize  mission struct!\n");
    }

    return mission;
}

/* Refer to quests_state.h */
achievement_t *achievement_new(mission_t *mission)
{
    achievement_t *achievement;
    int rc;
    achievement = malloc(sizeof(achievement_t));

    rc = achievement_init(achievement,mission);
    if (rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not initialize achievement struct!\n");
    }

    return achievement;
}

/* Refer to quests_state.h */
quest_t *quest_new(long quest_id, achievement_llist_t *achievement_list,
                   item_t *reward) 
{
    quest_t *q;
    int rc;
    q = calloc(1, sizeof(quest_t));

    if(q == NULL){
        fprintf(stderr, "\nCould not allocate memory for quest!\n");
        return NULL;
    }

    rc = quest_init(q, quest_id, achievement_list, reward, 0);
    if(rc != SUCCESS){
        fprintf(stderr, "\nCould not initialize quest struct!\n");
        return NULL;
    }

    return q;
}

/* Refer to quests_state.h */
int mission_init(mission_t *mission, item_t *item_to_collect, npc_t *npc_to_meet)
{
    assert(mission != NULL);

    mission->item_to_collect = item_to_collect;
    mission->npc_to_meet = npc_to_meet;

    return SUCCESS;

}

/* Refer to quests_state.h */
int achievement_init(achievement_t *achievement, mission_t *mission)
{
    assert(achievement != NULL);

    achievement->mission = mission;
    achievement->completed = 0;

    return SUCCESS;
}

/* Refer to quests_state.h */
int quest_init(quest_t *q, long quest_id, achievement_llist_t *achievement_list,
                item_t *reward, int status)
{
    assert(q != NULL);

    q->quest_id = quest_id;
    q->achievement_list = achievement_list;
    q->reward = reward;
    q->status = status;

    return SUCCESS;
}

/* Refer to quests_state.h */
int mission_free(mission_t *mission)
{
    assert(mission != NULL);

    free(mission->item_to_collect);
    free(mission->npc_to_meet);
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

    free(q->achievement_list);
    free(q->reward);
    free(q);

    return SUCCESS;
}

int compare_quests(quest_t *quest1, quest_t *quest2)
{
    if (strcmp(quest1->id, quest2->id) == 0)
    {
        return 0;
    } 
    return 1;
}

/* Refer to quests_state.h */
int add_achievement_to_quest(quest_t *quest, achievement_t *achievement_to_add)
{
    assert(quest != NULL);

    achievement_llist_t *achievement_to_add_llist;
    achievement_to_add_llist = malloc(sizeof(achievement_llist_t));
    achievement_to_add_llist->next = NULL;
    achievement_to_add_llist->achievement = achievement_to_add;
    
    LL_APPEND(quest->achievement_list,achievement_to_add_llist);

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

//to traverse:
//return pointer to achievement we're looking for
//take tree, achievement ID
//traverse tree in a BFS
//look for a) the achievement ID
//    if so, return a pointer to this achievement in the tree
//THEN b) if the achievement is completed
//    if so, step down and traverse the next level
//    as long as the node has children
//    else return NULL
//if we hit the end of a level, return NULL
//NOTE: this setup makes it so only ONE quest path can be completed
//once it's started.
achievement_t *find_achievement(achievement_tree_t *tree, char *id) {
    achievement_t *achievement = tree->achievement;

    assert(achievement != NULL);

    if (strcmp(achievement->id, id) == 0) {
        if (achievement->completed == 1) return NULL;
        return achievement;
    }
    else if (achievement->completed == 1) {
        if (tree->lmostchild != NULL) {
            return find_achievement(tree->lmostchild, id);
	}
	return NULL;
    }
    else if (tree->rsibling != NULL) {
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
    achievement_llist_t *head = quest->achievement_list;
    achievement_llist_t *incomplete_achievement;

    LL_SEARCH_SCALAR(head,incomplete_achievement,
                    achievement->completed,0);

    if(incomplete_achievement == NULL)
    {
        quest->status = 2;
        return 1;
    }
    else
    {
        return 0;
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
