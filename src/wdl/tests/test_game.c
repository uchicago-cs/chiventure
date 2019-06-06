#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "load_game.h"

/* check to see if rooms are added to game struct correctly */
Test(game, create_game)
{
    obj_t *doc = get_doc_obj(FILE_PATH);
    game_t *g = create_game(doc);
    char *str = g->start_desc;
    cr_assert_str_eq(str, "This is the intro", "Intro was not loaded correctly");
    
}
