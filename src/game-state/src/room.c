#include <stdlib.h>
#include "room.h"
#include "object.h"

/* See board.h */
room_t *room_new(char *short_desc, char *long_desc, llist_t *items, llist_t *exits) {
  /* TODO */
  return NULL;
}

/* See board.h */
int room_free(room_t *room) {
  /* TODO */
  return 0;
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

/* Get list of objects in room
 *
 * Parameters:
 *  pointer to room
 *
 * Returns:
 *  pointer to linked list of items in room
 */
llist_t *list_objs(room_t *room) {
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
llist_t *list_exits(room_t *room) {
  /* TODO */
  return NULL;
}

