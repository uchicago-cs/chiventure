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

    item_t *elixir = item_new("ELIXIR","This is an elixir.",
                   "This is an elixir. It will increase health and stamina but decrease xp.");
    add_item_to_room(room1, elixir);

    item_t *potion = item_new("POTION","This is a health potion.",
                   "This potion will increase your health. Feel free to take it.");
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
        return "I do not know what you mean.";
    }

    stats_global_t *stat, *tmp;
    int size = MIN_STRING_LENGTH + (MAX_NAME_LENGTH * HASH_COUNT(s));
    char list[size];
    char *line;

    HASH_ITER(hh, s, stat, tmp)
    {
        sprintf(line, "%s [max: %d]\n", stat->name, stat->max);
        strcat(list, line);
    }

    char *display = strdup(list);
    return display;
}

char *print_global_effects(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;

    if(tokens[2] != NULL)
    {
        return "I do not know what you mean.";
    }

    effects_global_t *effect, *tmp;

    int size = MIN_STRING_LENGTH + (MAX_NAME_LENGTH * HASH_COUNT(hash));
    char list[size];
    char *line;

    HASH_ITER(hh, hash, effect, tmp)
    {
        sprintf(line, "%s\n", effect->name);
        strcat(list, line);
    }

    char *display = strdup(list);
    return display;
}

char *print_player_stats(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;

    if(tokens[2] != NULL)
    {
        return "I do not know what you mean.";
    }

    return display_stats(game->curr_player->player_stats);
}

char *print_player_effects(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;

    if(tokens[2] != NULL)
    {
        return "I do not know what you mean.";
    }

    return display_global_stats(game->curr_player->player_effects);
}

char *add_player_stat(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;

    if(tokens[2] != NULL)
    {
        return "I do not know what you mean.";
    }
    if(tokens[1] == NULL)
    {
        return "You must identify a stat to add\n";
    }

    global_stat_t *check, *global = global_stat_new(tokens[1]);
    HASH_FIND(hh, game->curr_stats, global->name, strlen(global->name), check);
    
    if (check = NULL)
    {
        return "This stat does not exist in the game."
    }

    stat_t *stat = stat_new(global);
    add_stat(&game->curr_player->player_stats, stat);
    return "The stat has been added."

}

int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    /* Monkeypatch the CLI to add the new operations
     * (not handled by action management, as that code
     * currently only supports items) */
    add_entry("DISPLAY STATS", print_player_stats, NULL, ctx->table);
    add_entry("DISPLAY EFFECTS", print_player_effects, NULL, ctx->table);
    add_entry("GLOBAL STATS", print_global_stats, NULL, ctx->table);
    add_entry("GLOBAL EFFECTS", print_global_effects, NULL, ctx->table);
    add_entry("ADD STAT", add_player_stat, NULL, ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}

