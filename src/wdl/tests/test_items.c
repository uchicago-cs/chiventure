#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "load_item.h"

obj_t *get_doc_obj()
{
    obj_t *obj = obj_new("doc");
    parse_game(PATH, obj);
    return obj;
}

Test(items, test1)
{
    obj_t *doc = get_doc_obj();
    game_t *g = game_new();
    
    // check adding rooms to game
    int rc = load_items(doc, g);
    cr_assert_eq(rc, SUCCESS, "loading items failed");
}
