#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

//This is a test coordinate struct
/* These two test structs will be replaced with real structs
one communication with gamestate and calculation of coordinates
is complete*/
typedef struct coord{
  int x;
  int y;
  int z;
} coord_t;

//typdef struct coord coord_t;

//This is a test room struct, simulates gamestate's room struct
typedef struct room{
  struct coord *loc;
  char *name;
  char ex_w;
  char ex_e;
  char ex_n;
  char ex_s;
} room_t;

//This struct holds the pointer to the map's pad, the pad's max x and max y
// and max z coordinates
typedef struct map{
  WINDOW *pad;
  int maxx;
  int maxy;
  int maxz;
  int padx;
  int pady;
  int ul_x;
  int ul_y;
  int lr_x;
  int lr_y;
} map_t;

//Function Declarations

//Initializes the ncurses indow
void init();

//Erases a char in a specific location
void erase_ch(int y, int x);

//Draws a room at coordinates x,y of width 'witdh' and height 'height'
void draw_room(int width, int height, int x, int y, room_t *room, WINDOW *win);

//Draws a list of rooms starting at the coordinate given
void draw_rooms(room_t **rooms, int n, int left_x, int top_y, WINDOW *win);


//Gets an array of test rooms
room_t **get_test_rooms(int n);

//Initiates map at WINDOW * pointer to pad
map_t *init_map(room_t **rooms, int n);
