#include <stdlib.h>
#include "room.h"

/* See board.h */
room_t *room_new(char *short_desc, char *long_desc, all_objects_t *items, exit_t *exits) {
  /* TODO */
  return NULL;
}

/* See board.h */
int room_free(room_t *room) {
  /* TODO */
  return 0;
}

/* See board.h */
int add_room_to_hash(all_rooms_t all_rooms, int room_id, room_t *room) {
    room_t *s;
    HASH_FIND_INT(all_rooms, &room_id, s);
    if (s != NULL) {
        printf("FATAL: room_id already used!\n");
        exit(0);
    }
    HASH_ADD_INT(all_rooms, room_id, s);
    return 1;
}

/* See board.h */
int delete_all_rooms(all_rooms_t rooms) {
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
  /* TODO */
  return NULL;
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
  /* TODO */
  return NULL;
}

/* Get list (implemented with hashtable) of objects in room
 *
 * Parameters:
 *  pointer to room
 *
 * Returns:
 *  hashtable of items in room
 */
all_objects_t list_objs(room_t *room) {
  /* TODO */
  return NULL;
}

/* Get list of exits from room
 *
 * Parameters:
 *  pointer to room
 *
 * Returns:
 *  pointer to linked list of exits from room
 */
exit_t *list_exits(room_t *room) {
  /* TODO */
  return NULL;
}

//starting issue 47
