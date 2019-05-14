/*
 * Header file for wdl/yaml parsing functions and related utilities
 */

#ifndef INCLUDE_CONNECT_GAME_H
#define INCLUDE_CONNECT_GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parse.h"

/* Creates the various attributes of a game within 
 * the game state team's structs
 */
void create_game(obj_t *obj);

/* Creates the various attributes of the rooms within 
 * the game state team's structs
 */
void create_rooms(attr_list_t *ls, game_t *g);

/* Creates the various attributes of the items within 
 * the game state team's structs
 */
void create_items(attr_list_t *ls);

/* Given a room id and the list of all items in a game returns
 * a list with all the items in that room */
attr_list_t* get_items_in_room(char* room_id, attr_list_t* all_items);

#endif /*INCLUDE_CONNECT_GAME_H*/

