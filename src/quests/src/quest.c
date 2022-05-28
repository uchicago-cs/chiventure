#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/quest.h"
#define QUEST_NAME_MAX_LEN 44

/* Refer to quest.h */
quest_t *quest_new(char *quest_id, reward_t *reward, prereq_t *prereq) 
{
    quest_t *q;
    int rc;
    q = calloc(1, sizeof(quest_t));

    if(q == NULL)
    {
        fprintf(stderr, "\nCould not allocate memory for quest!\n");
        return NULL;
    }

    rc = quest_init(q, quest_id, reward, prereq);
    if(rc != SUCCESS){
        fprintf(stderr, "\nCould not initialize quest struct!\n");
        return NULL;
    }

    return q;
}

/* Refer to quest.h */
int quest_init(quest_t *q, char *quest_id, reward_t *reward, prereq_t *prereq)
{
    assert(q != NULL);

    q->quest_id = strndup(quest_id, QUEST_NAME_MAX_LEN);
    q->task_tree = NULL;
    q->reward = reward;
    q->prereq = prereq;
    
    return SUCCESS;
}

/* Refer to quest.h */
int quest_free(quest_t *q)
{
    assert(q != NULL);

    free(q->quest_id);
    task_tree_free(q->task_tree);
    free(q->reward);
    prereq_free(q->prereq);
    free(q);

    return SUCCESS;
}

