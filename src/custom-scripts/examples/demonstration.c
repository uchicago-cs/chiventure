/*
 * This example program runs a full instance of chiventure with an in-memory game,
 * and where the CLI is monkeypatched to accept a new operation:
 *
 *  - TASTE: A "kind 1" action that operates on an item. We support customization for the 
 *           output string upon running the action.
 */

#include <stdio.h>
#include <custom-scripts/custom_type.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"

const char *banner = "THIS IS AN EXAMPLE PROGRAM";

char *count_rocks(object_t *ot){
    char *str = malloc(80 * sizeof(char));
    int rocks = int_t_get(ot);
    sprintf(str, "There is a stack of %i rocks", rocks);
    return str;
}

char *eat_rock(object_t *ot){
    static int ct = 0;
    char *str = malloc(80 * sizeof(char));
    int rocks = int_t_get(ot);

    ot->data.i = rocks;

    fprintf(stderr, "rock count is %d", ct);
    ct++;
    sprintf(str, "You ate one rock. There are %i rocks remaining in the stack", rocks - 1);
    return str;
}

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, "sample.lua");

    game_t *game = game_new("Welcome to Chiventure!");

    /* Create two rooms (room1 and room2). room1 is the initial room */
    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
    room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room.");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;
    create_connection(game, "room1", "room2", "NORTH");

    /* Create a rock in room1 */
    object_t *rocks = obj_t_int(20, NULL);
    item_t *rock = item_new("ROCK", "It is a rock", count_rocks(rocks));
    add_item_to_room(room1, rock);
    
    /* Associate action "TASTE" with the rock.
     * It has no conditions, so it should succeed unconditionally. */
    add_action(rock, "TASTE", eat_rock(rocks), "It has a gravel-ey bouquet.");

    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}




int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    /* Monkeypatch the CLI to add a new "kind 1" action
     * (i.e., an action that operates on an item) */
    action_type_t taste_action = {"TASTE", ITEM};
    add_entry(taste_action.c_name, kind1_action_operation, &taste_action, ctx->cli_ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}