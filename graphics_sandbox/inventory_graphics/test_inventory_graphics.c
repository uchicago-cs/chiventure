#include "inventory_graphics.h"  

int main()
{
    player_t *p = player_new("1");
    display_dimensions_t dd;
    inventory_display_t id;
    stats_global_t *statg = stats_global_new("health", 100);
    stats_t *stat = stats_new(statg, 1)l
    statistics_display_t = sd;
    graphics_t g;

    dd->width = 300;
    dd->height = 300;

    td->rows = 10;
    td->columns = 10;
    td->color = WHITE;

    sd->corner = TOP_LEFT;
    sd->statistics = stat;
    sd->mode = NUMERICAL;

    g->dimensions = &gg;
    g->inventory = &td;
    g->statistics = &sd;

    item_t **items = populate_items(p,&g);

    player_inventory_t *pt;
    
    pt = new_player_inventory(&g, p);
}                            
