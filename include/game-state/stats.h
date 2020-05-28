#ifndef _STATS_H
#define _STATS_H

#include "game_state_common.h"

// GLOBAL STATS STRUCT DEFINITION ----------------------------------------------------
 /* This struct represents the global table that keeps track of all stats available.
  * It contains:
  *      the name of the stat,
  *      which is also the key to the hashtable
  *
  *      the maximal value a stat could have
  * */
typedef struct stats_global{
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
typedef struct effects_global{
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
 *      the max value of the stat
 * 
 *      cumulative modifiers from effects, set to 1 by default
 * */
typedef struct stats {
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
 *      the duration of the effect, an number 
 * */
typedef struct stat_mod {
    stats_t *stat;
    double modifier;
    int duration;
    struct stat_mod *next;
} stat_mod_t;



//// EFFECTS STRUCT DEFINITION ----------------------------------------------------
 /* This struct represents an effect that changes player's stats.
  * It contains:
  *      the name of the effect,
  *      which is also the key to the hashtable
  *
  *      a bool checking if the effect is activated
  *
  *      the duration of the effect
  * 
  *      a linked list, stat_mod, which contains the stats effected
  *      and the modifier value for each stat
  * */
typedef struct effects{
    effects_global_t *global;
    stat_mod_t *stat_list;
    UT_hash_handle hh; 
} stat_effects_t;

typedef struct effects effects_hash_t;

/*
 * Initializes a Stat with specified value and modifier 0
 *
 * Parameters:
 *  s: A stats struct Must point to already allocated memory.
 *  stats_name: the unique string ID of the stat
 *  init: starting value
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int stats_init(stats_t *s, char *stats_name, double init);

/*
 * Allocates a new stat
 *
 * Parameters:
 * stats_name: the unique string ID to be given to the stat
 * init: starting value
 * 
 * Returns:
 *  Pointer to allocated stats struct
 */
stats_t *stats_new(char *stats_name, double init);

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
int effect_init(stat_effects_t *effect, effects_global_t *global);

/*
 * Allocates a new player effect struct
 *
 * Parameters:
 *   - global: a pointer to a global effect (already allocated)
 * 
 * Returns:
 *   - Pointer to allocated player effects struct
 */
stat_effects_t *effect_new(effects_global_t *global);

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
int add_stat_player(stats_hash_t *sh, stats_t *s);

/*
 * Print the stats in a hashtable and their values/modifiers
 *
 * Parameters: 
 * sh: pointer to the stats hash table to be printed
 * 
 * Returns:
 *  string to be printed
 */
char *display_stats(stats_hash_t *sh);

/*
 * Frees a stats hash table
 *
 * Parameters: 
 * sh: pointer to the stats hash table to be freed
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int free_stats(stats_hash_t *sh);

/*
 * Frees a single player effects struct
 *
 * Parameters: 
 * effects: pointer to the effects struct to be freed
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int effect_free(stat_effects_t *effect);

/*
 * Frees a player effects hash table
 *
 * Parameters: 
 * effects: pointer to the effects hash table to be freed
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int delete_all_effects(effects_hash_t *effects);

/*
 * Frees a single global effect struct
 *
 * Parameters: 
 * effect: pointer to an effect struct
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int global_effect_free(effects_global_t *effect);

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