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

/* tests whether the game fields are valid */ 
Test(validate, game_type_check)
{
    // obtain doc/game objects
    obj_t *doc = __get_doc_obj("DEFAULT.json", FILE_PATH_1);
    obj_t *game = obj_get_attr(doc, "GAME", false);

    int rc = game_type_check(game);
    cr_assert_eq(rc, SUCCESS, "game verification failed");
}

/* tests whether the room fields are valid */
Test(validate, room_type_check)
{
    // obtain doc/room objects
    obj_t *doc = __get_doc_obj("DEFAULT.json", FILE_PATH_1);
    obj_t *rooms = obj_get_attr(doc, "ROOMS", false);

    int rc = list_type_check(rooms, room_type_check);
    cr_assert_eq(rc, SUCCESS, "rooms verification failed");
}

/* tests whether the item fields are valid */
Test(validate, item_type_check)
{
    // obraint doc/item objects
    obj_t *doc = __get_doc_obj("DEFAULT.json", FILE_PATH_1);
    obj_t *items = obj_get_attr(doc, "ITEMS", false);

    int rc = list_type_check(items, item_type_check);
    cr_assert_eq(rc, SUCCESS, "items verification failed");
}
