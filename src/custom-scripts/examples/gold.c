#include <stdlib.h> 
#include "lua.h"
#include "lualib.h"
#include "gold.h"

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

    /* Create a chest in room1 */
    item_t *chest = item_new("CHEST","It is a chest.",
                   "You shake the chest, but hear no rattle inside... must be empty :(");
    add_item_to_room(room1, chest);


    /* Where custom_type comes into play, create a dynamic string (hold different values) depending
       on what the user enters at the start of the game */
    int string_num;
    printf("You receive a premonition... how much gold do you see in your future?\n");
    scanf("%i", &string_num);  
    object_t *ot = obj_t_str("", "../../../../src/custom-scripts/examples/gold.lua");
    ot = obj_add_arg_int(ot, string_num);
    char* custom_string = (char*)malloc(500);
    custom_string = str_t_get(ot);
    
    int rand_weight = rand() % string_num; // The more money you request, the less likely you are to obtain it
    object_t *ot2 = obj_t_str("", "../../../../src/custom-scripts/examples/weight.lua");
    ot2 = obj_add_arg_int(ot2, rand_weight);
    char* custom_string2 = (char*)malloc(500);
    custom_string2 = str_t_get(ot2); 

    if (custom_string2[0] != 'f') {
      custom_string = custom_string2;
    }

    /* Associate action "SHAKE" with the chest.
     * It has no conditions, so it should succeed unconditionally. */
    add_action(chest, "SHAKE", custom_string, "You have already shaken the box!");

    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}

int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    /* Monkeypatch the CLI to add a new "kind 1" action
     * (i.e., an action that operates on an item) */
    action_type_t shake_action = {"SHAKE", ITEM};
    add_entry(shake_action.c_name, kind1_action_operation, &shake_action, ctx->cli_ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}