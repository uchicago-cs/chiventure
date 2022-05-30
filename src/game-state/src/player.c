#include "game-state/player.h"
#include "game-state/item.h"
#include "battle/battle_structs.h"
#include "game-state/stats.h"

/* See player.h */
int player_set_race(player_t *player, char *player_race)
{
    if (player == NULL || player_race == NULL)
    {
        return FAILURE;
    }

    player->player_race = malloc(MAX_ID_LEN);
    
    if (player->player_race == NULL)
    {
        return FAILURE;
    }

    strncpy(player->player_race, player_race, MAX_ID_LEN);


    return SUCCESS;
}


/* See player.h */
int player_set_class(player_t *player, class_t *player_class)
{
    if (player == NULL || player_class == NULL)
    {
        return FAILURE;
    }

    player->player_class = player_class;

    if (player_class->base_stats != NULL)
    {
        stats_t *curr, *tmp;
        HASH_ITER(hh, player_class->base_stats, curr, tmp)
        {
            stats_t *to_add = copy_stat(curr);

            add_stat(&player->player_stats, to_add);
        }
    }

    if (player_class->effects != NULL)
    {
        stat_effect_t *curr, *tmp;
        HASH_ITER(hh, player_class->effects, curr, tmp)
        {
            stat_effect_t *to_add = copy_effect(curr);

            add_stat_effect(&player->player_effects, to_add);
        }
    }

    if (player_class->starting_skills != NULL)
    {
        skill_inventory_t *to_add = 
        copy_inventory(player_class->starting_skills);

        player->player_skills = to_add;
    }

  
    return SUCCESS;
}


/* See player.h */
player_t* player_new(char *player_id)
{
    player_t *player;
    player = malloc(sizeof(player_t));
    assert(player != NULL);

    memset(player, 0, sizeof(player_t));
    player->player_id = malloc(MAX_ID_LEN);

    assert(player_id != NULL);

    strncpy(player->player_id, player_id, MAX_ID_LEN);
    player->level = 1;
    player->xp = 0;

    player->player_class = NULL;
    player->player_stats = NULL;
    player->player_skills = NULL;
    player->player_effects = NULL;
    player->player_race = NULL;
    player->player_quests = NULL;
    player->player_tasks = NULL;
    player->inventory = NULL;

    player->crnt_room = "";

    return player;
}

/* See player.h */
int player_free(player_t* player)
{
    assert(player != NULL);

    free(player->player_id);

    if (player->player_race != NULL)
    {
        free(player->player_race);
    }

    delete_all_items(&player->inventory);

    if (player->player_skills != NULL)
    {
        inventory_free(player->player_skills);
    }

    if (player->player_stats != NULL)
    {
        free_stats_table(player->player_stats);
    }

    if (player->player_effects != NULL)
    {
        delete_all_stat_effects(player->player_effects);
    }

    if (player->player_quests != NULL)
    {
        player_quest_hash_free(player->player_quests);
    }

    if (player->player_tasks != NULL)
    {
        player_task_hash_free(player->player_tasks);
    }

    free(player);
    
    return SUCCESS;
}

/* See player.h */
player_quest_t *player_quest_new(char *quest_id, int completion)
{
    player_quest_t *pquest;
    int rc;
    pquest = malloc(sizeof(player_quest_t));

    if(pquest == NULL)
    {
        fprintf(stderr, "\nCould not allocate memory for player quest!\n");
        return NULL;
    }

    rc = player_quest_init(pquest, quest_id, completion);
    if (rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not initialize player quest struct!\n");
        return NULL;
    }

    return pquest;
}

/* See player.h */
player_task_t *player_task_new(char *task_id, bool completed)
{
    player_task_t *ptask;
    int rc;
    ptask = calloc(1, sizeof(player_task_t));

    if(ptask == NULL)
    {
        fprintf(stderr, "\nCould not allocate memory for player task!\n");
        return NULL;
    }

    rc = player_task_init(ptask, task_id, completed);
    if (rc != SUCCESS)
    {
        fprintf(stderr, "\nCould not initialize player task struct!\n");
        return NULL;
    }

    return ptask;
}

/* See player.h */
int player_quest_init(player_quest_t *pquest, char *quest_id, int completion)
{
    assert(pquest != NULL);

    pquest->quest_id = strndup(quest_id, QUEST_NAME_MAX_LEN);
    pquest->completion = completion;
    return SUCCESS;
}

/* See player.h */
int player_task_init(player_task_t *ptask, char *task_id, bool completed)
{
    assert(ptask != NULL);

    ptask->task_id = strndup(task_id, QUEST_NAME_MAX_LEN);
    ptask->completed = completed;
    return SUCCESS;
}

/* See player.h */
int player_quest_free(player_quest_t *pquest) {
    assert(pquest != NULL);
    free(pquest->quest_id);
    free(pquest);
    return SUCCESS;
}

/* See player.h */
int player_quest_hash_free(player_quest_hash_t *player_quests)
{
    assert(player_quests != NULL);
    player_quest_hash_t *current_player_quest, *tmp;
    HASH_ITER(hh, player_quests, current_player_quest, tmp)
    {
        HASH_DEL(player_quests, current_player_quest);
        player_quest_free(current_player_quest);
    }
    return SUCCESS;
}

/* See player.h */
int player_task_free(player_task_t *ptask) {
    assert(ptask != NULL);
    free(ptask->task_id);
    free(ptask);
    return SUCCESS;
}

int player_task_hash_free(player_task_hash_t *player_tasks)
{
    assert(player_tasks != NULL);
    player_task_t *current_player_task, *tmp;
    HASH_ITER(hh, player_tasks, current_player_task, tmp)
    {
        HASH_DEL(player_tasks, current_player_task);
        free(current_player_task);
    }
    return SUCCESS;
}

/* See player.h */
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
int get_level(player_t* player)
{
    return player->level;
}

/* See player.h */
int change_level(player_t* player, int change)
{
    player->level += change;
    return player->level;
}

/* See player.h */
int get_xp(player_t* player)
{
    return player->xp;
}

/* See player.h */
int change_xp(player_t* player, int points)
{
    player->xp += points;
    return player->xp;
}


/* See player.h */
item_hash_t* get_inventory(player_t* player)
{
    return player->inventory;
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

/* see player.h */
int add_move(player_t *player, move_t *move) {
    assert(player != NULL);
    assert(move != NULL);

    move_t *last_move = player->moves;
    
    if (player->moves == NULL){
        player->moves = move;
        return SUCCESS;
    }

    while (last_move->next != NULL) {
        last_move = last_move->next;
    }
    last_move->next = move;
    return SUCCESS;
}

/* see player.h */
int add_item_to_player_without_checks(player_t *player, item_t *item) {
    int rc;
    assert(player != NULL);
    if(item == NULL) {
        return FAILURE;
    }
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
