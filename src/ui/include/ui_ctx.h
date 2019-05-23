#ifndef UI_CTX_H
#define UI_CTX_H

#include "window.h"
/*
 * UI context struct.  Contains the following fields:
 *  - map_win : contains the map
 *  - main_win : main window. May contain images or other info about the game
 *  - cli_win : window that contains the CLI. It's always displayed
 *  - displayed_win : window that is diplayed along with the CLI.
 */
typedef struct ui_ctx
{
    window_t *map_win;
    window_t *main_win;
    window_t *displayed_win;

    window_t *cli_win;

//    map_t *map;

    coord_t *player_loc;
    coord_record_t *coord_hash;

} ui_ctx_t;


/*
 * Crates a new UI context struct
 *
 * No parameters
 *
 * Returns the created UI context struct
 */
ui_ctx_t *ui_ctx_new();


/*
 * Initializes the values of a UI context struct.
 *
 * Each window is initialized with a height of half the terminal size and the width
 * of the terminal size. The map_win and the main_win are intially placed on
 * the top half of the terminal, while the cli_win is placed on the bottom half
 * displayed_win is intially set to main_win.
 *
 * No parameters
 *
 * Returns the created UI context struct
 */
int ui_ctx_init(ui_ctx_t *ui_ctx);

int ui_ctx_free(ui_ctx_t *ui_ctx);




#endif
