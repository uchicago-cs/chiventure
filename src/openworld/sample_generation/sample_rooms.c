#include <stdlib.h>

#include "../../../include/openworld/sample_rooms.h" 
#include "../../../include/openworld/sample_items.h"

/* See sample_rooms.h */
int room_init(room_t *new_room, room_tag_t room_tag)
{
	assert(new_room != NULL);
	switch (room_tag) {
		int rc;
		case LIBRARY:
			new_room->room_tag = LIBRARY;
			new_room->room_id = "library";
			new_room->short_desc = "This is a library room with resources";
			new_room->long_desc = "An old, dusty library with skill-boosting"
									" resources like books and potions";
			rc = add_item_to_room(new_room, item_new(BOOK));
			rc = add_item_to_room(new_room, item_new(DOOR));
			break;
		case DUNGEON:
			new_room->room_tag = DUNGEON;
			new_room->room_id = "dungeon";
			new_room->short_desc = "A dark dungeon";
			new_room->long_desc = "A dank, dark dungeon with traps"
									" and enemies to battle";
			rc = add_item_to_room(new_room, item_new(DOOR));
			rc = add_item_to_room(new_room, item_new(APPLE));
			break;
		case OPEN_FIELD:
			new_room->room_tag = OPEN_FIELD;
			new_room->room_id = "open field";
			new_room->short_desc = "An open field outside";
			new_room->long_desc = "An open field with grass and a clear view";
			rc = add_item_to_room(new_room, item_new(COW));
			rc = add_item_to_room(new_room, item_new(DOOR));
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

/* See sample_room.h */
int add_item_to_room(room_t *room, item_t *item)
{
	item_t* check;
	HASH_FIND(hh, room->items, item->item_id, strlen(item->item_id), check);

	if (check != NULL)
	{
		return FAILURE; //this item id is already in use.
	}
	HASH_ADD_KEYPTR(hh, room->items, item->item_id, strlen(item->item_id),
		item);
	return SUCCESS;

}

/* See sample_rooms.h */
int item_in_room(room_t* room, item_t* item) {
	item_list_t* llist = list_items(room);
	int i = 0;
	while (llist->item != NULL) {
		if(llist->item->hh = item->hh) {
			return 1;
		}
		llist = llist->next;
	}
	return 0;
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
item_list_t* list_items(room_t *room)
{
	return room->items;
}

/* See sample_rooms.h */
path_t *list_paths(room_t *room)
{
	return room->paths;
}


/* See sample_rooms.h */
room_t* generate_room() {
	int key = (rand()) % 3;
	return room_new(key);

}

/* See sample_rooms.h */
int path_init(path_t* new_path, room_t* dest, item_t* exit) {
	assert(new_path != NULL);
	assert(item_in_room(dest, exit));
	new_path->dest = dest;
	new_path->src_item = exit;
	return SUCCESS;
}

/* See sample_rooms.h */
path_t* path_new(room_t* dest, item_t* exit) {

	path_t *path = malloc(sizeof(path_t));
	memset(path, 0, sizeof(path_t));
	int check = path_init(path, dest, exit);

	if (path == NULL || path->dest == NULL || 
		path->src_item == NULL)
	{
		return NULL;
	}

	if (check != SUCCESS)
	{
		return NULL;
	}

	return path;

}

/* See sample_rooms.h */
int add_path_to_room(room_t *room, path_t *path){
	item_t* obj = path->src_item;
	if (item_in_room(room, obj) && check_exit_attr(obj)) {
		room->paths = path;
		return SUCCESS;
	}
	return FAILURE;
}

/* See sample_rooms.h */
path_t *path_search(room_t *room, char* direction)
{
	path_t *path;
	if (room == NULL)
	{
		return NULL; //cannot search path in NULL room
	}

	HASH_FIND(hh, room->paths, direction, strlen(direction), path);
	return path;
}

/* See sample_rooms.h */
room_t *find_room_from_path(path_t *path)
{
	if (path != NULL)
	{
		return path->dest;
	}
	return NULL;
}

/* See sample_rooms.h */
void connect_rooms(room_t* src, room_t* dest) {
	path_t* path = path_new(dest);
	int rc = add_path_to_room(src, path);
	return;
}

