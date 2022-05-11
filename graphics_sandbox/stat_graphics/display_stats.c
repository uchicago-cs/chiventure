#include "ui/display_stats.h"
#include "raylib.h"

/* See display_stats.h for details */
screen_stats_t* set_screen_stats(int ulx, int uly, int lrx, int lry, int num_stats, on-screen_stat *stats);

/* See display_stats.h for details */
int draw_screen_stats(screen_stats_t *screen_stats);

/* See display_stats.h for details */
screen_stats_t* update_screen_stats(player_t *player, screen_stats_t *screen_stats);

/* See display_stats.h for details */
pop-up_t* set_pop-up(int ulx, int uly, int lrx, int lry, pop-up_type type, player_t player);

/* See display_stats.h for details */
int open_pop-up(pop-up_t pop-up);

/* See display_stats.h for details */
int close_pop-up();
