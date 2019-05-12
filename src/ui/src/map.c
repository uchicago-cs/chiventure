#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

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
void draw_room (int width, int height, int x, int y, room_t *room){
  //Calculate dimensions
  int top_len = width - 2;
  int side_ht = height -2;
  int bot_y = y+height -1;
  int right_x = x+width-1;
  int halfy = y + height/2;
  int halfx = x + width/2;

  //Draw the corners
  mvaddch(y,x,ACS_ULCORNER);
  mvaddch(y,right_x,ACS_URCORNER);
  mvaddch(bot_y,x,ACS_LLCORNER);
  mvaddch(bot_y,right_x,ACS_LRCORNER);

  //Draw the sides
  mvhline(y,x+1,ACS_HLINE,(width-2));
  mvhline(bot_y,x+1,ACS_HLINE,top_len);
  mvvline(y+1,x,ACS_VLINE,side_ht);
  mvvline(y+1,right_x,ACS_VLINE,side_ht);

  //Checks if given room has exits on each side, draws exits
  if (room->ex_e){    
    mvaddch(halfy-1,right_x,ACS_HLINE);
    mvaddch(halfy,right_x,ACS_HLINE);
  }
  if (room->ex_w){
    mvaddch(halfy-1,x,ACS_HLINE);
    mvaddch(halfy,x,ACS_HLINE);
  }
  if (room->ex_n){
    mvaddch(y,halfx-1,ACS_VLINE);
    mvaddch(y,halfx,' ');
    mvaddch(y,halfx+1,ACS_VLINE);
  }
  if (room->ex_s){
    mvaddch(bot_y,halfx-1,ACS_VLINE);
    mvaddch(bot_y,halfx,' ');
    mvaddch(bot_y,halfx+1,ACS_VLINE);
  }
}

//Takes a coordinate and an array of rooms and draws them in
void draw_rooms(room_t **rooms,int n, int left_x, int top_y){
  //Declare variables
  int x,y,x_offset,y_offset;
  int room_h = 6;
  int room_w = 11;

  //Get x,y,z coordinates for rooms
  for (int i = 0; i<n; i++){
    x = rooms[i]->loc->x;
    y = rooms[i]->loc->y;
    //z = rooms[i]->loc->z;
    
    x_offset = left_x + (room_w * x);
    y_offset = top_y + (room_h * y);

    //Draw room at x/y coordinate given, with preset w/h
    draw_room(room_w, room_h, x_offset, y_offset,rooms[i]);
  }

  return;
}

room_t ** get_test_rooms(int n){
  //Initialize a bunch of coords
  /*  coord_t loc_a = {0,0,0};
  coord_t loc_b = {0,1,0};
  coord_t loc_c = {1,0,0};
  coord_t loc_d = {2,1,0};
  coord_t loc_e = {2,2,0};*/

  //Initialize a bunch of rooms
  int j = 0;
  
  room_t **rooms = malloc(sizeof(room_t *) * n);
  for(int i = 0; i < n; i++){
    
    room_t *roomi = malloc(sizeof(room_t));
    rooms[i] = roomi;
    coord_t *loci = malloc(sizeof(coord_t));
    loci->x = i%4;
    loci->y = j;
    loci->z = 0;
    roomi->loc = loci;
    roomi->ex_e = i%2;
    roomi->ex_n = (i+1)%2;
    roomi->ex_s = i%2;
    roomi->ex_w = (i+1)%2;

    if (i%4 == 3)
      j++;
  }

  //  room_t rm_a = {loc_a, "Room A", 1,1,0,0};
  //room_t rm_b = {loc_b, "Room B", 0,1,1,1};
  //room_t rm_c = {loc_c, "Room C", 1,0,1,0};
  //room_t rm_d = {loc_d, "Room D", 0,0,0,0};
  //room_t rm_e = {loc_e, "Room E", 1,1,1,1};
  
  //Create an array of the rooms
  //room_t *rooms[5] = {&rm_a, &rm_b, &rm_c, &rm_d, &rm_e};
 
  return rooms;

}
