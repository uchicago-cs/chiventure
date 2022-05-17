#include <criterion/criterion.h>
#include <stdlib.h>
#include "inventory_graphics/inventory_graphics.h"

Test(inventory, new)
{
    player_t *p = player_new("1");
    display_dimensions_t dd;
    inventory_display_t td;
    stats_global_t *statg = stats_global_new("health", 100);
    stats_t *stat = stats_new(statg, 1);
    statistics_display_t = sd;
    graphisc_t g;


    dd->width = 300;
    dd->height = 300;
    
    td->rows = 10;
    td->columns = 10;
    td->color = WHITE;

    sd->corner = TOP_LEFT;
    sd->statistics = stat;
    sd->mode = NUMERICAL;

    g->dimensions = &dd;
    g->inventory = &td;
    g->statistics = &sd;
    
    item_t **items = populate_items(p,&g);

    player_inventory_t *pt;

    pt = new_player_inventory(&g, p);
    
    cr_assert_not_null(pt, "new_player_inventory() failed");
    
    cr_assert_eq(pt->display,td, "new_player_inventory didn't set display");
    cr_assert_eq(pt->items,items, "new_player_inventory didn't set items");
}


/* Checks that player_inventory struct is freed properly */
Test(inventory, free)
{
    player_t *p = player_new("1");
    display_dimensions_t dd;
    inventory_display_t td;
    stats_global_t *statg = stats_global_new("health", 100);
    stats_t *stat = stats_new(statg, 1);
    statistics_display_t sd;
    graphics_t g;
    
    
    dd->width = 300;
    dd->height = 300;
    
    td->rows = 10;
    td->columns = 10;
    td->color = WHITE;

    sd->corner = TOP_LEFT;
    sd->statistics = stat;
    sd->mode = NUMERICAL;

    g->dimensions = &dd;
    g->inventory = &td;
    g->statistics = &sd;

    player_inventory_t *pt;
    int rc;

    pt = new_player_inventory(&g,p);

    cr_assert_not_null(pt, "new_player_inventory() failed");
    
    rc = free_player_inventory(pt);

    cr_assert_eq(rc, 0, "free_player_inventory() failed"); 
}


