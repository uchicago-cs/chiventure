#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libobj/load.h"
#include "wdl/load_game.h"
#include "wdl/load_item.h"
#include "test_wdl.h"

#define CLASSES_WDL_PATH "../../../tests/wdl/examples/wdl/classes.wdl"
/*
 * helper function for parsing a YAML file into an object (copied from test_game.c)
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
    char *data_path = CLASSES_WDL_PATH; // Edited to load the example file with classes

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

/* check to see if the load game function works when there are classes defined */
Test(class, load_game_with_classes)
{
    obj_t *obj_store = __get_doc_obj();
    game_t *game = load_game(obj_store);
    cr_assert_not_null(game, "load_game() did not load game correctly.\n");

    char *str = game->start_desc;
    cr_assert_str_eq(str, "This is the intro for a test game, which is exactly like that in connected-rooms.wdl execpt it also has classes.", 
                     "Intro was not loaded correctly.\n");
}

/* Checks to see if a full user defined class is loaded */
Test(class, load_fully_defined_class) {
    game_t *game = load_game(__get_doc_obj());
    /* The warrior is a fleshed out class defined in the WDL file */
    class_t* warrior = find_class(&game->all_classes, "Warrior"); // Case sensitive
    cr_assert_not_null(warrior, "load_game() did not load Warrior class correctly.\n");

    cr_assert_str_eq(warrior->shortdesc, "Warrior's short description", 
                     "Warrior's short description did not load correctly.\n");

    cr_assert_str_eq(warrior->longdesc, "Warrior's long description", 
                     "Warrior's long description did not load correctly.\n");

    cr_assert(obj_get_bool(warrior->attributes, "hot-headed") && obj_get_bool(warrior->attributes, "noble"), 
              "Warrior did not load hot-headed and noble attributes\n.");
}

/* Checks to see if a partially defined class is loaded */
Test(class, load_partially_defined_class) {
    game_t *game = load_game(__get_doc_obj());
    /* The rogue is a partially defined class */
    class_t* rogue = find_class(&game->all_classes, "Rogue"); 
    cr_assert_not_null(rogue, "load_game() did not load Rogue class correctly.\n");

    cr_assert_str_eq(rogue->shortdesc, "", 
                     "Rogue's short description should have been empty, but was not.\n");

    cr_assert_str_eq(rogue->longdesc, "Rogue's long description", 
                     "Rogue's long description did not load correctly.\n");
}

/* Checks to see if a prefab class is loaded */
Test(class, load_prefab_class) {
    game_t *game = load_game(__get_doc_obj());
    /* The rogue is a partially defined class */
    class_t* monk = find_class(&game->all_classes, "Monk"); 
    cr_assert_not_null(monk, "load_game() did not load Monk class correctly.\n");

    cr_assert_str_eq(monk->shortdesc, "An elite martial artist.", 
                     "Monk's short description did not load correctly.\n");

    cr_assert_str_eq(monk->longdesc, "The Monk is an expert of unarmed combat, and, through their training-- "
                     "in accordance with their strict spirituality--have learned how to defend themselves from attackers.", 
                     "Monk's long description did not load correctly.\n");

    cr_assert_eq(get_stat_current(monk->base_stats, "max_health"), 25, 
                 "Monk's max_health stat was loaded incorrectly.\n");
}