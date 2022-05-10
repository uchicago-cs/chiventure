/*
 * This example program runs a full instance of chiventure with an
 * memory game. The CLI is monkey-patched to accept a TALK action
 * to initiate a conversation by switching chiventure to CONVERSATION
 * mode.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "npc/npc.h"
#include "npc/dialogue.h"
#include "common/ctx.h"
#include "cli/operations.h"
#include "ui/ui.h"

const char *banner = "NPC CONVERSATION MODE DEMO";

/* Creates a sample conversation */
convo_t *create_steve_conversation()
{
    convo_t *c = convo_new();

    /* Adding dialogue nodes and edges */
    add_node(c, "1", "Pick an item: a sword or a shield?");
    add_node(c, "2a", "I see you prefer the path of offence. Do you prefer a longsword or a scimitar? Or do you change your mind?");
    add_node(c, "3a", "One longsword coming up.");
    add_node(c, "3b", "One scimitar coming up.");
    add_node(c, "2b", "Ah, I see you prefer the path of defence. Clever choice.");
    add_edge(c, "Sword", "1", "2a", NULL);
    add_edge(c, "Shield", "1", "2b", NULL);
    add_edge(c, "Longsword", "2a", "3a", NULL);
    add_edge(c, "Scimitar", "2a", "3b", NULL);
    add_edge(c, "I change my mind: I want a shield", "2a", "2b", NULL);

    return c;
}

/* Conversation based on Pokemon Red and Pokemon Blue */
convo_t *create_oak_conversation()
{
    convo_t *c = convo_new();

    add_node(c, "1", "Hello there! Welcome to the world of Pokemon!\n"
             "My name is Oak! People call me the Pokemon Prof!\n"
             "This world is inhabited by creatures called Pokemon!\n"
             "For some people, Pokemon are pets. Others use them for fights.\n"
             "Myself... I study Pokemon as a profession.");

    add_node(c, "1.5", "First, what is your name?");

    add_node(c, "2a", "So your name is Red?");
    add_node(c, "2b", "So your name is Ash?");
    add_node(c, "2c", "So your name is Misty?");

    add_node(c, "3a", "Right! your name is Red! This is my grandson. He's been your\n"
             "rival since you were a baby. ...Erm, what is his name again?");
    add_node(c, "3b", "Right! your name is Ash! This is my grandson. He's been your\n"
             "rival since you were a baby. ...Erm, what is his name again?");
    add_node(c, "3c", "Right! your name is Misty! This is my grandson. He's been your\n"
             "rival since you were a baby. ...Erm, what is his name again?");

    add_node(c, "4a", "That's right! I remember now! His name is Blue! Now, your very\n"
             "own Pokemon legend is about to unfold! A world of dreams and\n"
             "adventures with Pokemon awaits! Let's go!");
    add_node(c, "4b", "That's right! I remember now! His name is Gary! Now, your very\n"
             "own Pokemon legend is about to unfold! A world of dreams and\n"
             "adventures with Pokemon awaits! Let's go!");

    add_edge(c, "I'm excited to play Pokemon!", "1", "1.5", NULL);
    add_edge(c, "Red", "1.5", "2a", NULL);
    add_edge(c, "Ash", "1.5", "2b", NULL);
    add_edge(c, "Misty", "1.5", "2c", NULL);

    add_edge(c, "Yes", "2a", "3a", NULL);
    add_edge(c, "Yes", "2b", "3b", NULL);
    add_edge(c, "Yes", "2c", "3c", NULL);
    add_edge(c, "No", "2a", "1.5", NULL);
    add_edge(c, "No", "2b", "1.5", NULL);
    add_edge(c, "No", "2c", "1.5", NULL);

    add_edge(c, "Blue", "3a", "4a", NULL);
    add_edge(c, "Gary", "3a", "4b", NULL);
    add_edge(c, "Blue", "3b", "4a", NULL);
    add_edge(c, "Gary", "3b", "4b", NULL);
    add_edge(c, "Blue", "3c", "4a", NULL);
    add_edge(c, "Gary", "3c", "4b", NULL);

    return c;
}

/*
 * This monkey patch talk operation is replaced with the
 * operation now implemented in operations.h
 */
/* Defines an CLI operation for talking to an npc
char *talk_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    char *npc_id = "Oak"; //change to "Steve" for conversation with Steve.
    int rc;
    npc_t *npc = get_npc(ctx->game, npc_id);

    char* str = start_conversation(npc->dialogue, &rc, ctx->game);

    if (!rc)
    {
        game_mode_init(ctx->game->mode, CONVERSATION,
                       run_conversation_mode, npc_id);
    }

    return str;
}
 */

/*
 * Creates a chiventure context with a sample game and npc.
 *
 * Returns: a chiventure context with
 */
chiventure_ctx_t *create_sample_ctx()
{
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("room1", "This is room 1", "You are in Professor Oak's lab. Professor Oak is here.");
    room_t *room2 = room_new("room2", "This is room 2", "You are in a Pokemon Center.");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;
    create_connection(game, "room1", "room2", "NORTH");

    /*
     * To run example with Steve instead of Professor Oak
     * change the npc_id in talk_operation to "Steve"
     */

    /* Creating merchant npc */
    char *npc_id = "STEVE";
    npc_t *steve = npc_new(npc_id,
                           "Steve is a merchant.",
                           "Steve is the best merchant in town.",
                           NULL, NULL, 0);

    convo_t *c = create_steve_conversation();

    add_convo_to_npc(steve, c);
    add_npc_to_game(game, steve);
    add_npc_to_room(room2->npcs, steve);

    /* Create Professor oak */
    char *oak_id = "OAK";
    npc_t *oak = npc_new(oak_id, "Oak is a Pokemon Prof!",
                         "Professor Oak studies Pokemon in Pallet Town",
                         NULL, NULL, 0);

    convo_t *starting_speech = create_oak_conversation();
    add_convo_to_npc(oak, starting_speech);
    add_npc_to_game(game, oak);
    add_npc_to_room(room1->npcs, oak);

    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}

int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();


    /* Monkeypatching in a talk action to support dialogue */
    add_entry("TALK", talk_operation, NULL, ctx->cli_ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}
