#include <stdlib.h>
#include "room.h"

/* See room.h */
room_t *room_new(char *room_id, char *short_desc, char *long_desc, item_hash_t items, path_hash_t paths) {
  room_t *room = malloc(sizeof(room_t));
  room->room_id = room_id;
  room->short_desc = short_desc;
  room->long_desc = long_desc;
  room->items = items;
  room->paths = paths;
  return room;
}

/* See room.h */
int room_free(room_t *room) {
  //free(room_id);
  //free(room->short_desc);
  //free(room->long_desc);
  delete_all_paths(room->paths);
  delete_all_items(room->items);
  free(room);
  return 1;
}

/* See room.h */
int add_room_to_hash(room_hash_t all_rooms, char *room_id, room_t *room) {
    room_t *s;
    HASH_FIND_STR(all_rooms, room_id, s);
    if (s != NULL) {
        printf("FATAL: room_id already used!\n");
        exit(1);
    }
    HASH_ADD_STR(all_rooms, room_id, room);
    return 1;
}

/* See room.h */
int delete_all_rooms(room_hash_t rooms) {
    room_t *current_room, *tmp;
    HASH_ITER(hh, rooms, current_room, tmp) {
        HASH_DEL(rooms, current_room);  /* delete it (rooms advances to next) */
        room_free(current_room);             /* free it */
    }
    return 1;
}


/* Get short description of room
 *
 * Parameters:
 *  pointer to room
 *
 * Returns:
 *  short description string
 */
char *get_sdesc(room_t *room) {
  return room->short_desc;
}

/* Get long description of room
 *
 * Parameters:
 *  pointer to room
 *
 * Returns:
 *  long description string
 */
char *get_ldesc(room_t *room) {
  return room->long_desc;
}

/* Get list (implemented with hashtable) of items in room
 *
 * Parameters:
 *  pointer to room
 *
 * Returns:
 *  hashtable of items in room
 */
item_hash_t list_items(room_t *room) {
  return room->items;
}

//returns path to given room given hashtable of paths and room id
path_t *path_to_room(path_hash_t paths, char* room_id) {
  path_t *path;
  HASH_FIND_STR(paths, room_id, path);
  return path;
}

/* FOR ACTION MANAGEMENT
* go through hashtable of attributes
* check path for equal
* see item.h for fxn that checks equality
*/




