#ifndef UI_H
#define UI_H

#include "common/ctx.h"


#define MIN_COLS 80
#define MIN_ROWS 24

/* start_gui
 * Starts the gui and runs the game loop.
 *
 * Parameters:
 *    - ctx : chiventure context struct
 *    - banner : chiventure banner to be shown in the home screen
 *
 * No value is returned
 */
void start_gui(chiventure_ctx_t *ctx, const char *banner);

#endif

