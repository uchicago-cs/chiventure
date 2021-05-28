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

/* This is a enumeration type to differentiate audio types */
typedef enum {BACKGROUND, SOUND_EFFECT} SoundType;

/* This represents our sound data structure */
typedef struct{
    SoundType type;
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

/* THE FOLLOWING CODE IS FOR DEMO PURPOSES. THIS 
 * USES EXISTING DATA STRUCTURES AND FUNCTIONS FROM 
 * THE SDL2 LIBRARIES TO LOAD AND PLAY MUSIC
*/

/*  
 * The purpose of this function is to initiate the loading process of an audio file.
 * We initialize the SDL library, create a window for audio to be played, and locate
 * the audio files to load in the existing SDL sound structures.
 * Parameters: 
 *      type: the type of audio (background, sound effect etc.)
 */
void load_audio_demo(SoundType type);

/* Audio functions to play larger audio files like .mp3 formats
 * 
 * Parameters:
 *      backgroundSound: Mix_Music data structure with a loaded audio file
 *      window: the window created with specified dimensions
 *      renderer: a renderering struct that handles rendering for the window
 * Return:
 *      None
 * 
 */
void play_audio_demo_bgm(Mix_Music *backgroundSound, SDL_Window *window, SDL_Renderer *renderer);

/* Audio functions to play smaller audio files/music chunks
 * 
 * Parameters:
 *      soundEffect: Mix_Chunk data structure with a loaded audio file
 *      window: the window created with specified dimensions
 *      renderer: a renderering struct that handles rendering for the window
 * Return:
 *      None
 * 
 */
void play_audio_demo_effect(Mix_Chunk *soundEffect,SDL_Window *window, SDL_Renderer *renderer);

#endif /* INCLUDE_SOUND_H_ */