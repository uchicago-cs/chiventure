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
    game_t *game = ctx->game;
    attribute_value_t val_true;
    val_true.bool_val = true;
    attribute_value_t val_false;
    val_false.bool_val = false;
    room_t *dining_room = find_room_from_game(game, "dining room");
    room_t *living_room = find_room_from_game(game, "living room");
    
    /* Add bool attribute "CONSUMED" to all food items
     * Add condition "CONSUMED" == false to "EAT" action
     * Add effect "CONSUMED" == true to "EAT" action
     */ 
    for (int i = 0; i < 4; i++)
    {
        item_t *item;
        switch (i)
        {
        case 0:
            item = get_item_in_room(dining_room, "BREAD");
            break;
        case 1:
            item = get_item_in_room(dining_room, "SPAGHETTI");
            break;
        case 2:
            item = get_item_in_room(dining_room, "SALAD");
            break;
        case 3: 
            item = get_item_in_room(dining_room, "WATER");
            break;
        default:
            break;
        }
        
        set_bool_attr(item, "CONSUMED", false);
        attribute_t *attr = get_attribute(item, "CONSUMED");
        game_action_t *act = get_action(item, "EAT");

        // add_action_condition(item, act, item, attr, val_false);
        // ^ returns ROOM_NULL >:(
        // Seems to be exact same problem detailed in issue #612
    
        game_action_condition_t *new_condition = condition_new(item, attr, val_false);
        LL_APPEND(act->conditions, new_condition);
        add_action_effect(act, item, attr, val_true);
    }
    
    /* Add bool attribute "OPEN" to door
     * Add condition "OPEN" == false to "OPEN" action
     * Add effect "OPEN" == true to "OPEN" action
     */ 
    item_t *door = get_item_in_room(living_room, "DOOR");
    set_bool_attr(door, "OPEN", false);
    attribute_t *attr = get_attribute(door, "OPEN");
    game_action_t *act = get_action(door, "OPEN");
    // add_action_condition(door, act, door, attr, val_false);
    // ^ returns ROOM_NULL >:(
    // Seems to be exact same problem detailed in issue #612
    game_action_condition_t *new_condition = condition_new(door, attr, val_false);
    LL_APPEND(act->conditions, new_condition);
    add_action_effect(act, door, attr, val_true);
    
    return 0;
}

/* Hard codes end conditions in the sample game */
int add_end_conditions(chiventure_ctx_t *ctx)
{
    /* TODO:
     * Add end conditions for each food item - "consumed" must be true 
     * Spaghetti, bread, salad, water*/
    
    return 1;
}

/* Hard codes inventory conditions in the sample game */
int add_inventory_conditions(chiventure_ctx_t *ctx)
{
    /* TODO:
     * Edit spaghetti and salad items in dining room so that action "EAT"
     * cannot be performed unless a fork is in the inventory */
    return 1;
}

/* Hard codes conditional room connections in the sample game */
int add_conditional_room_connections(chiventure_ctx_t *ctx)
{
    /* TODO:
     * Edit path from living room to bedroom (direction "EAST") so that it
     * can only be traveled when door has attribute "open" */
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