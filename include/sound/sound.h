#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "common/uthash"

typedef struct{
    // path to sound file
    char* path;
    // duration of sound
    double duration;
    // name of sound
    char* name;
    // id for finding it in hash table
    int id; 
    // makes struct hashable
    UT_hash_handle hh; 
} sound_t;