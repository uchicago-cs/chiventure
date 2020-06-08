/*
 * This example program runs a full instance of chiventure with an in-memory game,
 * and where the CLI is monkeypatched to accept two new operations:
 *
 *  - GLITTER: This is a CLI-level operation that just prints out a messge
 *  - TASTE: A "kind 1" action that operates on an item. We define an item
 *           in the in-memory game that is able to accept this action.
 */

#include <stdio.h>
#include <custom-scripts/custom_type.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"

const char *banner = "THIS IS AN EXAMPLE PROGRAM";

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    printf("1\n");
    game_t *game = game_new("Welcome to Chiventure!");


    printf("1\n");
    /* Create two rooms (room1 and room2). room1 is the initial room */
    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
    room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room.");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;
    create_connection(game, "room1", "room2", "NORTH");

    printf("1\n");
    /* Create a rock in room1 */
    item_t *rock = item_new("ROCK","It is a rock.",
                   "You were hoping this was The Rock but, alas, it is just a plain and ordinary rock");
    add_item_to_room(room1, rock);

    printf("1\n");
    // char stringNum;
    // printf("Enter an integer: ");
    // scanf("%c", &stringNum);  
    printf("2\n");
    object_t *ot = obj_t_str("", "../../../../src/custom-scripts/examples/dynamic_string.lua");
    printf("3\n");
    ot = obj_add_arg_char(ot, '1');
    printf("4\n");
    char* custom_string = (char*)malloc(100);
    custom_string = str_t_get(ot);

    printf("5\n");

    printf("1\n");
    /* Associate action "TASTE" with the rock.
     * It has no conditions, so it should succeed unconditionally. */
    add_action(rock, "TASTE", custom_string, "It has a gravel-ey bouquet.");

    printf("1\n");
    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}




int main(int argc, char **argv)
{
    printf("1\n");
    chiventure_ctx_t *ctx = create_sample_ctx();
    printf("end\n");

    /* Monkeypatch the CLI to add a new "kind 1" action
     * (i.e., an action that operates on an item) */
    action_type_t taste_action = {"TASTE", ITEM};
    add_entry(taste_action.c_name, kind1_action_operation, &taste_action, ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}