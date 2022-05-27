#include <stdlib.h>
#include "npc/npc.h"

// STRUCT FUNCTIONS -----------------------------------------------------------

/* See npc.h */
int npc_quest_init(npc_quest_t *npc_quest, char *id, convo_t *quest_dialogue)
{
    assert(npc_quest != NULL);

    npc_quest->id = strndup(id, QUEST_NAME_MAX_LEN);
    npc_quest->dialogue = quest_dialogue;
    npc_quest->next = NULL;

    return SUCCESS;
}

/* See npc.h */
npc_quest_t *npc_quest_new(char *id, convo_t *quest_dialogue)
{
    npc_quest_t *npc_quest;
    int rc;
    npc_quest = malloc(sizeof(npc_quest_t));

    if (npc_quest == NULL)
    {
        fprintf(stderr, "\nCould not allocate memory for NPC quest!\n");
        return NULL;
    }

    rc = npc_quest_init(npc_quest, id, quest_dialogue);
    if (rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not initialize NPC quest struct!\n");
        return NULL;
    }

    return npc_quest; 
}

/* See npc.h */
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

/* See npc.h */
int npc_task_init(npc_task_t *npc_task, char *id, convo_t *task_dialogue)
{
    assert(npc_task != NULL);
    
    npc_task->id = strndup(id, QUEST_NAME_MAX_LEN);
    npc_task->dialogue = task_dialogue;
    npc_task->next = NULL;

    return SUCCESS;
}

/* See npc.h */
npc_task_t *npc_task_new(char *id, convo_t *task_dialogue)
{
    npc_task_t *npc_task;
    int rc;
    npc_task = malloc(sizeof(npc_task_t));

    if (npc_task == NULL)
    {
        fprintf(stderr, "\nCould not allocate memory for NPC task!\n");
        return NULL;
    }

    rc = npc_task_init(npc_task, id, task_dialogue);
    if (rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not initialize NPC task struct!\n");
        return NULL;
    }

    return npc_task;
}

/* See npc.h */
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

/* See npc.h */
int npc_quest_list_init(npc_quest_list_t *quest_list)
{
    assert(quest_list != NULL);
    quest_list->head = NULL;
    quest_list->length = 0;
    return SUCCESS;
}

/* See npc.h */
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

/* See npc.h */
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

/* See npc.h */
int npc_task_list_init(npc_task_list_t *task_list)
{
    assert(task_list != NULL);
    task_list->head = NULL;
    task_list->length = 0;

    return SUCCESS;
}

/* See npc.h */
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

/* See npc.h */
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

/* See npc.h */
int npc_quest_list_add(npc_quest_list_t *list, npc_quest_t *quest) {
    assert(list != NULL);
    assert(quest != NULL);

    npc_quest_t *head = list->head;
    if(head == NULL) {
        list->head = quest;
        return SUCCESS;
    }
    npc_quest_t *cur;
    for(cur = head; cur->next != NULL; cur = cur->next);
    cur->next = quest;

    (list->length)++;
    return SUCCESS;
}

/* See npc.h */
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

/* See npc.h */
int npc_init(npc_t *npc, char *npc_id, char *short_desc, char *long_desc,
             class_t *class, npc_mov_t *movement, hostility_t hostility_level)
{
    assert(npc != NULL);
    strcpy(npc->npc_id, npc_id);
    strcpy(npc->short_desc, short_desc);
    strcpy(npc->long_desc, long_desc);
    npc->standard_dialogue = NULL;
    npc->active_dialogue = npc->standard_dialogue;
    npc->inventory = NULL;
    npc->class = class;
    npc->hostility_level = hostility_level;
    npc->npc_battle = NULL;
    npc->movement = movement;
    npc->quests = npc_quest_list_new();
    npc->tasks = npc_task_list_new();

    return SUCCESS;
}

/* See npc.h */
npc_t *npc_new(char *npc_id, char *short_desc, char *long_desc,
               class_t *class, npc_mov_t *movement, hostility_t hostility_level)
{
    npc_t *npc;
    npc = malloc(sizeof(npc_t));
    memset(npc, 0, sizeof(npc_t));
    npc->npc_id = malloc(MAX_ID_LEN);
    npc->short_desc = malloc(MAX_SDESC_LEN);
    npc->long_desc = malloc(MAX_LDESC_LEN);
    npc->class = malloc(sizeof(class_t));
    npc->movement = malloc(sizeof(npc_mov_t));

    npc->quests = npc_quest_list_new();
    npc->tasks = npc_task_list_new();

    npc->quests = NULL;
    npc->tasks = NULL;

    char *insensitized_id = case_insensitized_string(npc_id);

    int check = npc_init(npc, insensitized_id, short_desc, long_desc,
                         class, movement, hostility_level);

    free(insensitized_id);

    if (npc == NULL || npc->npc_id == NULL ||  npc->short_desc == NULL ||
            npc->long_desc == NULL || check != SUCCESS)
    {
        return NULL;
    }

    return npc;
}

