#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "common/uthash"
#include "play_sound.h"

#define SUCCESS = 0;
#define FAILURE = 1;


int sound_play(sound_t *sound)
{
    if(sound == NULL)
    {
        error("Sound file null")
        return FAILURE;
    }
    
    
}