#include <stdlib.h>
#include "npc/npc.h"

// STRUCT FUNCTIONS -----------------------------------------------------------

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
    item_hash_t *items = NULL;
    npc->inventory = items;

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
    free_all_items_from_npc(npc);
    class_free(npc->class);
    free(npc);

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
npc_quest_t *get_npc_quest(npc_t *npc, char *quest_id)
{
    for (npc_quest_t *cur = npc->quests->head; cur != NULL; cur = cur->next)
    {
        if(!strcmp(cur->id, quest_id)) {
            return cur;
        }
    }
    return NULL;
}

/* See npc.h */
npc_task_t *get_npc_task(npc_t *npc, char *task_id)
{
    for (npc_task_t *cur = npc->tasks->head; cur != NULL; cur = cur->next)
    {
        if(!strcmp(cur->id, task_id)) {
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
item_t *get_item_from_npc(npc_t *npc, char *item_id)
{
    item_t *check;
    char *insensitized_id = case_insensitized_string(item_id);
    HASH_FIND(hh, npc->inventory, insensitized_id,
              strlen(insensitized_id), check);
    free(insensitized_id);
    return check;
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
    assert((item != NULL) && (npc != NULL));
    item_t *tmp;
    char *id = case_insensitized_string(item->item_id);
    HASH_FIND(hh, npc->inventory, id, strlen(id), tmp);
    if (tmp == NULL)
    {
        HASH_ADD_KEYPTR(hh, npc->inventory, id, strlen(id), item);
        return SUCCESS;
    }
    else
    {
        return FAILURE; // Hash tables should not contain duplicate items
    }
}

/* See npc.h */
int remove_item_from_npc(npc_t *npc, item_t *item)
{
    HASH_DELETE(hh, npc->inventory, item);
    return SUCCESS;
}

/* See npc.h */
int delete_all_items_from_npc(npc_t *npc)
{
    HASH_CLEAR(hh, npc->inventory);
    return SUCCESS;
}

/* See npc.h */
int free_all_items_from_npc(npc_t *npc)
{
    item_hash_t *elt, *tmp;
    HASH_ITER(hh, npc->inventory, elt, tmp)
    {
        HASH_DEL(npc->inventory, elt);
        free(elt);
    }
    return SUCCESS;
}

/* See npc.h */
int add_convo_to_npc(npc_t *npc, convo_t *c)
{
    assert(npc != NULL && c != NULL);

    npc->standard_dialogue = c;

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

/* See npc.h */
int move_npc(npc_t *npc)
{
    return move_npc_mov(npc->movement);
}

/* See npc.h */
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

/* See npc.h */
int set_proper_dialogue(quest_ctx_t *qctx, npc_t *npc) 
{
    assert(qctx != NULL);
    assert(npc != NULL);
    qctx->player->crnt_npc = npc->npc_id;
    npc_quest_t *quest_head = NULL;
    if (npc->quests != NULL) 
    {
        quest_head = npc->quests->head;
    }
    for (npc_quest_t *cur = quest_head; cur != NULL; cur = cur->next) 
    {
        if (can_player_start_quest(qctx, cur->id)) 
        {
            npc->active_dialogue = cur->dialogue;
            quest_t *quest = get_quest_from_hash(cur->id, qctx->quest_hash);
            if (quest == NULL) 
            {
                return FAILURE;
            }
            start_quest(quest, qctx);
            qctx->player->crnt_npc = "";
            return SUCCESS;
        }
    }
    npc_task_t *task_head = NULL;
    if (npc->tasks != NULL) 
    {
        task_head = npc->tasks->head;
    }
    for (npc_task_t *cur = task_head; cur != NULL; cur = cur->next) 
    {
        if (can_player_complete_task(qctx, cur->id)) 
        {
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

// Conversion FUNCTIONS ---------------------------------------------------

/* See npc.h */
int make_npc_hostile(npc_t *npc)
{
    assert(npc != NULL);
    npc->hostility_level = HOSTILE;

    return SUCCESS;
}

/* See npc.h */
int make_npc_cond_friendly(npc_t *npc)
{
    assert(npc != NULL);
    npc->hostility_level = CONDITIONAL_FRIENDLY;

    return SUCCESS;
}

/* See npc.h */
int change_npc_hostility(npc_t *npc, edge_t *edge)
{
    assert(npc != NULL);
    assert(edge != NULL);

    switch (edge->tone)
    {
        case POSITIVE: 
            break;
        case NEUTRAL: 
            break;
        case NEGATIVE: 
            make_npc_hostile(npc);
            break;
    }

    return SUCCESS;
}