/* See npc.h  */
int npc_free(npc_t *npc)
{
    assert(npc != NULL);

    if (npc->active_dialogue != NULL)
    {
        convo_free(npc->active_dialogue);
    }
    if (npc->standard_dialogue != NULL)
    {
        convo_free(npc->standard_dialogue);
    }
    if (npc->movement != NULL)
    {
        npc_mov_free(npc->movement);
    }
    if (npc->npc_battle != NULL)
    {
        npc_battle_free(npc->npc_battle);
    }
    if (npc->quests != NULL)
    {
        npc_quest_list_free(npc->quests);
    }
    if (npc->tasks != NULL)
    {
        npc_task_list_free(npc->tasks);
    }
    free(npc->npc_id);
    free(npc->short_desc);
    free(npc->long_desc);
    delete_all_items(&npc->inventory);
    class_free(npc->class);
    free(npc);

    return SUCCESS;
}

/* See npc.h */
int set_proper_dialogue(quest_ctx_t *qctx, npc_t *npc) {
    assert(qctx != NULL);
    assert(npc != NULL);
    qctx->player->crnt_npc = npc->npc_id;
    npc_quest_t *quest_head = NULL;
    if(npc->quests != NULL) {
        quest_head = npc->quests->head;
    }
    for(npc_quest_t *cur = quest_head; cur != NULL; cur = cur->next) {
        if(npc_can_give_quest(qctx, cur->id)) {
            npc->active_dialogue = cur->dialogue;
            quest_t *quest = get_quest_from_hash(cur->id, qctx->quest_hash);
            if(quest == NULL) {
                return FAILURE;
            }
            start_quest(quest, qctx);
            qctx->player->crnt_npc = "";
            return SUCCESS;
        }
    }
    npc_task_t *task_head = NULL;
    if(npc->tasks != NULL) {
        task_head = npc->tasks->head;
    }
    for(npc_task_t *cur = task_head; cur != NULL; cur = cur->next) {
        if(npc_can_complete_task(qctx, cur->id)) {
            npc->active_dialogue = cur->dialogue;
            update_task(cur->id, qctx);
            qctx->player->crnt_npc = "";
            return SUCCESS;
        }
    }
    qctx->player->crnt_npc = "";
    npc->active_dialogue = npc->standard_dialogue;
    return SUCCESS;
}

// "CHECK" FUNCTIONS ----------------------------------------------------------

/* See npc.h */
bool check_npc_battle(npc_t *npc)
{
    assert(npc != NULL);

    if (npc->hostility_level == HOSTILE && npc->npc_battle == NULL) 
    {
        return false;
    }
    else if (npc->hostility_level == FRIENDLY && npc->npc_battle != NULL)
    {
        return false;
    }
    else 
    {
        return true;
    }
}

/* See npc.h */
bool item_in_npc_inventory(npc_t *npc, char *item_id)
{
    item_t *check;
    char *insensitized_id = case_insensitized_string(item_id);
    HASH_FIND(hh, npc->inventory, insensitized_id,
              strnlen(item_id, MAX_ID_LEN), check);
    free(insensitized_id);
    if (check != NULL)
    {
        return true;
    }
    return false;
}

// "GET" FUNCTIONS ------------------------------------------------------------
/* See npc.h */
npc_quest_t *get_npc_quest(npc_t *npc, char *id)
{
    for (npc_quest_t *cur = npc->quests->head; cur != NULL; cur = cur->next)
    {
        if(!strcmp(cur->id, id)) {
            return cur;
        }
    }
    return NULL;
}

/* See npc.h */
npc_task_t *get_npc_task(npc_t *npc, char *id)
{
    for (npc_task_t *cur = npc->tasks->head; cur != NULL; cur = cur->next)
    {
        if(!strcmp(cur->id, id)) {
            return cur;
        }
    }
    return NULL;
}

/* See npc.h */
char *get_sdesc_npc(npc_t *npc)
{
    if (npc == NULL)
    {
        return NULL;
    }
    return npc->short_desc;
}

