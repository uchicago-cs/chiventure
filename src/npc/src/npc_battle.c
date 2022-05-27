#include "npc/npc.h"
#include "npc/npc_battle.h"


// STRUCT FUNCTIONS -----------------------------------------------------------

/* See npc_battle.h */
int npc_battle_init(npc_battle_t *npc_battle, stat_t* stats,
                    move_t* moves, difficulty_t ai, hostility_t hostility_level,
                    class_t *class_type, battle_item_t *items,
                    battle_equipment_t *armor, battle_equipment_t *accessory, 
                    battle_equipment_t *weapon)
{
    assert(npc_battle != NULL);
    npc_battle->stats = stats;
    npc_battle->moves = moves;
    npc_battle->ai = ai;
    npc_battle->hostility_level = hostility_level;
    npc_battle->class_type = class_type;
    npc_battle->items = items;
    npc_battle->armor = armor;
    npc_battle->accessory = accessory;
    npc_battle->weapon = weapon;


    return SUCCESS;
}

/* See npc_battle.h */
npc_battle_t *npc_battle_new(stat_t* stats, move_t* moves, 
		                     difficulty_t ai, hostility_t hostility_level, 
			                 class_t *class_type, battle_item_t *items,
                             battle_equipment_t *armor, battle_equipment_t *accessory, 
                             battle_equipment_t *weapon)
{
    npc_battle_t *npc_battle;
    npc_battle = malloc(sizeof(npc_battle_t));
    memset(npc_battle, 0, sizeof(npc_battle_t));
    npc_battle->stats = malloc(sizeof(stat_t));
    npc_battle->moves = malloc(sizeof(move_t)); 
    npc_battle->class_type = malloc(sizeof(class_t));
    npc_battle->items = malloc(sizeof(battle_item_t));
    npc_battle->weapon = malloc(sizeof(battle_equipment_t));
    npc_battle->accessory = malloc(sizeof(battle_equipment_t));
    npc_battle->armor = malloc(sizeof(battle_equipment_t));

    int check = npc_battle_init(npc_battle, stats, moves, ai, 
                                hostility_level, class_type, items,
                                armor, accessory, weapon);

    if (npc_battle == NULL || npc_battle->stats == NULL ||
            npc_battle->moves == NULL || npc_battle->class_type == NULL ||
            npc_battle->items == NULL || check != SUCCESS)
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
    class_free(npc_battle->class_type);

    battle_item_t *curr = npc_battle->items;
    while(curr)
    {
        battle_item_t *next = curr->next;
        free(curr);
        curr = next;
    }
    free(npc_battle);

    return SUCCESS;
}
