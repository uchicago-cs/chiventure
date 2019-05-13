
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int room_h = 6;
int room_w = 11;

//Initiallizes ncurses window
//This function will later live in ui.c
void init(){
  initscr();
  clear();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(0);
  return ;
}


//Erase a character
void erase_ch (int y, int x){
  mvaddch(y,x,'#');
}

//Draw a single room
void draw_room (int width, int height, int x, int y, room_t *room, WINDOW *win){
  //Calculate dimensions
  int top_len = width - 2;
  int side_ht = height -2;
  int bot_y = y+height -1;
  int right_x = x+width-1;
  int halfy = y + height/2;
  int halfx = x + width/2;

  //Draw the corners
  mvwaddch(win,y,x,ACS_ULCORNER);
  mvwaddch(win,y,right_x,ACS_URCORNER);
  mvwaddch(win,bot_y,x,ACS_LLCORNER);
  mvwaddch(win,bot_y,right_x,ACS_LRCORNER);

  //Draw the sides
  mvwhline(win,y,x+1,ACS_HLINE,(width-2));
  mvwhline(win,bot_y,x+1,ACS_HLINE,top_len);
  mvwvline(win,y+1,x,ACS_VLINE,side_ht);
  mvwvline(win,y+1,right_x,ACS_VLINE,side_ht);

  //Checks if given room has exits on each side, draws exits
  if (room->ex_e){    
    mvwaddch(win,halfy-1,right_x,ACS_HLINE);
    mvwaddch(win,halfy,right_x,ACS_HLINE);
  }
  if (room->ex_w){
    mvwaddch(win,halfy-1,x,ACS_HLINE);
    mvwaddch(win,halfy,x,ACS_HLINE);
  }
  if (room->ex_n){
    mvwaddch(win,y,halfx-1,ACS_VLINE);
    mvwaddch(win,y,halfx,' ');
    mvwaddch(win,y,halfx+1,ACS_VLINE);
  }
  if (room->ex_s){
    mvwaddch(win,bot_y,halfx-1,ACS_VLINE);
    mvwaddch(win,bot_y,halfx,' ');
    mvwaddch(win,bot_y,halfx+1,ACS_VLINE);
  }
}

//Takes a coordinate and an array of rooms and draws them in
void draw_rooms(room_t **rooms,int n, int left_x, int top_y, WINDOW *win){
  //Declare variables
  int x,y,x_offset,y_offset;
  //  int room_h = 6;
  //int room_w = 11;

  //Get x,y,z coordinates for rooms
  for (int i = 0; i<n; i++){
    x = rooms[i]->loc->x;
    y = rooms[i]->loc->y;
    //z = rooms[i]->loc->z;
    
    x_offset = left_x + (room_w * x);
    y_offset = top_y + (room_h * y);

    //Draw room at x/y coordinate given, with preset w/h
    draw_room(room_w, room_h, x_offset, y_offset,rooms[i],win);
  }
  return;
}

int *calculate_map_dims(room_t **rooms, int n){
  int x=0;
  int y=0;
  int z=0;
  coord_t *curr;
  int cx;
  int cy;
  int cz;
  
  for (int i = 0; i < n; i++){
    curr = rooms[i]->loc;
    cx = curr->x;
    cy = curr->y;
    cz = curr->z;
    if (cx > x)
      x = cx;
    if (cy>y)
      y = cy;
    if (cz>z)
      z = cz;
  }
  int *xyz = malloc(sizeof(int)*3);
  xyz[0] = x;
  xyz[1] = y;
  xyz[2] = z;
  return xyz;
}

map_t *init_map(room_t ** rooms, int n){
  //map_dims[0] is xmax, map_dims[1] is ymax, and map_dims[2] is zmax
  int *dims = calculate_map_dims(rooms,n);
  WINDOW *pad = newpad(dims[1],dims[0]);
  map_t *map = malloc(sizeof(map_t));
  map->pad = pad;
  map->maxx = dims[0];
  map->maxy = dims[1];
  map->maxz = dims[2];
  draw_rooms(rooms,n,0,0,pad);

  return map;
}

room_t ** get_test_rooms(int n){
  int j = 0;
  
  room_t **rooms = malloc(sizeof(room_t *) * n);
  for(int i = 0; i < n; i++){
    
    room_t *roomi = malloc(sizeof(room_t));
    rooms[i] = roomi;
    coord_t *loci = malloc(sizeof(coord_t));
    loci->x = i%8;
    loci->y = j;
    loci->z = 0;
    roomi->loc = loci;
    roomi->ex_e = i%2;
    roomi->ex_n = (i+1)%2;
    roomi->ex_s = i%2;
    roomi->ex_w = (i+1)%2;

    if (i%6 == 5)
      j++;
  }
 
  return rooms;
}
