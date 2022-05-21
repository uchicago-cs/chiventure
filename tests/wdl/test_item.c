#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libobj/load.h"
#include "wdl/load_item.h"
#include "test_wdl.h"


void item_check(char *room, char *item)
{
    obj_t *doc = __get_doc_obj("DEFAULT.json", FILE_PATH_1);
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

    obj_t *item_obj = obj_get_attr(doc, "ITEMS", false);
    item_obj = obj_get_attr(item_obj, item, false);

    char *s = get_sdesc_item(i);
    char *scmp = obj_get_str(item_obj, "short_desc");
    rc = strncmp(s, scmp, strlen(scmp));
    cr_assert_eq(rc, SUCCESS, "failed to parse item sdesc");

    char *l = get_ldesc_item(i);
    char *lcmp = obj_get_str(item_obj, "long_desc");
    rc = strncmp(l, lcmp, strlen(lcmp));
    cr_assert_eq(rc, SUCCESS, "failed to parse item sdesc");

    obj_t *actions = obj_get_attr(item_obj, "actions", false);

    obj_t *curr;
    DL_FOREACH(actions->data.lst, curr)
    {
        rc = possible_action(i, obj_get_str(curr, "action"));
        cr_assert_eq(rc, 0, "failed to load item action");
    }
}

void conditions_check(char* room, char* item, char* action)
{
    obj_t *doc = __get_doc_obj("inventory-cond.wdl", FILE_PATH_2);
    game_t *g = game_new("Welcome to UChicago");

    load_items(doc, g);

    //check adding conditions to game
    item_t* i = get_item_from_game(g, item);
    game_action_t *a = get_action(i, a);
}

Test(items, check_chair)
{
    item_check("room_A", "CHAIR");
}

Test(items, check_table)
{
    item_check("room_B", "TABLE");
}
