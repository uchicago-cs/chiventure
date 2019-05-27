#include <stdlib.h>
#include "common-item.h"
#include "common-item.h"
#include "common-room.h"
#include "common-path.h"

/* See room.h */
int room_init(room_t *new_room, char *room_id, char *short_desc, char *long_desc) {

    assert(new_room != NULL);

    strncpy(new_room->room_id, room_id, strlen(room_id));
    strncpy(new_room->short_desc, short_desc, strlen(short_desc));
    strncpy(new_room->long_desc, long_desc, strlen(long_desc));

    return SUCCESS;
}

room_t *room_new(char *room_id, char *short_desc, char *long_desc) {

    room_t *room = malloc(sizeof(room_t));
    room->room_id = malloc(MAX_ID_LEN);
    room->short_desc = malloc(MAX_SDESC_LEN);
    room->long_desc = malloc(MAX_LDESC_LEN);
    int check = room_init(room, room_id, short_desc, long_desc);

    if (room == NULL || room->room_id == NULL ||
       room->short_desc == NULL || room->long_desc == NULL) {
        exit(1);
    }

    if(check != SUCCESS) {
        exit(1);
    }

    return room;
}



/* See room.h */
int room_free(room_t *room) {
    free(room->room_id);
    free(room->short_desc);
    free(room->long_desc);
    delete_all_paths(room->paths);
    delete_all_items(room->items);
    // uthash_free(room->paths, sizeof(room->paths));
    // uthash_free(room->items, sizeof(room->items));
    free(room);
    return SUCCESS;
}


/* See room.h */
int add_item_to_room(room_t *room, item_t *item) {
    item_t* check;
    HASH_FIND(hh, room->items, item->item_id, strlen(item->item_id), check);

    if (check != NULL) {
        /* WARNING */
        /* SHOULD BE ABLE TO SUPPORT STACKING MULTIPLE items */
        fprintf(stderr, "add_item_to_room: this item id is already in use.\n");
        exit(1);
    }
    HASH_ADD_KEYPTR(hh, room->items, item->item_id, strlen(item->item_id), item);
    return SUCCESS;

}

/* See room.h */
int add_path_to_room(room_t *room, path_t *path) {
    path_t *s;
    HASH_FIND(hh, room->paths, path->direction, strlen(path->direction), s);
    if (s != NULL) {
        fprintf(stderr, "add_path_to_room: direction already used!\n");
        exit(1);
    }
    HASH_ADD_KEYPTR(hh, room->paths, path->direction, strlen(path->direction), path);
    return SUCCESS;
}

/* See common-room.h */
int delete_all_rooms(room_hash_t rooms) {
    room_t *current_room, *tmp;
    HASH_ITER(hh, rooms, current_room, tmp) {
        HASH_DEL(rooms, current_room);  /* delete it (rooms advances to next) */
        room_free(current_room);             /* free it */
    }
    return SUCCESS;
}

/* See room.h */
path_t *path_search(room_t *room, char* direction) {
  path_t *path;
  HASH_FIND(hh, room->paths, direction, strlen(direction), path);
  return path;
}

/* See room.h */
char *get_sdesc(room_t *room) {
    return room->short_desc;
}

/* See room.h */
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

/* Get list of paths from room
 *
 * Parameters:
 *  pointer to room
 *
 * Returns:
 *  pointer to hashtable of paths from room
 */
path_t *list_paths(room_t *room) {
  return room->paths;
}

/* FOR CLI
* Implement a function that returns an item
* given an item_ID as string and a pointer to the current room.
*/

/* see room.h */
item_t* get_item_in_room(room_t* room, char* item_id)
{
    item_t* return_value;
    HASH_FIND(hh, room->items, item_id, strlen(item_id), return_value);
    if (return_value == NULL) {
        return NULL;
    }
    return return_value;
}


/* See room.h */
room_t *find_room_from_path(path_t *path) {
    if(path != NULL)
        return path->dest;
    return NULL;
}

/* See room.h */
room_t *find_room_from_dir(room_t *curr, char* direction) {
    path_t *path = path_search(curr, direction);
    room_t *room_adj = find_room_from_path(path);
    return room_adj;
}