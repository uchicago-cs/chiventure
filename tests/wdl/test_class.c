#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libobj/load.h"
#include "wdl/load_game.h"
#include "wdl/load_item.h"
#include "test_wdl.h"
#include "game-state/stats.h"
#include "skilltrees/inventory.h"
#include "skilltrees/skilltree.h"

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

    /* The knight is a fleshed out class defined in the WDL file */
    class_t* knight = find_class(&game->all_classes, "Knight"); // Case sensitive
    cr_assert_not_null(knight, "load_game() did not load Knight class correctly.\n");

    cr_assert_str_eq(knight->shortdesc, "Knight's short description", 
                     "Knight's short description did not load correctly.\n");

    cr_assert_str_eq(knight->longdesc, "Knight's long description", 
                     "Knight's long description did not load correctly.\n");

    cr_assert(obj_get_bool(knight->attributes, "hot-headed") && obj_get_bool(knight->attributes, "noble"), 
              "Knight did not load hot-headed and noble attributes\n.");
    
    /* Stats are initialized correctly */
    stats_t* knight_health; 
    HASH_FIND_STR(knight->base_stats, "health", knight_health);
    cr_assert_eq(knight_health->val, 100, 
                 "Knight's health stat was loaded incorrectly.\n");
    cr_assert_eq(knight_health->global->max, 200, 
                 "Knight's health stat was loaded incorrectly.\n");
    
    stats_t* knight_mana; 
    HASH_FIND_STR(knight->base_stats, "mana", knight_mana);
    cr_assert_eq(knight_mana->val, 20, 
                 "Knight's mana stat was loaded incorrectly.\n");
    cr_assert_eq(knight_mana->global->max, 100, 
                 "Knight's mana stat was loaded incorrectly.\n");

    /* The Lich class shares some stats with the Warrior. Check that they point 
     * the same global stat. */
    class_t* lich = find_class(&game->all_classes, "Lich");
    stats_t* lich_health;
    HASH_FIND_STR(lich->base_stats, "health", lich_health);
    cr_assert_eq(lich_health->global, knight_health->global,
                 "Knight and Lich's health stat do not point to same global stat.\n");

    /* The following fields are not yet loaded. They should be NULL. */
    cr_assert_null(knight->effects, 
                   "Knight's effects field should have been empty, but was not.\n");

    cr_assert_null(knight->skilltree, 
                   "Knight's skilltree field should have been empty, but was not.\n");

    cr_assert_null(knight->starting_skills, 
                   "Knight's starting_skills field should have been empty, but was not.\n");
}

/* Checks to see if a partially defined class is loaded */
Test(class, load_partially_defined_class) {
    game_t *game = load_game(__get_doc_obj());

    /* The rogue is a partially defined class. Fields are filled in with "" or NULL. */
    class_t* rogue = find_class(&game->all_classes, "Rogue"); 
    cr_assert_not_null(rogue, "load_game() did not load Rogue class correctly.\n");

    cr_assert_str_eq(rogue->shortdesc, "", 
                     "Rogue's short description should have been empty, but was not.\n");

    cr_assert_str_eq(rogue->longdesc, "Rogue's long description", 
                     "Rogue's long description did not load correctly.\n");

    cr_assert_null(rogue->attributes, 
                   "Rogue's attributes field should have been empty, but was not.\n");

    cr_assert_null(rogue->base_stats, 
                   "Rogue's base_stats field should have been empty, but was not.\n");
}

/* Checks to see if a prefab class is loaded */
Test(class, load_prefab_class) {
    game_t *game = load_game(__get_doc_obj());

    /* The monk is a prefab class, it is initialized by us. */
    class_t* monk = find_class(&game->all_classes, "Monk"); 
    cr_assert_not_null(monk, "load_game() did not load Monk class correctly.\n");

    cr_assert_str_eq(monk->shortdesc, "An elite martial artist.", 
                     "Monk's short description did not load correctly.\n");

    cr_assert_str_eq(monk->longdesc, "The Monk is an expert of unarmed combat, and, through their training--"
                     "in accordance with their strict spirituality--have learned how to defend themselves from attackers.", 
                     "Monk's long description did not load correctly.\n");

    cr_assert_eq(get_stat_current(monk->base_stats, "max_health"), 25, 
                 "Monk's max_health stat was loaded incorrectly.\n");
}

/* Checks to see if a partially overwritten prefab class is loaded */
Test(class, load_overwritten_prefab_class) {
    game_t *game = load_game(__get_doc_obj());

    /* The warrior is a prefab class that has some fields overwritten */
    class_t* warrior = find_class(&game->all_classes, "Warrior");
    cr_assert_not_null(warrior, "load_game() did not load Warrior class correctly.\n");

    /* Unchanged short description */
    cr_assert_str_eq(warrior->shortdesc, "A mighty warrior.", 
                     "Warrior's short description did not load correctly.\n");

    /* Overwritten long description */
    cr_assert_str_eq(warrior->longdesc, "Warrior's overwritten long description", 
                     "Warrior's long description did not load correctly.\n");
            
    /* Warrior has new stat */
    stats_t* warrior_health; 
    HASH_FIND_STR(warrior->base_stats, "health", warrior_health);
    cr_assert_eq(warrior_health->val, 120, 
                 "Warrior's health stat was loaded incorrectly.\n");
    cr_assert_eq(warrior_health->global->max, 200, 
                 "Warriors's health stat was loaded incorrectly.\n");

    /* Warrior does not have old stat */
    stats_t* warrior_physical_attack;
    HASH_FIND_STR(warrior->base_stats, "physical_attacl", warrior_physical_attack);
    cr_assert_null(warrior_physical_attack, 
                   "Warrior should not have a physical attack stat, but it does.\n");
    
    /* Also, Warrior is the only prefab class to have skill structs. I'll check 
     * those here. */
    cr_assert_str_eq(warrior->starting_skills->active[0]->name, "Sword Slash", 
                    "Warrior skill inventory was not loaded correctly.\n");

    cr_assert_str_eq(warrior->skilltree->nodes[0]->skill->name, "Sword Slash",
                     "Warrior skill tree was not loaded correctly.\n");
    cr_assert_str_eq(warrior->skilltree->nodes[1]->skill->name, "Double Slash",
                     "Warrior skill tree was not loaded correctly.\n");
    cr_assert_str_eq(warrior->skilltree->nodes[2]->skill->name, "Triple Slash",
                     "Warrior skill tree was not loaded correctly.\n");

}
