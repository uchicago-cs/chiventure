#include <stdlib.h>

#include "../../../include/openworld/sample_rooms.h" 
#include "../../../include/openworld/sample_items.h"

/* See room.h */
int room_init(room_t *new_room, char *room_id)
{
	assert(new_room != NULL)
	switch (room_id) {
		case "LIBRARY":
			new_room->room_tag = LIBRARY;
			library_t l;
			new_room.room_type = l;
			break;
		case "DUNGEON":
			new_room->room_tag = DUNGEON;
			dungeon_t d;
			new_room.room_type = d;
			break;
		case "OPEN_FIELD":
			new_room->room_tag = OPEN_FIELD;
			open_field_t f;
			new_room.room_type = f;
			break;
		}
	return SUCCESS;
}


room_t *room_new(char *room_id)
{

	room_t *room = malloc(sizeof(room_t));
	memset(room, 0, sizeof(room_t));

	int check = room_init(room, room_id, short_desc, long_desc);

	if (room == NULL || room->room_tag == NULL ||
		room->type == NULL)
	{
		return NULL;
	}

	if (check != SUCCESS)
	{
		return NULL;
	}

	return room;
}



/* See room.h */
int room_free(room_t *room)
{
	free(room->room_id);
	free(room.room_type);
	free(room);
	return SUCCESS;
}


/* See room.h */
char *get_sdesc(room_t *room)
{
	return room.room_type->short_desc;
}

/* See room.h */
char *get_ldesc(room_t *room)
{
	return room.room_type->long_desc;
}

/* Get list (implemented with hashtable) of items in room
*
* Parameters:
*  pointer to room
*
* Returns:
*  hashtable of items in room
*/
item_hash_t* list_items(room_t *room)
{
	return room.room_type->items;
}

/* Get list of paths from room
*
* Parameters:
*  pointer to room
*
* Returns:
*  pointer to hashtable of paths from room
*/
path_t *list_paths(room_t *room)
{
	return room.room_type->paths;
}

/* FOR CLI
* Implement a function that returns an item
* given an item_ID as string and a pointer to the current room.
*/

/* see room.h */
item_t* get_item_in_room(room_t* room, char* item_id)
{
	item_t* return_value;
	HASH_FIND(hh, room.room_type->items, item_id, strlen(item_id), return_value);
	return return_value;
	//if it is NULL, return_value will be equal to NULL by default
}


/* See room.h */
item_list_t *get_all_items_in_room(room_t *room)
{
	item_list_t *head = NULL;
	item_t *ITTMP_ITEMRM, *curr_item;
	item_list_t *tmp;
	HASH_ITER(hh, room.room_type->items, curr_item, ITTMP_ITEMRM)
	{
		tmp = malloc(sizeof(item_list_t));
		tmp->item = curr_item;
		LL_APPEND(head, tmp);
	}
	return head;
}
