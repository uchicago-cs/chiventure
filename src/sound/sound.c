#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "../../include/common/uthash.h"
#include "sound.h"
#include "SDL/SDL.h"


<<<<<<< HEAD
int sound_init(char* path, double duration, char* name, int id, UT_hash_handle hh)
{
    if( SDL_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    return SUCCESS;
=======
int load_wav(sound_t *sound)
{
    /*
    uint32_t wavLength = sound->wavLength;
    uint8_t *wavBuffer = sound->wavBuffer;
    SDL_LoadWAV(sound->name, &(sound->wavSpec), &wavBuffer, &wavLength);
    */
    return 0;
>>>>>>> 11c37048538ee017e7d074cfe77595c915191024
}

int sound_free(sound_t *sound)
{
    return 0;
}

int play_sound(sound_t *sound, int delay)
{
    /*
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, sound->wavSpec, NULL, 0);
    int success = SDL_QueueAudio(deviceId, sound->wavBuffer, sound->wavLength);
    SDL_PauseAudioDevice(deviceId, 0);
    SDL_Delay(3000);

    // clean up
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(sound->wavBuffer);
    SDL_Quit();
    */
    return 0;
}