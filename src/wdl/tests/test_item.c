#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "load_item.h"

/* a function used to automate the testing of loading items 
 * 
 * parameters:
 *  - item: the id of the item as in the wdl file that is being loaded and tested
 *  - room: the id of the room in which the item is located, as written in the wdl file
 *  - index: a number indicating the position of the item in the list of items
 */
void item_check(char* room, char *item, char *index)
{
    obj_t *doc = get_doc_obj();
    game_t *g = game_new("Welcome to UChicago");

    // check adding items to game
    int rc = add_rooms_to_game(doc, g);
    cr_assert_eq(rc, SUCCESS, "adding rooms to game failed");

    int rc = add_items_to_game(doc, g);
    cr_assert_eq(rc, SUCCESS, "adding rooms to game failed");

    printf("it worked\n");
    // checking fields were correctly filled
    room_t *r = find_room_from_game(g, room);
    item_t *i = get_item_in_room(r, item);

    char *item_path = malloc(100); // setting up string buffer
    strcpy(item_path, "ITEMS.");
    strncat(item_path, index, 94);
    obj_t *item_obj = obj_get_attr(doc, item_path, false);

    rc = strcmp(obj_get_str(item_obj, "short_desc"), get_sdesc_item(i));
    cr_assert_eq(rc, 0, "failed to load item short_desc");

    rc = strcmp(obj_get_str(item_obj, "long_desc"), get_ldesc_item(i));
    cr_assert_eq(rc, 0, "failed to load item long_desc");

    obj_t *actions = obj_get_attr(item, "actions", false);
    attr_list_t *action_ll = obj_list_attr(actions);

    while(action_ll != NULL)
    {
        rc = allowed_action(i, action_ll->obj->id);
        cr_assert_eq(rc, 0, "failed to load item action");
    }
}
