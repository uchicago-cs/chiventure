#include "inventory_graphics.h"

/*
 * Populates the 2D array that will be used to hold items for inventory
 * graphics
 *
 * Parameters:
 * p : pointer to heap allocated player struct
 * graphics : pointer to heap allocated graphics struct
 *
 * Returns:
 * 2D array of items corresponding to items in player's inventory
 */
**item_t populate_items(player_t *p, graphics_t *graphics)
{
    item_list_t *itemlst = get_all_items_in_hash(p->inventory);
    
    item_t **inv = (item_t**)malloc(sizeof(item_t*)*graphics->inventory->rows);
    for (unsigned int i =0; i < graphics->inventory->rows; i++){
        inv[i] = (item_t*)malloc(sizeof(item_t) * graphics->inventory->columns;
    }

    while (itemlst->next != NULL){
        for(int i = 0; i < graphics->inventory->rows; i++){
            for(int j = 0; j < graphics->inventory->columns; j++){
                inv[i][j] = itemlst->item;
            }
        }
        itemlst = itemlst->next;
    }

    return inv;
}

/* See inventory_graphics.h */
player_inventory_t *new_player_inventory(graphics_t *graphics, player_t *p)
{
    player_inventory_t *inventory = (player_inventory_t*)mailloc(sizeof(player_inventory_t);

    inventory->display->rows = graphics->inventory->rows;
    inventory->display->columns = graphics->inventory->columns;
    inventory->display->color = graphics->inventory->color;

    inventory->items = populate_items(p,graphics);

    return inventory;
}

/* See inventory_graphics.h */
void free_player_inventory(player_inventory_t *player_inventory)
{
    for(int i = 0; i < player-inventory->display->rows; i++){
        free(player_inventory->items[i]);
    }
    free(player_inventory->display);
    free(player_inventory);
}
