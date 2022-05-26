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
#include <action_management/action_structs.h>
#include <action_management/actionmanagement.h>

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
    create_connection(game, "room2", "room1", "SOUTH");

    /* Create a rock in room1 */
    item_t *rock = item_new("ROCK","It is a rock.",
                   "You were hoping this was The Rock but, alas, it is just a plain and ordinary rock");
    add_item_to_room(room1, rock);

    /* Create a key in room1 */
    item_t *key = item_new("KEY","It is a key.",
                   "You have acquired a key. You can now enter a new room!");
    add_item_to_room(room1, key);


    /* Where custom_type comes into play, create a dynamic string (hold different values) depending
       on what the user enters at the start of the game */
    char string_num;
    printf("Enter either 1 or 2 (1 for non-caps, 2 for caps): ");
    scanf("%c", &string_num);  
    object_t *ot = obj_t_str("", "../../../../src/custom-scripts/examples/dynamic_string.lua");
    ot = obj_add_arg_char(ot, string_num);
    char* custom_string = (char*)malloc(500);
    custom_string = str_t_get(ot);

    /* Associate action "TASTE" with the rock.
     * It has no conditions, so it should succeed unconditionally. */
    add_action(rock, "TASTE", custom_string, "It has a gravel-ey bouquet.");

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

    // make key something that can be taken
    // test if player picked up the key
    // if yes, then create connections between rooms
    // how to do that without restarting the whole game
    // how to check if something has been taken into the itenerary

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}