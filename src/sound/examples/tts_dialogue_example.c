// reference dialogue_example.c in npc/examples
#include <stdio.h>
#include "sound/sound.h"
#include "cli/operations.h"
#include "common/ctx.h"
#include "ui/ui.h"
#include "npc/dialogue.h"
#include "sound/tts.h"

const char *banner = "CHIVENTURE SOUND";

// load audio
// this is where the implementation of adding sound will go

// create sample game
chiventure_ctx_t *create_sample_game()
{

    // Initializing game, player, and npc
    game_t *game = game_new("Welcome to Chiventure!");
    player_t *p = player_new("Rhea");
    npc_t *friend = npc_new("friend", "short", "long", NULL, NULL, 0);
    room_t *convo_room = room_new("convo room", "This is the conversation room","Welcome to the conversation room!");
    

    add_room_to_game(game, convo_room);
    add_player_to_game(game, p);
    add_npc_to_game(game, friend);
    add_npc_to_room(convo_room->npcs, friend);

    game->curr_room = convo_room;
    game->curr_player = p;
    game->mode = game_mode_new(NORMAL, NULL, "friend");


    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}

char *run_conversation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    // Creating a conversation between a player and npc, where the npc's responses will be played with tts
    convo_t *c1 = convo_new();
    add_node(c1, "1", "Welcome to Chiventure! How are you doing today?");
    add_node(c1, "2a", "Great!. Do you like the chiventure game?");
    add_node(c1, "3a", "Awesome! The sound team wishes you good luck.");
    add_node(c1, "3b", "We hope we can change your mind!");
    add_node(c1, "2b", "I'm sorry, feel better.");


    add_edge(c1, "Good", "1", "2a", NULL);
    add_edge(c1, "Bad", "1", "2b", NULL);
    add_edge(c1, "Yes", "2a", "3a", NULL);
    add_edge(c1, "No", "2a", "3b", NULL);
    
    // Execute the conversation, this is where we will need to play the sound for the conversation
    int rc = -1;
    int player_response;
    char *ret_str;
    
    tts_t* t = init_tts("English", 5000);

    print_to_cli(ctx, "Friend:\n");
    while (rc != 1)
    {
        if (rc < 0) {
            ret_str = start_conversation(c1, &rc, ctx->game);
        } else {
            ret_str = run_conversation_step(c1, player_response, &rc, ctx->game);
        }
        
        print_to_cli(ctx, ret_str);       
        // text to speech 
        speak(t, ret_str);

        
        
        if (rc != 1){
            scanf("%d", &player_response);
        }
        
        print_to_cli(ctx,"\n");
        free(ret_str);
    }

    rc = -1;

    print_to_cli(ctx, "Friend: (again)\n");
    while (rc != 1)
    {
        if (rc < 0) {
            ret_str = start_conversation(c1, &rc, ctx->game);

        } else {
            ret_str = run_conversation_step(c1, player_response, &rc, ctx->game);
        }

        print_to_cli(ctx, ret_str);
        
        // text to speech
        speak(t, ret_str);
        

        if (rc != 1){
            scanf("%d", &player_response);
        }

        print_to_cli(ctx, "\n");
        free(ret_str);
    }
    
    convo_free(c1);
    free_tts(t);
    return "end of convo";

}


int main() {
    chiventure_ctx_t *ctx = create_sample_game();

    add_entry("look_at_friend", run_conversation, NULL, ctx->cli_ctx->table);

    start_ui(ctx, banner);

    

    game_free(ctx->game);

    return 0;
}