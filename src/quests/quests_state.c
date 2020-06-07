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

/* Refer to quests_state.h */
int add_achievement_to_quest(quest_t *quest, achievement_t *achievement_to_add)
{
    assert(quest != NULL);

    achievement_llist_t *achievement_to_add_llist;
    achievement_to_add_llist = malloc(sizeof(achievement_llist_t));
    achievement_to_add_llist->next = NULL;
    achievement_to_add_llist->achievement = achievement_to_add;

    achievement_llist_t *head = quest->achievement_list;
    
    LL_APPEND(head,achievement_to_add_llist);

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
int complete_achievement(quest_t *quest, item_t *item_collected, npc_t *npc_met)
{
    achievement_llist_t *head = quest->achievement_list;
    achievement_llist_t *incomplete_achievement;

    LL_SEARCH_SCALAR(head,incomplete_achievement,
                    achievement->completed,0);


    mission_t* mission = incomplete_achievement->achievement->mission;

    if (((strcmp(mission->item_to_collect->item_id,item_collected->item_id)) == 0) &&
        ((strcmp(mission->npc_to_meet->npc_id,npc_met->npc_id)) == 0))
    {
        quest->achievement_list->achievement->completed = 1;
        return SUCCESS;
    }
    else
    {
        return FAILURE;
    }
}

int is_quest_completed(quest_t *quest)
{
    achievement_llist_t *head = quest->achievement_list;
    achievement_llist_t *incomplete_achievement;

    LL_SEARCH_SCALAR(head,incomplete_achievement,
                    achievement->completed,0);

    if(incomplete_achievement == NULL)
    {
        quest->status = 2;
        return SUCCESS;
    }
    else
    {
        return FAILURE;
    }
}

/* Refer to quests_state.h */
int quest_status(quest_t *quest)
{
    return quest->status;
}

/* Refer quests_state.h */
item_t *quest_completed(quest_t *quest)
{
    if (quest_status(quest) == 2)
        return quest->reward;
    else
        return NULL;
}