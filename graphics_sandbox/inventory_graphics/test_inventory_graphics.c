#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../include/game-state/item.h"
#include "../../include/game-state/player.h"
#include "inventory_graphics.h"  


player_t *synthesize_player(char *player_id)
{
    chiventure_ctx_t *ctx = chiventure_ctx_new(NULL);
    
    player_t *pt = player_new(player_id);
    
    item_t *il1 = item_new("Rock", "Gray Rock", "This is a medium gray rock");
    item_t *il2 = item_new("Orb", "Colorful orb", "This is a rainbow orb");
    item_t *il3 = item_new("Sword", "Dull sword", 
                           "This is a very used, dull sword");
    item_t *il4 = item_new("Feather", "Ashy feather",
                           "This is an ashy feather, likely from a dead phoenix");

    add_item_to_player(pt, il1, ctx->game);
    add_item_to_player(pt, il2, ctx->game); 
    add_item_to_player(pt, il3, ctx->game); 
    add_item_to_player(pt, il4, ctx->game); 
   
    return pt;
}

graphics_t *synthesize_graphics(char *stat)
{
    display_dimensions_t dd;
    inventory_display_t td;
    statistics_display_t sd;

    stats_global_t *statg = stats_global_new(stat, 100);
    stats_t *stat = stats_new(statg, 1);
    
    graphics_t g;

    dd.width = 300;
    dd.height = 300;

    td.rows = 3;
    td.columns = 5;
    td.color = WHITE;

    sd.corner = TOP_LEFT;
    sd.statistics = stat;
    sd.mode = NUMERICAL;

    g.dimensions = &dd;
    g.inventory = &td;
    g.statistics = &sd;

    return g;
} 


/* Checks that space is allocated and values are initialized for 
 * slot_t struct */
Test(slot, new)
{
    status s = FULL;
    item_t *il = item_new("Rock", "Gray Rock", "This is a medium gray rock");
    il->inventory_x_pos = 0;
    il->inventory_y_pos = 0;

    slot_t *slot;
    slot = new_slot(s,il);
    
    cr_assert_not_null(slot, "new_slot() failed");
    
    cr_assert_eq(slot->status, FULL, "new_slot() didn't set status");
    cr_assert_eq(strcmp(slot->item->short_desc, "Gray Rock"), 0, "new_slot() didn't set relation to short item description");
    cr_assert_eq(strcmp(slot->item->long_desc, "This is a medium gray rock"), 0, "new_slot() didn't set relation to long item description");
}

/* Checks that values for slot_t struct are properly initialized */
Test(slot, init)
{
    status s = FULL;
    item_t *il = item_new("Rock", "Gray Rock", "This is a medium gray rock");
    il->inventory_x_pos = 0;
    il->inventory_y_pos = 0;

    slot_t slot;
    int rc; 

    rc = init_slot(&slot, s, il);

    cr_assert_eq(rc, SUCCESS, "init_slot() failed");

    cr_assert_eq(slot.status, FULL, "init_slot() didn't set status");
    cr_assert_eq(strcmp(slot.item->short_desc, "Gray Rock"), 0, "init_slot() didn't set relation to short item description");
    cr_assert_eq(strcmp(slot.item->long_desc, "This is a medium gray rock"), 0, "init_slot() didn't set relation to long item description");
}

/* Checks that memory allocated for slot_t struct frees properly */
Test(slot, free)
{
    status s = FULL;
    item_t *il = item_new("Rock", "Gray Rock", "This is a medium gray rock");
    il->inventory_x_pos = 0;
    il->inventory_y_pos = 0;
    int rc;

    slot_t *slot;
    slot = new_slot(s,il);
    
    cr_assert_not_null(slot, "new_slot() failed");
    
    rc = free_slot(slot);

    cr_assert_eq(rc, SUCCESS, "free_slot() failed");
}

/* Checks that memory and values are properly allocated/initialized for
 * player_inventory_t struct */
Test(inventory, new)
{
    player_t *p = synthesize_player("1");
    graphics_t *g = synthesize_graphics("health");
    
    slot_t **slot = populate_items(p,g);

    player_inventory_t *inventory;
    
    inventory = new_player_inventory(g,slot);

    cr_assert_not_null(inventory, "new_player_inventory() failed");
    
    cr_assert_eq(inventory->display->rows,3,"new_player_inventory() didn't set rows");
    cr_assert_eq(inventory->display->columns,5,"new_palyer_inventory() didn't set columns");
    cr_assert_eq(inventory->slots[0][0]->status, FULL, "new_player_inventory() didn't set status");
}

/* Checks that values are properly initialized for player_inventory_t struct */
Test(inventory, init)
{  
    player_t *p = synthesize_player("1");
    graphics_t *g = synthesize_graphics("health");

    slot_t **slot = populate_items(p,g);

    player_inventory_t inventory;
    int rc;

    rc = init_player_inventory(&inventory, g, slot);

    cr_assert_eq(rc, SUCCESS, "init_player_inventory_failed");

    cr_assert_eq(inventory.display->rows,3,"init_player_inventory() didn't set rows");
    cr_assert_eq(inventory.display->columns,5,"init_player_inventory() didn't set columns");
    cr_assert_eq(inventory.dlots[0][0]->status, FULL,"init_player_inventory() didn't set status");
}

/* Checks that memory allocated for player_inventory_t struct is freed */
Test(inventory, free)
{
    player_t *p = synthesize_player("1");
    graphics_t *g = synthesize_graphics("health");

    slot_t **slot = populate_items(p,g);

    player_inventory_t *inventory;
    inventory = new_player_inventory(p,slot);
    
    cr_assert_not_null(inventory, "new_player_inventory() failed");    

    int rc;

    rc= free_player_inventory(inventory);

    cr_assert_eq(rc, SUCCESS, "free_player_inventory() failed");
}

    
    

     
