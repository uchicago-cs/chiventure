#ifndef LOAD_H
#define LOAD_H

#include "game.pb-c.h"
#include "dummy.h"

/* 
 * Takes a file, reads it, and returns the length of file
 * 
 * Parameters:
 * - filename: string that is name of file
 * - max_length: unsigned int of the max length the file can be
 * - out: a buffer
 *
 * Returns:
 * - size_t: length of file
 */
size_t read_file(char *filename, unsigned max_length, uint8_t *out);

/*
 * Loads object into game struct
 * 
 * Parameters:
 * - o: pointer to object in protofile
 * - o_t: pointer to an empty object in game struct to be filled from protofile
 *
 * Returns:
 * - 0 if successful
 * - -1 if unsuccessful
 */
int load_object(Object *o, object_t *o_t);

/*
 * Loads player into game struct
 * 
 * Parameters:
 * - p: pointer to player in protofile
 * - p_t: pointer to an empty player in game struct to be filled from protofile
 *
 * Returns:
 * - 0 if successful
 * - -1 if unsuccessful
 */
int load_player(Player *p, player_t *p_t);

/*
 * Loads room into game struct
 * 
 * Parameters:
 * - r: pointer to room in protofile
 * - r_t: pointer to an empty room in game struct to be filled from protofile
 *
 * Returns:
 * - 0 if successful
 * - -1 if unsuccessful
 */
int load_room(Room *r, room_t *r_t);

/*
 * Loads game into game struct
 * 
 * Parameters:
 * - g: pointer to game in protofile
 * - g_t: pointer to an empty game in game struct to be filled from protofile
 *
 * Returns:
 * - 0 if successful
 * - -1 if unsuccessful
 */
int load_game(Game *g, game_t *g_t);

/*
 * Unpacks the protofile and reloads all saved information into game structs
 *
 * Parameters:
 * - filename: string name of file with sereialized information
 * - g: proto game struct
 * - g_t: game struct
 * 
 * Returns:
 * - 0 if successful
 * - -1 if unsuccessful
 */
int load(char *filename, Game *g, game_t *g_t);

#endif
