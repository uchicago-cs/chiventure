/*
 * This example program runs a full instance of chiventure from a WDL file,
 * with the following extra features hard-coded in:
 *  - End conditions
 *  - Inventory conditons
 *  - Conditional connections between rooms
 * 
 * Additionally, the CLI is monkeypatched to accept "CONSUME", "DRINK",
 * and "USE" as synonyms for "EAT"
 */

#include <stdio.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"

const char *banner = "THIS IS AN EXAMPLE PROGRAM";

/* Hard codes various necessary item attributes/conditions/effects
 * in the sample game */
int set_item_attributes(chiventure_ctx_t *ctx)
{
    /* TODO */
    return 1;
}

/* Hard codes end conditions in the sample game */
int add_end_conditions(chiventure_ctx_t *ctx)
{
    /* TODO */
    return 1;
}

/* Hard codes inventory conditions in the sample game */
int add_inventory_conditions(chiventure_ctx_t *ctx)
{
    /* TODO */
    return 1;
}

/* Hard codes conditional room connections in the sample game */
int add_conditional_room_connections(chiventure_ctx_t *ctx)
{
    /* TODO */
    return 1;
}

/* Hardcodes CLI support for eat synonyms in the sample game */
int add_eat_synonyms(chiventure_ctx_t *ctx)
{
    /* TODO */
    return 1;
}

int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = chiventure_ctx_new("../src/action_management/"
                                               "examples/test_game.wdl");

    set_item_attributes(ctx);
    add_end_conditions(ctx);
    add_inventory_conditions(ctx);
    add_conditional_room_connections(ctx);
    add_eat_synonyms(ctx);

    start_ui(ctx, banner);

    game_free(ctx->game);
    return 0;
}