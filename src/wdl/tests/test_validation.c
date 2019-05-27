#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "validate.h"

/*
 * helper function for parsing a YAML file into an object
 */
obj_t *get_doc_obj()
{
    obj_t *obj = obj_new("doc");
    parse_game(PATH, obj);
    return obj;
}

Test(validate, game_type_check)
{
    // obtain doc/game objects
    obj_t *doc = get_doc_obj();
    obj_t *game = obj_get_attr(doc, "GAME", false);

    bool rc = game_type_check(game);
    cr_assert_eq(rc, true, "game verification failed");
}

Test(validate, room_type_check)
{
    // obtain doc/room objects
    obj_t *doc = get_doc_obj();
    attr_list_t *rooms = obj_list_attr(obj_get_attr(doc, "ROOMS", false));

    bool rc = list_type_check(rooms, room_type_check);
    cr_assert_eq(rc, true, "rooms verification failed");
}

Test(validate, item_type_check)
{
    // obraint doc/item objects
    obj_t *doc = get_doc_obj();
    attr_list_t *items = obj_list_attr(obj_get_attr(doc, "ITEMS", false));

    bool rc = list_type_check(items, item_type_check);
    cr_assert_eq(rc, true, "items verification failed");
}
