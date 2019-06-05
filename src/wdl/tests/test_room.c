#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "load_room.h"

/*
 * add_rooms_check
 * helper functions for checking whether the designated rooms from
 * the document object are correctly loaded into a game struct
 */
game_t *add_rooms_check()
{
    // get the document object located in FILE_PATH and create a new
    // game pointer
    obj_t *doc = get_doc_obj(ROOM_PATH);
    game_t *g = game_new("Welcome to UChicago");

    // check adding rooms to the game pointer
    int rc = add_rooms_to_game(doc, g);
    cr_assert_eq(rc, SUCCESS, "adding rooms to game failed");

    // return the game pointer for further access in tests
    return g;
}

/*
 * check_room_descs
 * helper functions for checking the short and long descriptions of
 * a certain room struct
 * Parameters:
 * - pointer to game
 * - string ID of specific room
 * - sdesc comparison string
 * - ldesc comparison string
 * Side Effects:
 * - asserts whether the sdesc and ldesc match the sdesc and ldesc of
 *   given room ID string
 */
void check_room_descs(game_t *g, char *id, char *sdesc, char *ldesc)
{
    // find room from the game
    room_t *r = find_room_from_game(g, id);

    // obtain the sdesc and ldesc to compare with the parameter strings
    char *scmp = get_sdesc(r);
    char *lcmp = get_ldesc(r);

    // first check sdesc
    int rc = strncmp(sdesc, scmp, strlen(sdesc));
    cr_assert_eq(rc, SUCCESS, "failed to parse sdesc of %s", id);

    // next check ldesc
    rc = strncmp(ldesc, lcmp, strlen(lcmp));
    cr_assert_eq(rc, SUCCESS, "failed to parse ldesc of %s", id);
}

/*
 * eck
 * helper function for checking add_connections_to_rooms
 * returns a game pointer containing the added connections and rooms
 */
 game_t *add_conns_check()
 {
     // first add rooms to game  and ensure it has run correctly
     obj_t *doc = get_doc_obj(ROOM_PATH);
     game_t *g = game_new("Welcome to UChicago");

     int rc = add_rooms_to_game(doc, g);
     cr_assert_eq(rc, SUCCESS, "adding rooms to game failed");

     // next add connections to room and ensure it has run correctly
     rc = add_connections_to_rooms(doc, g);
     cr_assert_eq(rc, SUCCESS, "adding connections to rooms failed");

     return g;
 }

/*
 * check_conns
 * helper function for checking connections via path searching to find a
 * room and comparing the room_id found to the known connection id
 * Parameters:
 * - pointer to game
 * - string ID of specific room
 * - string direction pertaining to above room
 * - string ID of connected room
 * Side Effects:
 * - asserts whether the inputted id of connected room matches the outputted
 *   connected room ID
 */
void check_conns(game_t *g, char *origin, char *dir, char *dest)
{
    // find room pertaining to the origin ID
    room_t *r = find_room_from_game(g, origin);

    // search for the path of the origin room
    path_t *p = path_search(r, dir);

    // initialize the outputted destination room ID
    char *to_id = p->dest->room_id;

    // compare the values of to_id and dest
    int rc = strncmp(to_id, dest, strlen(dest));
    cr_assert_eq(rc, SUCCESS, "failed to parse connection");
}

/*
 * check to see if rooms are added to game struct correctly
 * and check fields for room A
 */
Test(rooms, add_rooms_room_a)
{
    // check adding rooms and return game pointer
    game_t *g = add_rooms_check();

    // check whether room A was added correctly by comparing sdesc and ldesc
    char *id = "room A";
    char *sdesc = "This is room A";
    char *ldesc = "This is room A long";

    check_room_descs(g, id, sdesc, ldesc);
}

/* check fields for room B */
Test(rooms, add_rooms_room_b)
{
    // check adding rooms and return game pointer
    game_t *g = add_rooms_check();

    // check whether room B was added correctly by comparing sdesc and ldesc
    char *id = "room B";
    char *sdesc = "This is room B";
    char *ldesc = "This is room B long";

    check_room_descs(g, id, sdesc, ldesc);
}

/* check fields for room C */
Test(rooms, add_rooms_room_c)
{
    // same process as above
    game_t *g = add_rooms_check();

    char *id = "room C";
    char *sdesc = "This is room C";
    char *ldesc = "This is room C long";

    check_room_descs(g, id, sdesc, ldesc);
}

/*
 * check to see if connections are added to game struct correctly
 * and check connection from room A to room B
 */
Test(rooms, add_connections_A_B)
{
    // add rooms and connections check
    game_t *g = add_conns_check();

    // check connection from room A to room B
    check_conns(g, "room A", "north", "room B");
}

/* check connection from room B to room C */
Test(rooms, add_connections_B_C)
{
    // same process as above test
    game_t *g = add_conns_check();

    // check connection from room B to room C
    check_conns(g, "room B", "north", "room C");
}

/* check connection from room C to room A */
Test(rooms, add_connections_C_A)
{
    // same process as above
    game_t *g = add_conns_check();

    // check connection from room B to room C
    check_conns(g, "room C", "north", "room A");
}
