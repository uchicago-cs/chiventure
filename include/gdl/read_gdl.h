#ifndef READ_GDL
#define READ_GDL

/*
 * This is a Graphics Description Language
 * reading device
 *
 * Authors can describe preferred graphical
 * styles and features by writing a "GDL"
 * file in JSON format according to a set
 * of just a few rules
 */

#include "stats.h"

/* Contains the display_dimensions for all pop-up windows */
typedef struct display_dimensions {
    unsigned int width;
    unsigned int height;
} display_dimensions_t;


/* The set of background colors availible for the inventory */
typedef enum color {
    WHITE,
    GRAY,
    BLACK,
    RED,
    BLUE,
    GREEN,
    YELLOW,
    ORANGE,
    PURPLE,
    PINK,
} color;


/* 
 * This display struct contains the custom inventory 
 * represenation specified by the game developer with 
 * a set of rows and columns and a background color
 */
typedef struct inventory_display {
    unsigned int rows;
    unsigned int columns;
    color color;
} inventory_display_t;


typedef enum corner {
    TOP_LEFT;
    TOP_RIGHT;
    BOTTOM_LEFT;
    BOTTOM_RIGHT;
} corner;


typedef enum mode {
    NUMERICAL;
    GEOMETRICAL;
    GRAPHICAL;
} mode;


typedef struct statistics_display {
    corner corner;
    stats_t *statistics;
    mode mode;
} statistics_display_t;


/* 
 * Defines a large struct that contains all of the information
 * specified by the game developer in the GDL file by category
 *
 * Note: At the moment, custom graphics are only availible for
 * inventory and statistics preferences 
 */
typedef struct graphics {
    display_dimensions_t *dimensions;
    inventory_display_t *inventory;
    statistics_display_t *statistics;
} graphics_t;

graphics_t* read_gdl(FILE *gdl);


display_dimensions_t init_display_dimensions(graphics_t *graphics);


void free_display_dimensions(display_dimensions_t *display_dimensions);


inventory_display_t init_inventory_display(graphics_t *graphics);


void free_inventory_display(inventory_display_t *inventory_display);


statistics_display_t init_statistics_display(statistics_display_t * statistics_display);


void free_display_statistics(statistics_display *statistics_display);


#endif
