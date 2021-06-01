#include "npc/npc_battle.h"

// STRUCT FUNCTIONS -----------------------------------------------------------

/* See npc_battle.h */
int npc_battle_init(npc_battle_t *npc_battle, int health, stat_t* stats,
                    move_t* moves, difficulty_t ai, hostility_t hostility_level,
                    int surrender_level)
{
    assert(npc_battle != NULL);
    npc_battle->health = health;
    npc_battle->stats = stats;
    npc_battle->moves = moves;
    npc_battle->ai = ai;
    npc_battle->hostility_level = hostility_level;
    npc_battle->surrender_level = surrender_level;

    return SUCCESS;
}

/* See npc_battle.h */
npc_battle_t *npc_battle_new(int health, stat_t* stats, move_t* moves, 
		             difficulty_t ai, hostility_t hostility_level, 
			     int surrender_level)
{
    npc_battle_t *npc_battle;
    npc_battle = malloc(sizeof(npc_battle_t));
    memset(npc_battle, 0, sizeof(npc_battle_t));
    npc_battle->stats = malloc(sizeof(stat_t));
    npc_battle->moves = malloc(sizeof(move_t)); 

    int check = npc_battle_init(npc_battle, health, stats, moves, ai, 
                                hostility_level, surrender_level);

    if (npc_battle == NULL || npc_battle->stats == NULL ||  
        npc_battle->moves == NULL || check != SUCCESS)
    {
        return NULL;
    }

    return npc_battle;
}

/* See npc_battle.h  */
int npc_battle_free(npc_battle_t *npc_battle)
{
    assert(npc_battle != NULL);
    free(npc_battle->stats); /*waiting for battle team's stat_free function*/
    move_free(npc_battle->moves);
    free(npc_battle);

    return SUCCESS;
}


// "SET" FUNCTIONS ------------------------------------------------------------
/* See npc.h  */
int transfer_all_npc_items(npc_t *npc, room_t *room)
{
    item_list_t *item_lst = get_all_items_in_hash(&(npc->inventory));

    while (item_lst->next != NULL)
    {
        add_item_to_hash(&(room->items), item_lst->item);
        item_lst = item_lst->next;
    }

    delete_item_llist(item_lst);
    delete_all_items(&(npc->inventory));

    return SUCCESS;
}