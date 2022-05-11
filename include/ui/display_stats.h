#ifndef DISPLAY_STATS_H
#define DISPLAY_STATS_H

#include "stats.h"
#include "player.h"
#include "game.h"

/* 
 * Note:
 *
 * Of the statistics and information availible to the user 
 * in the game, a set number will be displayed on screen 
 * (as space is limited) and the remainder (a full set 
 * of details) will be accessible via the command line
 */

/* The set of types of on-screen information displays */
typedef union on_screen_stat {
    int num;
    char* identifier;
    stats_hast_t stat;
} on_screen_stat;

/* 
 * Define screen statistics by its window coordinates,
 * the number of stats shown, and the stats themselves 
 */
typedef struct screen_stats {
    int ulx;
    int uly;
    int lrx;
    int lry;
    int num_stats;
    on_screen_stat *screen_stats;
} screen_stats_t;

/* The set of types for pop-up windows */
enum pop_up_type {CLASS, STATS, SKILLS, EFFECTS, INVENTORY, MOVES};
typedef enum pop_up_type pop_up_type;

/*
 * Define the pop-up screen by its window coordinates, 
 * the information it presents, and the concerning player
 */
typedef struct pop_up {
    int ulx;
    int uly;
    int lrx;
    int lry;
    pop_up_type type;
    player_t *player;
} pop_up_t;


/*
 * Creates and initializes a screen_stats struct
 *
 * Parameters:
 * - Screen coordinates of the display (upper left x and lower right x and y):
 *   ulx,uly,rlx,rly
 * - The stats to be displayed on screen as specified in the WDL file 
 * - The number of stats on screen
 *
 * Returns:
 * - a pointer to an initialized screen_stat struct
 *
 * Note:
 * - This will require new functionality from the WDL file to allow
 *   the game authors to specify what stats they want displayed
 *   and then a function to translate that information as input
 *   (into an array on on-screen_stats) for graphics purposes
 */
screen_stats_t* set_screen_stats(int ulx, int uly, int lrx, int lry, int num_stats, on_screen_stat *stats);


/*
 * Displays stats on screen
 *
 * Parameters:
 * - an initialized screen_stats struct
 *
 * Returns:
 * - an integer indicating success
 */
int draw_screen_stats(screen_stats_t *screen_stats);


/*
 * Updates the screen statistics struct
 * when an appearing stat is affected
 *
 * Parameters:
 * - an player struct 
 * - the to be updated screen statisitcs struct
 *
 * Returns:
 * -an integer indicating sucess
 *
 * Note:
 * It is unclear as of now who is responsible for keeping the
 * graphics presented on the screen. If it is our responsability
 * then another function will be needed to call the update and
 * redraw the statistics but recieve input on when statistics need
 * to be adjusted
 */ 
screen_stats_t* update_screen_stats(player_t *player, screen_stats_t *screen_stats);

/*
 * Creates and initializes a pop-up struct with specified type
 *
 * Parameters:
 * - Screen coordinates of the display (upper left x and lower right x and y):
 *   ulx, uly, lrx, lry
 * - The type of pop-up (specifies what information the pop-up will present)
 * - The player the pop-up will refer to
 *
 * Returns:
 * - The intialized struct
 */
pop_up_t* set_pop_up(int ulx, int uly, int lrx, int lry, pop_up_type type, player_t player);

/*
 * Draws the specified pop up window to screen
 *
 * Parameters:
 * - a pop-up struct
 *
 * Returns:
 * - an integer indicating success
 */
int open_pop_up(pop_up_t pop_up);


/*
 * Closes the pop-up window displayed on the screen
 *
 * Parameters:
 * - None
 *
 * Retruns:
 * - An integer indicating sucess
 */
int close_pop_up();


#endif
