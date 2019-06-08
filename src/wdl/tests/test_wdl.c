#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "load_wdl.h"

Test(wdl, load_wdl)
{
  game_t *game = load_wdl();

  char *start_desc = game->start_desc;
  room
