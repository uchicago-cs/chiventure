#ifndef SAVE_H
#define SAVE_H
#include "game.pb-c.h"
#include "game.h"
#include "actionmanagement.h"


/* 
 * Packs the attribute_t struct into the Attribute field in the protofile.
 * 
 * Parameters:
 *   - i_t: pointer to an item_t struct
 *   - a_t: pointer to an attribute_t struct
 *   - a: pointer to the proto file Attribute struct
 *
 * Return:
 *   - 0 if successful
 *   - -1 if unsuccessful 
 */
int save_attribute(item_t *i_t, attribute_t *a_t, Attribute *a);


/* 
 * Packs the item_t struct into the Item field in the protofile.
 * 
 * Parameters:
 *   - i_t: pointer to an item_t struct
 *   - i: pointer to the proto file Item struct
 *
 * Return:
 *   - 0 if successful
 *   - -1 if unsuccessful 
 */
int save_item(item_t *i_t, Item *i);


/* 
 * Packs the room_t struct into the Room field in the protofile.
 * 
 * Parameters:
 *   - r_t: pointer to a room_t struct
 *   - r: pointer to the proto file room struct
 *
 * Return:
 *   - 0 if successful
 *   - -1 if unsuccessful 
 */
int save_room(room_t *r_t, Room *r);


/* 
 * Packs the player_t struct into the Player field in the protofile.
 * 
 * Parameters:
 *   - p_t: pointer to a player_t struct 
 *   - p: pointer to the proto file player struct
 *
 * Return:
 *   - 0 if successful, -1 if unsuccessful 
 */
int save_player(player_t *p_t, Player *p);


/* 
 * Packs the game_t struct into the Game field in the protofile.
 * 
 * Parameters:
 *   - g_t: pointer to a game_t struct
 *   - g: pointer to the proto file game struct
 *
 * Return:
 *   - 0 if successful
 *   - -1 if unsuccessful 
 */
int save_game(game_t *g_t, Game *g);


/* 
 * Writes the serialized game into a file
 * 
 * Parameters:
 *   - filename: pointer to string name of the file given from command line
 *   - buffer: pointer to buffer containing seraizlied game
 *   - len: the length of the serialized game in buffer
 *
 * Return:
 *   - 0 if successful
 *   - -1 if unsuccessful 
 */
int write_to_file(char *filename, uint8_t *buffer, unsigned len);


/* 
 * Calls all above functions to save game into file
 * 
 * Parameters:
 *   - g: pointer to game_t struct containing the game we want to save
 *   - filename: pointer to string name of the save file
 *
 * Return:
 *   - 0 if successful
 *   - -1 if unsuccessful 
 */
int save(game_t *g_t, char *filename);


#endif
