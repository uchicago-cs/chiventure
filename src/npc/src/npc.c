#include "npc/npc.h"

// STRUCT FUNCTIONS -----------------------------------------------------------

/* See npc.h */
int npc_battle_init(npc_battle_t *npc_battle, int health, stat_t* stats,
                    move_t* moves, difficulty_t ai, hostility_t hostility_level,
                    bool will_fight, int surrender_level)
{
    assert(npc_battle != NULL);
    npc_battle->health = health;
    npc_battle->stats = stats;
    npc_battle->moves = moves;
    npc_battle->ai = ai;
    npc_battle->hostility_level = hostility_level;
    npc_battle->will_fight = will_fight
    npc_battle->surrender_level = surrender_level;

    return SUCCESS;
}

/* See npc.h */
npc_t *npc_battle_new(int health, stat_t* stats, move_t* moves, difficulty_t ai,
                      hostility_t hostility_level, bool will_fight,
                      int surrender_level)
{
    npc_battle_t *npc_battle;
    npc = malloc(sizeof(npc_battle_t));
    memset(npc_battle, 0, sizeof(npc_battle_t));
    npc_battle->stats = malloc(sizeof(stat_t));
    npc_battle->moves = malloc(sizeof(move_t)); 

    int check = npc_battle_init(npc_battle, health, stats, moves, ai, 
                                hostility_level, will_fight, surrender_level);

    if (npc_battle == NULL || npc_battle->stats == NULL ||  
        npc_battle->moves == NULL || check != SUCCESS)
    {
        return NULL;
    }

    return npc_battle;
}

/* See npc.h  */
int npc_battle_free(npc_battle_t *npc_battle)
{
    assert(npc_battle != NULL);
    free(npc_battle->stats /* waiting for battle team's stat_free function */
    move_free(npc_battle->moves);
    free(npc_battle);

    return SUCCESS;
}

/* See npc.h */
int npc_init(npc_t *npc, char *npc_id, char *short_desc, char *long_desc,
             convo_t *dialogue, item_hash_t *inventory, class_t *class,
             npc_battle_t *npc_battle)
{
    assert(npc != NULL);
    strcpy(npc->npc_id, npc_id);
    strcpy(npc->short_desc, short_desc);
    strcpy(npc->long_desc, long_desc);
    npc->dialogue = dialogue;
    npc->inventory = inventory;
    npc->class = class;
    npc->npc_battle = npc_battle;

    return SUCCESS;
}

/* See npc.h */
npc_t *npc_new(npc_t *npc, char *npc_id, char *short_desc, char *long_desc,
               convo_t *dialogue, item_hash_t *inventory, class_t *class,
               npc_battle_t *npc_battle)
{
    npc_t *npc;
    npc = malloc(sizeof(npc_t));
    memset(npc, 0, sizeof(npc_t));
    npc->npc_id = malloc(MAX_ID_LEN);
    npc->short_desc = malloc(MAX_SDESC_LEN);
    npc->long_desc = malloc(MAX_LDESC_LEN);
    npc->dialogue = malloc(sizeof(convo_t));
    npc->inventory = malloc(sizeof(item_hash_t));
    npc->class = malloc(sizeof(class_t));
    npc->npc_battle = malloc(sizeof(npc_battle_t));

    int check = npc_init(npc, npc_id, short_desc, long_desc, dialogue, inventory
                         , class, npc_battle); 

    if (npc == NULL || npc->npc_id == NULL ||  npc->short_desc == NULL ||
        npc->long_desc == NULL || npc->dialogue == NULL || 
        npc->inventory == NULL || npc->class == NULL || npc->npc_battle == NULL
        || check != SUCCESS)
    {
        return NULL;
    }

    return npc;
}

/* See npc.h  */
int npc_free(npc_t *npc)
{
    assert(npc != NULL);
    
    free(npc->npc_id);
    free(npc->short_desc);
    free(npc->long_desc);
    convo_free(npc->dialogue);
    delete_all_items(&npc->inventory);
    class_free(npc->class);
    npc_battle_free(npc->npc_battle);
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
}
