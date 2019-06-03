#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "load_item.h"

Test(items, test1)
{
    obj_t *doc = get_doc_obj();
    game_t *g = game_new("Welcome to UChicago");
    
    // check adding items to game
    int rc = load_items(doc, g);
    cr_assert_eq(rc, SUCCESS, "loading items failed");
}


Test(items, correct_fields_chair)
{
    obj_t *doc = get_doc_obj();
    game_t *g = game_new("Welcome to UChicago");

    // check adding rooms to game
    int rc = add_rooms_to_game(doc, g);
    cr_assert_eq(rc, SUCCESS, "adding rooms to game failed");

    // check adding items to game
    int rc = load_items(doc, g);
    cr_assert_eq(rc, SUCCESS, "loading items failed");

    // checking fields were correctly filled
    room_t *r = find_room_from_game(g, "room A");
    item_t *i = get_item_in_room(r, "chair");

    char *s = get_sdesc(r);
    char *scmp = "This is a chair";
    rc = strncmp(s, scmp, strlen(scmp));
    cr_assert_eq(rc, SUCCESS, "failed to parse item sdesc");

    char *l = get_ldesc(r);
    char *lcmp = "This is a chair long";
    rc = strncmp(l, lcmp, strlen(lcmp));
    cr_assert_eq(rc, SUCCESS, "failed to parse item ldesc");
}