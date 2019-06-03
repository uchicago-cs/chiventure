#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdbool.h>
#include <signal.h>
#include "window.h"
#include "ui.h"
#include "ctx.h"


int main()
{
  //game_t *game = game_new("Starting the game");
  //assert (game != NULL);
    chiventure_ctx_t *ctx = chiventure_ctx_new();
    ctx->ui_ctx->coord_hash = get_test_coord_hash();
    
    start_ui(ctx);
}
