// reference dialogue_example.c in npc/examples
#include <stdio.h>
#include "sound/sound.h"
#include "cli/operations.h"
#include "common/ctx.h"
#include "ui/ui.h"
#include "npc/dialogue.h"
#include "sound/tts.h"
#include "npc/npc.h"


const char *banner = "CHIVENTURE SOUND";

convo_t *create_friend_conversation()
{
    tone_t tone = POSITIVE;
    convo_t *c1 = convo_new();
    add_node(c1, "1", "Welcome to Chiventure! My name is friend. My voice"
    " was created by the sound team from Spring of 2022 in their software"
    " development class. It is so nice to finally meet you. How are you "
    " doing today?", tone);
    add_node(c1, "2a", "Great! I am glad that you are having a nice day."
    "What can I do for you? Are you enjoying the chiventure game?", tone);
    add_node(c1, "3a", "Yay! That makes me so happy. We worked soooooooo"
    " hard on this, so it's really awesome that you enjoy it. Can I read"
    "you some of my favorite poetry to celebrate?", tone);
    add_node(c1, "4a", "Here is my favorite poem by Nicki Minaj. It goes like this:"
    " This one is for the boys with the booming system. Top down AC with the cooling system."
    " When he coming to the club he be blazing up. Got stacks on deck like he saving up."
    " Hope you enjoyed that, it was great speaking with you today!", tone);
    add_node(c1, "4b", "Oh, that fine. Maybe another time! Have a great day!", tone);
    add_node(c1, "3b", "Really? That sucqks. I think I'm pretty cool... "
    "We hope we can change your mind!", tone);
    add_node(c1, "2b", "Awwwwww, I'm sorry, feel better. Finals will be over soon."
    " School is temporary, code is forever. <3", tone);


    add_edge(c1, "Good", "1", "2a", NULL, tone);
    add_edge(c1, "Bad", "1", "2b", NULL, tone);
    add_edge(c1, "Yes, I love it!", "2a", "3a", NULL, tone);
    add_edge(c1, "No, leave me alone.", "2a", "3b", NULL, tone);
    add_edge(c1, "Duh.", "3a", "4a", NULL, tone);
    add_edge(c1, "I'll pass...", "3a", "4b", NULL, tone);

    return c1;
    
}

// create sample game
chiventure_ctx_t *create_sample_ctx()
{

    // Initializing game, player, and npc
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *convo_room = room_new("convo room", "This is the conversation room","Welcome to the conversation room!");
    

    add_room_to_game(game, convo_room);

    game->curr_room = convo_room;

    player_t *p = player_new("Rhea");
    npc_t *friend = npc_new("friend", "This is your friend.", "He would like to speak to you.", NULL, NULL, 0);

    convo_t *c = create_friend_conversation();

    add_convo_to_npc(friend,c);
    add_npc_to_game(game, friend);
    add_npc_to_room(convo_room->npcs, friend);

    add_player_to_game(game, p);

    game->curr_player = p;
    game->mode = game_mode_new(NORMAL, NULL, "friend");


    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}

char *run_conversation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    // Execute the conversation, this is where we will need to play the sound for the conversation
    int rc = -1;
    int player_response;
    char *ret_str;
    
    npc_t *npc = get_npc(ctx->game,"friend");

    tts_t* t = init_tts("English", 5000);

    print_to_cli(ctx, "Friend:\n");
    while (rc != 1)
    {
        if (rc < 0) {
            ret_str = start_conversation(npc->standard_dialogue, &rc, ctx->game);
        } else {
            ret_str = run_conversation_step(npc->standard_dialogue, player_response, &rc, ctx->game);
        }
        
        // text to speech 
        print_to_cli(ctx, ret_str);   
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
            ret_str = start_conversation(npc->standard_dialogue, &rc, ctx->game);

        } else {
            ret_str = run_conversation_step(npc->standard_dialogue, player_response, &rc, ctx->game);
        }

        // text to speech 
        print_to_cli(ctx, ret_str);
        speak(t, ret_str);

        
        if (rc != 1){
            scanf("%d", &player_response);
        }

        print_to_cli(ctx, "\n");
        free(ret_str);
    }
    
    convo_free(npc->standard_dialogue);
    free_tts(t);
    return "end of convo";

}


int main() {
    chiventure_ctx_t *ctx = create_sample_ctx();

    add_entry("talk_to_friend", run_conversation, NULL, ctx->cli_ctx->table);

    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}