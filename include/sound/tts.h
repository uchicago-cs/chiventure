#ifndef INCLUDE_TTS_H_
#define INCLUDE_TTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <espeak-ng/speak_lib.h>

/* This represents a text-to-speech object */ 
typedef struct {
    char* voicename; // The name of the speaker
    /* voicename cannot be anything - you can find a list of all
    possible voices by running espeak --voices. */
    char* text; // The text which will be spoken
    int buflength; // The buffer length in ms of sound buffers
} tts_t;

/* malloc and fill a tts_t struct with the necessary data
    Parameters:
        voicename: the name of the speaker
            important note: voicename is not arbitrary, pick from espeak --voices.
        text: the content that will be read aloud
        buflength: the length of sound buffers in ms
    Output: a pointer to a tts struct which stores the given data */
tts_t* init_tts(char* voicename, char* text, int buflength);

/* free the malloc'd components of a tts_t struct and the struct itself
    Parameters: a pointer t to a tts_t struct
    Output: N/A */
void free_tts(tts_t* t);

/* use the espeak library to speak the text content of a tts_t struct
    Parameters: a pointer t to a tts_t struct
    Output: N/A */
void speak(tts_t* t);

#endif /* INCLUDE_TTS_H_ */
