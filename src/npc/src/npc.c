#include "npc/npc.h"
#include "common-item.h"

/* See npc.h */
int npc_init(npc_t *npc, char *npc_id, int health, stats_t *stats) //TODO-convo_t *dialogue)
{
    assert(npc != NULL);
    strncpy(npc->npc_id, npc_id, strlen(npc_id));
    npc->health = health;
    //TODO-npc->dialogue = dialogue;
    npc->inventory = NULL;
    npc->stats = stats;
    

    return SUCCESS;
}

/* See npc.h */
npc_t* npc_new(char *npc_id, int health, stats_t *stats)
{
    npc_t *npc;
    npc = malloc(sizeof(npc_t));
    memset(npc, 0, sizeof(npc_t));
    npc->npc_id = malloc(MAX_ID_LEN);
    npc->stats = malloc(sizeof(stats));

    int check = npc_init(npc, npc_id, health, stats); //TODO-dialogue

    if (npc == NULL || npc->npc_id == NULL || check != SUCCESS)
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
    free(npc->stats);
    delete_all_items(&npc->inventory);
    free(npc);

    return SUCCESS;
}

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
    int rc;
    
    rc = add_item_to_hash(&(npc->inventory), item);
    
    return rc;
}

/* See npc.h */
int remove_item_from_npc(npc_t *npc, item_t *item)
{
    int rc;
    
    rc = add_item_to_hash(&(npc->inventory), item);
    
    return rc;
}


/* See npc.h */
item_hash_t* get_npc_inv_hash(npc_t *npc)
{
    return npc->inventory;
}

/* See npc.h */
item_list_t* get_npc_inv_list(npc_t *npc)
{
    item_list_t *head;
    
    head = get_all_items_in_hash(&(npc->inventory));
    
    return head;
}
