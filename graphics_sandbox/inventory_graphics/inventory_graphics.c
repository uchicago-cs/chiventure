#include "raylib.h"
#include "inventory_graphics.h"

player_inventory_t *new_player_inventory(graphics_t *graphics)
{
    player_inventory_t *inventory = (player_inventory_t)malloc(sizeof(player_inventory_t);

    inventory->display->rows = graphics->inventory->rows;
    inventory->display->columns = graphics->inventory->columns;
    inventory->display->color = graphics->inventory->color;
}
