#include <stdlib.h>
#include "npc/npc_quests.h"

/* See npc_quests.h */
int npc_quest_init(npc_quest_t *npc_quest, char *quest_id, 
                   convo_t *quest_dialogue)
{
    assert(npc_quest != NULL);

    npc_quest->id = strndup(quest_id, QUEST_NAME_MAX_LEN);
    npc_quest->dialogue = quest_dialogue;
    npc_quest->next = NULL;

    return SUCCESS;
}

/* See npc_quests.h */
npc_quest_t *npc_quest_new(char *quest_id, convo_t *quest_dialogue)
{
    npc_quest_t *npc_quest;
    int rc;
    npc_quest = malloc(sizeof(npc_quest_t));

    if (npc_quest == NULL)
    {
        fprintf(stderr, "\nCould not allocate memory for NPC quest!\n");
        return NULL;
    }

    rc = npc_quest_init(npc_quest, quest_id, quest_dialogue);
    if (rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not initialize NPC quest struct!\n");
        return NULL;
    }

    return npc_quest; 
}

/* See npc_quests.h */
int npc_quest_free(npc_quest_t *npc_quest)
{
    assert (npc_quest != NULL);
    
    free(npc_quest->id);
    int rc = convo_free(npc_quest->dialogue);

    if(rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not free convo struct in quest!\n");
        return FAILURE;
    }

    free(npc_quest);

    return SUCCESS;
}

/* See npc_quests.h */
int npc_task_init(npc_task_t *npc_task, char *task_id, convo_t *task_dialogue)
{
    assert(npc_task != NULL);
    
    npc_task->id = strndup(task_id, QUEST_NAME_MAX_LEN);
    npc_task->dialogue = task_dialogue;
    npc_task->next = NULL;

    return SUCCESS;
}

/* See npc_quests.h */
npc_task_t *npc_task_new(char *task_id, convo_t *task_dialogue)
{
    npc_task_t *npc_task;
    int rc;
    npc_task = malloc(sizeof(npc_task_t));

    if (npc_task == NULL)
    {
        fprintf(stderr, "\nCould not allocate memory for NPC task!\n");
        return NULL;
    }

    rc = npc_task_init(npc_task, task_id, task_dialogue);
    if (rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not initialize NPC task struct!\n");
        return NULL;
    }

    return npc_task;
}

/* See npc_quests.h */
int npc_task_free(npc_task_t *npc_task)
{
    assert (npc_task != NULL);
    
    free(npc_task->id);
    int rc = convo_free(npc_task->dialogue);

    if(rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not free convo struct in quest!\n");
        return FAILURE;
    }

    free(npc_task);

    return SUCCESS;
}

/* See npc_quests.h */
int npc_quest_list_init(npc_quest_list_t *quest_list)
{
    assert(quest_list != NULL);
    quest_list->head = NULL;
    quest_list->length = 0;
    return SUCCESS;
}

/* See npc_quests.h */
npc_quest_list_t *npc_quest_list_new()
{
    npc_quest_list_t *npc_quest_list;
    int rc;
    npc_quest_list = malloc(sizeof(npc_quest_list_t));

    if (!npc_quest_list) {
        fprintf(stderr, "\nCould not allocate memory for NPC quest list!\n");
        return NULL;
    }

    rc = npc_quest_list_init(npc_quest_list);
    if (rc != SUCCESS)
    {
        return NULL;
    }

    return npc_quest_list;
}

/* See npc_quests.h */
int npc_quest_list_free(npc_quest_list_t *npc_quest_list) {
    assert(npc_quest_list != NULL);
    npc_quest_t *tmp;
    for(npc_quest_t *cur = npc_quest_list->head; cur != NULL; cur = tmp) {
        tmp = cur->next;
        if(npc_quest_free(cur) == FAILURE) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

/* See npc_quests.h */
int npc_task_list_init(npc_task_list_t *task_list)
{
    assert(task_list != NULL);
    task_list->head = NULL;
    task_list->length = 0;

    return SUCCESS;
}

/* See npc_quests.h */
npc_task_list_t *npc_task_list_new()
{
    npc_task_list_t *npc_task_list;
    int rc;
    npc_task_list = malloc(sizeof(npc_task_list_t));

    if (!npc_task_list) {
        fprintf(stderr, "\nCould not allocate memory for NPC task list!\n");
        return NULL;
    }

    rc = npc_task_list_init(npc_task_list);
    if (rc != SUCCESS)
    {
        return NULL;
    } 
    
    return npc_task_list; 
}

/* See npc_quests.h */
int npc_task_list_free(npc_task_list_t *npc_task_list) {
    assert(npc_task_list != NULL);
    npc_task_t *tmp;
    for(npc_task_t *cur = npc_task_list->head; cur != NULL; cur = tmp) {
        tmp = cur->next;
        if(npc_task_free(cur) == FAILURE) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

/* See npc_quests.h */
int npc_quest_list_add(npc_quest_list_t *list, npc_quest_t *quest) {
    assert(list != NULL);
    assert(quest != NULL);
    if(list->head == NULL) {
        list->head = quest;
        return SUCCESS;
    }
    npc_quest_t *cur;
    for(cur = list->head; cur->next != NULL; cur = cur->next);
    cur->next = quest;

    list->length++;
    return SUCCESS;
}

/* See npc_quests.h */
int npc_task_list_add(npc_task_list_t *list, npc_task_t *task) {
    assert(list != NULL);
    assert(task != NULL);

    npc_task_t *head = list->head;
    if(head == NULL) {
        list->head = task;
        return SUCCESS;
    }
    npc_task_t *cur;
    for(cur = head; cur->next != NULL; cur = cur->next);
    cur->next = task;

    (list->length)++;
    return SUCCESS;
}

/* See npc_quests.h */
int add_convo_to_quest(npc_quest_t *quest, convo_t *c)
{
    assert(quest != NULL && c != NULL);

    quest->dialogue = c;

    return SUCCESS;
}

/* See npc_quests.h */
int add_convo_to_task(npc_task_t *task, convo_t *c)
{
    assert(task != NULL && c != NULL);

    task->dialogue = c;

    return SUCCESS;
}