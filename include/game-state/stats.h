#ifndef _STATS_H
#define _STATS_H

#include "game_state_common.h"

/* stats for a player in the game */
typedef struct stats {
    char *name; // key
    double val;//base value
    double modifier; //update the modifer each time an effect is visited
    UT_hash_handle hh; // to make the struct hashable, as provided in uthash.h 
} stats_t;

typedef struct stats stats_hash_t;

/* effects on a player */
typedef struct effects{
    char* name; // key
    bool status; // whether the player is currently impacted by effect
    double duration; // duration of effect
    stats_t* affected; // stats the effect impacts
    double modifier;
    UT_hash_handle hh; // to make the struct hashable, as provided in uthash.h 
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
int stats_init(stats_t *s, char* stats_name, int init);

/*
 * Allocates a new stat
 *
 * Parameters:
 * stats_name: the unique string ID of the stat
 * init: starting value
 * 
 * Returns:
 *  Pointer to allocated stats struct
 */
stats_t *stats_new(char* stats_name, int init);

/*
 * Assigns a table of stats to a player
 *
 * Parameters:
 *  player_id: the player's id
 *  sh: the stats hashtable
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int assign_stats(char* player_id, stats_hash_t sh);

/*
 * Assigns a table of stats to a player
 *
 * Parameters:
 *  player_id: the player's id
 *  stat: the name of the stat
 *  change: the value to add to the stat
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int modify_stat(char* player_id, char* stat, int change);

/*
 * function that gets integer value of a specified
 * stat of a player
 *
 * Parameters:
 *  player_id: the player's id
 *  stat: the name of the stat
 *
 * Returns:
 *  integer value of a players stat
 */
int get_stat(char* player_id, char* stat);

/*
 * function that gets integer value of  the modifier of 
 * a specified stat of a player
 *
 * Parameters:
 *  player_id: the player's id
 *  stat: the name of the stat
 *
 * Returns:
 *  integer value of a players stat mod
 */
int get_stat_mod(char* player_id, char* stat);

/*
 * Adds a stat to a player by adding it to just their
 * hash table
 *
 * Parameters: 
 * player_id: the player's id
 * s: pointer to a stats struct 
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int add_stat_player(char* player_id, stats_t *s);

/*
 * Adds a stat to the game by adding 
 * it on every players stats hashtable
 *
 * Parameters: 
 * s: pointer to a stats struct
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int add_stat_global(stats_t *s);

/*
 * Displays a players stats
 *
 * Parameters: 
 * player_id: the player's ID
 * 
 * Returns:
 *  Void
 */
void display_stats(char* player_id);

/*
 * Frees a stats struct
 *
 * Parameters: 
 * s: pointer to the stats struct to be freed
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int free_stats(stats *s);

/*
 * Frees a stats struct
 *
 * Parameters: 
 * s: pointer to the stats struct to be freed
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int delete_stats(stats_hash_t *sh);

#endif