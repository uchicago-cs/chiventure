#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

    //Allocates & Initializes map struct
    map_t *map = map_init(rooms, num_rooms);
    //Set the screen location of the map
    map_set_displaywin(map, 0,0,COLS,LINES-1);
    //Refresh the map centered on room 0,0,0
    map_center_on(map, 0,0,0);

    char ch;
    while (true) {
        ch = wgetch(map->pad);
        ch = tolower(ch);

        if (ch == 'w') {
            cur_y -= incr;
        }
        if (ch == 's') {
            cur_y += incr;
        }
        if (ch == 'a') {
            cur_x -= incr;
        }
        if (ch == 'd') {
            cur_x += incr;
        }
        if (ch == 'u') {
            cur_z += 1;
        }
        if (ch == 'i') {
            cur_z -= 1;
        }
        if (ch == 'q') {
            break;
        }
        map_center_on(map,cur_x,cur_y,cur_z);
    }

    //Ends the ncurses UI
    endwin();

    return 0;
}
