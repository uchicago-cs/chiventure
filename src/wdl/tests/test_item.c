#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "load_item.h"

//TEMPORARILY ADDING FUNCTIONS FOR TESTING; WILL REMOVE BEFORE PR
//**********************************************
/* see item.h */
char *get_sdesc_item(item_t *item)
{
  if (item == NULL) {
    return NULL;
  }
  return item->short_desc;
}

/* see item.h */
char *get_ldesc_item(item_t *item)
{
  if (item == NULL) {
    return NULL;
  }
  return item->long_desc;
}
//**********************************************

Test(items, load_items)
{
    obj_t *doc = get_doc_obj(FILE_PATH);
    game_t *g = game_new("Welcome to UChicago");
   
    // check and load rooms
    int rc = add_rooms_to_game(doc, g);
    cr_assert_eq(rc, SUCCESS, "adding rooms to game failed");

    // check adding items to game
    rc = load_items(doc, g);
    cr_assert_eq(rc, SUCCESS, "loading items failed");
}


Test(items, load_items_chair_check)
{
    obj_t *doc = get_doc_obj(FILE_PATH);
    game_t *g = game_new("Welcome to UChicago");

    // check adding rooms to game
    int rc = add_rooms_to_game(doc, g);
    cr_assert_eq(rc, SUCCESS, "adding rooms to game failed");

    // check adding items to game
    rc = load_items(doc, g);
    cr_assert_eq(rc, SUCCESS, "loading items failed");

    printf("it worked\n");
    // checking fields were correctly filled
    room_t *r = find_room_from_game(g, "room A");
    item_t *i = get_item_in_room(r, "chair");

    char *s = get_sdesc_item(i);
    char *scmp = "This is a chair";
    rc = strncmp(s, scmp, strlen(scmp));
    cr_assert_eq(rc, SUCCESS, "failed to parse item sdesc");

    char *l = get_ldesc_item(i);
    char *lcmp = "This is a chair long";
    rc = strncmp(l, lcmp, strlen(lcmp));
    cr_assert_eq(rc, SUCCESS, "failed to parse item ldesc");
}
