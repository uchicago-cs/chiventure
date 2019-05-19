#ifndef SAVE_H
#define SAVE_H

#include "game.pb-c.h"
#include "dummy.h"

/* 
 * Packs the object_t struct into the Object field in the protofile.
 * 
 * Parameters:
 *   - o_t: pointer to the game struct object_t struct
 *   - o: pointer to the proto file object struct
 *
 * Return:
 *   - 0 if successful
 *   - -1 if unsuccessful 
 */
int save_object(object_t *o_t, Object *o);


/* 
 * Packs the room_t struct into the Room field in the protofile.
 * 
 * Parameters:
 *   - r_t: the game struct room_t struct
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
 *   - p_t: pointer to the game struct player_t struct 
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
 *   - g_t: pointer to the game struct game_t struct
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
 *   - filename: name of the file given from command line
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
 *   - g: game_t struct containing the game we want to save
 *   - filename: the name of the save file
 *
 * Return:
 *   - 0 if successful
 *   - -1 if unsuccessful 
 */
int save(game_t *game, char *filename);

#endif
