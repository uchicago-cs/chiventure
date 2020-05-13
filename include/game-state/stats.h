#ifndef _STATS_H
#define _STATS_H

#include "game_state_common.h"

// STATS STRUCT DEFINITION -----------------------------------------------------
/* This struct represents a stat of the player.
 * It contains:
 *      the name of the stat, 
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
    char *name;
    double val;
    double max;
    double modifier; 
    UT_hash_handle hh; 
} stats_t;

typedef struct stats stats_hash_t;

// EFFECTS STRUCT DEFINITION ----------------------------------------------------
 /* This struct represents an effect that changes player's stats.
  * It contains:
  *      the name of the effect,
  *      which is also the key to the hashtable
  *
  *      a bool checking if the effect is activated
  *
  *      the duration of the effect
  *
  *      an array of the keys of stats affected by the effect
  *
  *      an array of modifiers affecting the stats,
  *      whose index corresponds to that of the stats affected 
  * */
typedef struct effects{
    char* name; 
    bool status; 
    double duration; 
    char** affected;
    double* modifier;
    UT_hash_handle hh; 
} effects_t;

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
int change_stat(stat_hash_t *sh, char *stat, double change);

/*
 * function that gets integer value of a specified
 * stats hash table, after calculation with modification
 *
 * Parameters:
 *  sh: the stats hash table
 *  stat: the name of the stat
 *
 * Returns:
 *  double value of a players stat
 */
double get_stat_current(stat_hash_t *sh, char* stat);

/*
 * function that gets integer base value of a specified
 * stats hash table, i.e. before calculation with modification
 *
 * Parameters:
 *  sh: the stats hash table
 *  stat: the name of the stat
 *
 * Returns:
 *  double value of a players stat
 */
double get_stat_max(stat_hash_t *sh, char* stat);


/*
 * function that gets integer value of  the modifier of 
 * a specified stat of a hashtable
 *
 * Parameters:
 *  sh: the stats hash table
 *  stat: the name of the stat
 *
 * Returns:
 *  double value of a players stat mod
 */
double get_stat_mod(stat_hash_t *sh, char* stat);

/*
 * Adds a stat to a stat hash table
 *
 * Parameters: 
 * sh: the stats hash table
 * stat_id: the name to be given to the stat
 * init: the initial value of the stat
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int add_stat(stats_hash_t *sh, char *stat_id, double init);

/*
 * Print the stats in a hashtable and their values/modifiers
 *
 * Parameters: 
 * sh: pointer to the stats hash table to be printed
 * 
 * Returns:
 *  string to be printed
 */
char* display_stats(stats_hash_t *sh);

/*
 * Frees a stats struct
 *
 * Parameters: 
 * sh: pointer to the stats hash table to be freed
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int free_stats(stats_hash_t *sh);

#endif