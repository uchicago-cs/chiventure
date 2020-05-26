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

// STAT_MOD STRUCT DEFINITION -----------------------------------------------------
/* This struct represents a modification of a stat, contained inside some effect
 * It contains:
 *      the pointer to the stat
 * 
 *      the modifier of the effect on that stat 
 * 
 *      the duration of the effect, an umber 
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
  *      a bool checking if the effect is activated
  *
  *      the duration of the effect
  * 
  *      a linked list, stat_mod, which contains the stats effected
  *      and the modifier value for each stat
  * */
typedef struct effects{
    char *name; 
    bool status;
    stat_mod_t *stat_list;
    UT_hash_handle hh; 
} stat_effect_t;

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

#endif