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

#include <wdl/load_game.h>
#include "wdl/load_room.h"
#include "wdl/load_item.h"
#include "wdl/load_npc.h"
#include "wdl/load_class.h"
#include "wdl/validate.h"
#include "game-state/mode.h"

const char *banner = "THIS IS AN EXAMPLE PROGRAM";

char *count_rocks(object_t *ot){
    char *str = malloc(80 * sizeof(char));
    int rocks = int_t_get(ot);
    sprintf(str, "There is a stack of %i rocks", rocks);
    return str;
}

char *eat_rock(object_t *ot){
    static int ct = 0;
    char *str = malloc(80 * sizeof(char));
    int rocks = int_t_get(ot);

    ot->data.i = rocks;

    fprintf(stderr, "rock count is %d", ct);
    ct++;
    sprintf(str, "You ate one rock. There are %i rocks remaining in the stack", rocks - 1);
    return str;
}

/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, "demo.lua");

    game_t *game = load_wdl("/home/ramarkob/cs220/chiventure/src/custom-scripts/examples/demo.wdl");



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

    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}