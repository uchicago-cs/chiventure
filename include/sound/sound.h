#ifndef INCLUDE_SOUND_H_
#define INCLUDE_SOUND_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "common/uthash.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

/* This is a enumeration type to differentiate audio types */
typedef enum {BACKGROUND, SOUND_EFFECT} SoundType;

/* This represents our sound data structure */
typedef struct {
    // type of sound
    SoundType type;
    // name of sound
    char* name;
    // wav file information
    SDL_AudioSpec wavSpec;
    uint32_t wavLength;
    uint8_t *wavBuffer;
    //below for hash table
    int id;
    // makes struct hashable
    UT_hash_handle hh;
} sound_t;

/* this stores output from loaded music depending on whether it's music or a sound effect */
typedef union {
    Mix_Music *backgroundSound;
    Mix_Chunk *soundEffect;
} sound_type_t;

/* Loads sound to SDL queue
 *
 * Parameters:
 *      sound: sound struct
 * Return:
 *      0 on success 1 on failure
 */
sound_type_t *load_wav(sound_t *sound);

/* free sound structure from memory heap
 *
 * Parameters:
 *      soundType: the type of sound it is (music or sound effect)
 *      sound: sound struct
 * Return:
 *      0 on success 1 on failure
 */
int sound_free(sound_type_t *soundType, sound_t *sound);

/* Plays sound from SDL queue
 *
 * Parameters:
 *      sound: sound struct
 * Return:
 *      0 on success 1 on failure
 */
int play_sound(sound_t* sound, int delay);


/*
* simple function which stops any sound that is played
*/
void stop_sound();

/*
* simple function which pauses any sound that is played
*/
void pause_sound();

/*
* simple function which resumes any sound that is played
*/
void resume_sound();

#endif /* INCLUDE_SOUND_H_ */
