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



void load_audio_demo(SoundType type) 
{

    SDL_Init(SDL_INIT_AUDIO);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,2, 2048);

    SDL_Window *window = SDL_CreateWindow("This is a music window", SDL_WINDOWPOS_UNDEFINED, 
                                            SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL); //SDL_WINDOW_HIDDEN HIDES THE WINDOW

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    
    if (type == BACKGROUND) {
        Mix_Music *backgroundSound = Mix_LoadMUS("sound_library/Spring Village.mp3");
        Mix_Chunk *soundEffect = Mix_LoadWAV("sound_library/Sword Slash.wav");

        /*SDL_Window *window = SDL_CreateWindow("This is a music window", SDL_WINDOWPOS_UNDEFINED, 
                                            SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_HIDDEN); //SDL_WINDOW_HIDDEN HIDES THE WINDOW

        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); */

        play_audio_demo_bgm(backgroundSound, soundEffect, window, renderer);
    }
    else {
        Mix_Chunk *soundEffect = Mix_LoadWAV("sound_library/Sword Slash.wav");

        /*SDL_Window *window = SDL_CreateWindow("This is a music window", SDL_WINDOWPOS_UNDEFINED, 
                                            SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_HIDDEN); //SDL_WINDOW_HIDDEN HIDES THE WINDOW

        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);*/

        play_audio_demo_effect(soundEffect, window, renderer);
    }
    
    


    return;
}

void play_audio_demo_bgm(Mix_Music *backgroundSound, Mix_Chunk *soundEffect, SDL_Window *window,
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
            else if(event.type == SDL_KEYUP)
            {
                if(event.key.keysym.sym == SDLK_1)
                {
                    Mix_PlayChannel(-1, soundEffect, 0);
                }
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeMusic(backgroundSound);
    Mix_CloseAudio();
    SDL_Quit();

}

void play_audio_demo_effect(Mix_Chunk *soundEffect, SDL_Window *window,
                    SDL_Renderer *renderer)
{
    
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
            
            else if(event.type == SDL_KEYUP)
            {
                if(event.key.keysym.sym == SDLK_1)
                {
                    Mix_PlayChannel(-1, soundEffect, 0);
                }
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeChunk(soundEffect);
    Mix_CloseAudio();
    SDL_Quit();

}

int main() {
    sound_t *sound_file = malloc(sizeof(sound_t));
    sound_file->type = BACKGROUND;

    load_audio_demo(sound_file->type);
    
}