#include "sound/tts.h"

int main(int argc, char* argv[])
{
    tts_t* t=init_tts("English", 500);
    speak(t, "Hello");
    speak(t, "world");
    free_tts(t);
    return 0;
}