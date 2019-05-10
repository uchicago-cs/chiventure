#include "map.h"

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
    mvaddch(y,halfx-2,ACS_VLINE);
    mvaddch(y,halfx-1,' ');
    mvaddch(y,halfx,ACS_VLINE);
  }
  if (room->ex_s){
    mvaddch(bot_y,halfx-2,ACS_VLINE);
    mvaddch(bot_y,halfx-1,' ');
    mvaddch(bot_y,halfx,ACS_VLINE);
  }
}

//Takes a coordinate and an array of rooms and draws them in
void draw_rooms(int top_y, int left_x, room_t **rooms, int n){
  //Declare variables
  int x,y,z,x_offset,y_offset;
  int room_h = 6;
  int room_w = 12;

  //Get x,y,z coordinates for rooms
  for (int i = 0; i<n; i++){
    x = rooms[i]->loc.x;
    y = rooms[i]->loc.y;
    z = rooms[i]->loc.z;
    
    x_offset = left_x + (room_w * x);
    y_offset = top_y + (room_h * y);

    //Draw room at x/y coordinate given, with preset w/h
    draw_room(room_w, room_h, x_offset, y_offset,rooms[i]);
  }

  return;
}
