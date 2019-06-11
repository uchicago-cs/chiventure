#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include "ctx.h"
#include "ui_ctx.h"
#include "room.h"

/* Initializes the ncurses window
 *
 * Inputs: N/A
 *
 * Outputs:N/A
 */
void ncurses_init()
{
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);
    return ;
}

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
    assert(head != NULL);
    memset(head, 0, sizeof(coord_record_t));

    // Initial coordinate is arbitrarily set to be (0,0)
    head->key.x = 0;
    head->key.y = 0;
    head->key.z = 0;
    head->r = room1;
    HASH_ADD(hh, coordmap, key, sizeof(coord_t), head);
    assert(coordmap != NULL);

    try_add_coord(coordmap, 0, 1, 0, room2);
    try_add_coord(coordmap, 0, 2, 0, room3);
    try_add_coord(coordmap, 1, 1, 0, room4);


    game_t *game = game_new("Starting the game");
    assert (game != NULL);
    ui_ctx_t *ui_ctx = ui_ctx_new(game);

    chiventure_ctx_t *ctx = chiventure_ctx_new();

    /* This example tests without a loaded game stuct, so
     * the coord_hash is set manually.
     */
    ctx->ui_ctx->coord_hash = coordmap;


    // Set the screen location of the map
    map_set_displaywin(ctx->ui_ctx->map, 0, 0, COLS, LINES-1);


    // Refresh the map centered on room 0,0,0
    map_center_on(ctx, 0, 0, 0);

    char ch;
    while (true) {
        ch = wgetch(ctx->ui_ctx->map->pad);
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
        map_center_on(ctx, cur_x, cur_y, cur_z);
    }

    //Ends the ncurses UI
    endwin();

    return 0;
}
