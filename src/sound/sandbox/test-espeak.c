#include <espeak-ng/speak_lib.h>
 
// in order to run this, in the chiventure/src/sound/sandbox directory run 
// gcc test-espeak.c -lespeak-ng -o test-espeak
// especially anytime after a change is made and then use
// ./test-espeak
// in order to hear the text

 espeak_AUDIO_OUTPUT output = AUDIO_OUTPUT_SYNCH_PLAYBACK;
 char *path = NULL;
 void* user_data;
 unsigned int *identifier;
 
 int main(int argc, char* argv[]) {
   char voicename[] = {"English"}; // Set voice by its name
   char text[] = {"Hello Parker!"}; // text to be output by speaker, if changed recompile as seen above
   int buflength = 500, options = 0;
   unsigned int position = 0, position_type = 0, end_position = 0, flags = espeakCHARS_AUTO;
   espeak_Initialize(output, buflength, path, options);
   espeak_SetVoiceByName(voicename);
   printf("Saying  '%s'...\n", text);
   espeak_Synth(text, buflength, position, position_type, end_position, flags, identifier, user_data);
   printf("Done\n");
   return 0;
 }