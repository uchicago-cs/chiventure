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
convo_t *create_sample_conversation()
{
    convo_t *c = convo_new();

    /* Adding dialogue nodes and edges */
    add_node(c, "1", "Pick an item: a sword or a shield?");
    add_node(c, "2a", "I see you prefer the path of offence. Do you prefer a longsword or a scimitar? Or do you change your mind?");
    add_node(c, "3a", "One longsword coming up.");
    add_node(c, "3b", "One scimitar coming up.");
    add_node(c, "2b", "Ah, I see you prefer the path of defence. Clever choice.");
    add_edge(c, "Sword", "1", "2a");
    add_edge(c, "Shield", "1", "2b");
    add_edge(c, "Longsword", "2a", "3a");
    add_edge(c, "Scimitar", "2a", "3b");
    add_edge(c, "I change my mind: I want a shield", "2a", "2b");

    return c;
}

/* Defines an CLI operation for talking to an npc */
char *talk_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    char* npc_id = "Steve";
    int rc;
    npc_t *npc;
    HASH_FIND(hh, ctx->game->all_npcs, npc_id,
              strnlen(npc_id, MAX_ID_LEN), npc);

    char* str = start_conversation(npc->dialogue, &rc);

    if (!rc)
    {
        game_mode_init(ctx->game->mode, CONVERSATION, 
                       run_conversation_mode, npc_id);
    }

    return str;
}

/*
 * Creates a chiventure context with a sample game and npc.
 *
 * Returns: a chiventure context with 
 */
chiventure_ctx_t *create_sample_ctx()
{
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
    room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room.");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;
    create_connection(game, "room1", "room2", "NORTH");

    /* Creating merchant npc */
    char* npc_id = "Steve";
    npc_t *steve = npc_new(npc_id,
                         "Steve is a merchant.",
                         "Steve is the best merchant in town.",
                         25, NULL, NULL);

    convo_t *c = create_sample_conversation();

    add_convo_to_npc(steve, c);
    add_npc_to_game(game, steve);

    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}

int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    /* Monkeypatching in a talk action to support dialogue */
    add_entry("TALK", talk_operation, NULL, ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}
