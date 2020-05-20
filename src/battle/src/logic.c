#include "battle/logic.h"
#include "common/utlist.h"

/* check logic.h 
int check_target(enemy_t *e) 
{
    return 0;
}*/

/* check logic.h */
/* Leaving this as return 1 so that for the future
 * people can use class or any typing to determine effectiveness
 */
double check_effectiveness(player_t *p, enemy_t *e, move_t *move) 
{
    return 1.0;
}

/* check logic.h */
int battle_over(player_t *p, enemy_t *e) 
{
    if(e->stats->hp > 0 && p->stats->hp > 0)
    {
        return 0;
    }
    else if(e->stats->hp <= 0)
    {
        return 1;
    } 
    else if(p->stats->hp <= 0)
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
    else if(e_speed > p_speed) 
    {
        return 1;
    }
    else
    {
        return -1;
    }
    /*int r = rand() % 2; //random number generator
    switch (difficulty)
    {
    case 1:
        return 0;
        break;
    case 2:
        if (r == 0)
            return 0;
        else
            return 1;
        break;
    case 3:
        return 1;
        break;
    default:
        printf("Invalid difficulty!");
        return -1;
    }*/
}

/* Creates a dummy armor list with hardcoded values
 * 	Inputs:
 * 		inventory - an player or enemy's inventory
 * 		ID - the ID number of the desired item
 * 	Outputs:
 * 		temp->item - pointer to the desired item */
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

/* see logic.h */
item_t* enemy_use_item(enemy_t *e, int ID)
{
    if (e->inventory == NULL)
    {
        fprintf(stderr, "Noooo! Your inventory is empty!");
        return NULL;
    }

    item_t *desired_item = calloc(1, sizeof(item_t));
    desired_item = find_item(e->inventory, ID);

    if (desired_item->quantity == 0)
    {
        fprintf(stderr, "ARGH!! You don't have any!");
        return desired_item;
    }
    else
    {
        desired_item->quantity -= 1;
        desired_item->durability -= 1;
        return desired_item;
    }
}

/* see logic.h */
int award_xp(stats_t *stats, double xp)
{
    stats->xp += xp;
    return 0;
}