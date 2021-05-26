#include "game-state/stats.h"
#define MIN_STRING_LENGTH 2
#define MAX_NAME_LENGTH 70

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
    if (check != SUCCESS)
    {
        return NULL;
    }

    return global_stat;
}

/* See stats.h */
stats_global_t* copy_global_stat(stats_global_t* global_stat)
{
    assert(global_stat != NULL);

    stats_global_t* copy = stats_global_new(global_stat->name, global_stat->max);

    return copy;
}

/* See stats.h */
int stats_init(stats_t *stat, stats_global_t *global_stat, double init)
{
    assert(stat != NULL);
    if (init > global_stat->max)
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

    if (check != SUCCESS)
    {
        return NULL;
    }
    return new_stat;
}

/* See stats.h */ 
stats_t* copy_stat(stats_t* stat)
{
    assert(stat != NULL);

    stats_t* copy = (stats_t*)malloc(sizeof(stats_t));

    if (copy == NULL)
        return NULL;

    copy->key = strdup(stat->key);
    copy->val = stat->val;
    copy->max = stat->max;
    copy->global = stat->global;
    copy->modifier = stat->modifier;

    return copy;
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
effects_global_t* copy_global_effect(effects_global_t* global_effect)
{
    assert(global_effect != NULL);

    effects_global_t* copy = global_effect_new(global_effect->name);

    return copy;
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
    stat_effect_t *effect = calloc(1, sizeof(stat_effect_t));

    int check = stat_effect_init(effect, global);
    
    if (check != SUCCESS || effect == NULL || effect->global == NULL)
    {
        return NULL;
    }

    return effect;
}

/* See stats.h */ 
stat_effect_t* copy_effect(stat_effect_t* stat_effect)
{
    assert(stat_effect != NULL);

    stat_effect_t* copy = stat_effect_new(stat_effect->global); 

    /* Point to the stats affected */
    copy->stat_list = stat_effect->stat_list;

    return copy;
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
     
    if (sh == NULL) {
        return FAILURE;
    }

    stats_t *curr;
    
    HASH_FIND(hh, sh, stat, strlen(stat), curr);

    if (curr == NULL) {
       return FAILURE;
    }
    
    double changed_stat = curr->val + change;

    if ((changed_stat > curr->global->max) || (changed_stat > curr->max)) {
        curr->val = curr->max;
    } else {
        curr->val = changed_stat;
    }

   return SUCCESS;
}

/* See stats.h */
int change_stat_max(stats_hash_t *sh, char *stat, double change)
{
    stats_t *s;
    HASH_FIND_STR(sh, stat, s);
    if (s == NULL)
    {
        return FAILURE;
    }
    double new_max = s->max + change;

    if (new_max > s->global->max) {
        s->max = s->global->max;
    } else {
        s->max = new_max;
    }

    return SUCCESS;
}

/* See stats.h */
double get_stat_current(stats_hash_t *sh, char *stat)
{
    if (sh == NULL) {
        return -1;
    }

    stats_hash_t *curr;
    
    HASH_FIND(hh, sh, stat, strlen(stat), curr);

    if (curr == NULL) {
       return -1;
    }
    double res = (curr->modifier) * (curr->val);

    if (res > curr->global->max) {
        res = curr->global->max;
    }
    return res;
}

/* See stats.h */
double get_stat_max(stats_hash_t *sh, char *stat)
{
    if (sh == NULL) {
        return -1;
    }

    stats_t *curr;
    
    HASH_FIND(hh, sh, stat, strlen(stat), curr);

    if (curr == NULL) {
       return -1;
    }
    
    return (curr->max);
}

/* See stats.h */
double get_stat_mod(stats_hash_t *sh, char *stat)
{
    if (sh == NULL) {
        return -1;
    }

    stats_hash_t *curr;
    
    HASH_FIND(hh, sh, stat, strlen(stat), curr);

    if (curr == NULL) {
       return -1;
    }
    
    return (curr->modifier);
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
    stats_t *stat, *tmp;
    int size = MIN_STRING_LENGTH + (MAX_NAME_LENGTH * HASH_COUNT(s));
    char list[size];
    char line[size];
    double stat_val;

    strcpy(list, "");

    if (s == NULL) {
        return "\n";
    }

    HASH_ITER(hh, s, stat, tmp)
    {
        stat_val = stat->val * stat->modifier;
        sprintf(line, "%s [%.2f / %.2f]\n", stat->key, 
                stat_val, stat->max);
        strcat(list, line);
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

char *display_stat_effects(effects_hash_t *hash)
{
    stat_effect_t *effect, *tmp;
    stat_mod_t *mod;
    int count = 0, list_count = 0;

    HASH_ITER(hh, hash, effect, tmp)
    {
        LL_COUNT(effect->stat_list, mod, list_count);
        count += list_count;
    }

    int size = MIN_STRING_LENGTH + (MAX_NAME_LENGTH * (count + HASH_COUNT(hash)));
    char list[size];
    char line[size];

    strcpy(list, "");

    if (hash == NULL) {
        return "\n";
    }

    HASH_ITER(hh, hash, effect, tmp)
    {
        sprintf(line, "*** %s ***\n", effect->key);
        strcat(list, line);
        LL_FOREACH(effect->stat_list, mod)
        {
            sprintf(line, "\t[ %s ] modifier: %.2f, duration: %d\n", 
                    mod->stat->key, mod->modifier, mod->duration);
            strcat(list, line);
        }
    }

    char *display = strdup(list);
    return display;
}

/* See stats.h */
int free_stats(stats_hash_t *stat)
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
int free_stat_effect(stat_effect_t* effect)
{
    assert(effect != NULL);

    free(effect->key);
    free(effect);

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
        free_stat_mod(current);
    }
    
    free_stat_effect(effect);

    return SUCCESS;
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
int free_global_effect(effects_global_t* effect)
{
    assert(effect != NULL);

    free(effect->name);
    free(effect);

    return SUCCESS;
}

/* See stats.h */
int delete_single_global_effect(effects_global_t *effect, 
                                effects_global_hash_t *hash)
{
    assert(effect != NULL);
    HASH_DEL(hash, effect);

    free_global_effect(effect);

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
