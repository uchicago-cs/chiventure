/*
 * This example program runs a full instance of chiventure with an in-memory game,
 * and where the CLI is monkeypatched to accept functions that model player stats and effects
 *
 */
 
#include <stdio.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "gamestate/stats.h"

const char *banner = "THIS IS AN EXAMPLE PROGRAM";

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    game_t *game = game_new("Welcome to Chiventure!");

    /* Create two rooms (room1 and room2). room1 is the initial room */
    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
    room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room.");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;
    create_connection(game, "room1", "room2", "NORTH");

    /* Create a poison in room1 */
    item_t *poison = item_new("POISON","This is poison.",
                   "This is poison and will harm your health. DO NOT TAKE OR PICKUP.");
    
    add_item_to_room(room1, poison);

    item_t *soup = item_new("SOUP","This is soup.",
                   "This is a warm, delicious soup and will help your health. Feel free to take it");
    add_item_to_room(room1, soup);

    item_t * = item_new("POISON","This is .",
                   "This is poison and will harm your health. DO NOT TAKE OR PICKUP.");
    add_item_to_room(room1, poison);


    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}

char *print_global_stats(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;

    if(tokens[2] != NULL)
    {
        return "I do on know what you mean.";
    }

    return display_global_stats(game->curr_stats);
}

char *print_global_effects(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;

    if(tokens[2] != NULL)
    {
        return "I do on know what you mean.";
    }

    return display_global_effects(game->all_effects;
}

char *print_player_stats(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;

    if(tokens[2] != NULL)
    {
        return "I do on know what you mean.";
    }

    return display_stats(game->curr_player->player_stats);
}

char *print_player_effects(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;

    if(tokens[2] != NULL)
    {
        return "I do on know what you mean.";
    }

    return display_global_stats(game->curr_player->player_effects);
}

