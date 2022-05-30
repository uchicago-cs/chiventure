/*
 * This example program runs a full instance of chiventure with an in-memory game,
 * and where the CLI is monkeypatched to accept a new operation:
 *
 *  - TASTE: A "kind 1" action that operates on an item. We support customization for the 
 *           output string upon running the action.
 */

#include <stdlib.h> 
#include <stdbool.h>
#include "lua.h"
#include "lualib.h"
#include "dark_room.h"

#include <stdio.h>
#include <custom-scripts/get_custom_type.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"

#include <sys/ioctl.h>
#include <unistd.h>
#include <wdl/load_game.h>
#include <ui/ui_ctx.h>
#include "libobj/load.h"


#include "game-state/mode.h"

const char *banner = "THIS IS AN EXAMPLE PROGRAM";

char* flip_state(bool st)
{
    char* str_state = (char*)malloc(20);
    
    /* output string depending on flip */
    if (!st) {
      str_state = "The torch is unlit.";
    } else {
      str_state = "The torch is lit.";
    }
    
    return str_state;
}

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    data_t jack;
    data_t dc;

    object_t *togay = obj_t_init(jack, STR_TYPE,"../../../../src/custom-scripts/examples/demo.lua");
   

    /* Create context */
    char string_num;
    printf("Enter either 1 or 2 (1 for wizard class, 2 for warrior class): ");
    scanf("%c", &string_num); 
    dc.c = string_num;
    togay = obj_add_arg(togay,dc,CHAR_TYPE);
    char* custom_string = (char*)malloc(100);
    data_t temp = arg_t_get(togay);
    custom_string = temp.s;

    obj_t *obj_store;

    char wizard[] = "Wizard Class", warrior[] = "Warrior Class";
    if(strcmp(wizard,custom_string)== 0){
        obj_store = load_obj_store("../../../../src/custom-scripts/examples/demo.wdl");
    }
    else{
        obj_store = load_obj_store("../../../../src/custom-scripts/examples/demo-warrior.wdl");
    }

    game_t *game = load_game(obj_store);
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    /* Create one rooms (room1). room1 is the initial room */
    room_t *room1 = room_new("room_torch", "This is the torch room", "This is a room with a torch in the corner");
    add_room_to_game(game, room1);
    create_connection(game, "room_A", "room_torch", "SOUTH");

    /* Create a torch in room1 */
    item_t *torch_item = item_new("TORCH","It is a torch.",
                   "The torch is nice, and can provide light!");
    agent_t torch = (agent_t){.item = torch_item, .npc = NULL};
    add_item_to_room(room1, torch_item);

    /* Associate action "LIGHT" and "UNLIGHT" with the torch.
    * They have no conditions, so they should succeed unconditionally. */
    add_action(&torch, "LIGHT", flip_state(true), "The torch is broken!");
    add_action(&torch, "UNLIGHT", flip_state(false), "The torch is broken!");

    return ctx;
}

int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    /* Monkeypatch the CLI to add a new "kind 1" actions
     * (i.e., actions that operate on an item) */
    action_type_t fireball_action = {"FIREBALL", ITEM};
    add_entry(fireball_action.c_name, kind1_action_operation, &fireball_action, ctx->cli_ctx->table);
    action_type_t slash_action = {"SLASH", ITEM};
    add_entry(slash_action.c_name, kind1_action_operation, &slash_action, ctx->cli_ctx->table);
    action_type_t light_action = {"LIGHT", ITEM};
    add_entry(light_action.c_name, kind1_action_operation, &light_action, ctx->cli_ctx->table);
    action_type_t unlight_action = {"UNLIGHT", ITEM};
    add_entry(unlight_action.c_name, kind1_action_operation, &unlight_action, ctx->cli_ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}