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

const char *banner = "THIS IS AN EXAMPLE PROGRAM";

/* Helper function to dynamically flip torch state using Lua each time flip is called 
   Variable st is state of torch before fliping */
char* flip_state(bool st)
{
    /* Use of boolean, switching item torch from 
    true (lit) to false (unlit), and conversely with Lua */
    object_t *ot = obj_t_bool("", "../../../../src/custom-scripts/examples/flip.lua");
    ot = obj_add_arg_bool(ot, st);
    st = bool_t_get(ot);
    
    char* str_state = (char*)malloc(20);
    
    /* output string depending on flip */
    if (st == false) {
      str_state = "The torch is unlit.";
    } else {
      str_state = "The torch is lit.";
    }
    
    return str_state;
}

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    game_t *game = game_new("Welcome to Chiventure!");

    /* Create one rooms (room1). room1 is the initial room */
    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
    add_room_to_game(game, room1);
    game->curr_room = room1;

    /* Create a torch in room1 */
    item_t *torch_item = item_new("TORCH","It is a torch.",
                   "The torch is nice, and can provide light!");
    add_item_to_room(room1, torch_item);
    agent_t torch = (agent_t){.item = torch_item, .npc = NULL};

    /* Associate action "LIGHT" and "UNLIGHT" with the torch.
    * They have no conditions, so they should succeed unconditionally. */
    add_action(&torch, "LIGHT", flip_state(true), "The torch is broken!");
    add_action(&torch, "UNLIGHT", flip_state(false), "The torch is broken!");

    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}

int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    /* Monkeypatch the CLI to add a new "kind 1" actions
     * (i.e., actions that operate on an item) */
    action_type_t light_action = {"LIGHT", ITEM};
    add_entry(light_action.c_name, kind1_action_operation, &light_action, ctx->cli_ctx->table);
    action_type_t unlight_action = {"UNLIGHT", ITEM};
    add_entry(unlight_action.c_name, kind1_action_operation, &unlight_action, ctx->cli_ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}