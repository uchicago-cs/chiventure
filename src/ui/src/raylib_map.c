#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

#include "ui/ui_ctx.h"
#include "ui/coordinate.h"
#include "ui/raylib_map.h"

//ncurses function that isn't used anywhere, delete?//
/*void erase_ch(int y, int x)
{
    mvaddch(y, x, '#');
}*/

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
    //int top_len = width - 2;
    //int side_ht = height -2;
    int bot_y = y+height -1;
    int right_x = x+width-1;

   // Calculations for door start/end x-positions
    int door_start_h = x + width / 3;
    int door_end_h = x + 2 * width / 3;

    // Calculations for door start/end y-positions
    int door_start_v = y + height / 3;
    int door_end_v = y + 2 * height / 3; 

    BeginDrawing();

    ClearBackground(BLACK);

    // Draw the room as a rectangle
    DrawRectangle(x, y, width, height, GRAY);

    // Draws any doors to adjacent rooms
    if (find_room_from_dir(room, "east") != NULL)
    {
        DrawLine(right_x, door_start_v, right_x, door_end_v, BLACK);
    }
    if (find_room_from_dir(room, "west") != NULL)
    {
        DrawLine(x, door_start_v, x, door_end_v, BLACK);
    }
    if (find_room_from_dir(room, "north") != NULL)
    {
        DrawLine(door_start_h, y, door_end_h, y, BLACK);
    }
    if (find_room_from_dir(room, "south") != NULL)
    {
        DrawLine(door_start_h, bot_y, door_end_h, bot_y, BLACK);
    }

    EndDrawing();
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
    for (itr = ctx->ui_ctx->coord_hash; itr != NULL; itr=itr->hh.next)
    {
        //Temporary:
        temp++;

        zroom = itr->key.z;
        x = itr->key.x;
        y = itr->key.y;

        if (zroom == z)
        {
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

    //Hard coded value, needs change?//
    map->room_h = 6;
    //Hard coded value, needs change?//
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

/* See map.h for documentation */
int map_set_displaywin(map_t *map, int ulx, int uly, int lrx, int lry)
{
    map->ulx = ulx;
    map->uly = uly;
    map->lrx = lrx;
    map->lry = lry - 1;

    return 0;
}

/* Draws info to the top left corner of the map view
 *
 * Inputs:
 * - The context struct
 *
 * Outputs: N/A
 */
void draw_info(chiventure_ctx_t *ctx)
{
    ui_ctx_t *ui_ctx = ctx->ui_ctx;
    map_t *map = ui_ctx->map;
    coord_t *curr_pos = ui_ctx->player_loc;

    int info_x = map->ulx + 2;
    int info_y = map->uly + 1;

    // Draws floor and position information on map display
    //2 is text size and is placeholder//
    DrawText("(%i, %i) Floor %i", curr_pos->x, curr_pos->y, curr_pos->z, info_x, info_y, 2, WHITE);
    return;
}

/* Draws the border on the map view
 *
 * Inputs:
 * - The chiventure context struct
 *
 * Outputs: N/A
 */
void draw_border(chiventure_ctx_t *ctx)
{
    ui_ctx_t *ui_ctx = ctx->ui_ctx;
    map_t *map = ui_ctx->map;
    WINDOW *win = map->pad;

    int ulx = map->ulx; // Upper left x
    int uly = map->uly; // Upper left y
    int lrx = map->lrx - 1; // Lower Right x
    int lry = map->lry; // Lower Right y

    BeginDrawing();

    // Draws the border as a rectangle
    DrawRectangle(ulx, uly, lrx - ulx, lry - ulr, WHITE);

    EndDrawing();

    return;
}


int map_refresh(chiventure_ctx_t *ctx, int x, int y, int z)
{
    assert(ctx->ui_ctx != NULL);
    assert(ctx->ui_ctx->map != NULL);
    assert(ctx->ui_ctx->map->pad != NULL);

    map_t *map = ctx->ui_ctx->map;

    if (z != map->padz || x != map->padx || y != map->pady)
    {
        wclear(map->pad);
        //Why are the x and y values negative here??//
        draw_rooms(ctx, -x, -y, z);
    }

    // Set the pad values in the map struct
    map->padx = x;
    map->pady = y;
    map->padz = z;


    //The x and y coordinates of the center of the map display screen
    int centx = (map->lrx - map->ulx) / 2;
    int centy = (map->lry - map->uly) / 2;

    BeginDrawing();

    // Draws the 'player' on to the screen
    //Look into what the radius should be, 2 is placeholder//
    DrawCircle(centx, centy, 2, WHITE);

    EndDrawing();

    draw_border(ctx);
    draw_info(ctx);

    //An ncurses function that I don't know what to do with//
    prefresh(map->pad, 0, 0, map->uly, map->ulx, map->lry, map->lrx);
    return 0;
}

/* See map.h for documentation */
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

