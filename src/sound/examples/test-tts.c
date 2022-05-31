#include "sound/tts.h"

int main(int argc, char* argv[])
{
    tts_t* t=init_tts("English", 500);
    speak(t, "Hello");
    speak(t, "world");
    speak(t, "welcome to chiventure. we hope you enjoy your stay courtesy of the sound team");
    speak(t, "press 1 to begin, press 2 to quit.");
    speak(t, "1 has been pressed, would you like to look around the room?");

    free_tts(t);
    return 0;
}