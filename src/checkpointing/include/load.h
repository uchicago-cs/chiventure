#ifndef LOAD_H
#define LOAD_H
#include "game.pb-c.h"
#include "game.h"

/* 
 * Takes a file, reads it, and returns the length of file
 * 
 * Parameters:
 * - filename: pointer to string that is name of file
 * - max_length: unsigned int of the max length the file can be
 * - out: pointer to a buffer
 *
 * Returns:
 * - size_t: length of file
 */
size_t read_file(char *filename, unsigned max_length, uint8_t *out);


/*
 * Loads attribute value into game struct
 * 
 * Parameters:
 * - av: pointer to Attribute_value in protofile
 * - av_t: pointer to an empty attribute_value_t in game struct to be filled from protofile
 *
 * Returns:
 * - 0 if successful
 * - -1 if unsuccessful
 */
int load_attribute_value(Attribute_value *av, attribute_value_t *av_t);


/*
 * Loads attribute into game struct
 * 
 * Parameters:
 * - a: pointer to Attribute in protofile
 * - a_t: pointer to an empty attribute_t in game struct to be filled from protofile
 *
 * Returns:
 * - 0 if successful
 * - -1 if unsuccessful
 */
int load_attribute(Attribute *a, attribute_t *a_t);


/*
 * Loads item into game struct
 * 
 * Parameters:
 * - i: pointer to Item in protofile
 * - i_t: pointer to an empty item_t in game struct to be filled from protofile
 *
 * Returns:
 * - 0 if successful
 * - -1 if unsuccessful
 */
int load_item(Item *i, item_t *i_t);


/*
 * Loads condition into game struct
 * 
 * Parameters:
 * - c: pointer to Condition in protofile
 * - c_t: pointer to an empty condition_t in game struct to be filled from protofile
 *
 * Returns:
 * - 0 if successful
 * - -1 if unsuccessful
 */
int load_condition(Condition *c, condition_t *c_t);


/*
 * Loads path into game struct
 * 
 * Parameters:
 * - p: pointer to Path in protofile
 * - p_t: pointer to an empty path_t in game struct to be filled from protofile
 *
 * Returns:
 * - 0 if successful
 * - -1 if unsuccessful
 */
int load_path(Path *p, path_t *p_t);


/*
 * Loads room into game struct
 * 
 * Parameters:
 * - r: pointer to Room in protofile
 * - r_t: pointer to an empty room_t in game struct to be filled from protofile
 *
 * Returns:
 * - 0 if successful
 * - -1 if unsuccessful
 */
int load_room(Room *r, room_t *r_t);


/*
 * Loads player into game struct
 * 
 * Parameters:
 * - p: pointer to Player in protofile
 * - p_t: pointer to an empty player_t in game struct to be filled from protofile
 *
 * Returns:
 * - 0 if successful
 * - -1 if unsuccessful
 */
int load_player(Player *p, player_t *p_t);


/*
 * Loads game into game struct
 * 
 * Parameters:
 * - g: pointer to Game in protofile
 * - g_t: pointer to an empty game_t in game struct to be filled from protofile
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
 * - filename: pointer to string name of file with sereialized information
 * - g: pointer to proto game struct
 * - g_t: pointer game struct
 * 
 * Returns:
 * - 0 if successful
 * - -1 if unsuccessful
 */
int load(char *filename, Game *g, game_t *g_t);

#endif
