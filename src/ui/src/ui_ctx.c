#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdbool.h>
#include <signal.h>
#include <assert.h>
#include "ui_ctx.h"
#include "game.h"
#include "coordinate.h"
#include "window.h"
#include "print_functions.h"
#include "map.h"

#define MAIN_WIN_NUM 1
#define MAP_WIN_NUM 2
#define INV_WIN_NUM 3

// see ui_ctx.h
ui_ctx_t *ui_ctx_new(game_t *game)
{
    assert(game != NULL);
    int init;
    ui_ctx_t *ui_ctx = (ui_ctx_t *) malloc(sizeof(ui_ctx_t));

    init = ui_ctx_init(ui_ctx, game);

    if (init == FAILURE) {
        return NULL;
    }

    return ui_ctx;
}

// see ui_ctx.h
int ui_ctx_init(ui_ctx_t *ui_ctx, game_t *game)
{
    assert(ui_ctx != NULL);
    assert(game != NULL);
    initscr();

    int height = LINES / 2;
    int width = COLS;

    window_t *map_win = window_new(height, width, 0, 0, print_map, true);
    window_t *main_win = window_new(height, width, 0, 0, print_info, true);
    window_t *displayed_win = main_win;

    window_t *cli_win = window_new(height, width, height, 0, print_cli, false);

    keypad(cli_win->w, TRUE);
    scrollok(cli_win->w, TRUE);
    wmove(cli_win->w, 0,0);

    ui_ctx->map_win = map_win;
    ui_ctx->main_win = main_win;
    ui_ctx->displayed_win = displayed_win;
    ui_ctx->cli_win = cli_win;

    ui_ctx->curr_page = MAIN_WIN_NUM;
    ui_ctx->cli_top = 0;

    /* This field will be NULL if a logical coordinate
     * system cannot be assigned
     */
    //ui_ctx->coord_hash = create_valid_map(game);
    ui_ctx->coord_hash = get_test_coord_hash();

    // Initial room coordinates always set to 0, 0, 0
    coord_t *initial_coord = coord_new(0, 0, 0);
    ui_ctx->player_loc = initial_coord;

    ui_ctx->map = map_init();

    return SUCCESS;
}

// see ui_ctx.h
int ui_ctx_free(ui_ctx_t *ui_ctx)
{
    assert(ui_ctx != NULL);

    window_free(ui_ctx->map_win);
    window_free(ui_ctx->main_win);
    window_free(ui_ctx->cli_win);
    free(ui_ctx->player_loc);

    coord_record_t *coord_hash, *item, *temp;
    coord_hash = ui_ctx->coord_hash;
    HASH_ITER(hh, coord_hash, item, temp) {
        HASH_DEL(coord_hash, item);
        free(item);
    }

    free(ui_ctx);

    return 0;
}

// see ui_ctx.h
void toggle_map(chiventure_ctx_t *ctx)
{
    if(ctx->ui_ctx->curr_page == MAP_WIN_NUM) {
        ctx->ui_ctx->curr_page = MAIN_WIN_NUM;
        ctx->ui_ctx->displayed_win = ctx->ui_ctx->main_win;

        window_t *win = ctx->ui_ctx->displayed_win;
        int height = LINES / 2;
        int width = COLS;
        wresize(win->w, height,width);
    } else {
        ctx->ui_ctx->curr_page = MAP_WIN_NUM;
    }

}

// see ui_ctx.h
void layout_switch(chiventure_ctx_t *ctx)
{
    int cli_top = !ctx->ui_ctx->cli_top;
    ctx->ui_ctx->cli_top = cli_top;

    int height = LINES / 2;
    int width = COLS / 2;

    mvwin(ctx->ui_ctx->cli_win->w, !(cli_top) * height, 0);
    mvwin(ctx->ui_ctx->main_win->w, (cli_top) * height, 0);
    if (ctx->ui_ctx->curr_page == MAP_WIN_NUM) {
        map_set_displaywin(ctx->ui_ctx->map, 0, cli_top * height, width,
                           height + cli_top * height);
        map_center_on(ctx, 0, 0, 0);
    }

}
