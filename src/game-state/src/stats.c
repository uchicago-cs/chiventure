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

/* copy_global_stat: Creates a deep copy of a global stat
 *
 * Input:
 *      - global_stat: The global stat to copy
 * 
 * Returns: Pointer to the newly made copy
 */
stats_global_t copy_global_stat(stats_global_t* global_stat)
{
    assert(global_stat != NULL);

    stats_global_t* copy = stats_global_new(global_stat->name, global_stat->max)

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

/* copy_stat: Creates a deep copy of a given stat
 *
 * NOTE: This does NOT create a new global stat. If User desires copy of a stat 
 *       alongisde a copy of the associated global_stat, use copy_stat_and_global
 * 
 * Input:
 *      - stat: The stat to copy
 * 
 * Returns: Pointer to the newly made copy 
 */ 
stats_t* copy_stat(stats_t* stat)
{
    assert(stat != NULL);

    stats_t* copy = (stats_t*)malloc(sizeof(stat_t));

    copy->key = strdup(stat->name);
    copy->val = stat->init;
    copy->max = stat->init;
    copy->global = stat->global_stat;
    copy->modifier = stat->modifier;

    return copy;
}

/* copy_stat_and_global: Creates a deep copy of both the given stat AND
 *                       the global stat associated to it
 *
 * Input:
 *      - stat: The stat to copy (containing a valid global_stat pointer)
 * 
 * Returns: Pointer to newly made copy
 */
stats_t* copy_stat_and_global(stats_t* stat)
{
    assert(stat != NULL);
    assert(stat->global != NULL);

    global_stat_t* global_copy = copy_global_stat(stat->global);
    stats_t* copy = copy_stat(stat);

    /* Set copied stat to point to newly created global stat instead of original */ 
    copy->global = global_copy;

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

/* copy_global_effect: Creates a deep copy of a global effect
 *
 * Input:
 *      - global_effect: The global effect to copy
 * 
 * Returns: Pointer to the newly made copy
 */
effects_global_t* copy_global_effect(effects_global_t* global_effect)
{
    assert(global_effect != NULL);

    effects_global_t* copy = global_effect_new(global_effect->name)

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

/* copy_stat_effect: Creates a deep copy of a given stat effect
 *
 * NOTE: This does NOT create a new global effect. If User desires copy of a stat 
 *       effect alongisde a copy of the associated global_effect, use copy_stat_and_global_effect
 * 
 * Input:
 *      - stat_effect: The stat effect to copy
 * 
 * Returns: Pointer to the newly made copy 
 */ 
stats_t* copy_stat_effect(stats_effect_t* stat_effect)
{
    assert(stat_effect != NULL);

    stats_effect_t* copy = (stats_effect_t*)malloc(sizeof(stat_effect_t));

    stat_effect_init(copy, stat_effect->global)

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
    
    int changed_stat = curr->val + change;

    if ((changed_stat > curr->global->max) || (changed_stat > curr->max)) {
        curr->val = curr->max;
    } else {
        curr->val = changed_stat;
    }

   return 0;
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
