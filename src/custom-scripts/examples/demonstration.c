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


#include <sys/ioctl.h>
#include <unistd.h>
#include <wdl/load_game.h>
#include <ui/ui_ctx.h>
#include "libobj/load.h"


#include "game-state/mode.h"

const char *banner = "THIS IS AN EXAMPLE PROGRAM";

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    data_t jack;
    data_t dc;

    object_t *togay = obj_t_init(jack, STR_TYPE,"../../../../src/custom-scripts/examples/dynamic_string.lua");
   

    /* Create context */
    char string_num;
    printf("Enter either 1 or 2 (1 for wizard class, 2 for warrior class): ");
    scanf("%c", &string_num); 
    dc.c = string_num;
    togay = obj_add_arg(togay,dc,CHAR_TYPE);
    char* custom_string = (char*)malloc(100);
    data_t temp = arg_t_get(togay);
    custom_string = temp.s;
    char wizard[] = "Wizard Class", warrior[] = "Warrior Class";
    if(strcmp(wizard,custom_string)== 0){
        obj_t *obj_store1 = load_obj_store("../../../../src/custom-scripts/examples/demo.wdl");
        game_t *game1 = load_game(obj_store1);
        chiventure_ctx_t *ctx1 = chiventure_ctx_new(game1);
        return ctx1;
    }
    else{
        obj_t *obj_store2 = load_obj_store("../../../../src/custom-scripts/examples/demo-warrior.wdl");
        game_t *game2 = load_game(obj_store2);
        chiventure_ctx_t *ctx2 = chiventure_ctx_new(game2);
        return ctx2;
    }
}


int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();

    action_type_t fireball_action = {"FIREBALL", ITEM};
    add_entry(fireball_action.c_name, kind1_action_operation, &fireball_action, ctx->cli_ctx->table);
    action_type_t slash_action = {"SLASH", ITEM};
    add_entry(slash_action.c_name, kind1_action_operation, &slash_action, ctx->cli_ctx->table);

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}