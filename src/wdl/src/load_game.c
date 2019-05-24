#include <stdio.h>
#include <stdlib.h>
#include "validate.h"
#include "parse.h"
#include "load_game.h"
#include "parse_document.h"

game_t *create_game(obj_t *doc)
{
  // to be used when game_state supports an intro in their game_t struct
  //  char *intro = obj_get_str(game,"GAME.1.intro");
  
  game_t *game_ret = game_new();
  return game_ret;
}

//uses find_room specified in game.c
void game_set_start(char *room_id, game_t *game)
{
  game->curr_room = find_room(game, room_id);
  return;
}
