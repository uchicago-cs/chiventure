#ifndef LOAD_INT_H
#define LOAD_INT_H
#include "checkpointing/load.h"
#include "game.pb-c.h"
#include "game-state/item.h"
#include "action_management/actionmanagement.h"


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
 * Loads item into game struct
 * 
 * Parameters:
 * - i: pointer to Item in protofile
 * - i_t: pointer to an empty item_t in game struct to be filled from protofile
 *
 * Returns:
 * - 0 (SUCCESS) if successful
 * - 1 (FAILURE) if unsuccessful
 */
int load_item(Item *i, item_t *i_t);


/*
 * Loads room into game struct
 * 
 * Parameters:
 * - r: pointer to Room in protofile
 * - r_t: pointer to an empty room_t in game struct to be filled from protofile
 * - all_items: pointer to array of items in the room
 * - all_items_len: lenght of the all_items array
 *
 * Returns:
 * - 0 (SUCCESS) if successful
 * - 1 (FAILURE) if unsuccessful
 */
int load_room(Room *r, room_t *r_t, item_t **all_items, int all_items_len);


/*
 * Loads player into game struct
 * 
 * Parameters:
 * - p: pointer to Player in protofile
 * - p_t: pointer to an empty player_t in game struct to be filled from protofile
 * - all_items: pointer to array of items in the room
 * - all_items_len: lenght of the all_items array
 *
 * Returns:
 * - 0 (SUCCESS) if successful
 * - 1 (FAILURE) if unsuccessful
 */
int load_player(Player *p, player_t *p_t, item_t **all_items, int all_items_len);


/*
 * Loads game into game struct
 * 
 * Parameters:
 * - g: pointer to Game in protofile
 * - g_t: pointer to an empty game_t in game struct to be filled from protofile
 *
 * Returns:
 * - 0 (SUCCESS) if successful
 * - 1 (FAILURE) if unsuccessful
 */
int load_game(Game *g, game_t *g_t);


#endif
