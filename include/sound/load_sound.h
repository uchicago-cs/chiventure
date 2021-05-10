#ifndef _ROOM_H
#define _ROOM_H
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "common.h"

/* loads sound 
 * Inputs: raw_file: probably .wav format 
 * Returns: sound_t* struct 
*/

sound_t* load_sound (raw_file);

/*
 * frees sound 
 * Inputs: sound_t* sound to free 
 * Returns: Success
*/
int free(sound_t* sound); 

#endif
