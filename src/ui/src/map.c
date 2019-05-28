#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "room.h"
#include "coordinate.h"

void ncurses_init()
{
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);
    return ;
}




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

    // Checks if given room has exits on each side, draws exits
    /* TO- DO -- Update using Game State function to check exits
    if (room->ex_e) {
        mvwaddch(win, halfy-1, right_x, ACS_HLINE);
        mvwaddch(win, halfy, right_x, ACS_HLINE);
    }
    if (room->ex_w) {
        mvwaddch(win, halfy-1, x, ACS_HLINE);
        mvwaddch(win, halfy, x, ACS_HLINE);
    }
    if (room->ex_n) {
        mvwaddch(win, y, halfx-1, ACS_VLINE);
        mvwaddch(win, y, halfx,' ');
        mvwaddch(win, y, halfx+1, ACS_VLINE);
    }
    if (room->ex_s) {
        mvwaddch(win, bot_y, halfx-1, ACS_VLINE);
        mvwaddch(win, bot_y, halfx, ' ');
        mvwaddch(win, bot_y, halfx+1, ACS_VLINE);
    }
    */
}

// Takes a coordinate and an array of rooms and draws them in
void draw_rooms(room_t **rooms, int n, int left_x, int top_y, int z, map_t *map)
{
    // Declare variables
    int x, y, zroom, x_offset, y_offset;
    int room_h = map->room_h;
    int room_w = map->room_w;

    // Get x, y, z coordinates for rooms
    /* Fixed in map-from-coords feature branch
    for (int i = 0; i < n; i++) {
        x = rooms[i]->loc->x;
        y = rooms[i]->loc->y;
        zroom = rooms[i]->loc->z;

        if (zroom == z) {
            x_offset = left_x + (room_w * x);
            y_offset = top_y + (room_h * y);

            // Draw room at x/y coordinate given, with preset w/h
            draw_room(room_w, room_h, x_offset, y_offset,rooms[i],map->pad);
       }
    }
    */
    return;
}

int *calculate_map_dims(room_t **rooms, int n)
{
    int x = 0;
    int y = 0;
    int z = 0;
    coord_t *curr;
    int cx;
    int cy;
    int cz;

    for (int i = 0; i < n; i++) {
        /* TO-DO -- Will have to reach into coord hash, not room structs,
            to access coordinates. This will be fixed in map-from-coords feature branch

            curr = rooms[i]->loc;

        cx = curr->x;
            cy = curr->y;
            cz = curr->z;
            if (cx > x){
                x = cx;
        }
            if (cy > y){
                y = cy;
        }
            if (cz > z){
                z = cz;
        }
        */
    }

    int *xyz = malloc(sizeof(int) * 3);
    xyz[0] = x + 1;
    xyz[1] = y + 1;
    xyz[2] = z + 1;
    return xyz;
}

map_t *map_init(room_t **rooms, int n)
{
    int xoffset = 0;
    int yoffset = 0;

    // map_dims[0] is xmax, map_dims[1] is ymax, and map_dims[2] is zmax
    int *dims = calculate_map_dims(rooms, n);
    int maxx = COLS;
    int maxy = LINES-1;
    WINDOW *pad = newpad(maxy, maxx);
    map_t *map = malloc(sizeof(map_t));
    map->rooms = rooms;
    map->n = n;
    map->room_h = 6;
    map->room_w = 11;
    map->pad = pad;
    map->xoff = xoffset;
    map->yoff = yoffset;
    map->maxx = maxx;
    map->maxy = maxy;
    map->maxz = dims[2];
    map->padx = xoffset;
    map->pady = yoffset;
    map->padz = 0;
    map->ulx = 0;
    map->uly = 0;
    map->lrx = 0;
    map->lry = 0;

    keypad(pad, TRUE);


    draw_rooms(rooms, n, xoffset, yoffset, 0, map);
    free(dims);
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

int map_refresh(map_t *map, int x, int y, int z)
{
    if (z != map->padz || x != map->padx || y != map->pady) {
        wclear(map->pad);
        draw_rooms(map->rooms, map->n, -x, -y, z, map);
    }

    map->padx = x;
    map->pady = y;
    map->padz = z;

    prefresh(map->pad, 0, 0, map->uly, map->ulx, map->lry, map->lrx);
    return 0;
}

int map_center_on(map_t *map, int x, int y, int z)
{
    int room_h = map->room_h;
    int room_w = map->room_w;
    int ulx = map->ulx;
    int uly = map->uly;
    int lrx = map->lrx;
    int lry = map->lry;
    int centx = (lrx - ulx) / 2;
    int centy = (lry - uly) / 2;
    int centxc = centx - (room_w / 2);
    int centyc = centy - (room_h / 2);
    int padx = room_w * x - centxc;
    int pady = room_h * y - centyc;

    map_refresh(map, padx, pady, z);
    return 0;
}

// TO-DO -- Fix this with new room stucts

room_t **get_test_rooms(int n)
{
    /*
      int j = 0;
      int k = 0;
      room_t **rooms = malloc(sizeof(room_t *) * n);
      for (int i = 0; i < (n - 2); i++) {

          room_t *roomi = malloc(sizeof(room_t));
          rooms[i] = roomi;

          coord_t *loci = malloc(sizeof(coord_t));
          loci->x = i % 12;
          loci->y = j;
          loci->z = k;
          roomi->loc = loci;
          roomi->ex_e = i % 2;
          roomi->ex_n = (i + 1) % 2;
          roomi->ex_s = i % 2;
          roomi->ex_w = (i + 1) % 3;

          if (i % 10 == 5) {
              j++;
          }
          if (i % 13 == 8) {
              k++;
          }
          if (i % 13 == 10) {
              k--;
          }
      }

      coord_t *coorda = malloc(sizeof(coord_t));
      coorda->x = 0;
      coorda->y = 0;
      coorda->z = 1;
      room_t *rooma = malloc(sizeof(room_t));
      rooma->loc = coorda;
      rooma->ex_e = 0;
      rooma->ex_w = 0;
      rooma->ex_s = 1;
      rooma->ex_n = 0;

      coord_t *coordb = malloc(sizeof(coord_t));
      coordb->x = 0;
      coordb->y = 1;
      coordb->z = 1;
      room_t *roomb = malloc(sizeof(room_t));
      roomb->loc = coordb;
      roomb->ex_e = 0;
      roomb->ex_w = 0;
      roomb->ex_s = 0;
      roomb->ex_n = 1;

      rooms[n - 2] = rooma;
      rooms[n - 1] = roomb;
      return rooms;
    */

}
