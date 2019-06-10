#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "load_wdl.h"

/*
 * checks that start_desc was loaded
 */
Test(wdl, load_wdl)
{
  game_t *game = load_wdl();

  char *start_desc = game->start_desc;
  cr_assert_str_eq(start_desc, "This is the intro", "Intro was not loaded corr\
ectly");
}

/*
 * checks that rooms were loaded
 */
Test(wdl, loading_rooms)
{
    game_t *game = load_wdl();

    room_list_t *rc = get_all_rooms(game);

    cr_assert_not_null(rc, "load_wdl did not load rooms");
}

/*
 * checks that items were loaded
 */
Test(wdl, loading_items)
{
    game_t *game = load_wdl();

    item_list_t *rc = get_all_items_in_game(game);

    cr_assert_not_null(rc, "load_wdl did not load items");
}

