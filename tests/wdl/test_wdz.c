#include <criterion/criterion.h>
#include "wdl/load_wdz_internal.h"

/* Checks the file extension checker when format is normal */
Test(load_wdz, file_extension_normal)
{
    cr_assert_eq(filename_extension_is("wdz", "myfile.wdz"), true,
        "File extension was wdz but filename_extension_is returned false");

    cr_assert_eq(filename_extension_is("wdz", "myfile.zip"), false,
        "File extension was NOT wdz but filename_extension_is returned true");
}

/* Checks the file extension checker when filename has multiple dots */
Test(load_wdz, file_extension_multiple_dots)
{
    cr_assert_eq(filename_extension_is("wdz", "myfile.backup.wdz"), true,
        "File extension was wdz but filename_extension_is returned false");

    cr_assert_eq(filename_extension_is("wdz", "myfile.wdz.backup"), false,
        "File extension was NOT wdz but filename_extension_is returned true");
}

/* Checks the file extension checker when filename has path */
Test(load_wdz, file_extension_withpath)
{
    cr_assert_eq(filename_extension_is("wdz", "path/to/myfile.wdz"), true,
        "File extension was wdz but filename_extension_is returned false");

    cr_assert_eq(filename_extension_is("wdz", "path/to/myfile.zip"), false,
        "File extension was NOT wdz but filename_extension_is returned true");
}

/* Test helper function */
void check_objstore_from_json
(
    const char *json_buf, 
    objtype_t obj_type, 
    char *expected_id
)
{
    json_object *j_obj = json_tokener_parse(json_buf);
    
    objstore_t *obj_store = NULL;
    
    int res = load_game_objects_from_json_object(&obj_store, j_obj);
    
    cr_assert_eq(res, SUCCESS, "Load function returned FAILURE");
    cr_assert_not_null(obj_store, "Object store still empty after load");
    
    objstore_t *imported = 
        find_objstore(&obj_store, expected_id, obj_type);
    
    
    object_t *target;
    
    cr_assert_not_null(imported, "Could not find the right object store node");
    target = imported->o;
    cr_assert_not_null(target, 
        "Could not get the loaded game object from the object store"
    );
    cr_assert_str_eq(target->id, expected_id, "Loaded game object did not have correct ID");
    free_all_objstore(&obj_store);
}

/* This test should cover everything from load_game_objs_from_json to
 * the conversion function convert_j_obj_to_game_obj, which also invokes
 * the make_data_from_j_value function. If this works, all of them work.
 */
Test(load_wdz, load_room_objs_from_json)
{
    const char *test_json = 
        "{\"rooms\":                                        \
            [                                               \
            {\"id\":\"best_room\", \"number\":123},         \
            {\"id\":\"test_room\", \"can_enter\":false}     \
            ]                                               \
        }";
    check_objstore_from_json(test_json, TYPE_ROOM, "best_room");
    check_objstore_from_json(test_json, TYPE_ROOM, "test_room");
}

/* Same as above, but the special player object needs some more attention */
Test(load_wdz, load_player_from_json)
{
    const char *test_json = 
        "{\"player\":                                       \
            {                                               \
                \"intro_text\":\"my intro text\",           \
                \"start_room\":\"whiteroom\"                \
            }                                               \
        }";
    check_objstore_from_json(test_json, TYPE_PLAYER, DEFAULT_PLAYER_OBJ_ID);
}


/* A test that simulates what would actually happen on chiventure startup */
#define RELATIVE_FILE_PATH "../../../src/wdl/examples/wdz/test_game.wdz"
Test(load_wdz, load_from_wdz_file)
{
    objstore_t *obj_store = NULL;
    int n_jsons;
    populate_objstore_from_wdz(&obj_store, &n_jsons, RELATIVE_FILE_PATH);
    cr_assert_not_null(obj_store, "Object store is empty after load");
    cr_log_warn("There are %d\n items in objstore", HASH_COUNT(obj_store));
    
    objstore_t *el, *tmp;
    HASH_ITER(hh, obj_store, el, tmp)
    {
        cr_log_warn("object has ID %s and type %d\n",el->key.id, el->key.type);
    }
 
    cr_assert_not_null(find_objstore(&obj_store, DEFAULT_PLAYER_OBJ_ID, TYPE_PLAYER),
        "Player object not loaded");
    // Find a representative object from each type
    cr_assert_not_null(find_objstore(&obj_store, "greenlever", TYPE_ITEM),
        "Item greenlever not loaded");
    cr_assert_not_null(find_objstore(&obj_store, "action_normal_pull <lever_num>", TYPE_ACTION),
        "Action action_normal_pull not loaded");
    cr_assert_not_null(find_objstore(&obj_store, "globcond_unlock", TYPE_GCONDITION),
        "Global condition globcond_unlock not loaded");
    cr_assert_not_null(find_objstore(&obj_store, "purpleroom", TYPE_ROOM),
        "Room purpleroom not loaded");
    free_all_objstore(&obj_store);
}
