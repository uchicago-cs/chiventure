#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "load_item.h"
#include "load_room.h"

Test(items, test1)
{
    obj_t *doc = get_doc_obj();
    game_t *g = game_new("Welcome to UChicago");
    
    // check adding rooms to game
    int rc = load_items(doc, g);
    cr_assert_eq(rc, SUCCESS, "loading items failed");
}
