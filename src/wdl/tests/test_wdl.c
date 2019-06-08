#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "load_wdl.h"

Test(wdl, load_wdl)
{
  printf("TEST WDL STARTS HERE\n");
  game_t *game = load_wdl();

  char *start_desc = game->start_desc;
  cr_assert_str_eq(start_desc, "This is the intro", "Intro was not loaded corr\
ectly");
}
