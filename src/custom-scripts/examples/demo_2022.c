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

typedef struct torch_t torch_t;

struct torch_t {
    bool state; // false = unlit, true = lit
} ;

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
    /* Where custom_type comes into play, create a dynamic string (hold different values) depending
    on what the user enters at the start of the game */
    data_t jack, d1, d2;
    data_t dc, di1, di2;

    /* Load Lua files*/
    object_t *togay = obj_t_init(jack, STR_TYPE,"../../../../src/custom-scripts/examples/lua/demo.lua");
    object_t *ot = obj_t_init(d1, STR_TYPE, "../../../../src/custom-scripts/examples/lua/gold.lua");
    object_t *ot2 = obj_t_init(d2, STR_TYPE, "../../../../src/custom-scripts/examples/lua/weight.lua");
   
    /* Initalize varaibles */
    char class_num;
    int gold_num;

    /* Read in User Input */
    printf("Enter either 1 or 2 (1 for wizard class, 2 for warrior class): ");
    scanf("%c", &class_num); 
    printf("You receive a premonition... how much gold do you see in your future? ");
    scanf("%i", &gold_num);  

    /* The class you selected */
    dc.c = class_num;
    togay = obj_add_arg(togay, dc, CHAR_TYPE);
    char* custom_string = (char*)malloc(100);
    data_t temp = arg_t_get(togay);
    custom_string = temp.s;

    /* The amount of money you requested */
    di1.i = gold_num;
    ot = obj_add_arg(ot, di1, INT_TYPE);
    char* gold_string = (char*)malloc(500);
    temp = arg_t_get(ot);
    gold_string = temp.s;

    /* The more money you request, the less likely you are to obtain it */
    di2.i = (gold_num ? rand() % gold_num : 0); 
    ot2 = obj_add_arg(ot2, di2, INT_TYPE);
    char* custom_string2 = (char*)malloc(500);
    temp = arg_t_get(ot2);
    custom_string2 = temp.s; 

    /* Create context */
    obj_t *obj_store = load_obj_store(custom_string);
    game_t *game = load_game(obj_store);
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    /* Create the torch room */
    room_t *room1 = room_new("room_torch", "This is the torch room", "This is a room with a torch in the corner");
    add_room_to_game(game, room1);
    create_connection(game, "room_A", "room_torch", "SOUTH");
    create_connection(game, "room_torch", "room_A", "NORTH");

    /* Create a torch in the torch room */
    item_t *torch_item = item_new("TORCH","It is a torch.", "The torch is nice, and can provide light!");
    add_item_to_room(room1, torch_item);
    agent_t torch = (agent_t){.item = torch_item, .npc = NULL};

    /* Associate action "LIGHT" and "UNLIGHT" with the torch.
    * They have no conditions, so they should succeed unconditionally. */
    add_action(&torch, "LIGHT", flip_state(true), "The torch is broken!");
    add_action(&torch, "UNLIGHT", flip_state(false), "The torch is broken!");

    /* Create the chest room */
    room_t *room2 = room_new("room_chest", "This is the chest room", "There is a chest in the middle of this room");
    add_room_to_game(game, room2);
    create_connection(game, "room_A", "room_chest", "WEST");
    create_connection(game, "room_chest", "room_A", "EAST");

    /* Create a chest in the chest room */
    item_t *chest_item = item_new("CHEST","It is a chest.",
                   "You shake the chest, but hear no rattle inside... must be empty :(");
    add_item_to_room(room2, chest_item);
    agent_t chest = (agent_t){.item = chest_item, .npc = NULL};

    /* Associate action "SHAKE" with the chest.
     * It has no conditions, so it should succeed unconditionally. */
    add_action(&chest, "SHAKE", gold_string, "You have already shaken the box!");

    /* Create the chest room */
    room_t *room3 = room_new("room_items", "This is the chest room", "There is a sword and a staff in the middle of this room");
    add_room_to_game(game, room3);
    create_connection(game, "room_A", "room_items", "EAST");
    create_connection(game, "room_items", "room_A", "WEST");

    /* Create a sword in the items room */
    item_t *sword_item = item_new("SWORD", "This is a sword", "This is a sword for a warrior");
    add_item_to_room(room3, sword_item);
    agent_t sword = (agent_t){.item = sword_item, .npc = NULL};

    /* Create a staff in the items room */
    item_t *staff_item = item_new("STAFF","This is a staff", "This is a staff for a wizard");
    add_item_to_room(room3, staff_item);
    agent_t staff = (agent_t){.item = staff_item, .npc = NULL};

    /* Associate action "SHAKE" with the chest.
     * It has no conditions, so it should succeed unconditionally. */
    if (class_num == 1 ){
      add_action(&sword, "TAKE", "THIS IS SPARTA", "You cannot take this sword unless you are a warrior class");
    }
    else {
      add_action(&staff, "TAKE", "You're a wizard, Harry", "You cannot take this staff unless you are a wizard class");
    }

    return ctx;
}

int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    /* Monkeypatch the CLI to add new "kind 1" actions
     * (i.e., actions that operate on an item) */
    action_type_t fireball_action = {"FIREBALL", ITEM};
    add_entry(fireball_action.c_name, kind1_action_operation, &fireball_action, ctx->cli_ctx->table);

    action_type_t slash_action = {"SLASH", ITEM};
    add_entry(slash_action.c_name, kind1_action_operation, &slash_action, ctx->cli_ctx->table);

    action_type_t light_action = {"LIGHT", ITEM};
    add_entry(light_action.c_name, kind1_action_operation, &light_action, ctx->cli_ctx->table);
    
    action_type_t unlight_action = {"UNLIGHT", ITEM};
    add_entry(unlight_action.c_name, kind1_action_operation, &unlight_action, ctx->cli_ctx->table);

    action_type_t shake_action = {"SHAKE", ITEM};
    add_entry(shake_action.c_name, kind1_action_operation, &shake_action, ctx->cli_ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}