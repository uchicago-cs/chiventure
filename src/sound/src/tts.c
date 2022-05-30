#include "sound/tts.h"
#include <espeak-ng/speak_lib.h>
#include <string.h>

espeak_AUDIO_OUTPUT output = AUDIO_OUTPUT_SYNCH_PLAYBACK;
char *path = NULL;
void *user_data;
unsigned int *identifier;

// malloc and fill a tts_t struct with the necessary data
tts_t* init_tts(char* voicename, char* text, int buflength){
    tts_t* ret=(tts_t*)malloc(sizeof(tts_t));
    ret->voicename=strdup(voicename);
    ret->text=strdup(text);
    ret->buflength=buflength;
    return ret;
}

// free the malloc'd components of a tts_t struct and the struct itself
void free_tts(tts_t* t){
    free(t->voicename);
    free(t->text);
    free(t);
}

// use the espeak library to speak the text content of a tts_t struct
void speak(tts_t* t){
    espeak_Initialize(output, t->buflength, path, 0);
    espeak_SetVoiceByName(t->voicename);
    espeak_Synth(t->text, t->buflength, 0, 0, 0, espeakCHARS_AUTO, identifier, user_data);
}
