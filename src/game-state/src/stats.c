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

/* See stats.h */
int change_stat(stats_hash_t *sh, char *stat, double change)
{
     
    if (sh == NULL) {
        printf("Error: insert valid hash table");
        exit(1);
    }

    stats_hash_t *curr;
    
    HASH_FIND(hh, sh, stat, strlen(stat), curr);

    if (curr == NULL) {
       printf("Error: no matching stat");
    }
    
    int changed_stat = curr->val + change;

    if (changed_stat > curr->max){
        changed_stat = curr->max;
    }
    if (changed_stat > (curr->global->max)) {
        printf("Error: changed value exceeds global maximum");
        exit(1);
        return FAILURE;
 
    } else {
        curr -> val = changed_stat;
    }

   return 0;
}

/* See stats.h */
double get_stat_current(stats_hash_t *sh, char *stat)
{
    if (sh == NULL) {
        printf("Error: insert valid hash table");
        exit(1);
    }

    stats_hash_t *curr;
    
    HASH_FIND(hh, sh, stat, strlen(stat), curr);

    if (curr == NULL) {
       printf("Error: no matching stat");
    }
    
    return (curr -> val);
}

/* See stats.h */
double get_stat_max(stats_hash_t *sh, char *stat)
{
    if (sh == NULL) {
        printf("Error: insert valid hash table");
        exit(1);
    }

    stats_hash_t *curr;
    
    HASH_FIND(hh, sh, stat, strlen(stat), curr);

    if (curr == NULL) {
       printf("Error: no matching stat");
    }
    
    return (curr -> max);
}

/* See stats.h */
double get_stat_mod(stats_hash_t *sh, char *stat)
{
    if (sh == NULL) {
        printf("Error: insert valid hash table");
        exit(1);
    }

    stats_hash_t *curr;
    
    HASH_FIND(hh, sh, stat, strlen(stat), curr);

    if (curr == NULL) {
       printf("Error: no matching stat");
    }
    
    return (curr -> mod);
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