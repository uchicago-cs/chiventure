#include "common/uthash.h"
#include "sound/sound.h"


/* See sound.h for details */
sound_type_t *load_wav(sound_t *sound)
{
    //This initializes the all SDL2 assets
    SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_VIDEO);

    //Basic Audio Format, future teams may want to experiment with this
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,2, 2048);

    sound_type_t *loaded = (sound_type_t*)malloc(sizeof(sound_type_t));

    if (sound == NULL)  // error check, nothing passed into function
    {
        fprintf(stderr, "no sound objects present\n");
        exit(1);
    }
    else if (sound->type == BACKGROUND)
    {
        Mix_Music *mus = Mix_LoadMUS(sound->name); // loads the music to be played
        if (!mus)  // error check
        {
            printf("Background music is not loaded\n");
            return NULL;
        }
        loaded->backgroundSound = mus;
    }
    else if (sound->type == SOUND_EFFECT)
    {
        Mix_Chunk *wav = Mix_LoadWAV(sound->name); // loads the sound effect to be played
        if (!wav)  // error check
        {
            printf("Sound effect is not loaded\n");
            return NULL;
        }
        loaded->soundEffect = wav;
    }
    return loaded;
}

/* See sound.h for details */
int sound_free(sound_type_t *soundType, sound_t *sound)
{
    if (sound == NULL)  // error check, nothing passed into function
    {
        fprintf(stderr, "no sound objects present\n");
        exit(1);
    }
    else if (sound->type == BACKGROUND)
    {
        Mix_FreeMusic(soundType->backgroundSound); // frees resources assocateed with the music
        return 1;
    }
    else if (sound->type == SOUND_EFFECT)
    {
        Mix_FreeChunk(soundType->soundEffect); // frees resources assocateed with the sound effect
        return 1;
    }
    return 0;
}

/* See sound.h for details */
int play_sound(sound_t *sound, int delay)
{
    
    if (sound == NULL)   // error check, nothing passed into function
    {
        fprintf(stderr, "no sound objects present\n");
        exit(1);
    }
    else if (sound->type == BACKGROUND)
    {
        sound_type_t *music = load_wav(sound);
        SDL_Delay(delay); // do a delay if there is one
        Mix_PlayMusic(music->backgroundSound, -1); // play the music
        int x = sound_free(music, sound);
        return 1;
    }
    else if (sound->type == SOUND_EFFECT)
    {
        sound_type_t *effect = load_wav(sound);
        SDL_Delay(delay); // do a delay if there is one
        Mix_PlayChannel(-1, effect->soundEffect, 0); // play the sound effect
        int y = sound_free(effect, sound);
        return 1;
    }
    return 0;
}

/* See sound.h for details */
void stop_sound()
{
    Mix_HaltMusic();
}

/* See sound.h for details */
void pause_sound()
{
    Mix_PauseMusic();
}

/* See sound.h for details */
void resume_sound()
{
    Mix_ResumeMusic();
}
