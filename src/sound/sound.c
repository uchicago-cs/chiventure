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

int load_wav(sound_t *sound)
{
    SDL_LoadWAV(sound->name, &sound->wavSpec, &sound.wavBuffer, &sound.wavLength);
    return 0;
}

int play_sound(sound_t *sound)
{
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    int success = SDL_QueueAudio(deviceId, sound->wavBuffer, sound->wavLength);
    SDL_PauseAudioDevice(deviceId, 0);
    SDL_delay(3000);

    // clean up
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
    SDL_Quit();
    return 0;
}

