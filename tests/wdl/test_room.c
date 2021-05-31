#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libobj/load.h"
#include "wdl/load_room.h"
#include "test_wdl.h"

/* TODO: This should not be hardcoded here. Find a way to incorporate these
 * files into the CMake-Criterion chain */
#define ROOM_PATH "../../../tests/wdl/examples/connected_rooms.wdl"

/*
 * helper function for parsing a YAML file into an object
 */
static obj_t *__get_doc_obj()
{
    char zip_name[10 * (MAXLEN_ID + 1)] = {0};
    strcat(zip_name, TEST_OUT_PATH);
    strcat(zip_name, "zip_default.zip");

    // Create the zip
    int error = 0;
    zip_t *zip = zip_open(zip_name, ZIP_CREATE | ZIP_TRUNCATE, &error);
    cr_assert_eq(error, ZIP_ET_NONE, 
        "Could not create zip file; code: %d", error);

    // Add DEFAULT.json to the zip
    char *data_name = "DEFAULT.json";
    char *data_path = FILE_PATH;

    zip_error_t err = {0};
    zip_source_t *zip_src = zip_source_file_create(data_path, 0, 0, &err);
    cr_assert_not_null(zip_src, "Could not create zip source; code: %d", zip_error_system_type(&err));

    zip_int64_t idx = zip_file_add(zip, data_name, zip_src, ZIP_FL_ENC_UTF_8);
    cr_assert_neq(idx, -1, 
        "Could not add file to zip file; check archive code");

    // Write and save to disk
    int rc = zip_close(zip);
    zip_error_t *close = zip_get_error(zip);
    cr_assert_neq(rc, -1, 
        "Could not close zip file; check archive code: %s", zip_error_strerror(close));

    int open_status;
    zip = zip_open(zip_name, 0, &open_status);

    // Read the zip into an obj
    obj_t *obj = obj_new("doc");
    rc = load_obj_store_from_zip(obj, zip);

    return obj;
}

/*
 * add_rooms_check
 * helper functions for checking whether the designated rooms from
 * the document object are correctly loaded into a game struct
 */
game_t *add_rooms_check()
{
    // get the document object located in FILE_PATH and create a new
    // game pointer
    obj_t *doc = __get_doc_obj();
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
     obj_t *doc = __get_doc_obj();
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
    char *id = "room_A";
    char *sdesc = "This is room A";
    char *ldesc = "This is room A. There's a chair and an exit to the south.";

    check_room_descs(g, id, sdesc, ldesc);
}

/* check fields for room B */
Test(rooms, add_rooms_room_b)
{
    // check adding rooms and return game pointer
    game_t *g = add_rooms_check();

    // check whether room B was added correctly by comparing sdesc and ldesc
    char *id = "room_B";
    char *sdesc = "This is room B";
    char *ldesc = "This is room B. There's a table and an exit to the west.";

    check_room_descs(g, id, sdesc, ldesc);
}

/* check fields for room C */
Test(rooms, add_rooms_room_c)
{
    // same process as above
    game_t *g = add_rooms_check();

    char *id = "room_C";
    char *sdesc = "This is room C";
    char *ldesc = "This is room C, the final room in the game";

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
    check_conns(g, "room_a", "south", "room_b");
}

/* check connection from room B to room C */
Test(rooms, add_connections_B_C)
{
    // same process as above test
    game_t *g = add_conns_check();

    // check connection from room B to room C
    check_conns(g, "room_b", "west", "room_c");
}

/* check connection from room C to room A */
Test(rooms, add_connections_C_A)
{
    // same process as above
    game_t *g = add_conns_check();

    // check connection from room B to room C
    check_conns(g, "room_c", "north", "room_a");
}
