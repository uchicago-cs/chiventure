/*
 * This file contains the functions needed to achieve Depth
 * First Search of a list of rooms
 *
 * See coordinate.h for coordiante struct reference.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "coordinate.h"

/* Dummy function:
 * We will use the hashing functions provided by game state
 * to access these paths in each room
 */
room_t *find_room(room_t *curr, char *direction)
{
    room_t *adj = NULL;
    return adj;
}

/* assign():
 * Parameters:
 * - pointer to hash
 * - vertical_hops: Number of units north of origin
 *   (Negative if south of origin)
 * - horizontal_hops: Number of units east of origin
 *   (Negative if west of origin)
 */
int assign(coord_record_t *coordmap, int vertical_hops,
           int horizontal_hops, room_t* room)
{
    int x = try_add_coord(coordmap, vertical_hops, horizontal_hops, room);

    if(x != SUCCESS) {
        return FAILURE;
    }

    /* TO-DO:
     * We will find a better way to implement this so that
     * we do not need to malloc this string every time we
     * call the assign fcn.
     * Also, this would change if game state decides to
     * use ENUMS instead of STRING keys for the hash*/
    //char *north = (char*) malloc(6 * sizeof(char));
    //strcpy(north, "north");

    room_t *find_room_north = find_room(room, "north");
    if (find_room_north != NULL) {
        int north = assign(coordmap, vertical_hops + 1,
                           horizontal_hops, find_room_north);
        if (north == FAILURE) {
            return FAILURE;
        }
    }

    room_t *find_room_east = find_room(room, "east");
    if (find_room_east != NULL) {
        int east = assign(coordmap, vertical_hops,
                          horizontal_hops + 1, find_room_east);
        if (east == FAILURE) {
            return FAILURE;
        }
    }

    room_t *find_room_south = find_room(room, "south");
    if (find_room_south != NULL) {
        int south = assign(coordmap, vertical_hops - 1,
                           horizontal_hops, find_room_south);
        if (south == FAILURE) {
            return FAILURE;
        }
    }

    room_t *find_room_west = find_room(room, "west");
    if (find_room_south != NULL) {
        int west = assign(coordmap, vertical_hops,
                          horizontal_hops - 1, find_room_west);
        if (west == FAILURE) {
            return FAILURE;
        }
    }

    return SUCCESS;
}

/* create_valid_map:
 * Return values:
 * - Returns pointer to  hashmap of coordinates upon SUCCESS
 * - Returns NULL if unable to assign a valid coordinate system
 *   (This means create_valid_map returns NULL when assign() returns FAILURE)
 */

coord_record_t *create_valid_map(/*will pass in info from Game State*/)
{
    /*  Must set hash to NULL (see uthash documentation) */
    coord_record_t *coordmap = NULL;

    /* initial: Read initial room that player begins in out of Game State struct
     * - temporarily set to NULL while we wait on game structs
     */
    room_t *initial = NULL;

    /* Initial room must be added prior to calling assign() function
     * because null hashmap cannot be sent into assign()
     */
    coord_record_t *cr = malloc(sizeof(coord_record_t));
    memset(cr, 0, sizeof(coord_record_t));

    /* Initial coordinate is arbitrarily set to be (0,0)
     */
    cr->key.x = 0;
    cr->key.y = 0;
    cr->r = initial;

    HASH_ADD(hh, coordmap, key, sizeof(coordinate_t), cr);

    /* Testing: Can be taken out later
     * if (coordmap != NULL)
     * fprintf(stderr,
     *    "check_valid_map() has successfully added initial room to hashmap\n");
     * else
     *  fprintf(stderr,"ERR: check_valid_map could not add initial room to hashmap\n");
     * --- end testing --- */

    /* Begin DFS search */
    int r =  assign(coordmap, 0, 0, initial);
    if (r == FAILURE)
        return NULL;
    return coordmap;
}


