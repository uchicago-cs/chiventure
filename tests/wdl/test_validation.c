#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libobj/load.h"
#include "wdl/validate.h"
#include "test_wdl.h"

/*
 * NOTE: these tests are specifically for the file designated by PATH located
 * within validate.h
 */

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

/* tests whether the game fields are valid */ 
Test(validate, game_type_check)
{
    // obtain doc/game objects
    obj_t *doc = __get_doc_obj();
    obj_t *game = obj_get_attr(doc, "GAME", false);

    int rc = game_type_check(game);
    cr_assert_eq(rc, SUCCESS, "game verification failed");
}

/* tests whether the room fields are valid */
Test(validate, room_type_check)
{
    // obtain doc/room objects
    obj_t *doc = __get_doc_obj();
    obj_t *rooms = obj_get_attr(doc, "ROOMS", false);

    int rc = list_type_check(rooms, room_type_check);
    cr_assert_eq(rc, SUCCESS, "rooms verification failed");
}

/* tests whether the item fields are valid */
Test(validate, item_type_check)
{
    // obraint doc/item objects
    obj_t *doc = __get_doc_obj();
    obj_t *items = obj_get_attr(doc, "ITEMS", false);

    int rc = list_type_check(items, item_type_check);
    cr_assert_eq(rc, SUCCESS, "items verification failed");
}
