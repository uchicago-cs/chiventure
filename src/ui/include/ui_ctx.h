#ifndef UI_CTX_H
#define UI_CTX_H

#include "game.h"
#include "window.h"
#include "coordinate.h"
#include "map.h"


/*
 * UI context struct.  Contains the following fields:
 *  - map_win : contains the map
 *  - main_win : main window. May contain images or other info about the game
 *  - cli_win : window that contains the CLI. It's always displayed
 *  - displayed_win : window that is diplayed along with the CLI.
 *  - coord_hash: a pointer to the head of a hash map that matches
 *                coordinate keys to room pointers
 */
typedef struct ui_ctx
{
    map_t *map;
    coord_t *player_loc;
    coord_record_t *coord_hash;
    window_t *map_win;
    window_t *main_win;
    window_t *displayed_win;
    window_t *cli_win;
    int curr_page;
    int cli_top;

} ui_ctx_t;


/*
 * Crates a new UI context struct
 *
 * Parameters:
 * - a pointer to the game_t struct
 *
 * Returns:
 * - The created UI context struct upon SUCCESS
 * - NULL upon FAILURE (cannot be allocated or
 *   cannot assign logical  coordinates)
 */
ui_ctx_t *ui_ctx_new(game_t *game);


/*
 * Initializes the values of a UI context struct.
 *
 * Each window is initialized with a height of half the terminal size and the width
 * of the terminal size. The map_win and the main_win are intially placed on
 * the top half of the terminal, while the cli_win is placed on the bottom half
 * displayed_win is intially set to main_win.
 *
 * Parameters
 * - a pointer to the game_t struct
 * Returns:
 * - SUCCESS if every field can be initialized and a logical
 *   coordinate system can be assigned to each room
 * - FAILURE if a logical coordinate system cannot be assigned
 */
int ui_ctx_init(ui_ctx_t *ui_ctx, game_t *game);


int ui_ctx_free(ui_ctx_t *ui_ctx);

void toggle_map(chiventure_ctx_t *ctx);

void layout_switch(chiventure_ctx_t *ctx);




#endif
