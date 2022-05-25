#ifndef GUI_H
#define GUI_H

#include "common/ctx.h"

#define MAX_INPUT_CHARS 20
#define POS_ZERO 0
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 500
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 700


/* run_gui
 * Runs the gui and runs the game loop.
 *
 * Parameters:
 *    - ctx : chiventure context struct
 *
 * No value is returned
 */
void run_gui(chiventure_ctx_t *ctx);

#endif