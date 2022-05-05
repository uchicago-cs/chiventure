#include "battle/battle_logic.h"
#include "common/utlist.h"
#include <ctype.h>

/* check battle_logic.h */
combatant_t* check_target(battle_t *b, char *target)
{
    combatant_t *temp;
    DL_FOREACH(b->enemy, temp)
    {
        if (strncmp(temp->name, target, MAX_NAME_LEN) == 0)
        {
            return temp;
        }
    }
    return NULL;
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

/* check battle_logic.h */
turn_t goes_first(battle_t *b)
{
    combatant_t *temp;
    DL_FOREACH(b->enemy, temp)
    {
        if (b->player->stats->speed < temp->stats->speed)
        {
            return ENEMY;
        }
    }
    return PLAYER;
}

/* see battle_logic.h */
move_t *find_player_move(battle_ctx_t *ctx, char *move_name)
{
    move_t *temp;
    move_t *player_move = NULL;

    DL_FOREACH(ctx->game->battle->player->moves, temp)
    {
        if (strncmp(temp->info, move_name, MAX_MOVE_INFO_LEN) == 0)
        {
            player_move = temp;
            return player_move;
        }
    }
    return NULL;
}

/* see battle_logic.h */
battle_item_t *find_battle_item(battle_item_t *inventory, char *input)
{
    battle_item_t *temp;

    DL_FOREACH(inventory, temp)
    {        
        if (strncmp(temp->name, input, 100) == 0)
        {
            return temp;
        }
    }

    return NULL;
}

/* see battle_logic.h */
int consume_battle_item(combatant_t *c, battle_item_t *item)
{
    if((c->stats->hp + item->hp) > c->stats->max_hp){
        c->stats->hp = c-stats->max_hp;
    }else{
        c->stats->hp += item->hp;
    }
    c->stats->phys_atk += item->attack;
    c->stats->phys_def += item->defense;
    /* Will be implemented once battle_item_t is updated
    c->stats->phys_atk += item->phys_atk;
    c->stats->phys_def += item->phys_def;
    c->stats->mag_atk += item->mag_atk;
    c->stats->mag_def += item->mag_def;
    if((c->stats->sp + item->sp) > c->stats->max_sp){
        c->stats->sp = c->stats->max_sp;
    }else{
        c->stats->sp += item->sp;
    }
    c->stats->accuracy += item->accuracy;
    c->stats->crit += item->crit;
    */
    return 0;
}

/* see battle_logic.h */
int use_battle_item(combatant_t *c, battle_t *battle, char *name)
{
    if (c->items == NULL)
    {
        return FAILURE;
    }
    
    battle_item_t *item = find_battle_item(c->items, name);
    
    if (item == NULL || item->quantity == 0)
    {
        return FAILURE;
    }

    if (item->is_weapon)
    {
        consume_battle_item(battle->enemy, item);
        item->durability -= 10;
    } else
    {
        consume_battle_item(c, item);
        item->quantity -= 1;
    }

    if (item->quantity == 0)
    {
        remove_battle_item(c, item);
    }
    
    return SUCCESS;
}

/* see battle_logic.h */
int remove_battle_item(combatant_t *c, battle_item_t *item)
{
    if (item == NULL)
    {
        return FAILURE;
    }

    battle_item_t *temp;
    DL_FOREACH(c->items, temp)
    {
        if (temp == item)
        {
            if (temp == c->items) // first item in the list
            {
                c->items = temp->next;
            }
            else
            {
                temp->prev->next = temp->next;
            }

            if (temp->next != NULL)
            {
                temp->next->prev = temp->prev;
            }
            free(item->name);
            free(item->description);
            free(item);
        }
    }
    return SUCCESS;
}

/* see battle_logic.h */
int award_xp(stat_t *stats, double xp)
{
    stats->xp += xp;
    return 0;
}

/* See Battle_logic.h */
int stat_changes_add_item_node(stat_changes_t *sc, battle_item_t *item)
{
    stat_changes_add_node(sc);

    stat_changes_t *current = sc;

    while (sc->next != NULL) {
        sc = sc->next;
    }

    sc->hp += item->hp;
    sc->phys_atk += item->attack;
    sc->phys_def += item->defense;
    /* Will be implemented once battle_item_t is updated
    sc->phys_atk += item->phys_atk;
    sc->phys_def += item->phys_def; 
    sc->mag_atk += item->mag_atk;
    sc->mag_def += item->mag_def;
    sc->speed += item->speed;
    if((sc->sp + item->sp) > sc->max_sp){
        sc->sp = sc->max_sp;
    }else{
        sc->sp += item->sp;
    }
    sc->crit += item->crit;
    sc->accuracy += item->accuracy;
    */

    return SUCCESS;
}