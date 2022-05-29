#include "sound/tts.h"

int main(int argc, char* argv[])
{
    tts_t* t=init_tts("English", "Hello world!", 500);
    speak(t);
    free_tts(t);
    return 0;
}