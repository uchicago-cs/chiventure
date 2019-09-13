#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ui/coordinate.h"

// Checks that a given x and y-coordinate are allocated in memory within a
// coordinate struct
Test(coordinate, new)
{
    coord_t *rc;
    rc = malloc(sizeof(coord_t));
    rc = coord_new(5, 3, 7);

    cr_assert_not_null(rc, "coord_new() failed");
    cr_assert_eq(rc->x, 5, "coord_new() didn't set the coordinates's x-coordinate");
    cr_assert_eq(rc->y, 3, "coord_new() didn't set the coordinates's y-coordinate");
    cr_assert_eq(rc->z, 7, "coord_new() didn't set the coordinates's z-coordinate");
}


/*This is a helper function used in check_find_coord to check 
whether the coord_record_t given by find_coord is the same 
as the expected coord_record_t*/
int check_equal(coord_record_t *one, coord_record_t *two)
{
    //returns success when a room associated with the coordinates 
    //does not exist and find_coord returns NULL 
    if (one == NULL && two == NULL) {
        return SUCCESS;
    }
    //returns failure when a room associated with the coordinates 
    //does exist and find_coord returns NULL 
    if (one == NULL || two == NULL) {
        return FAILURE;
    }
    if (one->r->room_id == NULL && two->r->room_id == NULL) {
        return SUCCESS;
    }

    int one_x = one->key.x;
    int one_y = one->key.y;
    int one_z = one->key.z;

    int two_x = two->key.x;
    int two_y = two->key.y;
    int two_z = two->key.z;

    char *one_id = one->r->room_id;
    char *two_id = two->r->room_id;

    if (one_x == two_x && one_y == two_y && one_z == two_z && strcmp(one_id, two_id) == 0) {
        return SUCCESS;
    }
    else {
        return FAILURE;
    }

}

/* checks find_coord():
 * - Implementation uses HASH_FIND to find coord_record
 * - UI Internal fcn only
 *
 * Parameters:
 * - coordmap: a pointer to the coordinate hash (internal to UI)
 * - x, y, z: Integer values (locations) of room
 *   to search for in hash.
 * - rd_expected: the expected coordinate hash
 * - expected: denotes whether it is or is not present
 *
 * Returns:
 * - returns coord_record_t struct (which contains a room pointer) if room
 *   exists at that coordinant key
 * - returns NULL if key not in hash
 */
void check_find_coord(coord_record_t *coordmap, int x, int y, int z,
                    coord_record_t *rd_expected, int expected)
{
    coord_record_t *rd = find_coord(coordmap, x, y, z);

    int equal = check_equal(rd, rd_expected);


    if (rd_expected != NULL) {
        cr_assert_eq(equal, expected,
                     " Coordinate record %d is %s but"
                     " find_room returned %s",
                     rd_expected->r->room_id,
                     expected? "not present":"present",
                     equal? "false":"true");
    }
    else {
        cr_assert_eq(equal, expected,
                     " Coordinate record NULL is %s but"
                     " find_room returned %s",
                     expected? "not present":"present",
                     equal? "false":"true");
    }


}

// Checks that a room not present in the hash table returns NULL
Test(coordinate, not_found)
{
    coord_record_t *coordmap = NULL;
    coord_record_t *cr = malloc(sizeof(coord_record_t));
    memset(cr, 0, sizeof(coord_record_t));
    cr->key.x = 0;
    cr->key.y = 0;
    cr->key.z = 0;

    room_t *initial = room_new("123", "walk", "walk far");
    cr->r = initial;

    HASH_ADD(hh, coordmap, key, sizeof(coord_t), cr);

    check_find_coord(coordmap, 1, 2, 1, NULL, SUCCESS);
}

