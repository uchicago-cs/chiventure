#ifndef UI_CTX_H
#define UI_CTX_H

#include "map.h"
#include "game-state/game.h"
#include "game-state/room.h"
#include "window.h"
#include "coordinate.h"

//Forward Declaration
typedef struct map map_t;
typedef struct coord coord_t;
typedef struct coord_record coord_record_t;

/*
 * UI context struct.  Contains the following fields:
 *  - map: instance of the map struct that contains map information
 *  - player_loc: current player location
 *  - coord_hash: a pointer to the head of a hash map that matches
 *                coordinate keys to room pointers
 *  - map_win: contains the map
 *  - main_win: main window. May contain images or other info about the game
 *  - cli_win: window that contains the CLI. It's always displayed
 *  - displayed_win: window that is diplayed along with the CLI.
 *  - curr_page: indicates what page to be displayed
 *  - cli_top: indicates if the CLI will be on top
 */
typedef struct ui_ctx {
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
 * - NULL upon FAILURE
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
 * - ui_ctx : ui context struct to be initialized
 * - game : a pointer to the game_t struct
 * Returns:
 * - SUCCESS if every field can be initialized
 * - FAILURE if there is a problem
 *
 * Note:
 * - If a logical coordmap cannot be created, ui_ctx_init will
 *   still fill in ui_ctx, but the coord_hash field will be NULL
 */
int ui_ctx_init(ui_ctx_t *ui_ctx, game_t *game);

/*
 * Frees the given ui_ctx struct and associated resources
 *
 * Parameters:
 *   - ui_ctx: ui context struct to be freed
 *
 * Always returns 0
 */
int ui_ctx_free(ui_ctx_t *ui_ctx);


/*
 * Switches between the map and the main window
 *
 * Parameters:
 *    - ctx : chiventure context struct
 *
 * Does not return anything
 *
 */
void toggle_map(chiventure_ctx_t *ctx);


/*
 * Switches the location of the CLI from top to bottom and veceversa
 *
 * Parameters:
 *    - ctx : chiventure context struct
 *
 * Does not return anything
 *
 */
void layout_switch(chiventure_ctx_t *ctx);




#endif
