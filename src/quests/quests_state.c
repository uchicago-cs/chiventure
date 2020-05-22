#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quests_state.h"


/* Refer to quests_state.h */
quest_t *quest_new(UT_hash_handle hh, char *quest_id, 
                   achievement_llist_t achievement_list, item_t *reward) 
{
    quest_t *q;
    int rc;
    q = calloc(1, sizeof(quest_t));

    if(q == NULL){
        fprintf(stderr, "\nCould not allocate memory for quest!\n");
        return NULL;
    }

    rc = quest_init(hh, quest_id, achievement_list, reward, 2);
    if(rc != SUCCESS){
        fprintf(stderr, "\nCould not initialize quest struct!\n");
        return NULL;
    }

    return q;
}


/* Refer to quests_state.h */
int quest_init(quest_t *q, UT_hash_handle hh, char *quest_id, 
               achievement_llist_t *achievement_list, item_t *reward, int status)
{
    assert(q != NULL);
    assert(quest_id != NULL);
    assert(achievement_list != NULL);
    assert(reward != NULL);

    q->hh = hh;
    q->quest_id = quest_id;
    q->achievement_list = achievement_list;
    q->reward = reward;
    q->status = status;

    return SUCCESS;
}


/* Refer to quests_state.h */
int quest_free(quest_t *q)
{
    assert(q != NULL);

    free(q);

    return SUCCESS;
}