#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "../../include/common/uthash.h"
#include "sound.h"
#include "SDL/SDL.h"


int load_wav(sound_t *sound)
{
    /*
    uint32_t wavLength = sound->wavLength;
    uint8_t *wavBuffer = sound->wavBuffer;
    SDL_LoadWAV(sound->name, &(sound->wavSpec), &wavBuffer, &wavLength);
    */
    return 0;
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

int main()
{
    return 0;
}