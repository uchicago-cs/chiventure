#include "battle/battle_logic.h"
#include "common/utlist.h"

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
move_t *find_player_move(chiventure_ctx_battle_t *ctx, char *move_name)
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
    c->stats->hp += item->hp;
    c->stats->strength += item->attack;
    c->stats->defense += item->defense;
    return 0;
}

/* see battle_logic.h */
int use_battle_item(combatant_t *c, char *name)
{
    if (c->items == NULL)
    {
        return FAILURE;
    }
    
    battle_item_t *item = find_battle_item(c->items, name);
    
    if(item == NULL || item->quantity == 0)
    {
        return FAILURE;
    }

    consume_battle_item(c, item);
    item->quantity -= 1;

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
            free(temp->name);
            free(temp->description);
            free(temp);
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
    sc->strength += item->attack;
    sc->defense += item->defense;

    return SUCCESS;
}