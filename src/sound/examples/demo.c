#include "demo.h"
#include "sound/sound.h"

/*THE FOLLOWING CODE IS FOR DEMO PURPOSES IN SPRINT 4 */

#define WIDTH 800
#define HEIGHT 600

/*See sound.h for details */
void load_audio_demo(SoundType type) 
{
    //This initializes the all SDL2 assets
    SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_VIDEO); 

    //Basic Audio Format, future teams may want to experiment with this
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,2, 2048);

    //This creates a window for music to be plated, the dimensions of the window are set by WIDTH and HEIGHT
    SDL_Window *window = SDL_CreateWindow("This is a music window", SDL_WINDOWPOS_UNDEFINED, 
                                            SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL); //SDL_WINDOW_HIDDEN HIDES THE WINDOW

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    IMG_Init(IMG_INIT_PNG);

    SDL_Texture *texture = IMG_LoadTexture(renderer, "../../../../sound_library/chiventure.png");
    

    //Mix Music and MixChunk are data structures in the SDL, this is how we load (.wav//mp3 formats)
    //The parameter take is the file pathway to the audio file 
    Mix_Music *backgroundSound = Mix_LoadMUS("../../../../sound_library/Spring Village.mp3");

    Mix_Chunk *soundEffect = Mix_LoadWAV("../../../../sound_library/Sword Slash.wav");
    if (!soundEffect) {
        printf("MixPlayChannel: %s\n", Mix_GetError()); //Gets error if an audio cannot be loaded properly
    }

    Mix_Chunk *wap = Mix_LoadWAV("../../../../sound_library/Boss Fight.wav");
    if (!wap) {
        printf("MixPlayChannel: %s\n", Mix_GetError()); //Gets error if an audio cannot be loaded properly
    }
    
    Mix_PlayMusic(backgroundSound, -1); //SDL function that plays music, takes in Mix_Music struct
    bool running = true;                //Setting to -1 plays music in an infinite loop
    SDL_Event event;
    while (running)
    {
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&event))    //Determines if there is a pending event
        {
            if (event.type == SDL_QUIT)  
            {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN)  // Triggers an event if a key is pressed
            {
                if (event.key.keysym.sym == SDLK_1)  //Pressing the 1 key plays the chunk
                {
                    Mix_PlayChannel(-1, soundEffect, 0); //Mix_PlayChannel is the function that plays Mix_Chunks
                }
                else if (event.key.keysym.sym == SDLK_q) //Pressing q initiates the sequence of events
                {
                    Mix_PauseMusic();
                    int y = Mix_PlayChannel(-1, wap, 0);
                    Mix_Volume(y, 100);
                    if (Mix_PlayChannel(-1,wap,0) == -1) {
                        printf("MixplayChannel: %s\n", Mix_GetError());
                    }
                }
            }
        }
        
    }

    SDL_DestroyRenderer(renderer); //Closes the window
    SDL_DestroyWindow(window);
    Mix_FreeMusic(backgroundSound); //Frees the resources taken up by music/chunks; note
    Mix_FreeChunk(soundEffect);     //the different functions to free audio
    Mix_FreeChunk(wap);
    Mix_CloseAudio();               
    SDL_Quit();


    return;
}

int main() {
    sound_t *sound_file = malloc(sizeof(sound_t));
    sound_file->type = BACKGROUND;

    load_audio_demo(sound_file->type);
    
}