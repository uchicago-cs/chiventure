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

    quest->achievement_list->next = quest->achievement_list->achievement;
    quest->achievement_list->achievement = achievement_to_add;

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
int quest_status(quest_t *quest)
{
    return quest->status;
}

/* Refer quests_state.h */
item_t *quest_completed(quest_t *quest)
{
    if (quest->status == 0) {
        return quest->reward;
    }
    // How do we deal with the case when the quest has not been completed?
}