// Checks that a room present in the hash table returns the correct coord_record
Test(coordinate, found)
{
    coord_record_t *coordmap = NULL;
    coord_record_t *cr = malloc(sizeof(coord_record_t));
    memset(cr, 0, sizeof(coord_record_t));
    cr->key.x = 0;
    cr->key.y = 0;
    cr->key.z = 0;

    room_t *initial = room_new("125", "walk", "walk far");
    cr->r = initial;

    HASH_ADD(hh, coordmap, key, sizeof(coord_t), cr);

    check_find_coord(coordmap, 0, 0, 0, coordmap, SUCCESS);
}

/* Checks try_add_coord():
 * Parameters:
 * - coordmap is both an in and out parameter, so it must be non-NULL
 * - x, y, z are the respective coordinates. They will be bundled
 *           into a coordinate key for hashing
 * - r is a pointer to the room to assign the coords to
 * - expected denotes whether it should or should not be added 
 *
 * Return value:
 * - returns SUCCESS if:
 *           -  does not find coordinate and successfully adds it
 *           - finds coordinate and it is already mapped to the same room
 * - returns FAILURE if it finds coordinate already and
 *   the coord is mapped to a different room
 */
void check_add_coord(coord_record_t *coordmap, int x, int y, int z, room_t *r,
                     int expected)
{
    int rc;

    rc = try_add_coord(coordmap, x, y, z, r);

    cr_assert_eq(rc, expected,
                 " Room %.02f has %s but "
                 "try_add_room returned %s",
                 r->room_id,
                 expected? "not been added":"been added",
                 rc? "false":"true");
}

// Checks that a room not present in the hash table is added
Test(coordinate, added_successfully)
{
    coord_record_t *coordmap = NULL;
    coord_record_t *cr = malloc(sizeof(coord_record_t));
    memset(cr, 0, sizeof(coord_record_t));
    cr->key.x = 0;
    cr->key.y = 0;
    cr->key.z = 0;

    room_t *initial = room_new("125", "walk", "walk far");
    cr->r = initial;

    HASH_ADD(hh, coordmap, key, sizeof(coord_t), cr);

    room_t *r = room_new("24", "run", "run far");

    check_add_coord(coordmap, 3, 4, 1, r, SUCCESS);
}

// Checks that a room present in the hash table is not added
Test(coordinate, add_failure)
{
    coord_record_t *coordmap = NULL;
    coord_record_t *cr = malloc(sizeof(coord_record_t));
    memset(cr, 0, sizeof(coord_record_t));
    cr->key.x = 0;
    cr->key.y = 0;
    cr->key.z = 0;

    room_t *initial = room_new("125", "walk", "walk far");
    cr->r = initial;

    room_t *room_2 = room_new("126", "run", "run far");

    HASH_ADD(hh, coordmap, key, sizeof(coord_t), cr);

    check_add_coord(coordmap, 0, 0, 0, room_2, FAILURE);
}

// Checks that all rooms are assigned coordinates
void check_create_valid_map(game_t *game,
                            int expected)
{
    coord_record_t *end_map;
    end_map = malloc(sizeof(coord_record_t));


    end_map = create_valid_map(game);

    cr_assert_eq(end_map, expected,
                 "The map %s but "
                 "create_valid_map returned %s",
                 expected? "is not a valid map":"is a valid map",
                 end_map? "failure":"success");
}

// checks that a valid map is crated from a game struct
Test(coordinate, valid_map)
{
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("vroom1", "test room", "yes this is a test room");
    room_t *room2 = room_new("nroom", "test next door", "KND number 1");
    cr_assert_not_null(room1, "room 1 not initialized");
    cr_assert_not_null(room2, "room 2 not initialized");

    int r1 = add_room_to_game(game, room1);
    int r2 = add_room_to_game(game, room2);
    cr_assert_eq(r1, SUCCESS, "add_room_to_game: room1 failed");
    cr_assert_eq(r2, SUCCESS, "add_room_to_game: room2 failed");

    check_create_valid_map(game, SUCCESS);
}
