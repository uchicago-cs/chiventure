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
    chiventure_ctx_t *ctx = chiventure_ctx_new();

    start_ui(ctx);
}
