/*  The header file for the parser code
 *
 */

#include "game-state/game.h"
#include "game-state/room.h"

/* necessary includes to use JSON-C */
#include <json-c/json.h>

/* 
 * add_connections_to_rooms()
 * Adds the connections to the rooms
 * 
 * Parameters:
 *  - doc: The json_object that it was stored in
 *  - g: the game object
 *
 * Returns:
 *  - SUCCESS if passes, FAILURE if fails
 */
int add_connections_to_rooms(json_object *doc, game_t *g);

/* 
 * add_items_to_game()
 * Adds the items to the game object
 * 
 * Parameters:
 *  - doc: The json_object that it was stored in
 *  - g: the game object
 *
 * Returns:
 *  - SUCCESS if passes, FAILURE if fails
 */
int add_items_to_game(json_object *doc, game_t *g);

/* 
 * add_rooms_to_game()
 * Adds the rooms to the game object
 * 
 * Parameters:
 *  - doc: The json_object that it was stored in
 *  - g: the game object
 *
 * Returns:
 *  - SUCCESS if passes, FAILURE if fails
 */
int add_rooms_to_game(json_object *doc, game_t *g);

/* 
 * parse_wdl()
 * parses the wdl document into a game_t
 * 
 * Parameters:
 *  - filename: the path to the file to be parsed
 *
 * Returns:
 *  - a zero for success
 */
game_t *parse_wdl(char* filename);

/*
 * main()
 * 
 */
int main(int argc, char **argv);
