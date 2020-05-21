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
			new_room->room->room_id = "barn";
			new_room->room->short_desc = "A red barn";
			new_room->room->long_desc = "A red barn with stables inside";
			add_item_to_fix_room(new_room, items_wanted, BARN);
			break;
		case CAFETERIA:
			new_room->room_tag = CAFETERIA;
			new_room->room->room_id = "cafeteria";
			new_room->room->short_desc = "A grungy cafeteria";
			new_room->room->long_desc = "A messy high school cafeteria with trays and tables out";
			add_item_to_fix_room(new_room, items_wanted, CAFETERIA);
			break;
		case CLASSROOM:
			new_room->room_tag = CLASSROOM;
			new_room->room->room_id = "classroom";
			new_room->room->short_desc = "A medium-sized classroom with 30 desks";
			new_room->room->long_desc = "A geography teacher's classroom with 30 desks";
			add_item_to_fix_room(new_room, items_wanted, CLASSROOM);
			break;
		case CLOSET:
			new_room->room_tag = CLOSET;
			new_room->room->room_id = "closet";
			new_room->room->short_desc = "A broom closet";
			new_room->room->long_desc = "A small broom closet with supplies";
			add_item_to_fix_room(new_room, items_wanted, CLOSET);
			break;
		case DUNGEON:
			new_room->room_tag = DUNGEON;
			new_room->room->room_id = "dungeon";
			new_room->room->short_desc = "A dark dungeon";
			new_room->room->long_desc = "A dank, dark dungeon with traps"
				" and enemies to battle";
			add_item_to_fix_room(new_room, items_wanted, DUNGEON);
			break;
		case FIELD:
			new_room->room_tag = FIELD;
			new_room->room->room_id = "open field";
			new_room->room->short_desc = "An open field outside";
			new_room->room->long_desc = "An open field with grass and a clear view";
			add_item_to_fix_room(new_room, items_wanted, FIELD);
			break;
		case HALLWAY:
			new_room->room_tag = HALLWAY;
			new_room->room->room_id = "hallway";
			new_room->room->short_desc = "A well-lit hallway";
			new_room->room->long_desc = "A sterile, white hallway with no windows";
			add_item_to_fix_room(new_room, items_wanted, HALLWAY);
			break;
		case KITCHEN:
			new_room->room_tag = KITCHEN;
			new_room->room->room_id = "kitchen";
			new_room->room->short_desc = "A 60s era (outdated) kitchen";
			new_room->room->long_desc = "An outdated kitchen with obvious wear-and-tear";
			add_item_to_fix_room(new_room, items_wanted, KITCHEN);
			break;
		case LIBRARY:
			new_room->room_tag = LIBRARY;
			new_room->room->room_id = "library";
			new_room->room->short_desc = "This is a library room with resources";
			new_room->room->long_desc = "An old, dusty library with skill-boosting"
									" resources like books and potions";
			add_item_to_fix_room(new_room, items_wanted, LIBRARY);
			break;
		case LIVING_ROOM:
			new_room->room_tag = LIVING_ROOM;
			new_room->room->room_id = "living room";
			new_room->room->short_desc = "A living room with basic items";
			new_room->room->long_desc = "A plain, unremarkable living room";
			add_items_to_fix_room(new_room, items_wanted, LIVING_ROOM);
			break;
		case THRONE_ROOM:
			new_room->room_tag = THRONE_ROOM;
			new_room->room->room_id = "throne room";
			new_room->room->short_desc = "This is a throne room";
			new_room->room->long_desc = "A regal throne room decked out with lavish items";
			add_item_to_fix_room(new_room, items_wanted, THRONE_ROOM);
			break;

		}
	return SUCCESS;
}

