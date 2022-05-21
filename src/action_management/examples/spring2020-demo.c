/*
 * This example program runs a full instance of chiventure from a WDL file,
 * with the following extra features hard-coded in:
 *  - End conditions
 *  - Inventory conditons
 *  - Conditional connections between rooms
 */

#include <stdio.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include <wdl/load_game.h>
#include "libobj/load.h"

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
            item = get_item_in_room(dining_room, "SALAD");
            break;
        case 2:
            item = get_item_in_room(dining_room, "WATER");
            break;
        case 3: 
            item = get_item_in_room(dining_room, "SPAGHETTI");
            break;
        default:
            break;
        }
        
        set_bool_attr(item, "CONSUMED", false);
        attribute_t *attr = get_attribute(item, "CONSUMED");
        game_action_t *act = get_action(item, "CONSUME");

        add_action_attribute_condition(act, item, attr, val_false);
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

    add_action_attribute_condition(act, door, attr, val_false);
    add_action_effect(act, door, attr, val_true);
    
    return 0;
}

/* Hard codes end conditions in the sample game */
int add_end_conditions(chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    attribute_value_t val_true;
    val_true.bool_val = true;
    attribute_value_t val_false;
    val_false.bool_val = false;
    room_t *dining_room = find_room_from_game(game, "dining room");
    
    /* Add end condition that "CONSUMED" must equal true for all food items */
    for (int i = 0; i < 4; i++)
    {
        item_t *item;
        switch (i)
        {
        case 0:
            item = get_item_in_room(dining_room, "BREAD");
            break;
        case 1:
            item = get_item_in_room(dining_room, "SALAD");
            break;
        case 2:
            item = get_item_in_room(dining_room, "WATER");
            break;
        case 3: 
            item = get_item_in_room(dining_room, "SPAGHETTI");
            break;
        default:
            break;
        }
        
        add_item_to_game(game, item); // necessary for add_end_condition_to_game
        condition_t *new_condition = attribute_condition_new(item, "CONSUMED", val_true);
        add_end_condition_to_game(game, new_condition);
    }
    
    
    return 0;
}

/* Hard codes inventory conditions in the sample game */
int add_inventory_conditions(chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    player_t *player = game->curr_player;
    room_t *dining_room = find_room_from_game(game, "dining room");
    room_t *kitchen = find_room_from_game(game, "kitchen");
    item_t *fork = get_item_in_room(kitchen, "FORK");
    
    /* Add condition that fork must be in inventory
     * to consume salad & spaghetti */
    for (int i = 0; i < 2; i++)
    {
        item_t *item;
        switch (i)
        {
        case 0:
            item = get_item_in_room(dining_room, "SALAD");
            break;
        case 1:
            item = get_item_in_room(dining_room, "SPAGHETTI");
            break;
        default:
            break;
        }
        
        game_action_t *act = get_action(item, "CONSUME");
        add_action_inventory_condition(act, player, fork);
    }
    
    return 0;
}

/* Hard codes conditional room connections in the sample game */
int add_conditional_room_connections(chiventure_ctx_t *ctx)
{
    /* TODO:
     * Edit path from living room to bedroom (direction "EAST") so that it
     * can only be traveled when door has attribute "open" */
    return 1;
}

int main(int argc, char **argv)
{
    game_t *game = load_game(load_obj_store("../src/action_management/examples/test_game.wdl"));
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    set_item_attributes(ctx);
    add_end_conditions(ctx);
    add_inventory_conditions(ctx);
    add_conditional_room_connections(ctx);

    start_ui(ctx, banner);

    game_free(game);
    return 0;
}
