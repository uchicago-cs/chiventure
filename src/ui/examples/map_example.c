#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "map.h"

int main()
{
    ncurses_init();


    int cur_x = 0;
    int cur_y = 0;
    int cur_z = 0;
    int incr = 1;
    int num_rooms = 100;
    room_t ** rooms = get_test_rooms(num_rooms);

    map_t *map = map_init(rooms, num_rooms);
    map_set_displaywin(map, 0,0,COLS,LINES-1);




    map_refresh(map, 0,0,0);


    //draw_rooms(rooms,num_rooms,0,0,pad);


    char ch;
    while(true)
    {
        ch = wgetch(map->pad);
        if(ch == 'w' || ch == 'W')
        {
            cur_y -= incr;
            // map_refresh(map,cur_x,cur_y,cur_z);
            map_crefresh(map,cur_x,cur_y,cur_z);
        }
        if(ch == 'S' || ch == 's')
        {
            cur_y += incr;
            //      map_refresh(map,cur_x,cur_y,cur_z);
            map_crefresh(map,cur_x,cur_y,cur_z);
        }

        if(ch == 'a' || ch == 'A')
        {
            cur_x -= incr;
            //      map_refresh(map,cur_x,cur_y,cur_z);
            map_crefresh(map,cur_x,cur_y,cur_z);
        }
        if(ch == 'd' || ch == 'D')
        {
            cur_x += incr;
            //      map_refresh(map,cur_x,cur_y,cur_z);
            map_crefresh(map,cur_x,cur_y,cur_z);
        }
        if(ch == 'u' || ch == 'U')
        {
            cur_z += 1;
            //map_refresh(map,cur_x, cur_y, cur_z);
            map_crefresh(map,cur_x,cur_y,cur_z);
        }
        if(ch == 'i' || ch == 'I')
        {
            cur_z -= 1;
            //      map_refresh(map,cur_x, cur_y, cur_z);
            map_crefresh(map,cur_x,cur_y,cur_z);
        }
        if(ch == 'c' || ch == 'C')
        {
            map_crefresh(map,0,1,1);
        }
        if(ch == 'Q'|| ch == 'q')
        {
            break;
        }

    }

    //delwin(pad);
    endwin();
    return 0;
}