/* See sample_rooms.h */
fix_room_t *fix_room_new(fix_room_tag_t room_tag, int items_wanted)
{
	fix_room_t *room = malloc(sizeof(fix_room_t));
	memset(room, 0, sizeof(fix_room_t));
	int check = fix_room_init(room, room_tag, items_wanted);

	if (room == NULL || room->room->room_id == NULL 
		|| room->room->short_desc == NULL|| room->room->long_desc == NULL)
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
	free(room->room->room_id);
	free(room->room->short_desc);
	free(room->room->long_desc);
	free(room->room);
	free(room);
	return SUCCESS;
}

/* See sample_room.h */
int add_item_to_fix_room(fix_room_t *room, int items_wanted)
{
	fix_item_tag_t* avail;
	int rc, i, length = 0;

	switch (room->room_tag) {
		case BARN:
			avail[9] = { APPLE, COW, DOOR, FRUIT, LADDER, NAIL,
			RABBIT, YAM, ZEBRA };
			length = 9;
			break;
		case CAFETERIA:
			avail[9] = { APPLE, DOOR, FRUIT, ICE, JUG, KETTLE,
				OLIVE, TRAY, YAM };
			length = 9;
			break;
		case CLASSROOM:
			avail[10] = { BOOK, DOOR, HAT, PENCIL, QUILL, VIDEO,
				SCISSORS, TRAY, WATERCOLORS, XYLOPHONE };
			length = 10;
			break;
		case CLOSET:
			avail[8] = { GOLD, HAT, ICE, JUG, LADDER, NAIL,
				TRAY, UMBRELLA };
			length = 8;
			break;
		case DUNGEON:
			avail[4] = { DOOR, GOLD, LADDER, NAIL };
			length = 4;
			break;
		case FIELD:
			avail[7] = { APPLE, COW, EAGLE, RABBIT, NAIL,
				YAM, ZEBRA };
			length = 7;
			break;
		case HALLWAY:
			avail[4] = { DOOR, MIRROR, LADDER, NAIL };
			length = 4;
			break;
		case KITCHEN:
			avail[10] = { APPLE, DOOR, FRUIT, ICE, JUG, KETTLE,
				OLIVE, SCISSORS, TRAY, YAM };
			length = 10;
			break;
		case LIBRARY:
			avail[11] = { BOOK, DOOR, GOLD, LADDER, MIRROR,
				PENCIL, QUILL, SCISSORS, VIDEO,
				WATERCOLORS, XYLOPHONE };
			length = 11;
			break;
		case LIVING_ROOM:
			avail[8] = { BOOK, DOOR, FRUIT, MIRROR, UMBRELLA,
				VIDEO, WATERCOLORS, XYLOPHONE };
			length = 8;
			break;
		case THRONE_ROOM:
			avail[5] = { DOOR, GOLD, HAT, MIRROR, QUILL };
			length = 5;
			break;
	}

	for (i = 0; i < length; i++) {
		fix_item_t* item = fix_item_new(avail[rand() % length]);

		fix_item_t* check;
		HASH_FIND(hh, room->room->items, item->item-s>item_id,
			strlen(item->item->item_id), check);

		if (check != NULL)
		{
			return FAILURE; //this item id is already in use.
		}
		HASH_ADD_KEYPTR(hh, room->room->items, item->item->item_id,
			strlen(item->item->item_id), item);
	}
	return SUCCESS;
}

/* See sample_rooms.h */
char *get_sdesc_fix(fix_room_t *room)
{
	return room->room->short_desc;
}

/* See sample_rooms.h */
char *get_ldesc_fix(fix_room_t *room)
{
	return room->room->long_desc;
}

/* See sample_rooms.h */
item_hash_t* list_fix_items(fix_room_t *room)
{
	return room->room->items;
}

/* See sample_rooms.h */
path_hash_t *list_fix_paths(fix_room_t *room)
{
	return room->room->paths;
}

/* See sample_rooms.h */
fix_room_t* generate_room() {
	int key = (rand()) % 11;
	int items_wanted = (rand())%5;
	return fix_room_new(key, items_wanted);
}

