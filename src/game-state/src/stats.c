#include "game-state/stats.h"
#define MIN_STRING_LENGTH 2
#define MAX_NAME_LENGTH 50

/* See stats.h */
int stats_init(stats_t *s, char *stats_name, double init)
{
    printf("stats_init: function not yet implemented\n");
    return 0; // still needs to be implemented
}

/* See stats.h */
stats_t *stats_new(char *stats_name, double init)
{
    printf("stats_new: function not yet implemented\n");
    return 0; // still needs to be implemented
}

/* See stats.h */
int global_effect_init(effects_global_t *effect, char *effect_name)
{
    assert(effect != NULL);
    effect->name = strdup(effect_name);

    return SUCCESS;
}

/* See stats.h */
effects_global_t *global_effect_new(char *effect_name)
{
    effects_global_t *effect = malloc(sizeof(effects_global_t));

    int check = global_effect_init(effect, effect_name);

    if (check != SUCCESS || effect == NULL || effect->name == NULL)
    {
        return NULL;
    }

    return effect;
}

/* See stats.h */
int stat_effect_init(stat_effect_t *effect, effects_global_t *global)
{
    assert(effect != NULL);

    effect->key = strdup(global->name);
    effect->global = global;
    effect->stat_list = NULL;

    return SUCCESS;
}

/* See stats.h */
stat_effect_t *stat_effect_new(effects_global_t *global)
{
    stat_effect_t *effect = malloc(sizeof(stat_effect_t));

    int check = stat_effect_init(effect, global);
    
    if(check != SUCCESS || effect == NULL || effect->global == NULL)
    {
        return NULL;
    }

    return effect;
}

stat_mod_t *stat_mod_new(stats_t *stat, double modifier, int duration) {
    stat_mod_t *s = malloc(sizeof(stat_mod_t));
    s->stat = stat;
    s->modifier = modifier;
    s->duration = duration;
    return s;
}

/* See stats.h */
int change_stat(stats_hash_t *sh, char *stat, double change)
{
    printf("change_stat: function not yet implemented\n");
    return 0; // still needs to be implemented
}

/* See stats.h */
double get_stat_current(stats_hash_t *sh, char *stat)
{
    printf("get_stat_current: function not yet implemented\n");
    return 0; // still needs to be implemented
}

/* See stats.h */
double get_stat_max(stats_hash_t *sh, char *stat)
{
    printf("get_stat_max: function not yet implemented\n");
    return 0; // still needs to be implemented
}

/* See stats.h */
double get_stat_mod(stats_hash_t *sh, char *stat)
{
    printf("get_stat_mod: function not yet implemented\n");
    return 0; // still needs to be implemented
}

/* See stats.h */
int add_stat_player(stats_hash_t **sh, stats_t *s)
{
    stats_t *check;
    
    HASH_FIND(hh, *sh, s->key, strlen(s->key), check);

    if (check != NULL)
    {
        return FAILURE;
    }

    HASH_ADD_KEYPTR(hh, *sh, s->key, strlen(s->key), s);
    return SUCCESS;
}

/* See stats.h */
char* display_stats(stats_hash_t *s)
{
    stats_t *stat;
    int size = MIN_STRING_LENGTH + (MAX_NAME_LENGTH * HASH_COUNT(s));
    char list[size];
    
    stat = s;
    if (stat != NULL) 
    {
        strcpy(list, stat->global->name);
    }

    for (stat = stat->hh.next; stat != NULL; stat = stat->hh.next)
    {
        strcat(list, ", ");
        strcat(list, stat->global->name);
    }

    char *display = strdup(list);
    return display;
}

/* See stats.h */
int add_stat_effect(effects_hash_t **hash, stat_effect_t *effect) {
    stat_effect_t *check;
    HASH_FIND(hh, *hash, effect->key, strlen(effect->key), check);

    if (check != NULL)
    {
        return FAILURE; //the effect already exists in the player hash table
    }

    HASH_ADD_KEYPTR(hh, *hash, effect->key, strlen(effect->key), effect);
    return SUCCESS;
}

/* Compares two stat_mod_t struct for equality
 *
 * Parameters: 
 * - mod1, mod2: two stat_mod_t structs
 *
 * Returns:
 * 0 when equal, nonzero value when not equal
 */
int stat_mod_equal(stat_mod_t *m1, stat_mod_t *m2) {
    return strcmp(m1->stat->key, m2->stat->key);
}

/* See stats.h */
int apply_effect(effects_hash_t **hash, stat_effect_t  *effect, stats_t **stats, 
                 double *intensities, int *durations, int num_stats) {
                     
    add_stat_effect(hash, effect);
    stat_effect_t *player_effect;
    HASH_FIND(hh, *hash, effect->key, strlen(effect->key), player_effect);

    stat_mod_t *new, *tmp;
    int i;
    for (i = 0; i < num_stats; i++) {
        stats[i]->modifier *= intensities[i];
        stat_mod_t *new = stat_mod_new(stats[i], intensities[i], durations[i]);
        LL_SEARCH(player_effect->stat_list, tmp, new, stat_mod_equal);
        if (tmp != NULL) {
            tmp->modifier = new->modifier;
            tmp->duration = new->duration;
            free(new);
        } else {
            LL_APPEND(player_effect->stat_list, new);
        }
    }

    return SUCCESS;
}

/* See stats.h */
int free_stats(stats_hash_t *s)
{
    printf("free_stats: function not yet implemented\n");
    return 0; // still needs to be implemented
}

/* See stats.h */
int delete_single_stat_effect(stat_effect_t *effect, effects_hash_t *hash)
{
    assert(effect != NULL);
    HASH_DEL(hash, effect);

    stat_mod_t *current, *tmp;

    LL_FOREACH_SAFE(effect->stat_list, current, tmp)
    {
        LL_DELETE(effect->stat_list, current);
        free(current);
    }

    free(effect->key);

    free(effect);
}

/* See stats.h */
int delete_all_stat_effects(effects_hash_t *effects)
{
    stat_effect_t *current_effect, *tmp;

    HASH_ITER(hh, effects, current_effect, tmp)
    {
        delete_single_stat_effect(current_effect, effects);
    }

    return SUCCESS;
}

/* See stats.h */
int delete_single_global_effect(effects_global_t *effect, 
                                effects_global_hash_t *hash)
{
    assert(effect != NULL);
    HASH_DEL(hash, effect);

    free(effect->name);
    free(effect);

    return SUCCESS;
}

/* See stats.h */
int delete_all_global_effects(effects_global_hash_t *effects)
{
    effects_global_t *current_effect, *tmp;
    HASH_ITER(hh, effects, current_effect, tmp)
    {
        delete_single_global_effect(current_effect, effects);
    }

    return SUCCESS;
}