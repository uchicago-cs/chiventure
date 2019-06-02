/*
* A two-dimensional coordinate data structure
* and corresponding hashmap
*/

#ifndef INCLUDE_COORDINATE_H_
#define INCLUDE_COORDINATE_H_

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include "uthash.h"

#define SUCCESS 1 
#define FAILURE 0 

struct room;

/* A dummy struct to mimic the hash that we expect
 * game state to create, based on their communication with us!
 */

typedef struct {
    // direction
    char *key;
    // adjacent room in that direction
    struct room *adj;
    UT_hash_handle hh;
} room_hash_t;

// Dummy room struct
typedef struct room {
    int id;
    room_hash_t hash;
} room_t;

/* Dummy function called find_room()
 * Will be integrating with Game State's real function
 * for Sprint 3 task
 *
 * PURPOSE:
 * This function goes into current room and checks
 * if a room exists in that direction.
 * i.e.: Is there a room to the North?
 *
 * Will use game state's hash table
 * Returns:
 * - pointer to room if room exists in that direction
 * - NULL if no room in that direction
 */

room_t *find_room(room_t *curr, char *direction);

// A coordinate in two-dimensional space
typedef struct {
    int x;
    int y;
} coordinate_t;

/* Structure to make coordinate hashable
 * Defines a coordinate_t as the key
 */
typedef struct coord_record {
    coordinate_t key;
    room_t *r;
    UT_hash_handle hh;
} coord_record_t;

// Initialize coordinate_t struct
void coord_init(coordinate_t *c, int x, int y);

/* find_coord():
 * - Implementation will use HASH_FIND to find coord_record
 * - Internal fcn only
 *
 * Input:
 * - coordmap: a pointer to the coordinate hash (internal to UI)
 * - x, y: Integer values (locations) of room one
 *   wishes to find in hash. Values are determined by internal
 *   DFS algorithm (Initial room is assigned 0,0)
 *
 * Returns:
 * - returns coord_record_t struct (which contains a room pointer) if room
 *   exists at that coordinant key
 * - returns NULL if key not in hash
 */
coord_record_t *find_coord(coord_record_t *coordmap, int x, int y);

/* try_add_coord():
 * Parameters:
 * - coordmap is both an in and out parameter, so must be non-NULL
 * - x, y are the respective coordinates. They will be bundled
 *  into a coordinate key for hashing
 * - r is a pointer to the room to assign the coords to
 *
 * Return value:
 * - returns SUCCESS if does not find coordinate and add its
 * - returns FAILURE if it finds coordinate already and
 *   the coord is mapped to a different room
 *
 * Note:
 * - Printing debug statements to a seperate txt file
 *
 * Info on struct keys from uthash guide:
 * https://troydhanson.github.io/uthash/userguide.html#_structure_keys
 */
int try_add_coord(coord_record_t *coordmap, int x, int y, room_t *r);


/* create_valid_map():
 * - will be called on as soon as game is loaded in by WDL and Game State
 *
 * Parameters: TO-DO
 * - Will Pass in info from WDL/gamestate. Likely will take in
 *   a game state context struct. (Sprint 3)
 *
 * Return values:
 * - Returns pointer to hashmap of coordinates upon SUCCESS
 * - Returns NULL if unable to assign a valid coordinate system
 *   (This means create_valid_map returns NULL when assign() returns FAILURE)
 */
coord_record_t *create_valid_map();


#endif /* INCLUDE_COORDINATE_H_ */
