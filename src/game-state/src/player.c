#include "game-state/player.h"
#include "game-state/item.h"
#include "game-state/stats.h"

/* See player.h */
int player_set_race(player_t *plyr, char *player_race)
{
    if (plyr == NULL || player_race == NULL)
    {
        return FAILURE;
    }

    plyr->player_race = malloc(MAX_ID_LEN);
    
    if (plyr->player_race == NULL)
    {
        return FAILURE;
    }

    strncpy(plyr->player_race, player_race, MAX_ID_LEN);


    return SUCCESS;
}


/* See player.h */
int player_set_class(player_t *plyr, class_t *player_class)
{
    if (plyr == NULL || player_class == NULL)
    {
        return FAILURE;
    }

    plyr->player_class = player_class;

    if (player_class->base_stats != NULL)
    {
        stats_t *curr, *tmp;
        HASH_ITER(hh, player_class->base_stats, curr, tmp)
        {
            stats_t *to_add = copy_stat(curr);

            add_stat(&plyr->player_stats, to_add);
        }
    }

    if (player_class->effects != NULL)
    {
        stat_effect_t *curr, *tmp;
        HASH_ITER(hh, player_class->effects, curr, tmp)
        {
            stat_effect_t *to_add = copy_effect(curr);

            add_stat_effect(&plyr->player_effects, to_add);
        }
    }

    if (player_class->starting_skills != NULL)
    {
        skill_inventory_t *to_add = 
        copy_inventory(player_class->starting_skills);

        plyr->player_skills = to_add;
    }

  
    return SUCCESS;
}


/* See player.h */
player_t* player_new(char *player_id)
{
    player_t *plyr;
    plyr = malloc(sizeof(player_t));
    assert(plyr != NULL);

    memset(plyr, 0, sizeof(player_t));
    plyr->player_id = malloc(MAX_ID_LEN);

    assert(player_id != NULL);

    strncpy(plyr->player_id, player_id, MAX_ID_LEN);
    plyr->level = 1;
    plyr->xp = 0;

    plyr->player_class = NULL;
    plyr->player_stats = NULL;
    plyr->player_skills = NULL;
    plyr->player_effects = NULL;
    plyr->player_race = NULL;
    plyr->inventory = NULL;

    return plyr;
}

/* See player.h */
int player_free(player_t* plyr)
{
    assert(plyr != NULL);

    free(plyr->player_id);

    if (plyr->player_race != NULL)
    {
        free(plyr->player_race);
    }

    delete_all_items(&plyr->inventory);

    if (plyr->player_skills != NULL)
    {
        inventory_free(plyr->player_skills);
    }

    if (plyr->player_stats != NULL)
    {
        free_stats_table(plyr->player_stats);
    }

    if (plyr->player_effects != NULL)
    {
        delete_all_stat_effects(plyr->player_effects);
    }

    free(plyr);
    
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
    int rc;

    if (item->stat_effects != NULL) {
        stat_effect_t *current, *tmp, *e;
        stat_mod_t *elt, *search;
        stats_t *s;
        HASH_ITER(hh, item->stat_effects, current, tmp) {
            LL_FOREACH(current->stat_list, elt) {
                HASH_FIND(hh, player->player_class->base_stats, elt->stat->key, 
                          strlen(elt->stat->key), s);
                if (s != NULL) {
                    apply_effect(&player->player_class->effects, current, &s,
                                 &elt->modifier, &elt->duration, 1);
                }
            }
        }
    }

    rc = add_item_to_hash(&(player->inventory), item);

    return rc;
}

/* See player.h */
int remove_item_from_player(player_t *player, item_t *item)
{
    int rc;
    
    rc = remove_item_from_hash(&(player->inventory), item);
    
    return rc;
}

/* See player.h */
item_list_t *get_all_items_in_inventory(player_t *player)
{
    item_list_t *head;
    
    head = get_all_items_in_hash(&(player->inventory));
    
    return head;
}

/* See player.h */
bool item_in_inventory(player_t *player, item_t *item)
{
    item_t *check;
    HASH_FIND(hh, player->inventory, item->item_id, strlen(item->item_id),
              check);
    if(check != NULL){
        return true;
    }
    return false;
}

/* See player.h */
int player_add_skill(player_t *player, skill_t *skill)
{
    int rc;

    rc = inventory_skill_add(player->player_skills, skill);

    return rc;
}

/* See player.h */
int player_remove_skill(player_t *player, skill_t *skill)
{
    int rc;

    rc = inventory_skill_remove(player->player_skills, skill);

    return rc;
}

/* See player.h */
int player_has_skill(player_t *player, sid_t sid, skill_type_t type)
{
    int rc;

    rc = inventory_has_skill(player->player_skills, sid, type);

    return rc;
}

/* see player.h */
int player_change_stat(player_t *player, char *stat, double change)
{
    int rc;

    rc = change_stat(player->player_stats, stat, change);

    return rc;
}

/* see player.h */
int player_change_stat_max(player_t *player, char *stat, double change)
{
    int rc;

    rc = change_stat_max(player->player_stats, stat, change);

    return rc;
}

/* see player.h */
double player_get_stat_current(player_t *player, char *stat)
{
    double res;

    res = get_stat_current(player->player_stats, stat);

    return res;
}

/* see player.h */
int player_add_stat(player_t *player, stats_t *s)
{
    int rc;

    rc = add_stat(&(player->player_stats), s);

    return rc;
}

/* see player.h */
int player_add_stat_effect(player_t *player, stat_effect_t *effect)
{
    int rc;

    rc = add_stat_effect(&(player->player_effects), effect);

    return rc;
}