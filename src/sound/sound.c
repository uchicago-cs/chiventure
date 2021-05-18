#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "common/uthash"
#include "include/sound.h"


int sound_new()
{
    
}

int sound_init(char* path, double duration, char* name, int id, UT_hash_handle hh)
{

}

int device_init()
{
    SDL_Init(SDL_INIT_AUDIO);
    // Opens the default audio device
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    return SUCCESS;
}