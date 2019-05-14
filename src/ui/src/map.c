
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
  //  keypad(stdscr, TRUE);
  curs_set(0);
  return ;
}


//Erase a character
void erase_ch (int y, int x){
  mvaddch(y,x,'#');
}

//Draw a single room
void draw_room (int width, int height, int x, int y, room_t *room, WINDOW *win){
  fprintf(debug,"Drawing room with w %i, h %i at (%i,%i)\n",width,height,x,y);
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
void draw_rooms(room_t **rooms,int n, int left_x, int top_y, int z,map_t *map){
  //Declare variables
  int x,y,zroom,x_offset,y_offset;

  //Get x,y,z coordinates for rooms
  for (int i = 0; i<n; i++){
    x = rooms[i]->loc->x;
    y = rooms[i]->loc->y;
    zroom = rooms[i]->loc->z;

    if (zroom == z){
      x_offset = left_x + (room_w * x);// + map->xoff;
      y_offset = top_y + (room_h * y);// + map->yoff;
    
    //Draw room at x/y coordinate given, with preset w/h
    // fprintf(debug,"Drawing room at x %i, y %i\n",x_offset, y_offset);
    draw_room(room_w, room_h, x_offset, y_offset,rooms[i],map->pad);
    }
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
  xyz[0] = x+1;
  xyz[1] = y+1;
  xyz[2] = z+1;
  fprintf(debug,"Dims %i, %i, %i\n",xyz[0],xyz[1],xyz[2]);
  return xyz;
}

map_t *map_init(room_t ** rooms, int n){
  int xoffset = 10;
  int yoffset = 5;
  
  //map_dims[0] is xmax, map_dims[1] is ymax, and map_dims[2] is zmax
  int *dims = calculate_map_dims(rooms,n);
  int maxx = dims[0] * room_w + 2*xoffset;
  int maxy = dims[1] * room_h + 2*yoffset;
  WINDOW *pad = newpad(maxy,maxx);
  map_t *map = malloc(sizeof(map_t));
  map->rooms = rooms;
  map->n = n;
  map->pad = pad;
  map->xoff = xoffset;
  map->yoff = yoffset;
  map->maxx = maxx;
  map->maxy = maxy;
  map->maxz = dims[2];
  map->padx = xoffset;
  map->pady = yoffset;
  map->padz = 0;
  map->ulx = 0;
  map->uly = 0;
  map->lrx = 0;
  map->lry = 0;

  keypad(pad, TRUE);
  draw_rooms(rooms,n,xoffset,yoffset,0,map);
  return map;
}

int map_set_displaywin(map_t *map, int ulx, int uly, int lrx, int lry){
  map->ulx = ulx;
  map->uly = uly;
  map->lrx = lrx;
  map->lry = lry;
  fprintf(debug,"Display Window Set With\nMap Struct maxx %i, maxy %i\nulx %i, uly %i, lrx %i, lry %i\n",map->maxx,map->maxy,ulx,uly,lrx,lry);
  fprintf(debug,"Padx %i, Pady %i Map xoff %i, yoff %i\n",map->padx, map->pady,map->xoff, map->yoff);
  return 0;
}

int map_refresh(map_t *map, int x, int y, int z){
  // touchwin(map->pad);
  if (z != map->padz){
    wclear(map->pad);
    draw_rooms(map->rooms,map->n,map->xoff,map->yoff,z,map);
  }
  
  map->padx = x;
  map->pady = y;
  map->padz = z;
  //fprintf(debug, "Debugging refresh\n padx %i, pady %i\n",x,y);
  prefresh(map->pad, y,x,map->uly,map->ulx,map->lry,map->lrx);
  return 0;
}

int map_crefresh(map_t *map, int x, int y, int z){
  int ulx = map->ulx;
  int uly = map->uly;
  int lrx = map->lrx;
  int lry = map->lry;
  int centx = (lrx+ulx)/2;
  int centy = (lry+uly)/2;
  int centxc = centx - (room_w/2);
  int centyc = centy - (room_h/2);
  int padx = room_w*x + map->xoff - centxc;
  int pady = room_h*y + map->yoff - centyc;

  map_refresh(map, padx, pady,z);
  //  prefresh(map->pad, padx,pady,uly,ulx,lry,lrx);
  return 0;
}

room_t ** get_test_rooms(int n){
  int j = 0;
  
  room_t **rooms = malloc(sizeof(room_t *) * n);
  for(int i = 0; i < (n-2); i++){
    
    room_t *roomi = malloc(sizeof(room_t));
    rooms[i] = roomi;
    coord_t *loci = malloc(sizeof(coord_t));
    loci->x = i%9;
    loci->y = j;
    loci->z = 0;
    roomi->loc = loci;
    roomi->ex_e = i%2;
    roomi->ex_n = (i+1)%2;
    roomi->ex_s = i%2;
    roomi->ex_w = (i+1)%3;

    if (i%7 == 5)
      j++;
  }
  
  coord_t *coorda  = malloc(sizeof(coord_t));
  coorda->x = 0;
  coorda->y = 0;
  coorda->z = 1;
  room_t *rooma = malloc(sizeof(room_t));
  rooma->loc = coorda;
  rooma->ex_e = 0;
  rooma->ex_w = 0;
  rooma->ex_s = 1;
  rooma->ex_n = 0;

  coord_t *coordb  = malloc(sizeof(coord_t));
  coordb->x = 0;
  coordb->y = 1;
  coordb->z = 1;
  room_t *roomb = malloc(sizeof(room_t));
  roomb->loc = coordb;
  roomb->ex_e = 0;
  roomb->ex_w = 0;
  roomb->ex_s = 0;
  roomb->ex_n = 1;

  rooms[n-2] = rooma;
  rooms[n-1] = roomb;
  return rooms;
}
