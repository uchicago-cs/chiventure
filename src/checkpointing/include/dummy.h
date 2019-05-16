#ifndef DUMMY_H
#define DUMMY_H

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

#endif
