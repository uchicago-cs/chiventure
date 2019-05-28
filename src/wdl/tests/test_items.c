#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "load_items.h"

obj_t *get_doc_obj()
{
    obj_t *obj = obj_new("doc");
    parse_game(PATH, obj);
    return obj;
}

Test(items, test1)
{
    obj_t *doc = get_doc_obj();
    //printf("ROOMS.0.id: %s\n", obj_get_str(doc, "ROOMS.0.id"));
    game_t *g = game_new();

    if(load_items(doc, g) == 0)
    {
         return SUCCESS;
    }
}
