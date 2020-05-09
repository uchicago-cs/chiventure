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





#endif