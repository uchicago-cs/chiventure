# Sound Library for Chiventure

## About

* A simple SDL Audio library that will be used to load/play sound file
* The code was inspired from https://gigi.nullneuron.net/gigilabs/playing-a-wav-file-using-sdl2/
* Basic structure and design are provided, but the actual implementation are still premature

## Basic Structure
```c
    typedef struct{
        //name of wav file
        char *name;
        // wav file information
        SDL_AudioSpec wavSpec;
        // length of the wav sound file
        uint32_t wavLength;
        // wav file buffer
        uint8_t *wavBuffer;
        //below for hash table
        int id; 
        // makes struct hashable
        UT_hash_handle hh; 
    } sound_t;
```
## Key load/play Functions
```c
// This function must be able to load the sound file to the SDL queue
int load_wav(sound_t *sound);

// This function must be able to play the sound from the SDL queue
int play_sound(sound_t *sound);

## Sandbox Demo
Sandbox demo plays the sound file differently to the current sound module. There are multiple ways of playing sound using SDL library, and it would be the next team's task to modularize it effectively. 

## Current Status
The basic design is provided. However, the current version of sound module contains many compiler errors that the team was unfortunately not able to complete due to the lack of time. We are hoping that the next team could pick up from where we have left.