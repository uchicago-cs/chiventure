#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "../../include/common/uthash.h"
#include "sound.h"
#include "SDL/SDL.h"

int sound_new(char* path, double duration, char* name, int id, UT_hash_handle hh)
{
    
}

int sound_init()
{
    SDL_Init(SDL_INIT_AUDIO);
}

int load_wav(sound_t *sound)
{
    uint32_t wavLength = sound->wavLength;
    uint8_t *wavBuffer = sound->wavBuffer;
    SDL_LoadWAV(sound->name, &(sound->wavSpec), &wavBuffer, &wavLength);
    return 0;
}
/*
int play_sound(sound_t *sound)
{
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, sound->wavSpec, NULL, 0);
    int success = SDL_QueueAudio(deviceId, sound->wavBuffer, sound->wavLength);
    SDL_PauseAudioDevice(deviceId, 0);
    SDL_Delay(3000);

    // clean up
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(sound->wavBuffer);
    SDL_Quit();
    return 0;
}

*/