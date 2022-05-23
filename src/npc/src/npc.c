#include <stdlib.h>
#include "npc/npc.h"

// STRUCT FUNCTIONS -----------------------------------------------------------

/* See npc.h */
int npc_quest_init(npc_quest_t *npc_quest, char *id, convo_t *quest_dialogue)
{
    assert(npc_quest != NULL);

    npc_quest->id = id;
    npc_quest->quest_dialogue;
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
int *npc_quest_free(npc_quest_t *npc_quest)
{
    npc_quest_t *temp;

    assert (npc_quest != NULL);
    
    free(npc_quest->id);
    int rc = convo_free(npc_quest->quest_dialogue);

    if(rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not free convo struct in quest!\n");
        return NULL;
    }

    temp = npc_quest->next;
    free(npc_quest);

    npc_quest = temp;

    return(npc_quest_free(npc_quest));
    }
    else return SUCCESS;
}

/* See npc.h */
int npc_task_init(npc_task_t *npc_task, char *id, convo_t *task_dialogue)
{
    assert(npc_task != NULL);
    
    npc_task->id = id;
    npc_task->task_dialogue;
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
int *npc_task_free(npc_task_t *npc_task)
{
    npc_task_t *temp;

    if (npc_task != NULL)
    {
        free(npc_task->id);
        int rc = convo_free(npc_task->task_dialogue);

        if(rc != SUCCESS)
        {
            fprintf(stderr, "\nCould not free convo struct in task!\n");
            return NULL;
        }

        temp = npc_task->next;
        free(npc_task);

        npc_task = temp;

        return(npc_task_free(npc_task));
    }
    else return SUCCESS;
}

/* See npc.h */
int npc_quest_list_init(npc_quest_list_t *quest_list)
{

}
npc_quest_list_t *npc_quest_list_new();

/* See npc.h */
int npc_quest_list_free(npc_quest_list_t *quest_list)
{
    npc_quest_t *temp;
    npc_quest_t *head = quest_list;

    while (head != NULL)
    {
        temp = head->next;
        head = head->next;
        npc_quest_free(temp);
    }
    return SUCCESS;
}

int npc_task_list_init(npc_task_list_t *task_list);
npc_task_list_t *npc_task_list_new();

/* See npc.h */
npc_task_list_t *npc_task_list_free(npc_task_list_t *task_list)
{
    npc_task_t *temp;
    npc_task_t *head = task_list;

    while (head != NULL)
    {
        temp = head->next;
        head = head->next;
        npc_task_free(temp);
    }
    return SUCCESS;
}

/* See npc.h */
int npc_init(npc_t *npc, char *npc_id, char *short_desc, char *long_desc,
             class_t *class, npc_mov_t *movement, bool will_fight,
             npc_quest_list_t *quests, npc_task_list_t *tasks)
{
    assert(npc != NULL);
    strcpy(npc->npc_id, npc_id);
    strcpy(npc->short_desc, short_desc);
    strcpy(npc->long_desc, long_desc);
    npc->dialogue = NULL;
    npc->inventory = NULL;
    npc->class = class;
    npc->will_fight = will_fight;
    npc->npc_battle = NULL;
    npc->movement = movement;
    // NEW //
    int rc1 = npc_quest_list_init(quests);
    int rc2 = npc_task_list_init(tasks);

    if ((rc1 != SUCCESS) | (rc2 != SUCCESS))
    {
        return FAILURE;
    }
    // NEW //

    return SUCCESS;
}

/* See npc.h */
npc_t *npc_new(char *npc_id, char *short_desc, char *long_desc,
               class_t *class, npc_mov_t *movement, bool will_fight,
               npc_quest_list_t *quests, npc_task_list_t *tasks)
{
    npc_t *npc;
    npc = malloc(sizeof(npc_t));
    memset(npc, 0, sizeof(npc_t));
    npc->npc_id = malloc(MAX_ID_LEN);
    npc->short_desc = malloc(MAX_SDESC_LEN);
    npc->long_desc = malloc(MAX_LDESC_LEN);
    npc->class = malloc(sizeof(class_t));
    npc->movement = malloc(sizeof(npc_mov_t));
    // NEW //
    int rc1 = npc->quests = npc_quest_list_new();
    int rc2 = npc->tasks = npc_task_list_new();

    if ((rc1 != SUCCESS) | (rc2 != SUCCESS))
    {
        return FAILURE;
    }
    // NEW //

    char *insensitized_id = case_insensitized_string(npc_id);

    int check = npc_init(npc, insensitized_id, short_desc, long_desc,
                         class, movement, will_fight, quests, tasks);

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

    if (npc->dialogue != NULL)
    {
        convo_free(npc->dialogue);
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

// "CHECK" FUNCTIONS ----------------------------------------------------------

/* See npc.h */
bool check_npc_battle(npc_t *npc)
{
    assert(npc != NULL);

    if (npc->will_fight == true && npc->npc_battle == NULL)
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
int get_npc_health(npc_t *npc)
{
    assert(npc != NULL);

    if (npc->npc_battle == NULL)
    {
        return -1;
    }
    else
    {
        return npc->npc_battle->health;
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

    npc->dialogue = c;

    return SUCCESS;
}

/* See npc.h */
int add_battle_to_npc(npc_t *npc, int health, stat_t *stats, move_t *moves,
                      difficulty_t ai, hostility_t hostility_level,
                      int surrender_level, class_t *class_type, 
                      battle_item_t *items)
{
    assert(npc != NULL);

    npc_battle_t *npc_battle = npc_battle_new(health, stats, moves, ai,
                                              hostility_level, surrender_level,
                                              class_type, items);

    assert(npc_battle != NULL);

    npc->npc_battle = npc_battle;

    return SUCCESS;
}

/* See npc.h */
int change_npc_health(npc_t *npc, int change, int max)
{
    assert(npc->npc_battle != NULL);

    if ((npc->npc_battle->health + change) < 0)
    {
        npc->npc_battle->health = 0;
    }
    else if ((npc->npc_battle->health + change) < max)
    {
        npc->npc_battle->health += change;
    }
    else
    {
        npc->npc_battle->health = max;
    }
    return npc->npc_battle->health;
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

