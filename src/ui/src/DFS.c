/*
 * This file contains the functions needed to achieve Depth
 * First Search of a list of rooms
 * See coordinate.h for coordinant struct reference.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "ui/coordinate.h"

/* assign():
 *
 * Internal function for UI
 *
 * Parameters:
 * - pointer to hash
 * - vertical_hops: Number of units north of origin
 *   (Negative if south of origin)
 * - horizontal_hops: Number of units east of origin
 *   (Negative if west of origin)
 */
int assign(coord_record_t *coordmap, int vertical_hops,
           int horizontal_hops, int up_down_hops, room_t* room)
{
    // Returns failure if coordinate has already been assigned
    int x = try_add_coord(coordmap, horizontal_hops, vertical_hops,
                          up_down_hops, room);
    if (x != SUCCESS)
    {
        return FAILURE;
    }

    // Begin Search
    room_t *find_room_north = find_room_from_dir(room, "north");
    if (find_room_north != NULL)
    {
        int north = assign(coordmap, vertical_hops + 1,
                           horizontal_hops, up_down_hops, find_room_north);
        if (north == FAILURE)
        {
            return FAILURE;
        }
    }

    room_t *find_room_east = find_room_from_dir(room, "east");
    if (find_room_east != NULL)
    {
        int east = assign(coordmap, vertical_hops,
                          horizontal_hops + 1, up_down_hops, find_room_east);
        if (east == FAILURE)
        {
            return FAILURE;
        }
    }

    room_t *find_room_south = find_room_from_dir(room, "south");
    if (find_room_south != NULL)
    {
        int south = assign(coordmap, vertical_hops - 1,
                           horizontal_hops, up_down_hops, find_room_south);
        if (south == FAILURE)
        {
            return FAILURE;
        }
    }

    room_t *find_room_west = find_room_from_dir(room, "west");
    if (find_room_west != NULL)
    {
        int west = assign(coordmap, vertical_hops,
                          horizontal_hops - 1, up_down_hops, find_room_west);
        if (west == FAILURE)
        {
            return FAILURE;
        }
    }

    room_t *find_room_up = find_room_from_dir(room, "up");
    if (find_room_up != NULL)
    {
        int up = assign(coordmap, vertical_hops, horizontal_hops,
                        up_down_hops + 1, find_room_up);
        if (up == FAILURE)
        {
            return FAILURE;
        }
    }

    room_t *find_room_down = find_room_from_dir(room, "down");
    if (find_room_down != NULL)
    {
        int down = assign(coordmap, vertical_hops, horizontal_hops,
                          up_down_hops - 1, find_room_down);
        if (down == FAILURE)
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}

// See coordinate.h for details
coord_record_t *create_valid_map(game_t *game)
{
    if (game == NULL)
    {
        return NULL;
    }

    if (game->curr_room == NULL)
    {
        return NULL;
    }

    //  Must set hash to NULL (see uthash documentation)
    coord_record_t *coordmap = NULL;

    room_t *initial = game->curr_room;

    /* Initial room must be added prior to calling assign() function
     * because null hashmap cannot be sent into assign()
     */
    coord_record_t *cr = malloc(sizeof(coord_record_t));
    assert(cr != NULL);
    memset(cr, 0, sizeof(coord_record_t));

    // Initial coordinate is arbitrarily set to be (0,0)
    cr->key.x = 0;
    cr->key.y = 0;
    cr->key.z = 0;
    cr->r = initial;

    HASH_ADD(hh, coordmap, key, sizeof(coord_t), cr);
    assert(coordmap != NULL);

    // Begin DFS search
    int r =  assign(coordmap, 0, 0, 0, initial);

    if (r == FAILURE)
    {
        return NULL;
    }
    return coordmap;
}
