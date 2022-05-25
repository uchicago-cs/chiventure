#include <stdlib.h> 
#include <stdbool.h>
#include "lua.h"
#include "lualib.h"
#include "dark_room.h"

#include <stdio.h>
#include <custom-scripts/custom_type.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"

const char *banner = "THIS IS AN EXAMPLE PROGRAM";

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    game_t *game = game_new("Welcome to Chiventure!");

    /* Create one rooms (room1). room1 is the initial room */
    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
    add_room_to_game(game, room1);
    game->curr_room = room1;

    /* Create a torch in room1 */
    item_t *torch = item_new("TORCH","It is a torch.",
                   "The torch is nice, and can provide light!");
    add_item_to_room(room1, torch);

    /* setup unlit torch */
    torch_t* t = malloc(sizeof(torch_t));
    t->state = false;

    /* Use of dynamic boolean, switching item torch from 
    unlit to lit, and conversely with Lua */
    object_t *ot = obj_t_bool("", "../../../../src/custom-scripts/examples/flip.lua");
    ot = obj_add_arg_bool(ot, t->state);
    t->state = bool_t_get(ot);
    
    char* str_state = (char*)malloc(500);
    
    if (t->state == false) {
      str_state = "The torch is unlit.";
    } else {
      str_state = "The torch is lit.";
    }
  
    /* Associate action "FLIP" with the torch.
     * It has no conditions, so it should succeed unconditionally. */
    add_action(torch, "FLIP", str_state, "The torch is broken!");

    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}

int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    /* Monkeypatch the CLI to add a new "kind 1" action
     * (i.e., an action that operates on an item) */
    action_type_t flip_action = {"FLIP", ITEM};
    add_entry(flip_action.c_name, kind1_action_operation, &flip_action, ctx->cli_ctx->table);


    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}