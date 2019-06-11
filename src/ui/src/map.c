#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "room.h"
#include "coordinate.h"
#include "common.h"
#include "ctx.h"
#include "ui.h"

void erase_ch(int y, int x)
{
    mvaddch(y, x, '#');
}

/* Draw a single room at exact location within a window
 *
 * Inputs:
 * - width, height: Width and height of the room to be drawn
 * - x,y: Column and Row numbers of the room's upper left corder
 * - room: room's room struct (THIS IS A TEST STRUCT)
 * - win: window pointer to draw window
 */
void draw_room(int width, int height, int x, int y, room_t *room, WINDOW *win)
{
    // Calculate dimensions
    int top_len = width - 2;
    int side_ht = height -2;
    int bot_y = y+height -1;
    int right_x = x+width-1;

    /* These are commented because they are only used for drawing exits
     * We will add them back in once merged with Game State, so we would
     * like to keep this commented code here
     */
    int halfy = y + height/2;
    int halfx = x + width/2;

    // Draw the corners
    mvwaddch(win, y, x, ACS_ULCORNER);
    mvwaddch(win, y, right_x, ACS_URCORNER);
    mvwaddch(win, bot_y, x, ACS_LLCORNER);
    mvwaddch(win, bot_y, right_x, ACS_LRCORNER);

    // Draw the sides
    mvwhline(win, y, x+1, ACS_HLINE, (width-2));
    mvwhline(win, bot_y, x+1, ACS_HLINE, top_len);
    mvwvline(win, y+1, x, ACS_VLINE, side_ht);
    mvwvline(win, y+1, right_x, ACS_VLINE, side_ht);

    if (find_room_from_dir(room, "east") != NULL) {
        mvwaddch(win, halfy-1, right_x, ACS_HLINE);
        mvwaddch(win, halfy, right_x, ACS_HLINE);
    }
    if (find_room_from_dir(room, "west") != NULL) {
        mvwaddch(win, halfy-1, x, ACS_HLINE);
        mvwaddch(win, halfy, x, ACS_HLINE);
    }
    if (find_room_from_dir(room, "north") != NULL) {
        mvwaddch(win, y, halfx-1, ACS_VLINE);
        mvwaddch(win, y, halfx,' ');
        mvwaddch(win, y, halfx+1, ACS_VLINE);
    }
    if (find_room_from_dir(room, "south") != NULL) {
        mvwaddch(win, bot_y, halfx-1, ACS_VLINE);
        mvwaddch(win, bot_y, halfx, ' ');
        mvwaddch(win, bot_y, halfx+1, ACS_VLINE);
    }
}

/* Draws all of the rooms stored in the hashmap of the ui_ctx given
 *
 * Inputs: 
 * - ctx: The game's ctx struct
 * - left_x: the top, left coordinate of the top-left most room
 * - top_y: the top left coordinate of the top-left-most room
 * - z: the z coordinate of the floor being draw (0 is ground floor)
 * 
 * Outputs:
 * - Draws the rooms to the screen
 *
 * Note: Map and ctx structs must be initialized before calling
 */
void draw_rooms(chiventure_ctx_t *ctx, int left_x, int top_y, int z)
{
    assert(ctx != NULL);
    assert(ctx->ui_ctx != NULL);

    // Declare variables
    coord_record_t *itr;
    map_t *map = ctx->ui_ctx->map;
    int x, y, zroom, x_offset, y_offset;
    int room_h = map->room_h;
    int room_w = map->room_w;

    // Get x, y, z coordinates for rooms

    //Temporary integer to count loop
    int temp = 1;
    for (itr = ctx->ui_ctx->coord_hash; itr != NULL; itr=itr->hh.next) {
        //Temporary:
        temp++;

        zroom = itr->key.z;
        x = itr->key.x;
        y = itr->key.y;

        if (zroom == z) {
            x_offset = left_x + (room_w * x);
            y_offset = top_y + (room_h * y);

            // Draw room at x/y coordinate given, with preset w/h
            draw_room(room_w, room_h, x_offset, y_offset, itr->r, map->pad);
        }
    }

    return;
}

map_t *map_init()
{
    int xoffset = 0;
    int yoffset = 0;
    int maxx = COLS;
    int maxy = LINES-1;
    WINDOW *pad = newpad(maxy, maxx);
    map_t *map = malloc(sizeof(map_t));

    map->room_h = 6;
    map->room_w = 11;
    map->pad = pad;
    map->xoff = xoffset;
    map->yoff = yoffset;
    map->maxx = maxx;
    map->maxy = maxy;
    map->maxz = 0;
    map->padx = xoffset;
    map->pady = yoffset;
    map->padz = 0;
    map->ulx = 0;
    map->uly = 0;
    map->lrx = 0;
    map->lry = 0;

    keypad(pad, TRUE);
    return map;
}

int map_set_displaywin(map_t *map, int ulx, int uly, int lrx, int lry)
{
    map->ulx = ulx;
    map->uly = uly;
    map->lrx = lrx;
    map->lry = lry;

    return 0;
}

int map_refresh(chiventure_ctx_t *ctx, int x, int y, int z)
{
    assert(ctx->ui_ctx != NULL);
    assert(ctx->ui_ctx->map != NULL);
    assert(ctx->ui_ctx->map->pad != NULL);

    map_t *map = ctx->ui_ctx->map;

    if (z != map->padz || x != map->padx || y != map->pady) {
        wclear(map->pad);

        draw_rooms(ctx, -x, -y, z);
    }

    map->padx = x;
    map->pady = y;
    map->padz = z;

    prefresh(map->pad, 0, 0, map->uly, map->ulx, map->lry, map->lrx);
    return 0;
}

int map_center_on(chiventure_ctx_t *ctx, int x, int y, int z)
{
    assert(ctx != NULL);
    assert(ctx->ui_ctx != NULL);
    assert(ctx->ui_ctx->map != NULL);
    assert(ctx->ui_ctx->map->pad != NULL);

    map_t *map = ctx->ui_ctx->map;

    // Width and height of a room
    int room_h = map->room_h;
    int room_w = map->room_w;

    // The upper left hand corner of the map display on screen
    int ulx = map->ulx;
    int uly = map->uly;
    // The lower right hand corner of the map display on screen
    int lrx = map->lrx;
    int lry = map->lry;
    //The x and y coordinates of the center of the map display screen
    int centx = (lrx - ulx) / 2;
    int centy = (lry - uly) / 2;
    /* The display coordinates of the upper left corner of the room at the
     center of the screen*/
    int centxc = centx - (room_w / 2);
    int centyc = centy - (room_h / 2);
    // The x and y offset of the map in order to put room (x, y, z) in the center
    int padx = room_w * x - centxc;
    int pady = room_h * y - centyc;

    // Pass these offsets to map_refresh
    map_refresh(ctx, padx, pady, z);
    return 0;
}

