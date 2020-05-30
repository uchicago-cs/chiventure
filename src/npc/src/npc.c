#include "npc/npc.h"
#include "game-state/item.h"

/* See npc.h */
int npc_init(npc_t *npc, char *npc_id, char *short_desc, char *long_desc,
             int health, stats_t *stats) //TODO-convo_t *dialogue)
{
    assert(npc != NULL);
    strcpy(npc->npc_id, npc_id);
    strcpy(npc->short_desc, short_desc);
    strcpy(npc->long_desc, long_desc);
    npc->health = health;
    //TODO-npc->dialogue = dialogue;
    npc->inventory = NULL;
    npc->stats = stats;
    
    return SUCCESS;
}

/* See npc.h */
 npc_t* npc_new(char *npc_id, char *short_desc, char *long_desc, 
                int health, stats_t *stats)
{
    npc_t *npc;
    npc = malloc(sizeof(npc_t));
    memset(npc, 0, sizeof(npc_t));
    npc->npc_id = malloc(MAX_ID_LEN);
    npc->short_desc = malloc(MAX_SDESC_LEN);
    npc->long_desc = malloc(MAX_LDESC_LEN);
    npc->stats = malloc(sizeof(stats));

    int check = npc_init(npc, npc_id, short_desc, long_desc, health, stats); 
                         //TODO-dialogue

    if (npc == NULL || npc->npc_id == NULL || npc->short_desc == NULL ||
        npc->long_desc == NULL || npc->stats == NULL || check != SUCCESS)
    {
        return NULL;
    }

    return npc;
}

/* See npc.h */
int npc_free(npc_t *npc)
{
    assert(npc != NULL);
    
    // TODO-free_dialog(npc->dialogue);
    free(npc->npc_id);
    free(npc->short_desc);
    free(npc->long_desc);
    free(npc->stats);
    delete_all_items(&npc->inventory);
    free(npc);

    return SUCCESS;
}

/* See npc.h */


/* See npc.h */
int get_npc_health(npc_t *npc)
{
    return npc->health;
}

/* See npc.h */
int change_npc_health(npc_t *npc, int change, int max)
{
    if ((npc->health + change) < 0)
    {
        npc->health = 0;
    }
    if ((npc->health + change) < max)
    {
        npc->health += change;
    }
    else
    {
        npc->health = max;
    }
    return npc->health;
}

/* See npc.h */
int add_item_to_npc(npc_t *npc, item_t *item)
{
    item_t *check;
    HASH_FIND(hh, npc->inventory, item->item_id, strlen(item->item_id),
              check);
    
    if (check != NULL)
    {
        return FAILURE; //this item id is already in use
    }
    HASH_ADD_KEYPTR(hh, npc->inventory, item->item_id,
                    strlen(item->item_id), item);
    return SUCCESS;
}

/* See npc.h */
item_hash_t* get_npc_inv_hash(npc_t *npc)
{
    return npc->inventory;
}

/* See npc.h */
item_list_t* get_npc_inv_list(npc_t *npc)
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
