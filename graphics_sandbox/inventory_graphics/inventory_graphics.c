#include "raylib.h"
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
    for (unsigned int i = 0; i < graphics->inventory->rows; i++){
        inv[i] = (item_t*)malloc(sizeof(item_t) * graphics->inventory->columns;
    }

    while (itemlst->next != NULL){
        inv[itemlst->item->inventory_x_pos][itemlst->item->inventory_y_pos]
            = itemlst->item;
        itemlst = itemlst->next;    
    }
    inv[itemlst->item->inventory_x_pos][itemlst->item->inventory_y_pos] == itemlst->item;
    itemlst = itemlst->next;
    return inv;
}


/* See inventory_graphics.h */
player_inventory_t *new_player_inventory(graphics_t *graphics, player_t *p)
{
    player_inventory_t *inventory;
    inventory = (player_inventory_t*)malloc(sizeof(player_inventory_t);
    
    inventory->display = graphics->inventory;
    inventory->items = populate_items(p, graphics);

    return inventory;
}


/* See inventory_graphics.h */
int free_player_inventory(player_inventory_t *player_inventory)
{
    for(int i = 0; i < player-inventory->display->rows; i++){
        free(player_inventory->items[i]);
    }
    free(player_inventory->items);
    free(player_inventory->display);
    free(player_inventory);
    return 0;
}


/* See inventory_graphics.h */
void add_item_inventory(player_inventory_t *player_inventory, item_t *item)
{
    change = 0;
    for(int i; i < player_inventory->display->rows; i++) {
        for(int j; j < player_inventory->display->columns; j++) {
            if (player_inventory->slots[i][j].status == EMPTY) {
                player_inventory->items[i][j] = item;
                change = 1;
                break;
            }
        }
        if (change == 1) {
            break;
        }
    }
    if (change == 0) {
        fprintf(stderr, "inventory full");
    }
    return;
}


/* See inventory_graphics.h */
void draw_player_inventory(player_inventory_t *player_inventory);


/* See inventory_graphics.h */
void remove_item_inventory(player_inventory_t *player_inventory, item_t *item)
{
    if (player_inventory->slots[item->inventory_x_pos][item->inventory_y_pos].status != EMPTY) {
        free(player_inventory->items[item->inventory_x_pos][item->inventory_y_pos]);
    } else {
        fprintf(stderr, "inventory empty at position (%d,%d)\n", item->inventory_x_pos, item->inventory_y_pos);
    }
    return;
}