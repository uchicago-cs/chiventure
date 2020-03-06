#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include <assert.h>
#include <locale.h>

#include "ui/ui_ctx.h"
#include "ui/coordinate.h"
#include "ui/window.h"
#include "ui/print_functions.h"
#include "ui/map.h"

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

    if (init == FAILURE)
    {
        return NULL;
    }

    return ui_ctx;
}

// see ui_ctx.h
int ui_ctx_init(ui_ctx_t *ui_ctx, game_t *game)
{
    assert(ui_ctx != NULL);
    assert(game != NULL);

    /* This field will be NULL if a logical coordinate
     * system cannot be assigned
     */
    ui_ctx->coord_hash = create_valid_map(game);

    // Failsafe: Draws very basic map so that program does not crash
    if (ui_ctx->coord_hash == NULL)
    {
        ui_ctx->coord_hash = get_test_coord_hash();
    }
    // Initial room coordinates always set to 0, 0, 0
    coord_t *initial_coord = coord_new(0, 0, 0);
    ui_ctx->player_loc = initial_coord;

    return SUCCESS;
}

// see ui_ctx.h
int ui_ctx_free(ui_ctx_t *ui_ctx)
{
    assert(ui_ctx != NULL);

    free(ui_ctx->player_loc);

    coord_record_t *coord_hash, *item, *temp;
    coord_hash = ui_ctx->coord_hash;
    HASH_ITER(hh, coord_hash, item, temp)
    {
        HASH_DEL(coord_hash, item);
        free(item);
    }

    free(ui_ctx);

    return 0;
}

// see ui_ctx.h
void toggle_map(chiventure_ctx_t *ctx)
{
    if(ctx->ui_ctx->curr_page == MAP_WIN_NUM)
    {
        ctx->ui_ctx->curr_page = MAIN_WIN_NUM;
        ctx->ui_ctx->displayed_win = ctx->ui_ctx->main_win;

        window_t *win = ctx->ui_ctx->displayed_win;
        int height = LINES / 2;
        int width = COLS;
        wresize(win->w, height,width);
    }
    else
    {
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
    if (ctx->ui_ctx->curr_page == MAP_WIN_NUM)
    {
        map_set_displaywin(ctx->ui_ctx->map, 0, cli_top * height, width,
                           height + cli_top * height);
        map_center_on(ctx, 0, 0, 0);
    }

}
