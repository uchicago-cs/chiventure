/*
 * This example program runs a full instance of chiventure with an in-memory game,
 * and where the CLI is monkeypatched to accept a new operation:
 *
 *  - TASTE: A "kind 1" action that operates on an item. We support customization for the 
 *           output string upon running the action.
 */

#include <stdio.h>
#include <custom-scripts/get_custom_type.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"

const char *banner = "THIS IS AN EXAMPLE PROGRAM";

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    game_t *game = game_new("Welcome to Chiventure!");

    /* Create two rooms (room1 and room2). room1 is the initial room */
    room_t *room0 = room_new("Journey's Other End", "This is room 0", "Here, our journey begins.");
    room_t *room1 = room_new("McDonalds", "This is room 1", "The greasy smell of fries beckons you closer");
    room_t *room2 = room_new("Wingstop", "This is room 2", "The saucy smell of wings call to you");
    room_t *room3 = room_new("Subway", "This is room 3", "The fresh smell of sammies summons.");
    room_t *room5 = room_new("room5", "This is room 5", "Strangely, this is only the fourth room.");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    add_room_to_game(game, room0);
    add_room_to_game(game, room3);
    add_room_to_game(game, room5);
    game->curr_room = room0;
    create_connection(game, "Journey's Other End", "McDonalds", "NORTH");
    create_connection(game, "McDonalds", "Journey's Other End", "SOUTH");
    create_connection(game, "Journey's Other End", "Wingstop", "EAST");
    create_connection(game, "Wingstop", "Journey's Other End", "WEST");
    create_connection(game, "Journey's Other End", "Subway", "SOUTH");
    create_connection(game, "Subway", "Journey's Other End", "NORTH");
    create_connection(game, "Journey's Other End", "room5", "WEST");
    create_connection(game, "room5", "Journey's Other End", "EAST");
    create_connection(game, "Subway", "room5", "SOUTH");
    create_connection(game, "room5", "Subway", "NORTH");


    /* Create a rock in room1 */
    item_t *Lost_McDonalds_Order = item_new("McDonalds?","It seems to be an order of McDonalds.",
                   "It seems like someone didn't get their order... Hopefully it can get back to them!");
    add_item_to_room(room1, Lost_McDonalds_Order);

    item_t *Lost_Wingstop_Order = item_new("Wingstop?","It seems to be an order of Wingstop.",
                   "It seems like someone didn't get their order... Hopefully it can get back to them!");
    add_item_to_room(room2, Lost_Wingstop_Order);

    item_t *Lost_Subway_Order = item_new("Subway?","It seems to be an order of Subway.",
                   "It seems like someone didn't get their order... Hopefully it can get back to them!");
    add_item_to_room(room3, Lost_Subway_Order);

    /* Where custom_type comes into play, create a dynamic string (hold different values) depending
       on what the user enters at the start of the game */
    data_t d1init, d2init, d3init;
    data_t d1, d2, d3, mcd, wng, sub;
    data_t rv2, rv3;

    d1.s = (char*)malloc(sizeof(char) * 500);
    d2.s = (char*)malloc(sizeof(char) * 500);
    d3.s = (char*)malloc(sizeof(char) * 500);

    mcd.s = "McDonalds";
    wng.s = "Wingstop";
    sub.s = "Subway";

    char* name;
    name = (char*)malloc(sizeof(char) * 500);
    printf("Please enter your name: ");
    scanf("%s", name);  

    strcpy(d1.s, name);
    strcpy(d2.s, name);
    strcpy(d3.s, name);

    object_t *ot1 = obj_t_init(d1init, STR_TYPE, "../../../../src/custom-scripts/examples/lost_order.lua");
    ot1 = obj_add_arg(obj_add_arg(ot1, d1, STR_TYPE), mcd, STR_TYPE);
    char* custom_string1 = (char*)malloc(sizeof(char*) * 500);
    data_t rv1 = arg_t_get(ot1);
    custom_string1 = rv1.s;

    object_t *ot2 = obj_t_init(d2init, STR_TYPE, "../../../../src/custom-scripts/examples/lost_order2.lua");
    ot2 = obj_add_arg(obj_add_arg(ot2, d2, STR_TYPE), wng, STR_TYPE);
    char* custom_string2 = (char*)malloc(sizeof(char*) * 500);
    rv2 = arg_t_get(ot2);
    custom_string2 = rv2.s;

    object_t *ot3 = obj_t_init(d3init, STR_TYPE, "../../../../src/custom-scripts/examples/lost_order3.lua");
    ot3 = obj_add_arg(obj_add_arg(ot3, d3, STR_TYPE), sub, STR_TYPE);
    char* custom_string3 = (char*)malloc(sizeof(char*) * 500);
    rv3 = arg_t_get(ot3);
    custom_string3 = rv3.s;

    /* Associate action "INSPECT" with each order.
     * It has no conditions, so it should succeed unconditionally. */
    agent_t McDonalds = (agent_t){.item = Lost_McDonalds_Order, .npc = NULL};
    add_action(&McDonalds, "INSPECT", custom_string1, "It smells greasy!");

    agent_t Wingstop = (agent_t){.item = Lost_Wingstop_Order, .npc = NULL};
    add_action(&Wingstop, "INSPECT", custom_string2, "It smells saucy!");

    agent_t Subway = (agent_t){.item = Lost_Subway_Order, .npc = NULL};
    add_action(&Subway, "INSPECT", custom_string3, "It smells... fresh?");

    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    free(name);

    return ctx;
}

int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    /* Monkeypatch the CLI to add a new "kind 1" action
     * (i.e., an action that operates on an item) */
    action_type_t inspect_action = {"INSPECT", ITEM};
    add_entry(inspect_action.c_name, kind1_action_operation, &inspect_action, ctx->cli_ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}