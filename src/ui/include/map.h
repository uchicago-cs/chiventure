#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

//This is a test coordinate struct
/* These two test structs will be replaced with real structs
one communication with gamestate and calculation of coordinates
is complete*/
struct coord{
  int x;
  int y;
  int z;
};
typdef struct coord coord_t;

//This is a test room struct, simulates gamestate's room struct

//Function Declarations

//Erases a char in a specific location
void erase_ch(int y, int x);

//Draws a room at coordinates x,y of width 'witdh' and height 'height'
void draw_room(int width, int height, int x, int y, room_t* room);

//Draws a list of rooms starting at the coordinate given
void draw_rooms(int topy, int left_x, room_t **rooms, int n);

