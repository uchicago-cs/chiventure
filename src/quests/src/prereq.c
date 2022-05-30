#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "quests/prereq.h"

/* Refer to prereq.h */
prereq_t *prereq_new(int hp, int level) {
    prereq_t *prereq = malloc(sizeof(prereq_t));

    int rc = prereq_init(prereq, hp, level);
    if(rc != SUCCESS) {
        fprintf(stderr, "\nCould not initialize prereq struct!\n");
        return NULL;
    }
    return prereq;
}

/* Refer to prereq.h */
int prereq_init(prereq_t * prereq, int hp, int level) {
    assert(prereq != NULL);

    prereq->hp = hp;
    prereq->level = level;
    prereq->quest_list = id_list_new();
    prereq->task_list = id_list_new();

    return SUCCESS;
}

/* Refer to prereq.h */
int prereq_free(prereq_t *prereq) {
    if(prereq == NULL) {
        return SUCCESS;
    }
    if(prereq->quest_list) {
        id_list_free(prereq->quest_list);
    }
    if(prereq->task_list) {
        id_list_free(prereq->task_list);
    }
    free(prereq);
    return SUCCESS;
}

/* Refer to prereq.h */
id_list_t *id_list_new() {
    id_list_t *id_list = malloc(sizeof(id_list_t));

    int rc = id_list_init(id_list);
    if(rc != SUCCESS) {
        fprintf(stderr, "\nCould not initialize id_list struct!\n");
        return NULL;
    }
    return id_list;  
}

/* Refer to prereq.h */
int id_list_init(id_list_t *id_list) {
    assert(id_list != NULL);

    id_list->head = NULL;
    id_list->length = 0;

    return SUCCESS;
}

/* Refer to quests_state.h */
int id_list_free(id_list_t *id_list) {
    assert(id_list != NULL);
    id_list_node_t *next = NULL;
    for(id_list_node_t *cur = id_list->head; cur != NULL; cur = next) {
        next = cur->next;
        free(cur);
    }
    free(id_list);
    return SUCCESS;
}

/* Refer to prereq.h */
int id_list_add(id_list_t *id_list, char *id) {
    assert(id_list != NULL);
    assert(id != NULL);

    id_list_node_t *node = malloc(sizeof(id_list_node_t));
    assert(node != NULL);

    node->id = id;
    node->next = NULL;
    
    if(id_list->head == NULL) {
        id_list->head = node;
    }
    else {
        id_list_node_t *cur = id_list->head;
        while(cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = node;
    }
    id_list->length++;
    return SUCCESS;
} 

/*Refer to prereq.h */
int prereq_add_task(prereq_t *prereq, char *task_id) {
    assert(prereq != NULL);
    assert(task_id != NULL);
    return id_list_add(prereq->task_list, task_id);
}

/*Refer to prereq.h */
int prereq_add_quest(prereq_t *prereq, char *quest_id) {
    assert(prereq != NULL);
    assert(quest_id != NULL);
    return id_list_add(prereq->quest_list, quest_id);
}

