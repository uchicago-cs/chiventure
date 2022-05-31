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


#include "../include/game-state/stats.h"
#include "raylib.h"
#include "common.h"
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
graphics_t* new_graphics(display_dimensions_t *dimensions, camera_t *camera,
    inventory_display_t *inventory, statistics_display_t *statistics);


/*
 * Initializes a graphics structure
 *
 * Parameters:
 * - an initialized dimensions struct
 * - an initialized camera struct
 * - an initialized inventory struct
 * - an initialized statistics struct
 * - an uninitialized graphics strucuture
 *     
 * Returns:
 * - an integer indicating success
 */
int init_graphics(graphics_t *graphics, display_dimensions_t *dimensions, camera_t *camera, 
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
display_dimensions_t* new_display_dimensions(unsigned int width,
    unsigned int height);


/*
 * Frees a display structure from the heap
 *
 * Parameters:
 * - a pointer to a display structure on the heap
 *
 * Returns:
 * - int on success or failure 
 */
int free_display_dimensions(display_dimensions_t *display_dimensions);


/*
 * Initializes a display structure
 *
 * Parameters:
 * - an uninitialized dimensions sturcture
 * - an integer for the width
 * - an integer for the height
 *
 * Returns:
 * - an integer for success
 */
int init_display_dimensions(display_dimensions_t *dimensions, unsigned int width, unsigned int height);


/*
 * Allocates and initializes a camera structure on the heap
 *
 * Parameters:
 * - window width
 * - window height
 *
 * Returns:
 * - a pointer to the camera structure on the heap
 */
camera_t* new_camera(unsigned int width, unsigned int height);


/*
 * Initializes a camera structure
 *
 * Parameters:
 * - an uninitialized camera structure
 * - an integer for camera width
 * - an integer for camera height
 *
 * Returns:
 * - an integer value for success
 */
int init_camera(camera_t *camera, unsigned int width, unsigned int height);


/*
 * Frees a camera structure from the heap
 *
 * Parameters:
 * - a pointer to a cameray structure on the heap
 *
 * Returns:
 * - int on success or failure 
 */
int free_camera(camera_t *camera);


/*
 * Allocates and initializes an inventory structure on the heap
 *
 * Parameters:
 * - number of rows
 * - number of solumns
 * - the background color of the display
 *
 * Returns:
 * - a pointer to the inventory structure on the heap
 */
inventory_display_t* new_inventory_display(unsigned int rows,
    unsigned int columns, color color);


/* 
 * Initializes and uninitialized inventory display struct
 *
 * Parameters:
 * - an uninitialized inventory display structure
 * - the number of rows
 * - the number of columns
 * - the background color of the inventory display
 *
 * Returns:
 * - an integer indicating success
 */
int init_inventory_display(inventory_display_t* inventory, unsigned int rows, unsigned int columns, color color);


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
statistics_display_t* new_statistics_display(corner corner, stats_t *statistics,
    unsigned int num_statistics, mode mode);


/* 
 * Initializes and uninitialized statustic display struct
 *
 * Parameters:
 * - an uninitialized statistic display structure
 * - the number of statistics
 * - the array of statistic values
 * - the corner in which to display the statistics
 * - an array of modes corresponding to each statistic
 *
 * Returns:
 * - an integer indicating success
 */
int init_statistics_display(statistics_display_t* statistics_display, corner corner,
    stats_t *statistics,unsigned int num_statistics, mode mode);
                           
 
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
