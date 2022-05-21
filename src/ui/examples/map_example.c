#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include "common/ctx.h"
#include "ui/ui_ctx.h"
#include "game-state/room.h"

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



    game_t *game = game_new("Starting the game");
    assert (game != NULL);
    ui_ctx_t *ui_ctx = ui_ctx_new(game);

    chiventure_ctx_t *ctx = chiventure_ctx_new();

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
        set_player_loc(ctx, cur_x, cur_y, cur_z);
        map_center_on(ctx, cur_x, cur_y, cur_z);
    }

    //Ends the ncurses UI
    endwin();

    chiventure_ctx_free(ctx);    
    return 0;
}
