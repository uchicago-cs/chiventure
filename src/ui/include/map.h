#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "room.h"

//Struct Declarations________________________________________________________
/*The map struct holds a lot of crucial information for the performance
  of all of the map functions*/ 
typedef struct map{
  WINDOW *pad;
  room_t **rooms;
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
} map_t;



//Function Declarations________________________________________________________
//Initializes the ncurses window
void ncurses_init();

//Erases a char in a specific location
void erase_ch(int y, int x);


//Draws a list of rooms starting at the coordinate given
void draw_rooms(room_t **rooms, int n, int left_x, int top_y,int z, map_t *map);


//Gets an array of test rooms
room_t **get_test_rooms(int n);


/*Initiates map at WINDOW * pointer to pad
 *
 *Inputs:
 * - rooms, an array of pointers to room structs
 * - n , the number of rooms in array "rooms"
 * Outputs:
 * - A pointer to a new map struct initialized with rooms and coordinates
 */
map_t *map_init(room_t **rooms, int n);

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
int map_crefresh(map_t *map, int x, int y, int z);

