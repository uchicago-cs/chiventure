#include "inventory_graphics.h"  

int main()
{
    /* This establishes an item to use for player_t */
    item_t *i1 = item_new("Rock", "Gray Rock", "This is a medium gray rock");
       

    player_t *p = player_new("1");

    add_item_to_player(p,i1);
   
    item_hash_t *inv = get_inventory(p);

    display_dimensions_t dd;
    inventory_display_t td;
    statistics_display_t sd;

    stats_global_t *statg = stats_global_new("health", 100);
    stats_t *stat = stats_new(statg, 1);
    
    graphics_t g;

    dd.width = 300;
    dd.height = 300;

    td.rows = 10;
    td.columns = 10;
    td.color = WHITE;

    sd.corner = TOP_LEFT;
    sd.statistics = stat;
    sd.mode = NUMERICAL;

    g.dimensions = &dd;
    g.inventory = &td;
    g.statistics = &sd;

    slot_t **items = populate_items(p,&g);

    player_inventory_t *pt;
    
    pt = new_player_inventory(&g, p);

}                            
