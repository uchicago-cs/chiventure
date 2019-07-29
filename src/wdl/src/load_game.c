#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "validate.h"
#include "parse.h"
#include "game.h"
#include "load_game.h"

/*
 * load_wdl, function that loads a wdl into all the game-state structs
 *
 * takes a path to a yaml file, automatically load yaml found in FILE_PATH
 *
 *
 */
game_t *load_wdl(char *path_to_yaml)
{
    obj_t *big_document = get_doc_obj(path_to_yaml);

    printf("GAME.0.start: %c\n", obj_get_char(big_document,"GAME.0.start"));
    printf("GAME.1.intro: %s\n",obj_get_str(big_document,"GAME.1.intro"));
    printf("GAME.2.end.inventory: %s\n",obj_get_str(big_document,"GAME.2.end.inventory"));
    printf("OBJECTS.0.short_desc: %s\n", obj_get_str(big_document,"OBJECTS.0.short_desc"));
    printf("ROOMS.0.id: %c\n", obj_get_char(big_document, "ROOMS.0.id"));

    game_t *game = create_game(big_document);

    // call functions that parse items, actions, rooms, and game attributes
    // into a game pointer
    int rooms = add_rooms_to_game(big_document, game);
    int connections =  add_connections_to_rooms(big_document, game);
    obj_t *game_document = obj_get_attr(big_document, "GAME.0", false);
    char *start_room = obj_get_str(game_document, "start");
    game_set_start(start_room, game);
    obj_t *end = obj_get_attr(game_document, "end.0", false);
    char *end_room = obj_get_str(end, "in_room");
    room_t *final_room = find_room_from_game(game, end_room);
    game->final_room = final_room;
    int items = load_items(big_document, game);

     if(rooms+connections == 0){
      if(items != -1){
	return game;
      }
    }
    return NULL;
}

game_t *create_game(obj_t *doc)
{
    obj_t *game = obj_get_attr(doc, "GAME.0", false);
    if (game == NULL) {
      fprintf(stderr, "game object not found\n");
      exit(0);
    }

    bool check = game_type_check(doc);
    if (check == false) {
      fprintf(stderr, "game object fails type checking\n");
      exit(0);
    }
    

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
