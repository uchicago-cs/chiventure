#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libobj/load.h"
#include "wdl/load_game.h"
#include "wdl/load_item.h"
#include "test_wdl.h"


/* check to see if rooms are added to game struct correctly */
Test(game, create_game)
{
    obj_t *doc = __get_doc_obj("DEFAULT.json", FILE_PATH_1);
    game_t *g = create_game(doc);
    cr_assert_not_null(g, "create_game() did not load game correctly");

    char *str = g->start_desc;
    cr_assert_str_eq(str, "This is the intro", "Intro was not loaded correctly");
}

/* check to see if the load game function works */
Test(game, load_game)
{
    obj_t *obj_store = __get_doc_obj("DEFAULT.json", FILE_PATH_1);
    cr_assert_not_null(obj_store, "Object store is NULL.\n");
    game_t *g = load_game(obj_store);
    cr_assert_not_null(g, "load_game() did not load game correctly.\n");

    char *str = g->start_desc;
    cr_assert_str_eq(str, "This is the intro", "Intro was not loaded correctly.\n");
}
