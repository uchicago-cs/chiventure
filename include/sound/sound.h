#ifndef INCLUDE_SOUND_H_
#define INCLUDE_SOUND_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "common/uthash.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

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


void load_audio(sound_t *name, sound_t *source);
void play_audio(sound_t *name);

/* THE FOLLOWING CODE IS FOR DEMO PURPOSES THIS 
 * EXISTING CODE FROM SDL2 LIBRARIES TO LOAD AND 
 * PLAY MUSIC
 */
void load_audio_demo();
void play_audio_demo(Mix_Music *backgroundSound,SDL_Window *window, SDL_Renderer *renderer);








#endif /* INCLUDE_SOUND_H_ */