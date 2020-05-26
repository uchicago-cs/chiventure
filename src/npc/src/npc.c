#include "npc/npc.h"
#include "common-item.h"

// BASIC NPC FUNCTIONS --------------------------------------------------------

/* See npc.h */
int npc_init(npc_t *npc, char *npc_id, int health) //TODO-convo_t *dialogue)
{
    assert(npc != NULL);
    strncpy(npc->npc_id, npc_id, strlen(npc_id));
    npc->health = health;
    //TODO-npc->dialogue = dialogue;
    npc->inventory = NULL;

    return SUCCESS;
}

/* See npc.h */
npc_t* npc_new(char *npc_id, int health)
{
    npc_t *npc;
    npc = malloc(sizeof(npc_t));
    memset(npc, 0, sizeof(npc_t));
    npc->npc_id = malloc(MAX_ID_LEN);

    int check = npc_init(npc, npc_id, health); //TODO-dialogue

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


// NPCS IN ROOM FUNCTIONS -----------------------------------------------------

/* See npc.h */
int npcs_in_room_init(npcs_in_room_t *npcs_in_room, long room_id,
                      char *room_name)
{
    assert(npcs_in_room != NULL);

    strncpy(npcs_in_room->room_name,room_name,strlen(room_name)+1);
    npcs_in_room->room_id = room_id;
    npcs_in_room->npc_list = NULL;
    npcs_in_room->num_of_npcs = 0;

    return SUCCESS;
}

/* See npc.h */
npcs_in_room_t* npcs_in_room_new(long room_id, char *room_name)
 {
    npcs_in_room_t *npcs_in_room;
    npcs_in_room = malloc(sizeof(npcs_in_room_t));
    
    int check = npcs_in_room_init(npcs_in_room, room_id);

    if (npcs_in_room == NULL || npcs_in_room->room_id == 0 || check != SUCCESS)
    {
        return NULL;
    }

    return npcs_in_room;
 }

 /* See npc.h */
int npcs_in_room_free(npcs_in_room_t *npcs_in_room)
{
    assert(npcs_in_room != NULL);

    free(npcs_in_room->room_id);
    free(npcs_in_room->room_name);
    free(npcs_in_room->npc_list);
    free(npcs_in_room->num_of_npcs);
    free(npcs_in_room);
    return SUCCESS;
}

/* See npc.h */
int npcs_in_room_get_number(npcs_in_room_t *npcs_in_room)
{
    return npcs_in_room->num_of_npcs;
}

/* See npc.h */
int add_npc_to_room(npcs_in_room_t *npcs_in_room, npc_t *npc)
{
    npc_t *check;
    HASH_FIND(hh, npcs_in_room->npc_list, npc->npc_id, strlen(npc->npc_id),
             check);
 
    if (check != NULL)
    {
        return FAILURE; //this npc is already in the room
    }
    HASH_ADD_KEYPTR(hh, npcs_in_room->npc_list, npc->npc_id,
                    strlen(npc->npc_id), npc);
    npcs_in_room->num_of_npcs++;

    return SUCCESS;
}