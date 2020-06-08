#include "game-state/stats.h"
#define MIN_STRING_LENGTH 2
#define MAX_NAME_LENGTH 50

/* See stats.h*/
int stats_global_init(stats_global_t *s, char *name, double max)
{
    assert(s != NULL);
    s->name = strdup(name);
    s->max = max;
    return SUCCESS;
}

/* See stats.h*/
stats_global_t *stats_global_new(char *name, double max)
{
    stats_global_t *global_stat;
    global_stat = malloc(sizeof(stats_global_t));

    int check = stats_global_init(global_stat, name, max);
    if(check != SUCCESS)
    {
        return NULL;
    }

    return global_stat;
}

/* See stats.h */
int stats_init(stats_t *stat, stats_global_t *global_stat, double init)
{
    assert(stat != NULL);
    if(init > global_stat->max)
    {
        init = global_stat->max;
    }

    stat->key = strdup(global_stat->name);
    stat->val = init;
    stat->max = init;
    stat->global = global_stat;
    stat->modifier = 1;
    return SUCCESS;
}

/* See stats.h */
stats_t *stats_new(stats_global_t *global_stat, double init)
{
    stats_t *new_stat;
    new_stat = malloc(sizeof(stats_t));

    int check = stats_init(new_stat, global_stat, init);

    if(check != SUCCESS)
    {
        return NULL;
    }
    return new_stat;
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

/* See stats.h */
int stat_mod_init(stat_mod_t *mod, stats_t *stat, double modifier, int duration) {
    assert(mod != NULL);
    mod->stat = stat;
    mod->modifier = modifier;
    mod->duration = duration;
    return SUCCESS;
}

/* See stats.h */
stat_mod_t *stat_mod_new(stats_t *stat, double modifier, int duration) {
    stat_mod_t *s = malloc(sizeof(stat_mod_t));

    int check = stat_mod_init(s, stat, modifier, duration);

    if (check != SUCCESS || s == NULL || s->stat == NULL) {
        return NULL;
    }

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
int add_stat(stats_hash_t **sh, stats_t *s)
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

/* See stats.h */
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
    for (int i = 0; i < num_stats; i++) {
        stats[i]->modifier *= intensities[i];
        stat_mod_t *new = stat_mod_new(stats[i], intensities[i], durations[i]);
        LL_SEARCH(player_effect->stat_list, tmp, new, stat_mod_equal);
        if (tmp != NULL) {
            tmp->modifier = new->modifier;
            tmp->duration = new->duration;
            free_stat_mod(new);
        } else {
            LL_APPEND(player_effect->stat_list, new);
        }
    }

    return SUCCESS;
}

/* See stats.h */
int free_stats(stats_t *stat)
{
    free(stat->key);
    free(stat);
    return SUCCESS;
}

/* See stats.h */
int free_stats_global(stats_global_t *gs)
{
    free(gs->name);
    free(gs);
    return SUCCESS;
}

/* See stats.h */
int free_stats_table(stats_hash_t *stats_table)
{
    stats_t *current_stat, *tmp;
    HASH_ITER(hh, stats_table, current_stat, tmp)
    {     
        HASH_DEL(stats_table, current_stat);
        free_stats(current_stat);
    }
    return SUCCESS;
}

/* See stats.h */
int free_stats_global_table(stats_global_hash_t *gst)
{
    stats_global_t *current_gs, *tmp;
    HASH_ITER(hh, gst, current_gs, tmp)
    {     
        HASH_DEL(gst, current_gs);
        free_stats_global(current_gs);
    }
    return SUCCESS;
}

/* See stats.h */
int free_stat_mod(stat_mod_t *mod) 
{
    free(mod);
    return SUCCESS;
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
