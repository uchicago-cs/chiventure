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
 *      cumulative modifiers from effects, set to 1 by default
 * */
typedef struct stats {
    char *name; 
    double val;
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
 *      a bool tracking if it is still in effect
 *
 *      the duration of the effect
 *
 *      a list of stats affected
 *
 *      the list of modifier values applied to each stat,
 *      whose array index corresponds to that of the affect stat
 * */
typedef struct effects{
    char* name;
    bool status; 
    double duration; 
    stats_t** affected; 
    double* modifier;
    UT_hash_handle hh; 
} effects_t;

typedef struct effects effects_hash_t;





#endif