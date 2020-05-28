#include "game-state/stats.h"

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
int effect_init(stat_effects_t *effect, effects_global_t *global)
{
    assert(effect != NULL);

    effect->global = global;
    effect->stat_list = NULL;

    return SUCCESS;
}

/* See stats.h */
stat_effects_t *effect_new(effects_global_t *global)
{
    stat_effects_t *effect = malloc(sizeof(stat_effects_t));

    int check = effect_init(effect, global);
    
    if(check != SUCCESS || effect == NULL || effect->global == NULL)
    {
        return NULL;
    }

    return effect;
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
int add_stat_player(stats_hash_t *sh, stats_t *s)
{
    printf("add_stat: function not yet implemented\n");
    return 0; // still needs to be implemented
}

/* See stats.h */
char* display_stats(stats_hash_t *s)
{
    printf("display_stats: function not yet implemented\n");
    return "0"; // still needs to be implemented
}

/* See stats.h */
int free_stats(stats_hash_t *s)
{
    printf("free_stats: function not yet implemented\n");
    return 0; // still needs to be implemented
}

/* See stats.h */
int effect_free(stat_effects_t *effect)
{
    assert(effect != NULL);

    stat_mod_t *current, *next;
    current = effect->stat_list;

    while(current != NULL)
    {
        next = effect->stat_list->next;
        free(current);
        current = next;
    }

    free(effect);
}

/* See stats.h */
int delete_all_effects(effects_hash_t *effects)
{
    stat_effects_t *current_effect, *tmp;

    HASH_ITER(hh, effects, current_effect, tmp)
    {
        HASH_DEL(effects, current_effect);
        effect_free(current_effect);
    }

    return SUCCESS;
}

/* See stats.h */
int global_effect_free(effects_global_t *effect)
{
    assert(effect != NULL);

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
        HASH_DEL(effects, current_effect);
        global_effect_free(current_effect);
    }

    return SUCCESS;
}