#include <stdlib.h>

#include "../../../include/openworld/sample_rooms.h" 
#include "../../../include/openworld/sample_items.h"

/* See sample_rooms.h */
int room_init(room_t *new_room, room_tag_t room_tag)
{
	assert(new_room != NULL);
	switch (room_tag) {
		case LIBRARY:
			new_room->room_tag = LIBRARY;
			new_room->room_id = "library";
			new_room->short_desc = "This is a library room with resources";
			new_room->long_desc = "An old, dusty library with skill-boosting"
									" resources like books and potions";
			new_room->items  = item_new(BOOK);
			break;
		case DUNGEON:
			new_room->room_tag = DUNGEON;
			new_room->room_id = "dungeon";
			new_room->short_desc = "A dark dungeon";
			new_room->long_desc = "A dank, dark dungeon with traps"
									" and enemies to battle";
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

/* See sample_rooms.h */
room_t *room_new(room_tag_t room_tag)
{

	room_t *room = malloc(sizeof(room_t));
	memset(room, 0, sizeof(room_t));
	int check = room_init(room, room_tag);

	if (room == NULL || room->room_tag == NULL ||
		room->room_id == NULL || room->short_desc == NULL||
		room->long_desc == NULL)
	{
		return NULL;
	}

	if (check != SUCCESS)
	{
		return NULL;
	}

	return room;
}



/* See sample_rooms.h */
int room_free(room_t *room)
{
	free(room->room_id);
	free(room->short_desc);
	free(room->long_desc);
	free(room);
	return SUCCESS;
}


/* See sample_rooms.h */
char *get_sdesc(room_t *room)
{
	return room->short_desc;
}

/* See sample_rooms.h */
char *get_ldesc(room_t *room)
{
	return room->long_desc;
}

/* See sample_rooms.h */
item_hash_t* list_items(room_t *room)
{
	return room->items;
}

/* See sample_rooms.h */
path_t *list_paths(room_t *room)
{
	return room->paths;
}

