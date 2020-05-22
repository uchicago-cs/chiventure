#include "battle/logic.h"
#include "common/utlist.h"

/* check logic.h */
int check_target(battle_t *b, char *target)
{
    while(b->enemy != NULL)
    {
        if (b->enemy->name == target)
        {
            return 0;
        }
        else
        {
            b->enemy = b->enemy->next;
        }
    }
    return 1;
}

/* check logic.h */
int battle_over(combatant_t *p, combatant_t *e)
{
    if (e->stats->hp > 0 && p->stats->hp > 0)
    {
        return 0;
    }
    else if (e->stats->hp <= 0)
    {
        return 1;
    }
    else if (p->stats->hp <= 0)
    {
        return 2;
    }
    else
    {
        return -1;
    }
}

/* check logic.h */
int goes_first(double p_speed, double e_speed)
{
    if (p_speed > e_speed || e_speed == p_speed)
    {
        return 0;
    }
    else if (e_speed > p_speed)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

/* 
 * Finds the desired item to be used
 * 	Inputs:
 * 		inventory - an player or enemy's inventory
 * 		ID - the ID number of the desired item
 * 	Outputs:
 * 		temp->item - pointer to the desired item 
 */
item_t *find_item(item_t *inventory, int ID)
{
    item_t *temp;

    DL_FOREACH(inventory, temp)
    {
        if (temp->id == ID)
        {
            return temp;
        }
    }

    return NULL;
}

int consume_item(combatant_t *c, item_t *item)
{
    c->stats->hp += item->hp;
    c->stats->strength += item->attack;
    c->stats->defense += item->defense;
    return 0;
}

/* see logic.h */
int *player_use_item(combatant_t *c, item_t *inv, int ID)
{
    if (inv == NULL)
    {
        return 1;
    }
    
    item_t *item = find_item(inv, ID);
    
    if(item == NULL || item->quantity == 0)
    {
        return 2;
    }

    consume_item(c, item);
    
    if(res == 0)
    {
        item->quantity -= 1;
        return 0;
    }
    return -1;
}

/* see logic.h */
int award_xp(stat_t *stats, double xp)
{
    stats->xp += xp;
    return 0;
}