#include "common/uthash.h"
#include "sound/sound.h"


/* See sound.h for details */
int load_wav(sound_t *sound)
{
    return 0;
}

/* See sound.h for details */
int sound_free(sound_t *sound)
{
    return 0;
}

/* See sound.h for details */
int play_sound(sound_t *sound, int delay)
{
    if (sound == NULL) {
        fprintf(stderr, "no sound objects present\n");
        exit(1);
    }else if (sound->type == BACKGROUND) {
        SDL_Delay(delay);

        Mix_Music *backgroundSound = Mix_LoadMUS(sound->name);
        Mix_Chunk *soundEffect = Mix_LoadWAV(sound->name);
        if (!soundEffect) {
            printf("MixPlayChannel: %s\n", Mix_GetError()); //Gets error if an audio cannot be loaded properly
        }

        Mix_PlayMusic(backgroundSound, -1);
        Mix_PlayChannel(-1, soundEffect, 0)
    } 
    // else it is SOUND_EFFECT
    else {

    }
    return 0;
}
