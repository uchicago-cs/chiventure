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
#include <stdio.h>
#include <stdlib.h>


/* Contains the display_dimensions for all pop-up windows */
typedef struct display_dimensions {
    unsigned int width;
    unsigned int height;
} display_dimensions_t;


/* This includes camera size information to display scenes */
typedef struct camera {
    unsigned int width;
    unsigned int height;
} camera_t;


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
    PINK
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
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
} corner;


typedef enum mode {
    NUMERICAL,
    GEOMETRICAL,
    GRAPHICAL
} mode;


typedef struct statistics_display {
    corner corner;
    stats_t *statistics;
    unsigned int num_statistics;
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
    camera_t *camera;
    inventory_display_t *inventory;
    statistics_display_t *statistics;
} graphics_t;

/*
 * Allocates and initializes a graphics struct
 *
 * Parameters:
 * - an initialized dimensions struct
 * - an initialized camera struct
 * - an initialized inventory struct
 * - an initialized statistics struct
 *
 * Returns:
 * - a pointer to the graphics struct on the heap
 */
graphics_t* make_graphics(display_dimensions_t *dimensions, camera_t *camera,
    inventory_display_t *inventory, statistics_display_t *statistics);


/*
 * Reads through a gdl file to allocate and initialize a graphics structure
 * 
 * Parameters:
 * - the gdl file
 *
 * Returns:
 * - a graphics struct whose fields correspond to specifications of the author
 */
graphics_t* read_gdl();


/*
 * frees a graphics structure from the heap
 *
 * Parameters:
 * - a pointer to a graphics structure on the heap
 *
 * Returns:
 * - int on success or failure 
 */
int free_graphics(graphics_t* graphics);


/*
 * allocates and initializes a display structure on the heap
 *
 * Parameters:
 * - window width
 * - window height
 *
 * Returns:
 * - a pointer to the display structure on the heap
 */
display_dimensions_t* make_display_dimensions(unsigned int width,
    unsigned int height);


/*
 * frees a display structure from the heap
 *
 * Parameters:
 * - a pointer to a display structure on the heap
 *
 * Returns:
 * - int on success or failure 
 */
int free_display_dimensions(display_dimensions_t *display_dimensions);

/*
 * allocates and initializes a camera structure on the heap
 *
 * Parameters:
 * - window width
 * - window height
 *
 * Returns:
 * - a pointer to the camera structure on the heap
 */
camera_t* make_camera(unsigned int width, unsigned int height);


/*
 * frees a camera structure from the heap
 *
 * Parameters:
 * - a pointer to a cameray structure on the heap
 *
 * Returns:
 * - int on success or failure 
 */
int free_camera(camera_t *camera);

/*
 * allocates and initializes an inventory structure on the heap
 *
 * Parameters:
 * - number of rows
 * - number of solumns
 * - the background color of the display
 *
 * Returns:
 * - a pointer to the inventory structure on the heap
 */
inventory_display_t* make_inventory_display(unsigned int rows,
    unsigned int columns, color color);


/*
 * frees an inventory structure from the heap
 *
 * Parameters:
 * - a pointer to an inventory structure on the heap
 *
 * Returns:
 * - int on success or failure 
 */
int free_inventory_display(inventory_display_t *inventory_display);


/*
 * allocates and initializes a statistics structure on the heap
 *
 * Parameters:
 * - the corner if the screne it will reside in
 * - an array of statistics to be displayed
 * - the number of statstics to be displayed
 * - the mode (represenation) of the statistcs
 *
 * Returns:
 * - a pointer to the inventory structure on the heap
 */
statistics_display_t* make_statistics_display(corner corner, stats_t *statistics,
    unsigned int num_statistics, mode mode);


/*
 * frees a statistics structure from the heap
 *
 * Parameters:
 * - a pointer to a statistics structure on the heap
 *
 * Returns:
 * - int on success or failure 
 */
int free_statistics_display(statistics_display_t *statistics_display);


#endif
