#include <stdio.h>
#include <../cli/operations.h>
#include "../common/ctx.h"
#include "../ui/ui.h"
#include "../sound/sound.h"

const char *banner = "THIS IS A SOUND EXAMPLE PROGRAM";

// check loaded game
char *check_game(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if (game == NULL || game->curr_room == NULL) {
        return "Error\n";
    }
    if (tokens[1] != NULL) {
        return "What?\n";
    }
}
void load_audio_demo(SoundType type) 
{
    // This implementation is referenced from demo.c
    
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

    
    Mix_PlayMusic(backgroundSound, -1); //SDL function that plays music, takes in Mix_Music struct
    bool running = true;                //Setting to -1 plays music in an infinite loop
    while (running)
    {
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer); //Closes the window
    SDL_DestroyWindow(window);
    Mix_FreeMusic(backgroundSound); //Frees the resources taken up by music/chunks; note
    Mix_CloseAudio();               
    SDL_Quit();
}


// create sample game
chiventure_ctx_t *create_sample_ctx()
{
    chiventure_ctx_t *ctx = chiventure_ctx_new(NULL);

    game_t *game = game_new("Welcome to Chiventure!");

    load_normal_mode(game);

    // make room
    room_t *room1 = room_new("room1", "Room One","Welcome.");
    add_room_to_game(game, room1);
    game->curr_room = room1;

    ctx->game = game;

    return ctx;
}

int main() {
    chiventure_ctx_t *ctx = create_sample_ctx();

    // sound operations
    sound_t *sound_file = malloc(sizeof(sound_t));
    sound_file->type = BACKGROUND;

    load_audio_demo(sound_file->type);

    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}