/* See npc.h */
char *get_ldesc_npc(npc_t *npc)
{
    if (npc == NULL)
    {
        return NULL;
    }
    return npc->long_desc;
}

/* See npc.h */
item_hash_t *get_npc_inv_hash(npc_t *npc)
{
    return npc->inventory;
}

/* See npc.h */
item_list_t *get_npc_inv_list(npc_t *npc)
{
    item_list_t *head = NULL;
    item_t *ITTMP_ITEMRM, *curr_item;
    item_list_t *tmp;
    HASH_ITER(hh, npc->inventory, curr_item, ITTMP_ITEMRM)
    {
        tmp = malloc(sizeof(item_list_t));
        tmp->item = curr_item;
        LL_APPEND(head, tmp);
    }
    return head;
}

/* See npc.h */
npc_battle_t *get_npc_battle(npc_t *npc)
{
    assert(npc != NULL);

    return npc->npc_battle;
}

/* See npc.h */
int get_npc_max_hp(npc_t *npc)
{
    assert(npc != NULL);

    if (npc->npc_battle == NULL) 
    {
        return -1;
    } 
    else 
    {
        return npc->npc_battle->stats->max_hp;
    }
}

/* See npc.h */
int get_npc_hp(npc_t *npc)
{
    assert(npc != NULL);

    if (npc->npc_battle == NULL)
    {
        return -1;
    }
    else
    {
        return npc->npc_battle->stats->hp;
    }
}

/* See npc.h */
npc_mov_t *get_npc_mov(npc_t *npc)
{
    assert(npc != NULL);

    return npc->movement;
}
// "SET" FUNCTIONS ------------------------------------------------------------

/* See npc.h */
int add_item_to_npc(npc_t *npc, item_t *item)
{
    int rc;

    rc = add_item_to_hash(&(npc->inventory), item);

    return rc;
}

/* See npc.h */
int remove_item_from_npc(npc_t *npc, item_t *item)
{
    int rc;

    rc = remove_item_from_hash(&(npc->inventory), item);

    return rc;
}

/* See npc.h */
int add_convo_to_npc(npc_t *npc, convo_t *c)
{
    assert(npc != NULL && c != NULL);

    npc->standard_dialogue = c;

    return SUCCESS;
}


/* Adds a conversation to a quest.
 * 
 * Parameters:
 * - quest: the npc's quest
 * - c: the quest-specific dialogue
 * 
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 */
int add_convo_to_quest(npc_quest_t *quest, convo_t *c)
{
    assert(quest != NULL && c != NULL);

    quest->dialogue = c;

    return SUCCESS;
}

/* Adds a conversation to a task.
 * 
 * Parameters:
 * - task: the npc's task
 * - c: the task-specific dialogue
 * 
 * Returns:
 *  - SUCCESS on success, FAILURE if an error occurs
 */
int add_convo_to_task(npc_task_t *task, convo_t *c)
{
    assert(task != NULL && c != NULL);

    task->dialogue = c;

    return SUCCESS;
}

/* See npc.h */
int add_battle_to_npc(npc_t *npc, stat_t *stats, move_t *moves,
                      difficulty_t ai, hostility_t hostility_level,
                      class_t *class_type, battle_item_t *items,
                      battle_equipment_t *armor,
                      battle_equipment_t *accessory, battle_equipment_t *weapon)
{
    assert(npc != NULL);

    npc_battle_t *npc_battle = npc_battle_new(stats, moves, ai,
                                              hostility_level,
                                              class_type, items,
                                              armor, accessory, weapon);

    assert(npc_battle != NULL);

    npc->npc_battle = npc_battle;

    return SUCCESS;
}

/* See npc.h */
int change_npc_hp(npc_t *npc, int change)
{
    assert(npc->npc_battle != NULL);

    if ((npc->npc_battle->stats->hp + change) < 0)
    {
        npc->npc_battle->stats->hp = 0;
    }
    else if ((npc->npc_battle->stats->hp + change) < 
             (npc->npc_battle->stats->max_hp))
    {
        npc->npc_battle->stats->hp += change;
    }
    else
    {
        npc->npc_battle->stats->hp = 
        npc->npc_battle->stats->max_hp;
    }
    return npc->npc_battle->stats->hp;
}

int delete_all_npcs(npc_hash_t *npcs)
{
    npc_t *current_npc, *tmp;
    HASH_ITER(hh, npcs, current_npc, tmp)
    {
        HASH_DEL(npcs, current_npc);
        npc_free(current_npc);
    }
    return SUCCESS;
}

