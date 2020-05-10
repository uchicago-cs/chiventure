#include <stdlib.h>

#include "../../../include/openworld/sample_rooms.h" 
#include "../../../include/openworld/sample_items.h"

/* See room.h */
int room_init(room_t *new_room, room_tag_t room_tag)
{
	assert(new_room != NULL);
	switch (room_tag) {
		case LIBRARY:
			new_room->room_tag = LIBRARY;
			new_room->room_id = "library";
			new_room->short_desc = "This is a library room with resources";
			new_room->long_desc = "An old, dusty library with skill-boosting resources like books and potions";
			new_room->items  = item_new(BOOK);
			break;
		case DUNGEON:
			new_room->room_tag = DUNGEON;
			new_room->room_id = "dungeon";
			new_room->short_desc = "A dark dungeon";
			new_room->long_desc = "A dank, dark dungeon with traps and enemies to battle";
			new_room->items = item_new(APPLE);
			break;
		case OPEN_FIELD:
			new_room->room_tag = OPEN_FIELD;
			new_room->room_id = "open field";
			new_room->short_desc = "An open field outside";
			new_room->long_desc = "An open field with grass and a clear view";
			new_room->items = item_new(COW);
			break;
		}
	return SUCCESS;
}


room_t *room_new(room_tag_t room_tag)
{

	room_t *room = malloc(sizeof(room_t));
	memset(room, 0, sizeof(room_t));
	int check = room_init(room, room_tag);

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
	free(room->short_desc);
	free(room->long_desc);
	free(room);
	return SUCCESS;
}


/* See room.h */
char *get_sdesc(room_t *room)
{
	return room->short_desc;
}

/* See room.h */
char *get_ldesc(room_t *room)
{
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
item_hash_t* list_items(room_t *room)
{
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
path_t *list_paths(room_t *room)
{
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
	return return_value;
	//if it is NULL, return_value will be equal to NULL by default
}
