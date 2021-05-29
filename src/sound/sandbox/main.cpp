#ifdef WIN32
#include "SDL/include/SDL.h"
#undef main
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
#endif
#ifndef WIN32
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

#endif

#define NUM_WAVEFORMS 2
const char* _waveFileNames[] =
{
"Kick-Drum-1.wav",
"Snare-Drum-1.wav",
};

#define NUM_MUSIC 1
const char* _mp3FileNames[] =
{
"Cardi-B-ft.-Megan-Thee-Stallion-–-Wap.mp3"
};

Mix_Chunk* _chunks[NUM_WAVEFORMS];

Mix_Music* _music[NUM_MUSIC];

// Initializes the application data
int Init(void) 
{
    memset(_chunks, 0, sizeof(Mix_Chunk*) * NUM_WAVEFORMS);
    memset(_music, 0, sizeof(Mix_Music*) * NUM_MUSIC);

    // Set up the audio stream
    int result = Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
    if( result < 0 )
    {
        fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
        exit(-1);
    }

    result = Mix_AllocateChannels(4);
    if( result < 0 )
    {
        fprintf(stderr, "Unable to allocate mixing channels: %s\n", SDL_GetError());
        exit(-1);
    }

    // Load waveforms
    for( int i = 0; i < NUM_WAVEFORMS; i++ )
    {
        _chunks[i] = Mix_LoadWAV(_waveFileNames[i]);
        if( _chunks[i] == NULL )
        {
            fprintf(stderr, "Unable to load wave file: %s\n", _waveFileNames[i]);
        }
    }

    // Load music
    for( int i = 0; i < NUM_MUSIC; i++ )
    {
        _music[i] = Mix_LoadMUS(_mp3FileNames[i]);
        if( _music[i] == NULL )
        {
            fprintf(stderr, "Unable to load wave file: %s\n", _mp3FileNames[i]);
        }
    }

    return true;
}

int main(int argc, char** argv)
{
    // Initialize the SDL library with the Video subsystem
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO );
    atexit(SDL_Quit);

    SDL_Window* window = SDL_CreateWindow("Sounds",
										  SDL_WINDOWPOS_UNDEFINED,
										  SDL_WINDOWPOS_UNDEFINED,
										  256,
										  256,
 										  SDL_WINDOW_RESIZABLE);

    // Application specific Initialize of data structures
    if (Init() == false)
        return -1;

    // Event descriptor
    SDL_Event Event;

    bool done = false;
    while (!done)
    {
        bool gotEvent = SDL_PollEvent(&Event);

        while (!done && gotEvent)
        {
            switch (Event.type)
            {
                case SDL_KEYDOWN:
                    switch (Event.key.keysym.sym)
                    {
                        case 'q':
                            Mix_PlayChannel(-1, _chunks[0], 0);
                            break;
                        case 'w':
                            Mix_PlayChannel(-1, _chunks[1], 0);
                            break;
			case 'e':
                            Mix_PlayMusic(_music[0], 1);
                            break;
                        default:
                            break;
                    }
                    break;

                case SDL_QUIT:
                    done = true;
                    break;

                default:
                    break;
            }
            if( !done ) gotEvent = SDL_PollEvent(&Event);
        }
#ifndef WIN32
		//usleep(1000);
#else
		Sleep(1);
#endif
    }

    for( int i = 0; i < NUM_WAVEFORMS; i++ )
    {
        Mix_FreeChunk(_chunks[i]);
    }

    for( int i = 0; i < NUM_MUSIC; i++)
    {
        Mix_FreeMusic(_music[i]);
    }

    Mix_CloseAudio();
    SDL_Quit();
    return 0;
}