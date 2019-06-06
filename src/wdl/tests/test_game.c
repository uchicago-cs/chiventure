#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "load_game.h"

obj_t *get_doc_obj()
{
    obj_t *obj = obj_new("doc");
    parse_game(PATH, obj);
    return obj;
}

/* check to see if rooms are added to game struct correctly */
Test(game, create_game)
{
    obj_t *doc = get_doc_obj();
    game_t *g = create_game(doc);
    char *str = g->start_desc;
    cr_assert_str_eq(str, "This is the intro", "Intro was not loaded correctly")
    
}
