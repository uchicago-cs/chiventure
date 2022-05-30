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
    room_t *room0 = room_new("room0", "This is room 0", "Here, our journey begins.");
    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
    room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room.");
    room_t *room3 = room_new("room3", "This is room 3", "By definition, this is the third room.");
    room_t *room5 = room_new("room5", "This is room 5", "Strangely, this is only the fourth room.");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    add_room_to_game(game, room0);
    add_room_to_game(game, room3);
    add_room_to_game(game, room5);
    game->curr_room = room0;
    create_connection(game, "room0", "room1", "NORTH");
    create_connection(game, "room0", "room2", "EAST");
    create_connection(game, "room0", "room3", "SOUTH");
    create_connection(game, "room0", "room4", "WEST");
    create_connection(game, "room3", "room5", "SOUTH");



    /* Create a rock in room1 */
    item_t *Lost_McDonalds_Order_item = item_new("McDonalds?","It seems to be an order of McDonalds.",
                   "It seems like someone didn't get their order... Hopefully it can get back to them!");
    add_item_to_room(room1, Lost_McDonalds_Order_item);

    item_t *Lost_Wingstop_Order_item = item_new("Wingstop?","It seems to be an order of Wingstop.",
                   "It seems like someone didn't get their order... Hopefully it can get back to them!");
    add_item_to_room(room2, Lost_Wingstop_Order_item);

    item_t *Lost_Subway_Order_item = item_new("Subway?","It seems to be an order of Subway.",
                   "It seems like someone didn't get their order... Hopefully it can get back to them!");
    add_item_to_room(room3, Lost_Subway_Order_item);

    /* Where custom_type comes into play, create a dynamic string (hold different values) depending
       on what the user enters at the start of the game */
    char* name;
    printf("Please enter your name: ");
    scanf("%s", &name);  
    
    object_t *ot1 = obj_t_str("", "../../../../src/custom-scripts/sandbox/lost_order.lua");
    ot1 = obj_add_arg_str(obj_add_arg_str(ot1, name), "McDonalds");
    char* custom_string1 = (char*)malloc(300);
    custom_string1 = str_t_get(ot1);

    object_t *ot2 = obj_t_str("", "../../../../src/custom-scripts/sandbox/lost_order.lua");
    ot2 = obj_add_arg_str(obj_add_arg_str(ot2, name), "Wingstop");
    char* custom_string2 = (char*)malloc(300);
    custom_string2 = str_t_get(ot2);

    object_t *ot3 = obj_t_str("", "../../../../src/custom-scripts/sandbox/lost_order.lua");
    ot3 = obj_add_arg_str(obj_add_arg_str(ot3, name), "Subway");
    char* custom_string3 = (char*)malloc(300);
    custom_string3 = str_t_get(ot3);


    /* Associate action "INSPECT" with each order.
     * It has no conditions, so it should succeed unconditionally. */
    agent_t Lost_McDonalds_Order = (agent_t){.item = Lost_McDonalds_Order_item, .npc = NULL};
    add_action(&Lost_McDonalds_Order, "INSPECT", custom_string1, "It smells greasy!");

    agent_t Lost_Wingstop_Order = (agent_t){.item = Lost_Wingstop_Order_item, .npc = NULL};
    add_action(&Lost_Wingstop_Order, "INSPECT", custom_string2, "It smells saucy!");

    agent_t Lost_Subway_Order = (agent_t){.item = Lost_Subway_Order_item, .npc = NULL};
    add_action(&Lost_Subway_Order, "INSPECT", custom_string3, "It smells... fresh?");

    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

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