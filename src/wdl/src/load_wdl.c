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

    // call functions that parse items, actions, rooms, and game attributes
    // into a game pointer
    int rooms = add_rooms_to_game(big_document, game);
    int connections =  add_connections_to_rooms(big_document, game);
    obj_t *game_document = obj_get_attr(big_document, "GAME.0", false);
    char *start_room = obj_get_str(game_document, "start");
    game_set_start(start_room, game);
    char *end_room = obj_get_str(game_document, "end");
    room_t *final_room = find_room_from_game(game, end_room);
    int final = add_final_room_to_game(game, final_room);
    int items = load_items(big_document, game);

    if (final == FAILURE) {
        fprintf(stderr, "failed to add final room to game\n");
	return NULL;
    }
    if((rooms + connections) == 0) {
        if(items == FAILURE) {
	    //load_items is the only one that returns -1 on failure
            fprintf(stderr, "failed to add items to game\n");
	    return NULL;
        }
        else {
            printf("game has successfully been loaded\n");
	    return game;
        }
    }
    else if (rooms = FAILURE) {
        fprintf(stderr, "failed to add rooms to game\n");
	return NULL;
    }
    else {
	fprintf(stderr, "failed to add connections to game\n");
	return NULL;
}
