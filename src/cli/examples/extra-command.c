/*
 * This example program runs a full instance of chiventure with an in-memory game,
 * and where the CLI is monkeypatched to accept two new operations:
 *
 *  - GLITTER: This is a CLI-level operation that just prints out a messge
 *  - TASTE: A "kind 1" action that operates on an item. We define an item
 *           in the in-memory game that is able to accept this action.
 */

#include <stdio.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"

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

    /* Create a rock in room1 */
    item_t *rock = item_new("ROCK","It is a rock.",
                   "You were hoping this was The Rock but, alas, it is just a plain and ordinary rock");
    agent_t *agent_rock = malloc(sizeof(agent_t));
    agent_rock->item = rock;
    agent_rock->npc = NULL;
    add_item_to_room(room1, agent_rock->item);

    /* Associate action "TASTE" with the rock.
     * It has no conditions, so it should succeed unconditionally. */
    add_action(agent_rock, "TASTE", "It has a gravel-ey bouquet.", "You can't taste the rock.");

    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);
    free(agent_rock);
    return ctx;
}

/* Defines a new CLI operation that just prints out a message */
char *glitter_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if(game == NULL || game->curr_room == NULL)
        return "Room not found! Error! You can't throw glitter if you're not in a room!\n";

    /* This operation has to be called without parameters */
    if(tokens[1] != NULL)
        return "I do not know what you mean.";

    return "You throw some glitter. For a fleeting moment, the room "
           "feels a bit more fabulous. The glitter seems to have no "
           "effect beyond that.";
}


int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    /* Monkeypatch the CLI to add a new operation
     * (not handled by action management) */
    add_entry("GLITTER", glitter_operation, NULL, ctx->cli_ctx->table);

    /* Monkeypatch the CLI to add a new "kind 1" action
     * (i.e., an action that operates on an item) */
    action_type_t taste_action = {"TASTE", ITEM};
    add_entry(taste_action.c_name, kind1_action_operation, &taste_action, ctx->cli_ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}
