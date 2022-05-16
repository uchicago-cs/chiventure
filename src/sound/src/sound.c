#include "common/uthash.h"
#include "sound/sound.h"


/* See sound.h for details */
int load_wav(sound_t *sound)
{
    //This initializes the all SDL2 assets
    SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_VIDEO); 

    //Basic Audio Format, future teams may want to experiment with this
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,2, 2048);

    if (sound == NULL){ // error check, nothing passed into function
        fprintf(stderr, "no sound objects present\n");
        exit(1);
    } else if (sound->type == BACKGROUND) {
        Mix_Music *mus = Mix_LoadMUS(sound->name); // loads the music to be played
        if (!mus){ // error check
            printf("Background music is not loaded\n");
            return 1;
        }
    } else if (sound->type == SOUND_EFFECT){ 
        Mix_Chunk *wav = Mix_LoadWAV(sound->name); // loads the sound effect to be played
        if (!wav){ // error check
            printf("Sound effect is not loaded\n");
            return 1;
        }
    }
    return 0;
}

/* See sound.h for details */
int sound_free(sound_t *sound)
{
    if (sound == NULL){ // error check, nothing passed into function
        fprintf(stderr, "no sound objects present\n");
        exit(1);
    } else if (sound->type == BACKGROUND) {
        Mix_FreeMusic(backgroundSound); // frees resources assocateed with the music
        return 1;
    } else if (sound->type == SOUND_EFFECT) {
        Mix_FreeChunk(soundEffect); // frees resources assocateed with the sound effect
        return 1;
    }
    return 0;
}

/* See sound.h for details */
int play_sound(sound_t *sound, int delay)
{
    if (sound == NULL) { // error check, nothing passed into function
        fprintf(stderr, "no sound objects present\n");
        exit(1);
    }else if (sound->type == BACKGROUND) {
        SDL_Delay(delay); // do a delay if there is one
        Mix_PlayMusic(backgroundSound, -1); // play the music
        return 1;
    } 
    else if (sound->type == SOUND_EFFECT){
        SDL_Delay(delay); // do a delay if there is one
        Mix_PlayChannel(-1, soundEffect, 0) // play the sound effect
        return 1;
    }
    return 0;
}
