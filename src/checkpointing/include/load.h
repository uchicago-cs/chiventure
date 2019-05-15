#ifndef LOAD_H
#define LOAD_H

#include "../game.pb-c.h"

/*
 * Dummy Structs Generally Based off of Game-State's Structs
 */

typedef struct object {
  char *object_id;
  char *short_desc;
  char *long_desc;
  //placeholder tagged union thing;
} object_t;

typedef struct player {
  int player_id;
  char *username; // initialized to null if not in use
  int level; // initialized to -1 if not in use
  int health; // initialized to -1 if not in use
  int xp; // initialized to -1 if not in use
  object_t **inventory; // array of pointers inventory objects
  int inventory_len;
  object_t **clothes; // array of pointers clothes objects
  int clothes_len;
} player_t;

typedef struct room {
  char *room_id;
  char *short_desc;
  char *long_desc;
  int objs_len;
  object_t **objs; // array of pointers objects
  // path_t paths; // hashtable placeholder for potential paths
} room_t;

typedef struct game {
  player_t **players; // array of pointers of players
  int players_len;
  room_t **rooms; // array of pointers of rooms
  int rooms_len;
  char *curr_room; // room id
  int start_time;
} game_t;

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
static size_t read_file(char *filename, unsigned max_length, uint8_t *out);

/*
 * Prints out object saved in protofile and loads object into game struct
 * 
 * Parameters:
 * - o: pointer to object in protofile
 * - o_t: pointer to an empty object in game struct to be filled from protofile
 *
 * Returns:
 * - 0 if successful
 * - -1 if unsuccessful
 */
int print_object(Object *o, object_t *o_t);

/*
 * Prints out player saved in protofile and loads player into game struct
 * 
 * Parameters:
 * - p: pointer to player in protofile
 * - p_t: pointer to an empty player in game struct to be filled from protofile
 *
 * Returns:
 * - 0 if successful
 * - -1 if unsuccessful
 */
int print_player(Player *p, player_t *p_t);

/*
 * Prints out room saved in protofile and loads room into game struct
 * 
 * Parameters:
 * - r: pointer to room in protofile
 * - r_t: pointer to an empty room in game struct to be filled from protofile
 *
 * Returns:
 * - 0 if successful
 * - -1 if unsuccessful
 */
int print_room(Room *r, room_t *r_t);

/*
 * Prints out game saved in protofile and loads game into game struct
 * 
 * Parameters:
 * - g: pointer to game in protofile
 * - g_t: pointer to an empty game in game struct to be filled from protofile
 *
 * Returns:
 * - 0 if successful
 * - -1 if unsuccessful
 */
int print_game(Game *g, game_t *g_t);

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
