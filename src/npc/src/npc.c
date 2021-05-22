#include <stdlib.h>
#include "npc/npc.h"

// STRUCT FUNCTIONS -----------------------------------------------------------
/* See npc.h */
int npc_init(npc_t *npc, char *npc_id, char *short_desc, char *long_desc,
             int health, class_t *class, npc_mov_t *movement)
{
    assert(npc != NULL);
    strcpy(npc->npc_id, npc_id);
    strcpy(npc->short_desc, short_desc);
    strcpy(npc->long_desc, long_desc);
    npc->health = health;
    npc->inventory = NULL;
    npc->class = class;
    npc->movement = movement;

    return SUCCESS;
}

/* See npc.h */
npc_t *npc_new(char *npc_id, char *short_desc, char *long_desc,
               int health, class_t *class, npc_mov_t *movement)
{
    npc_t *npc;
    npc = malloc(sizeof(npc_t));
    memset(npc, 0, sizeof(npc_t));
    npc->npc_id = malloc(MAX_ID_LEN);
    npc->short_desc = malloc(MAX_SDESC_LEN);
    npc->long_desc = malloc(MAX_LDESC_LEN);
    npc->class = malloc(sizeof(class_t));
    npc->movement = malloc(sizeof(npc_mov_t));

    int check = npc_init(npc, npc_id, short_desc, long_desc, health, class,
    movement); 

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
    free(npc->npc_id);
    free(npc->short_desc);
    free(npc->long_desc);
    free(npc->class);
    delete_all_items(&npc->inventory);
    free(npc);

    return SUCCESS;
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
int get_npc_health(npc_t *npc)
{
    return npc->health;
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

// "SET" FUNCTIONS ------------------------------------------------------------
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
