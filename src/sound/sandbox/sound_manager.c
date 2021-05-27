#include "sound/sound.h"



/*void play_audio(sound_t *name)
{
    return null
}

void load_audio(sound_t *name, sound_t *source)
{
    return null;
} */

/*THE FOLLOWING CODE IS FOR DEMO PURPOSES IN SPRINT 4 */
#define WIDTH 800
#define HEIGHT 600



void load_audio_demo() 
{

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,2, 2048);

    Mix_Music *backgroundSound = Mix_LoadMUS("Spring Village.wav");

    SDL_Window *window = SDL_CreateWindow("This is a music window", SDL_WINDOWPOS_UNDEFINED, 
                                            SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_HIDDEN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);

    play_audio_demo(backgroundSound, window, renderer);

    return;
}

void play_audio_demo(Mix_Music *backgroundSound, SDL_Window *window,
                    SDL_Renderer *renderer)
{
    Mix_PlayMusic(backgroundSound, -1);
    bool running = true;
    SDL_Event event;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
            }
            
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    SDL_Quit();

}

int main() {

    load_audio_demo();
    
}
