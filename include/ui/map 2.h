#ifndef MAP_H
#define MAP_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "common/ctx.h"

// Forward declaration
typedef struct chiventure_ctx chiventure_ctx_t;


/* The map struct holds a lot of crucial information for the performance
 * of all of the map functions
 */

typedef struct map {
    WINDOW *pad;
    int n;
    int xoff;
    int yoff;
    int maxx;
    int maxy;
    int maxz;
    int padx;
    int pady;
    int padz;
    int ulx;
    int uly;
    int lrx;
    int lry;
    int room_h;
    int room_w;
} map_t;

/* Initiates map at WINDOW * pointer to pad
 *
 * Inputs: N/A
 * Outputs:
 * - A pointer to a new, initialized, map struct
 */
map_t *map_init();

/* Sets the portion of the map to be displayed on screen
 *
 * Inputs:
 * - map: a pointer to an initialized map struct
 * - ulx, uly, lrx, lry, Screen coordinates for the upper left x,y and
 * lower right x,y for the map display
 * Outputs:
 * - an integer indicating success
 */
int map_set_displaywin(map_t *map, int ulx, int uly, int lrx, int lry);

/* Updates the map to display with given col/row number as the pad's upper left corner
 *
 * Inputs:
 * - ctx: The game's ctx struct
 * - x, y, and z: the pad coordinates to be the upper left corner of display
 *
 * Outputs:
 * - 0
 */
int map_refresh(chiventure_ctx_t *ctx, int x, int y, int z);

/* Updates the map to display with given room coordinates at center
 *
 * Inputs:
 * - ctx: The game's ctx struct
 * - x, y, and z: The room coordinates of the room at the center of the new display
 *
 * Outputs:
 * - 0
 */
int map_center_on(chiventure_ctx_t *ctx, int x, int y, int z);

#endif
