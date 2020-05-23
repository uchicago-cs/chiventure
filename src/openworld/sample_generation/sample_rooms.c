#include <stdlib.h>
#include <string.h>

#include "../../../include/openworld/sample_rooms.h" 

/* see sample_rooms.h */
roomspec_t **get_allowed_room(char *bucket, char *sh_desc, char *l_desc,
	item_list_t *llist) {

	if (llist == NULL) {
		llist = item_list_new();
	}
	roomspec_t *barn = roomspec_new("barn", "A red barn",
		"A red barn with stables inside",
		get_allowed_items("barn", llist), NULL, NULL);
	roomspec_t *cafeteria = roomspec_new(("cafeteria", "A grungy cafeteria",
		"A messy high school cafeteria with trays and tables out",
		get_allowed_items("cafeteria", llist), NULL, NULL);
	roomspec_t *classroom = roomspec_new("classroom",
		"A medium-sized classroom with 30 desks",
		get_allowed_items("classroom", llist), NULL, NULL);
	"A geography teacher's classroom with 30 desks");
	roomspec_t *closet = roomspec_new(("closet", "A broom closet",
		"A small broom closet with supplies",
		get_allowed_items("closet", llist), NULL, NULL);
	roomspec_t *dungeon = roomspec_new(("dungeon", "A dark dungeon",
		"A dank, dark dungeon with traps and enemies to battle",
		get_allowed_items("dungeon", llist), NULL, NULL);
	roomspec_t *field = roomspec_new("open field",
		"An open field outside",
		"An open field with grass and a clear view",
		get_allowed_items("open field", llist), NULL, NULL);
	roomspec_t *hallway = roomspec_new("hallway", "A well-lit hallway",
		"A sterile, white hallway with no windows",
		get_alowed_items("hallway", llist), NULL, NULL);
	roomspec_t *kitchen = roomspec_new("kitchen", "A 60s era (outdated) kitchen",
		"An outdated kitchen with obvious wear-and-tear",
		get_allowed_items("kitchen", llist), NULL, NULL);
	roomspec_t *library = roomspec_new("library", "This is a library room with resources",
		"An old, dusty library with skill-boosting resources like books and potions",
		get_allowed_items("library", llist), NULL, NULL);
	roomspec_t *living_room = roomspec_new("living room", "A living room with basic items",
		"A plain, unremarkable living room",
		get_allowed_items("living room", llist), NULL, NULL);
	roomspec_t *throne_room = roomspec_new("throne room", "This is a throne room",
		"A regal throne room decked out with lavish items",
		get_allowed_items("throne room", llist), NULL, NULL);

	assert(bucket != NULL);

	if (!strcmp(bucket, "school")) {
		roomspec_t **school_rooms = { cafeteria, classroom, closet,
		field, hallway,  library };
		return school_rooms;
	}
	else if (!strcmp(bucket, "farmhouse")) {
		roomspec_t **farm_rooms = { barn, closet , field,
			kitchen, hallway, living_room };
		return farm_rooms;
	} else if(!strcmp(bucket, "castle")) {	
		roomspec_t **castle_rooms = { closet, dungeon, living_room,
			library, hallway, throne_room };
		return castle_rooms;
	} else{
		return &roomspec_new(bucket, sh_desc, l_desc,
			get_allowed_items(bucket, llist), NULL, NULL);
	}
}

/* see sample_rooms.h */
roomspec_t *make_default_room(char *bucket, char *sh_desc, char *l_desc,
	item_list_t *items) {
	roomspec_t *hash = NULL;

	//get allowed rooms and defined descriptions
	roomspec_t **rooms = get_allowed_room(bucket, sh_desc, l_desc, item_list_t *items);

	int i = 0;

	while (rooms[i] != NULL) {
		//count number of allowed items
		unsigned int count = DL_COUNT(rooms[i]->allowed_items);

		//generate actual item list from allowed items
		for (unsigned int i = 0; i < count; i++) {
			//get the item description strings given an id  from allowed items
			char **details = get_desc_item(rooms[i]->allowed_items->item->item_id);
			//add the "random" item details from allowed_items to a new item
			item_t *new_item = item_new(details[0], details[1], details[2]);
			//append this to item_hash_t for this room spec
			DL_APPEND(rooms[i]->allowed_items, new_item);
			HASH_ADD_STR(hash, room_name, rooms[i]);
			//iterate to next allowed item
			rooms[i]->allowed_items = rooms[i]->allowed_items->next;
		}
		i++;
	}
	return hash;
}

