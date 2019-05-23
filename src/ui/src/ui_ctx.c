#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdbool.h>
#include <signal.h>
#include <assert.h>
#include "coordinate.h"
#include "window.h"
#include "print_functions.h"
#include "map.h"
#include "ui_ctx.h"


/* see ui_ctx.h */
ui_ctx_t *ui_ctx_new()
{
    ui_ctx_t *ui_ctx = (ui_ctx_t *) malloc(sizeof(ui_ctx_t));

    ui_ctx_init(ui_ctx);

    return ui_ctx;

}

/* see ui_ctx.h */
int ui_ctx_init(ui_ctx_t *ui_ctx)
{
    assert(ui_ctx != NULL);

    int height = LINES / 2;
    int col = COLS;


    window_t *map_win = window_new(height, width, 0, 0, print_map, true);
    winodw_t *main_win = window_new(height, width, 0, 0, print_info, true);
    window_t *displayed_win = main_win;

    window_t *cli_win = window_new(height, width, height, 0, print_cli, false);

    ui_ctx->map_win = map_win;
    ui_ctx->main_win = main_win;
    ui_ctx->displayed_win = displayed_win;
    ui_ctx->cli_win = cli_win;
    ui_ctx->coord_hash = NULL;
    ui_ctx->player_loc = NULL;

    return 0;
}

/* see ui_ctx.h */
int ui_ctx_free(ui_ctx_t *ui_ctx)
{
    assert(ui_ctx_init != NULL);

    window_free(ui_ctx->map_win);
    window_free(ui_ctx->main_win);
    window_free(ui_ctx->cli_win);

    free(ui_ctx_free);

    return 0;
}
