#include <stdio.h>
#include <stdlib.h>
#include "validate.h"
#include "parse.h"
#include "load_game.h"
#include "parse_document.h"

game_t *create_game(obj_t *game)
{
  //  char *intro = obj_get_str(game,"GAME.1.intro");
  
  game_t *game_ret = game_new();
  return game_ret;
}
