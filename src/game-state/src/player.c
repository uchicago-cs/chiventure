#include "game-state/player.h"
#include "common-item.h"

/* See player.h */
int player_init(player_t* plyr, char* player_id, int health)
{

    assert(plyr != NULL);
    strncpy(plyr->player_id, player_id, strlen(player_id));
    plyr->level = 1;
    plyr->health = health;
    plyr->xp = 0;
    plyr->inventory = NULL;

    return SUCCESS;
}

/* See player.h */
player_t* player_new(char* player_id, int health)
{
    player_t *plyr;
    plyr = malloc(sizeof(player_t));
    memset(plyr, 0, sizeof(player_t));
    plyr->player_id = malloc(MAX_ID_LEN);

    int check = player_init(plyr, player_id, health);

    if (plyr == NULL || plyr->player_id == NULL)
    {
        return NULL;
    }

    if(check != SUCCESS)
    {
        return NULL;
    }

    return plyr;
}

/* See player.h */
int player_free(player_t* plyr)
{
    assert(plyr != NULL);

    free(plyr->player_id);
    delete_all_items(&plyr->inventory);

    return SUCCESS;
}

int delete_all_players(player_hash_t* players)
{
    player_t *current_player, *tmp;
    HASH_ITER(hh, players, current_player, tmp)
    {
        HASH_DEL(players, current_player);
        player_free(current_player);
    }
    return SUCCESS;
}

/* See player.h */
int get_health(player_t* plyr)
{
    return plyr->health;
}

/* See player.h */
int change_health(player_t* plyr, int change, int max)
{
    if((plyr->health + change) < max)
    {
        plyr->health += change;
    }
    else
    {
        plyr->health = max;
    }
    return plyr->health;
}

/* See player.h */
int get_level(player_t* plyr)
{
    return plyr->level;
}

/* See player.h */
int change_level(player_t* plyr, int change)
{
    plyr->level += change;
    return plyr->level;
}

/* See player.h */
int get_xp(player_t* plyr)
{
    return plyr->xp;
}

/* See player.h */
int change_xp(player_t* plyr, int points)
{
    plyr->xp += points;
    return plyr->xp;
}


/* See player.h */
item_hash_t* get_inventory(player_t* plyr)
{
    return plyr->inventory;
}

/* See player.h */
int add_item_to_player(player_t *player, item_t *item)
{
    item_t *check;

    HASH_FIND(hh, player->inventory, item->item_id, strlen(item->item_id),
              check);

    if (check != NULL)
    {
        return FAILURE; //this item id is already in use.
    }
    HASH_ADD_KEYPTR(hh, player->inventory, item->item_id,
                    strlen(item->item_id), item);
    return SUCCESS;
}

/* See player.h */
item_list_t *get_all_items_in_inventory(player_t *player)
{
    item_list_t *head = NULL;
    item_t *ITTMP_ITEMRM, *curr_item;
    item_list_t *tmp;
    HASH_ITER(hh, player->inventory, curr_item, ITTMP_ITEMRM)
    {
        tmp = malloc(sizeof(item_list_t));
        tmp->item = curr_item;
        LL_APPEND(head, tmp);
    }
    return head;
}

/* See player.h */
int assign_stats_player(player_t *plyr, stats_hash_t *sh)
{
    printf("assign_stats_player: function not yet implemented\n");
    return 0; // still needs to be implemented
}