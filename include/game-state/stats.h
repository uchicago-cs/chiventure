#ifndef _STATS_H
#define _STATS_H

#include "game_state_common.h"

// GLOBAL STATS STRUCT DEFINITION ----------------------------------------------------
 /* This struct represents the global table that keeps track of all stats available.
  * It contains:
  *      the name of the stat,
  *      which is also the key to the hashtable
  *
  *      the global maximal value a stat could have
  * */
typedef struct stats_global {
    char *name;
    double max;
    UT_hash_handle hh; 
} stats_global_t;

typedef struct stats_global stats_global_hash_t;


// GLOBAL EFFECTS STRUCT DEFINITION ----------------------------------------------------
 /* This struct represents the effects table that keeps track of all available effects
  * It contains:
  *      the name of the effect,
  *      which is also the key to the hashtable
  * */
typedef struct effects_global {
    char *name;
    UT_hash_handle hh; 
} effects_global_t;
typedef struct effects_global effects_global_hash_t;


// STATS STRUCT DEFINITION -----------------------------------------------------
/* This struct represents a stat of the player.
 * It contains:
 *      a pointer to the global stat, 
 *      which is also the key to the hashtable
 *
 *      the base value of the stat, 
 *      whose final value will be multiplied by the modifier
 * 
 *      the max value of the stat for the player (should not exceed global max)
 * 
 *      cumulative modifiers from effects, set to 1 by default
 * */
typedef struct stats {
    char *key; //key for hashtable (same as global stat name)
    stats_global_t *global;
    double val;
    double max;
    double modifier; 
    UT_hash_handle hh; 
} stats_t;

typedef struct stats stats_hash_t;

// STAT_MOD STRUCT DEFINITION -----------------------------------------------------
/* This struct represents a modification of a stat, contained inside some effect
 * It contains:
 *      the pointer to the stat
 * 
 *      the modifier of the effect on that stat 
 * 
 *      the duration of the effect, an int 
 * */
typedef struct stat_mod {
    stats_t *stat;
    double modifier;
    int duration;
    struct stat_mod *next;
} stat_mod_t;



// EFFECTS STRUCT DEFINITION ----------------------------------------------------
 /* This struct represents an effect that changes player's stats.
  * It contains:
  *      the name of the effect,
  *      which is also the key to the hashtable
  *
  *      a pointer to the related global effect
  * 
  *      a linked list, stat_mod_t, which contains the stats effected
  *      and the modifier value for each stat (an empty list means the 
  *      the effect is turned off)
  * */
typedef struct effects{
    char *key; //key for hashtable (should be same as name of effect)
    effects_global_t *global;
    stat_mod_t *stat_list;
    UT_hash_handle hh; 
} stat_effect_t;

typedef struct effects effects_hash_t;


/*
 * Initializes a global stat with max value stated
 *
 * Parameters:
 *  s: A global stat struct Must point to already allocated memory.
 *  name: the unique string ID that the stat has
 *  max: maximal value of the stat
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */

int stats_global_init(stats_global_t *s, char *name, double max);


/*
 * Initializes a Stat with specified value and modifier 0
 *
 * Parameters:
 *  s: A stats struct Must point to already allocated memory.
 *  stat: the pointer to the global stat struct
 *  init: starting value
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int stats_init(stats_t *s, char *stats_name, double init);

/*
 * Allocates a new global stat
 *
 * Parameters:
 * name: the unique string ID to be given to the stat
 * max: maximal value this stat could have
 * 
 * Returns:
 *  Pointer to allocated global stats struct
 */

stats_global_t *stats_global_new(char *name, double max);

/*
 * Allocates a new stat
 *
 * Parameters:
 * stat: the pointer to the global stat struct.
 * init: starting value
 * 
 * Returns:
 *  Pointer to allocated stats struct
 */
stats_t *stats_new(char *stats_name, double init);

/*
 * Initializes a stat_mod struct
 *
 * Parameters:
 *   - mod: a stat_mod struct (must already be allocated in memory)
 *   - stat: pointer to a stats struct
 *   - modifier: modifier for the stat
 *   - duration: duration an effect with this stat_mod should last
 * 
 * Returns:
 *   - SUCCESS on success, FAILURE if an error occurs.
 */
int stat_mod_init(stat_mod_t *mod, stats_t *stat, double modifier, int duration);

/*
 * Allocates a new stat_mod struct
 *
 * Parameters:
 * stat: the pointer to a stat struct.
 * modifier: modifier for the stat
 * duration: duration an effect with this stat_mod should last
 * 
 * Returns:
 *  Pointer to allocated stat_mod struct
 */
stat_mod_t *stat_mod_new(stats_t *stat, double modifier, int duration);

/*
 * Initializes a global effect struct
 *
 * Parameters:
 *   - effect: a global effect struct (must already be allocated in memory)
 *   - effect_name: the unique string ID to be given to the effect
 * 
 * Returns:
 *   - SUCCESS on success, FAILURE if an error occurs.
 */
int global_effect_init(effects_global_t *effect, char *effect_name);

