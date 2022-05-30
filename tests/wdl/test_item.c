#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libobj/load.h"
#include "wdl/load_item.h"
#include "test_wdl.h"

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

void item_check(char *room, char *item)
{
    obj_t *doc = __get_doc_obj();
    game_t *g = game_new("Welcome to UChicago");

    // check adding rooms to game
    int rc = add_rooms_to_game(doc, g);
    cr_assert_eq(rc, SUCCESS, "adding rooms to game failed");

    // check adding items to game
    rc = load_items(doc, g);
    cr_assert_eq(rc, SUCCESS, "loading items failed");

    // checking fields were correctly filled
    room_t *r = find_room_from_game(g, room);
    item_t *i = get_item_in_room(r, item);
    agent_t *agent = malloc(sizeof(agent_t));
    agent->item = i;
    agent->npc = NULL;

    obj_t *item_obj = obj_get_attr(doc, "ITEMS", false);
    item_obj = obj_get_attr(item_obj, item, false);

    char *s = get_sdesc_item(agent->item);
    char *scmp = obj_get_str(item_obj, "short_desc");
    rc = strncmp(s, scmp, strlen(scmp));
    cr_assert_eq(rc, SUCCESS, "failed to parse item sdesc");

    char *l = get_ldesc_item(agent->item);
    char *lcmp = obj_get_str(item_obj, "long_desc");
    rc = strncmp(l, lcmp, strlen(lcmp));
    cr_assert_eq(rc, SUCCESS, "failed to parse item sdesc");

    obj_t *actions = obj_get_attr(item_obj, "actions", false);

    obj_t *curr;
    DL_FOREACH(actions->data.lst, curr)
    {
        rc = possible_action(agent, obj_get_str(curr, "action"));
        cr_assert_eq(rc, 0, "failed to load item action");
    }
}

Test(items, check_chair)
{
    item_check("room_A", "CHAIR");
}

Test(items, check_table)
{
    item_check("room_B", "TABLE");
}
