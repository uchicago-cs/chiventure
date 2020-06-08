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

#define EMPTY_GAME_OBJ_NAME "__empty_obj__"

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

Test(load_wdz, load_game_objs_from_json)
{
    const char *test_json = 
        "{\"rooms\":                    \
            [                           \
            {\"id\":\"best_room\"},     \
            {\"id\":\"test_room\"}      \
            ]                           \
        }";
    check_objstore_from_json(test_json, TYPE_ROOM, "best_room");
}