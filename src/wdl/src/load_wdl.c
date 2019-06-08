#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parse.h"
#include "load_wdl.h"

/*
 * load_wdl, function that loads a wdl into all the game-state structs
 *
 * has no parameters, automatically load yaml found in FILE_PATH
 *
 *
 */
game_t *load_wdl()
{
  obj_t *big_document = get_doc_obj(PATH_TO_YAML);
  game_t *game = create_game(big_document);

  int rooms = add_rooms_to_game(big_document, game);
  int connections =  add_connections_to_rooms(big_document, game);
  obj_t *game_document = obj_get_attr(big_document, "GAME.0", false);
  char *start_room = obj_get_str(game_document, "start");
  game_set_start(start_room, game);
  //  int items = load_items(big_document, game);

  return game;
  /*  if((rooms + connections) == 0){
    if(items == -1){
      return NULL;
    }else{
      return game;
    }
  }else{
    return NULL;
    }*/
}

    
