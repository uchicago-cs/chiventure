#include "battle/battle_logic.h"
#include "common/utlist.h"

/* check battle_logic.h */
bool check_target(battle_t *b, char *target)
{
    combatant_t *temp;
    DL_FOREACH(b->enemy, temp)
    {
        if (strncmp(temp->name, target, MAX_NAME_LEN) == 0)
        {
            return true;
        }
    }
    return false;
}

/* check battle_logic.h */
battle_status_t battle_over(battle_t *b)
{
    if(b->player->stats->hp <= 0)
    {
        return BATTLE_VICTOR_ENEMY;
    }

    combatant_t *temp;
    DL_FOREACH(b->enemy, temp)
    {
        if(temp->stats->hp > 0)
        {
            return BATTLE_IN_PROGRESS;
        }
    }

    return BATTLE_VICTOR_PLAYER;
}

/*
 * A helper function to goes_first that allows us to sort out the order
 * in which everyone goes
 */
int compare_speeds(int speed1, int speed2) 
{
    return speed1 - speed2;
}

/* check battle_logic.h 
 * The hope is that this function returns a linked list based on compare_speeds
 */
turn_t goes_first(battle_t *b)
{
    void (*cmp)(int) = &compare_speeds;
    DL_SORT(head, cmp);
}

/* see battle_logic.h */
item_t *find_item(item_t *inventory, int id)
{
    item_t *temp;

    DL_FOREACH(inventory, temp)
    {
        if (temp->id == id)
        {
            return temp;
        }
    }

    return NULL;
}

/* see battle_logic.h */
int consume_item(combatant_t *c, item_t *item)
{
    c->stats->hp += item->hp;
    c->stats->strength += item->attack;
    c->stats->defense += item->defense;
    return 0;
}

/* see battle_logic.h */
int use_item(combatant_t *c, int id)
{
    if (c->items == NULL)
    {
        return FAILURE;
    }
    
    item_t *item = find_item(c->items, id);
    
    if(item == NULL || item->quantity == 0)
    {
        return FAILURE;
    }

    consume_item(c, item);
    item->quantity -= 1;
    
    return SUCCESS;
}

/* see battle_logic.h */
int award_xp(stat_t *stats, double xp)
{
    stats->xp += xp;
    return 0;
}
