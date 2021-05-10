#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "wdl/load_game.h"
#include "wdl/load_item.h"
#include "test_wdl.h"

/* check to see if rooms are added to game struct correctly */
Test(game, create_game)
{
    obj_t *doc = get_doc_obj(FILE_PATH);
    game_t *g = create_game(doc);
    cr_assert_not_null(g, "create_game() did not load game correctly");

    char *str = g->start_desc;
    cr_assert_str_eq(str, "This is the intro", "Intro was not loaded correctly");
}
