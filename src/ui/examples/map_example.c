#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ctx.h"
#include "ui_ctx.h"

int main()
{
    ncurses_init();

    int cur_x = 0;
    int cur_y = 0;
    int cur_z = 0;
    int incr = 1;

    // Sample Rooms
    room_t *room1 = room_new("One", "", "");
    room_t *room2 = room_new("Two", "", "");
    room_t *room3 = room_new("Three", "", "");
    room_t *room4 = room_new("Four", "", "");

    //  Must set hash to NULL (see uthash documentation)
    coord_record_t *coordmap = NULL;
    
    coord_record_t *head = malloc(sizeof(coord_record_t));
    memset(cr, 0, sizeof(coord_record_t));

    // Initial coordinate is arbitrarily set to be (0,0)
    head->key.x = 0;
    head->key.y = 0;
    head->r = room1;
    HASH_ADD(hh, coordmap, key, sizeof(coordinate_t), head);

    try_add_coord(coordmap, 0, 1, room2);
    try_add_coord(coordmap, 0, 2, room3);
    try_add_coord(coordmap, 1, 1, room4);
    game_t *game = game_new();
    ui_ctx_t *ui_ctx = ui_ctx_new(game);

    /* Game State functions needed for DFS not complete at this stage,
     * so we will disregard the coord hash created in ui_ctx_new 
     * (which does not work yet) and instead create use own mini coord hash
     */
    ui_ctx->coord_hash = coordmap;
    
    // Set the screen location of the map
    map_set_displaywin(ui_ctx->map, 0, 0, COLS, LINES-1);
    // Refresh the map centered on room 0,0,0
    map_center_on(ui_ctx->map, 0, 0, 0);

    char ch;
    while (true) {
        ch = wgetch(ui_ctx->map->pad);
        ch = tolower(ch);

        if (ch == 'w') {
            cur_y -= incr;
        }
        if (ch == 's') {
            cur_y += incr;
        }
        if (ch == 'a') {
            cur_x -= incr;
        }
        if (ch == 'd') {
            cur_x += incr;
        }
        if (ch == 'u') {
            cur_z += 1;
        }
        if (ch == 'i') {
            cur_z -= 1;
        }
        if (ch == 'q') {
            break;
        }
        map_center_on(ui_ctx->map, cur_x, cur_y, cur_z);
    }

    //Ends the ncurses UI
    endwin();

    return 0;
}
