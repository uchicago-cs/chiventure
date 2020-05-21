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
			add_item_to_fix_room(new_room, items_wanted);
			break;
		case CAFETERIA:
			new_room->room_tag = CAFETERIA;
			new_room->room->room_id = "cafeteria";
			new_room->room->short_desc = "A grungy cafeteria";
			new_room->room->long_desc = "A messy high school cafeteria with trays and tables out";
			add_item_to_fix_room(new_room, items_wanted);
			break;
		case CLASSROOM:
			new_room->room_tag = CLASSROOM;
			new_room->room->room_id = "classroom";
			new_room->room->short_desc = "A medium-sized classroom with 30 desks";
			new_room->room->long_desc = "A geography teacher's classroom with 30 desks";
			add_item_to_fix_room(new_room, items_wanted);
			break;
		case CLOSET:
			new_room->room_tag = CLOSET;
			new_room->room->room_id = "closet";
			new_room->room->short_desc = "A broom closet";
			new_room->room->long_desc = "A small broom closet with supplies";
			add_item_to_fix_room(new_room, items_wanted);
			break;
		case DUNGEON:
			new_room->room_tag = DUNGEON;
			new_room->room->room_id = "dungeon";
			new_room->room->short_desc = "A dark dungeon";
			new_room->room->long_desc = "A dank, dark dungeon with traps"
				" and enemies to battle";
			add_item_to_fix_room(new_room, items_wanted);
			break;
		case FIELD:
			new_room->room_tag = FIELD;
			new_room->room->room_id = "open field";
			new_room->room->short_desc = "An open field outside";
			new_room->room->long_desc = "An open field with grass and a clear view";
			add_item_to_fix_room(new_room, items_wanted);
			break;
		case HALLWAY:
			new_room->room_tag = HALLWAY;
			new_room->room->room_id = "hallway";
			new_room->room->short_desc = "A well-lit hallway";
			new_room->room->long_desc = "A sterile, white hallway with no windows";
			add_item_to_fix_room(new_room, items_wanted);
			break;
		case KITCHEN:
			new_room->room_tag = KITCHEN;
			new_room->room->room_id = "kitchen";
			new_room->room->short_desc = "A 60s era (outdated) kitchen";
			new_room->room->long_desc = "An outdated kitchen with obvious wear-and-tear";
			add_item_to_fix_room(new_room, items_wanted);
			break;
		case LIBRARY:
			new_room->room_tag = LIBRARY;
			new_room->room->room_id = "library";
			new_room->room->short_desc = "This is a library room with resources";
			new_room->room->long_desc = "An old, dusty library with skill-boosting"
									" resources like books and potions";
			add_item_to_fix_room(new_room, items_wanted);
			break;
		case LIVING_ROOM:
			new_room->room_tag = LIVING_ROOM;
			new_room->room->room_id = "living room";
			new_room->room->short_desc = "A living room with basic items";
			new_room->room->long_desc = "A plain, unremarkable living room";
			add_item_to_fix_room(new_room, items_wanted);
			break;
		case THRONE_ROOM:
			new_room->room_tag = THRONE_ROOM;
			new_room->room->room_id = "throne room";
			new_room->room->short_desc = "This is a throne room";
			new_room->room->long_desc = "A regal throne room decked out with lavish items";
			add_item_to_fix_room(new_room, items_wanted);
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
	int rc, i, length = 0;

	fix_item_tag_t* avail;
	switch (room->room_tag) {
		case BARN: ;
			fix_item_tag_t barn[9] = { APPLE, COW, DOOR, FRUIT, LADDER, NAIL,
			RABBIT, YAM, ZEBRA };
			length = 9;
			avail = barn;
			break;
		case CAFETERIA: ;
			fix_item_tag_t cafe[9] = { APPLE, DOOR, FRUIT, ICE, JUG, KETTLE,
				OLIVE, TRAY, YAM };
			length = 9;
			avail = cafe;
			break;
		case CLASSROOM: ;
			fix_item_tag_t class[10] = { BOOK, DOOR, HAT, PENCIL, QUILL, VIDEO,
				SCISSORS, TRAY, WATERCOLORS, XYLOPHONE };
			length = 10;
			avail = class;
			break;
		case CLOSET: ;
			fix_item_tag_t closet[8] = { GOLD, HAT, ICE, JUG, LADDER, NAIL,
				TRAY, UMBRELLA };
			length = 8;
			avail = closet;
			break;
		case DUNGEON: ;
			fix_item_tag_t dungeon[4] = { DOOR, GOLD, LADDER, NAIL };
			length = 4;
			avail = dungeon;
			break;
		case FIELD: ;
			fix_item_tag_t field[7] = { APPLE, COW, EAGLE, RABBIT, NAIL,
				YAM, ZEBRA };
			length = 7;
			avail = field;
			break;
		case HALLWAY: ;
			fix_item_tag_t hall[4] = { DOOR, MIRROR, LADDER, NAIL };
			length = 4;
			avail = hall;
			break;
		case KITCHEN: ;
			fix_item_tag_t kitch[10] = { APPLE, DOOR, FRUIT, ICE, JUG, KETTLE,
				OLIVE, SCISSORS, TRAY, YAM };
			length = 10;
			avail = kitch;
			break;
		case LIBRARY: ;
			fix_item_tag_t libr[11] = { BOOK, DOOR, GOLD, LADDER, MIRROR,
				PENCIL, QUILL, SCISSORS, VIDEO,
				WATERCOLORS, XYLOPHONE };
			length = 11;
			avail = libr;
			break;
		case LIVING_ROOM: ;
			fix_item_tag_t living[8] = { BOOK, DOOR, FRUIT, MIRROR, UMBRELLA,
				VIDEO, WATERCOLORS, XYLOPHONE };
			length = 8;
			avail = living;
			break;
		case THRONE_ROOM: ;
			fix_item_tag_t throne[5] = { DOOR, GOLD, HAT, MIRROR, QUILL };
			length = 5;
			avail = throne;
			break;
		default:
			length = 0;
			break;
	}

	for (i = 0; i < length; i++) {
		fix_item_t* item = fix_item_new(avail[rand() % length]);
		rc = add_item_to_room(room->room, item->item);
	}
	return rc;
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

