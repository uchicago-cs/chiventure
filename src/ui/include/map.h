#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

/* These two test structs will be replaced with real structs
 * one communication with gamestate and calculation of coordinates
 * is complete
 */
typedef struct coord {
    int x;
    int y;
    int z;
} coord_t;

// This is a test room struct, simulates gamestate's room struct
typedef struct room {
    struct coord *loc;
    char *name;
    char ex_w;
    char ex_e;
    char ex_n;
    char ex_s;
} room_t;

/* The map struct holds a lot of crucial information for the performance
 * of all of the map functions
 */
typedef struct map {
    WINDOW *pad;
    int n;
    int xoff;
    int yoff;
    int maxx;
    int maxy;
    int maxz;
    int padx;
    int pady;
    int padz;
    int ulx;
    int uly;
    int lrx;
    int lry;
    int room_h;
    int room_w;
} map_t;

/* Initializes the ncurses window
 *
 * Inputs: N/A
 *
 * Outputs:N/A
 */
void ncurses_init();

/* Draws a list of rooms starting at the coordinate given
 * 
 * Inputs:
 * - rooms: an array of pointers to rooms
 * - n: the number of rooms
 * - left_x: the top left corner of the top-left most room
 * - top_y: to top left corner of the top-left-most room
 * - z: the z coordinate of the floor being drawn
 * - map: pointer to a map_t struct
 * 
 * Outputs:
 * - Draws the rooms to the scren
 */
void draw_rooms(chiventure_ctx_t *ctx, int left_x, int top_y,int z);

/* Gets an array of test rooms
 * 
 * Inputs: 
 * - n: number of rooms to generate
 * 
 * Outputs:
 * - An array of pointers to random room structs
 */
room_t **get_test_rooms(int n);

/* Initiates map at WINDOW * pointer to pad
 *
 * Inputs: N/A
 * Outputs:
 * - A pointer to a new map struct initialized with rooms and coordinates
 */
map_t *map_init();

/* Sets the portion of the map to be displayed on screen
 *
 * Inputs:
 * - map, a pointer to an initialized map struct
 * - ulx, uly, lrx, lry, Screen coordinates for the upper left x,y and
 * lower right x,y for the map display
 * Outputs:
 * - an integer indicating success
 */
int map_set_displaywin(map_t *map, int ulx, int uly, int lrx, int lry);

/* Updates the map to display with given col/row number as the pad's upper left corner
 *
 * Inputs:
 * - map, a pointer to an initialized map struct
 * - x, y, and z are the pad coordinates to be the upper left corner of display
 *
 * Outputs:
 * - 0
 */
int map_refresh(map_t *map, int x, int y, int z);

/* Updates the map to display with given room coordinates at center
 *
 * Inputs:
 * - map, a pointer to an initialized map struct
 * - x, y, and z are the room coordinates of the room at the center of the new display
 *
 * Outputs:
 * - 0
 */
int map_center_on(map_t *map, int x, int y, int z);

