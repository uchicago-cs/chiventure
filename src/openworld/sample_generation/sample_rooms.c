#include <stdlib.h>

#include "../../../include/openworld/sample_rooms.h" 
#include "../../../include/openworld/sample_items.h"

/* See sample_rooms.h */
int fix_room_init(fix_room_t *new_room, fix_room_tag_t room_tag, int items_wanted)
{
	assert(new_room != NULL);
	switch (room_tag) {
		int rc;
		case BARN:
			new_room->room_tag = BARN;
			new_room->room_id = "barn";
			new_room->short_desc = "A red barn";
			new_room->long_desc = "A red barn with stables inside";
			rc = add_items_to_barn(new_room, items_wanted);
			break;
		case CAFETERIA:
			new_room->room_tag = CAFETERIA;
			new_room->room_id = "cafeteria";
			new_room->short_desc = "A grungy cafeteria";
			new_room->long_desc = "A messy high school cafeteria with trays and tables out";
			rc = add_items_to_cafeteria(new_room, items_wanted);
			break;
		case CLASSROOM:
			new_room->room_tag = CLASSROOM;
			new_room->room_id = "classroom";
			new_room->short_desc = "A medium-sized classroom with 30 desks";
			new_room->long_desc = "A geography teacher's classroom with 30 desks";
			rc = add_items_to_classroom(new_room, items_wanted);
			break;
		case CLOSET:
			new_room->room_tag = CLOSET;
			new_room->room_id = "closet";
			new_room->short_desc = "A broom closet";
			new_room->long_desc = "A small broom closet with supplies";
			rc = add_items_to_closet(new_room, items_wanted);
			break;
		case DUNGEON:
			new_room->room_tag = DUNGEON;
			new_room->room_id = "dungeon";
			new_room->short_desc = "A dark dungeon";
			new_room->long_desc = "A dank, dark dungeon with traps"
				" and enemies to battle";
			rc = add_items_to_dungeon(new_room, items_wanted);
			break;
		case FIELD:
			new_room->room_tag = FIELD;
			new_room->room_id = "open field";
			new_room->short_desc = "An open field outside";
			new_room->long_desc = "An open field with grass and a clear view";
			rc = add_items_to_field(new_room, items_wanted);
			break;
		case HALLWAY:
			new_room->room_tag = HALLWAY;
			new_room->room_id = "hallway";
			new_room->short_desc = "A well-lit hallway";
			new_room->long_desc = "A dank, dark dungeon with traps"
				" and enemies to battle";
			rc = add_items_to_hallway(new_room, items_wanted);
			break;
		case KITCHEN:
			new_room->room_tag = KITCHEN;
			new_room->room_id = "kitchen";
			new_room->short_desc = "A 60s era (outdated) kitchen";
			new_room->long_desc = "An outdated kitchen with obvious wear-and-tear";
			rc = add_items_to_kitchen(new_room, items_wanted);
			break;
		case LIBRARY:
			new_room->room_tag = LIBRARY;
			new_room->room_id = "library";
			new_room->short_desc = "This is a library room with resources";
			new_room->long_desc = "An old, dusty library with skill-boosting"
									" resources like books and potions";
			rc = add_items_to_library(new_room, items_wanted);
			break;
		case LIVING_ROOM:
			new_room->room_tag = LIVING_ROOM;
			new_room->room_id = "living room";
			new_room->short_desc = "A living room with basic items";
			new_room->long_desc = "A plain, unremarkable living room";
			rc = add_items_to_living(new_room, items_wanted);
			break;
		case THRONE_ROOM:
			new_room->room_tag = THRONE_ROOM;
			new_room->room_id = "throne room";
			new_room->short_desc = "This is a throne room";
			new_room->long_desc = "A regal throne room decked out with lavish items";
			rc = add_items_to_throne(new_room, items_wanted);
			break;

		}
	return SUCCESS;
}

