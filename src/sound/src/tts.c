#include "sound/tts.h"
#include <espeak-ng/speak_lib.h>
#include <string.h>

espeak_AUDIO_OUTPUT output = AUDIO_OUTPUT_SYNCH_PLAYBACK;
char *path = NULL;
void *user_data;
unsigned int *identifier;

// malloc and fill a tts_t struct with the necessary data
tts_t* init_tts(char* voicename, int buflength){
    tts_t* ret=(tts_t*)malloc(sizeof(tts_t));
    ret->voicename=strdup(voicename);
    ret->buflength=buflength;
    espeak_Initialize(output, ret->buflength, path, 0);
    return ret;
}

// free the malloc'd components of a tts_t struct and the struct itself
void free_tts(tts_t* t){
    free(t->voicename);
    free(t);
}

// use the espeak library to speak the given string
void speak(tts_t* t, char* str){
    espeak_SetVoiceByName(t->voicename);
    espeak_Synth(str, t->buflength, 0, 0, 0, espeakCHARS_AUTO, identifier, user_data);
}
