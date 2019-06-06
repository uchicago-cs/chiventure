#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "validate.h"
#include "parse.h"
#include "game.h"
#include "load_game.h"

game_t *create_game(obj_t *doc)
{
  obj_t *game = obj_get_attr(doc, "GAME.0", false);
  char *intro = obj_get_str(game, "intro");
 
  game_t *game_ret = game_new(intro);
  return game_ret;
}

//uses find_room specified in game.c
void game_set_start(char *room_id, game_t *game)
{
  game->curr_room = find_room_from_game(game, room_id);
  return;
}
