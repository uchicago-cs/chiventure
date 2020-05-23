#include <stdlib.h>
#include <string.h>

#include "../../../include/openworld/sample_rooms.h" 
#include "../../../include/openworld/sample_items.h"
#include "../../../include/openworld/gen_structs.h"

/* see sample_rooms.h */
char ***get_desc_room(char *bucket, char *sh_desc, char *l_desc) {
	char *barn[3] = { "barn", "A red barn", 
		"A red barn with stables inside" };
	char *cafeteria[3] = { "cafeteria", "A grungy cafeteria" ,
		"A messy high school cafeteria with trays and tables out" };
	char *classroom[3] = { "classroom",
		"A medium-sized classroom with 30 desks" ,
		"A geography teacher's classroom with 30 desks" };
	char *closet[3] = { "A broom closet",
		"A small broom closet with supplies" };
	char *dungeon[3] = { "dungeon", "A dark dungeon",
		"A dank, dark dungeon with traps and enemies to battle" };
	char *field[3] = { "open field", 
		"An open field outside", 
		"An open field with grass and a clear view" };
	char *hallway[3] = { "hallway", "A well-lit hallway", 
		"A sterile, white hallway with no windows" };
	char *kitchen[3] = {"kitchen", "A 60s era (outdated) kitchen", 
		"An outdated kitchen with obvious wear-and-tear"};
	char *library[3]= {"library", "This is a library room with resources",
		"An old, dusty library with skill-boosting resources like books and potions" };
	char *living_room[3] = 	{"living room", "A living room with basic items", 
		"A plain, unremarkable living room"};
	char *throne_room[3] = { "throne room", "This is a throne room", 
		"A regal throne room decked out with lavish items"};

	assert(bucket != NULL);
	switch(bucket){
		case !strcmp(bucket, "school"):
			return { cafeteria, classroom, closet,
			field, hallway,  library };
		case !strmp(bucket, "farmhouse"):
			return { barn, closet , field,
				kitchen, hallway, living_room };
		case !strcmp(bucket, "castle"):
			return { closet, dungeon, living_room,
				library, hallway, throne_room };
		default:
			//will return NULL (which will throw error) if bucket empty
			//or should I add some error code here??
			return { { bucket, sh_desc, l_desc } };
	}
}

/* see sample_rooms.h */
roomspec_t *make_default_room(char *bucket, char *sh_desc, char *l_desc,
	item_list_t *items) {
	roomspec_t *hash = NULL;

	//get room name and defined descriptions
	char ***desc = get_desc_room(bucket, sh_desc, l_desc);

	int i = 0;

	while (desc[i] != NULL) {
		item_list_t *allowed = get_allowed_items(desc[i][0], items);

		//create the new roomspec that's eventually added to hash at end
		roomspec_t *match = roomspec_new(desc[i][0], desc[i][1],
			desc[i][2], allowed, NULL, NULL);

		//count number of allowed items
		unsigned int count = DL_COUNT(match->allowed_items);

		//generate actual item list from allowed items
		for (unsigned int i = 0; i < count; i++) {
			//get the item description strings given an id  from allowed items
			char **details = get_desc_item(match->allowed_items[i]);
			//add the "random" item details from allowed_items to a new item
			item_t *new_item = item_new(details[0], details[1], details[2]);
			//append this to item_hash_t for this room spec
			DL_APPEND(match->items, new_item);
			HASH_ADD_STR(hash, room->room_id, match);
		}
		i++;
	}
	return hash;
}