/* See sample_rooms.h */
fix_room_t *fix_room_new(fix_room_tag_t room_tag)
{
	fix_room_t *room = malloc(sizeof(fix_room_t));
	memset(room, 0, sizeof(fix_room_t));
	int check = fix_room_init(room, room_tag);

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
int fix_room_free(fix_room_t *room)
{
	free(room->room_id);
	free(room->short_desc);
	free(room->long_desc);
	free(room);
	return SUCCESS;
}

/* See sample_room.h */
int add_item_to_room(fix_room_t *room, item_t *item)
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

void add_items_to_barn(fix_room_t *room, int items_wanted) {
	//can add apple, cow, fruit, ladder, nail, rabbit, yam, zebra
	item_tag_t *avail_barn = { APPLE, COW, DOOR, FRUIT, LADDER, NAIL,
						 RABBIT, YAM, ZEBRA };
	int i = 0, rc;
	for (i = 0; i < item; i++) {
		rc = add_item_to_room(room, item_new(avail[rand() % 9]));
	}
	return rc;
}

void add_items_to_cafeteria(fix_room_t *room, int items_wanted) {
	item_tag_t *avail = { APPLE, DOOR, FRUIT, ICE, JUG, KETTLE, 
						OLIVE, TRAY, YAM };
	int i = 0, rc;
	for (i = 0; i < item; i++) {
		rc = add_item_to_room(room, item_new(avail[rand() % 9]));
	}
	return rc;
}

void add_items_to_classroom(fix_room_t *room, int items_wanted) {
	item_tag_t *avail = { BOOK, DOOR, HAT, PENCIL, QUILL, VIDEO,
						SCISSORS, TRAY, WATERCOLORS, XYLOPHONE };
	int i = 0, rc;
	for (i = 0; i < item; i++) {
		rc = add_item_to_room(room, item_new(avail[rand() % 10]));
	}
	return rc;
}

void add_items_to_closet(fix_room_t *room, int items_wanted) {
	item_tag_t *avail = { GOLD, HAT, ICE, JUG, LADDER, NAIL,
							TRAY, UMBRELLA };
	int i = 0, rc;
	for (i = 0; i < item; i++) {
		rc = add_item_to_room(room, item_new(avail[rand() % 8]));
	}
	return rc;
}

void add_items_to_dungeon(fix_room_t *room, int items_wanted) {
	item_tag_t *avail = { DOOR, GOLD, LADDER, NAIL};
	int i = 0, rc;
	for (i = 0; i < item; i++) {
		rc = add_item_to_room(room, item_new(avail[rand() % 4]));
	}
	return rc;
}

void add_items_to_field(fix_room_t *room, int items_wanted) {
	item_tag_t *avail = { APPLE, COW, EAGLE, RABBIT, NAIL,
						YAM, ZEBRA };
	int i = 0, rc;
	for (i = 0; i < item; i++) {
		rc = add_item_to_room(room, item_new(avail[rand() % 7]));
	}
	return rc;
}

void add_items_to_hallway(fix_room_t *room, int items_wanted) {
	item_tag_t *avail = { DOOR, MIRROR, LADDER, NAIL };
	int i = 0, rc;
	for (i = 0; i < item; i++) {
		rc = add_item_to_room(room, item_new(avail[rand() % 4]));
	}
	return rc;
}

void add_items_to_kitchen(fix_room_t *room, int items_wanted) {
	item_tag_t *avail = { APPLE, DOOR, FRUIT, ICE, JUG, KETTLE,
							OLIVE, SCISSORS, TRAY, YAM };
	int i = 0, rc;
	for (i = 0; i < item; i++) {
		rc = add_item_to_room(room, item_new(avail[rand() % 10]));
	}
	return rc;
}

void add_items_to_library(fix_room_t *room, int items_wanted) {
	item_tag_t *avail = { BOOK, DOOR, GOLD, LADDER, MIRROR, 
						PENCIL, QUILL, SCISSORS, VIDEO,
						WATERCOLORS, XYLOPHONE };
	int i = 0, rc;
	for (i = 0; i < item; i++) {
		rc = add_item_to_room(room, item_new(avail[rand() % 11]));
	}
	return rc;
}

void add_items_to_living(fix_room_t *room, int items_wanted) {
	item_tag_t *avail = { BOOK, DOOR, FRUIT, MIRROR, UMBRELLA, 
						VIDEO, WATERCOLORS, XYLOPHONE };
	int i = 0, rc;
	for (i = 0; i < item; i++) {
		rc = add_item_to_room(room, item_new(avail[rand() % 8]));
	}
	return rc;
}

void add_items_to_throne(fix_room_t *room, int items_wanted) {
	item_tag_t *avail = { DOOR, GOLD, HAT, MIRROR, QUILL };
	int i = 0, rc;
	for (i = 0; i < item; i++) {
		rc = add_item_to_room(room, item_new(avail[rand() % 5]));
	}
	return rc;
}

/* See sample_rooms.h */
int item_in_room(fix_room_t* room, item_t* item) {
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
char *get_sdesc(fix_room_t *room)
{
	return room->short_desc;
}

/* See sample_rooms.h */
char *get_ldesc(fix_room_t *room)
{
	return room->long_desc;
}

/* See sample_rooms.h */
item_list_t* list_items(fix_room_t *room)
{
	return room->items;
}

/* See sample_rooms.h */
path_t *list_paths(fix_room_t *room)
{
	return room->paths;
}


/* See sample_rooms.h */
fix_room_t* generate_room() {
	int key = (rand()) % 11;
	return fix_room_new(key, rand()%3);

}