/*
 * Allocates a new global effect
 *
 * Parameters:
 *   - effect_name: the unique string ID to be given to the effect
 * 
 * Returns:
 *   - Pointer to allocated global effects struct
 */
effects_global_t *global_effect_new(char *effect_name);

/*
 * Initializes a player effect struct
 *
 * Parameters:
 *   - effect: a player effect struct (must already be allocated in memory)
 *   - global: a pointer to a global effect
 * 
 * Returns:
 *   - SUCCESS on success, FAILURE if an error occurs.
 */
int stat_effect_init(stat_effect_t *effect, effects_global_t *global);

/*
 * Allocates a new player effect struct
 *
 * Parameters:
 *   - global: a pointer to a global effect (already allocated)
 * 
 * Returns:
 *   - Pointer to allocated player effects struct
 */
stat_effect_t *stat_effect_new(effects_global_t *global);

/*
 * Changes the base value of a stat by the
 * specified double amount through addition
 *
 * Parameters:
 *  sh: the hash table of stats 
 *  stat: the name/key of the stat
 *  change: the value to add to the stat
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int change_stat(stats_hash_t *sh, char *stat, double change);

/*
 * function that gets double value of a specified
 * stats hash table, after calculation with modifier
 *
 * Parameters:
 *  sh: the stats hash table
 *  stat: the name of the stat
 *
 * Returns:
 *  double value of a players stat
 */
double get_stat_current(stats_hash_t *sh, char *stat);

/*
 * function that gets double base value of a specified stats 
 * hash table, i.e. the max field with no calculation with modifier
 *
 * Parameters:
 *  sh: the stats hash table
 *  stat: the name of the stat
 *
 * Returns:
 *  double max value of a players stat
 */
double get_stat_max(stats_hash_t *sh, char *stat);


/*
 * function that gets double value of the modifier of 
 * a specified stat of a hashtable
 *
 * Parameters:
 *  sh: the stats hash table
 *  stat: the name of the stat
 *
 * Returns:
 *  double value of a players stat mod
 */
double get_stat_mod(stats_hash_t *sh, char *stat);

/*
 * Adds a stat to a stat hash table
 *
 * Parameters: 
 * sh: the stats hash table of the player
 * s: the stat to be added to the table
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int add_stat(stats_hash_t **sh, stats_t *s);

/*
 * Print a list of the stats in a hashtable
 *
 * Parameters: 
 * sh: pointer to the stats hash table to be printed
 * 
 * Returns:
 *  string to be printed
 */
char *display_stats(stats_hash_t *sh);

/* Compares two stat_mod_t struct for equality
 *
 * Parameters: 
 * - mod1, mod2: two stat_mod_t structs
 *
 * Returns:
 * 0 when equal, nonzero value when not equal
 */
int stat_mod_equal(stat_mod_t *m1, stat_mod_t *m2);

/*
 * Adds an effect to an effects hash table
 *
 * Parameters: 
 * hash: pointer to effects hash table
 * effect: pointer to effect to be added
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int add_stat_effect(effects_hash_t **hash, stat_effect_t *effect);

/*
 * Applies an effect on a player
 *
 * Parameters: 
 * hash: pointer to a pointer for the effects hash table of player
 * effect: pointer to effect to be applied
 * stats: array of the player's stats to be impacted
 * intensities: array of modifiers for each stat
 * durations: array of durations for the effect on each stat
 * num_stats: number of stats to be impacted
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int apply_effect(effects_hash_t **hash, stat_effect_t  *effect, stats_t **stats, 
                 double *intensities, int *durations, int num_stats);

/*
 * Frees a stats hash table
 *
 * Parameters: 
 * stat: pointer to the stats hashtable to be freed
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int free_stats(stats_hash_t *stat);

/*
 * Frees a global stat hashtable
 *
 * Parameters: 
 * stat: pointer to the global stat hashtable to be freed
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int free_stats_global(stats_global_hash_t *stat);

/*
 * Frees a stat_mod struct
 *
 * Parameters: 
 * mod: pointer to the stat_mod struct to be freed
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int free_stat_mod(stat_mod_t *mod);

/*
 * Deletes a single player effects struct from a hash table,
 * then frees the struct
 *
 * Parameters: 
 * effect: pointer to the effects struct to be freed
 * hash: pointer to the hash table containing the effect to be freed
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int delete_single_stat_effect(stat_effect_t *effect, effects_hash_t *hash);

/*
 * Frees a player effects hash table
 *
 * Parameters: 
 * effects: pointer to the effects hash table to be freed
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int delete_all_stat_effects(effects_hash_t *effects);

/*
 * Deletes a single global effect struct from a hash table,
 * then frees it
 *
 * Parameters: 
 * effect: pointer to a global effect struct to be freed
 * hash: pointer to hash table containing global effect to be freed
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int delete_single_global_effect(effects_global_t *effect, 
                                effects_global_hash_t *hash);

/*
 * Frees a global effects hash table
 *
 * Parameters: 
 * effects: pointer to the effects hash table to be freed
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int delete_all_global_effects(effects_global_hash_t *effects);

#endif