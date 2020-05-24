#include <stdlib.h>
#include <string.h>

#include "../../../include/common/utlist.h"
#include "../../../include/common/uthash.h"
#include "../../../include/openworld/default_rooms.h" 
#include "../../../include/openworld/default_items.h"

/* see default_rooms.h */
roomspec_t **get_allowed_rooms(char *bucket, char *sh_desc, char *l_desc) {

	assert(bucket != NULL);
	item_hash_t *default_items = get_default_items();
	char *a;
	//these types of rooms are shared by more than one themed room group

	//CLOSET
	roomspec_t *closet = roomspec_new("closet", "A broom closet",
		"A small broom closet with supplies",
		NULL, NULL, NULL);
	LL_APPEND(closet->allowed_items, HASH_FIND_STR(default, "door", a));
	LL_APPEND(closet->allowed_items, HASH_FIND_STR(default, "nail", a));
	LL_APPEND(closet->allowed_items, HASH_FIND_STR(default, "mirror",a));
	LL_APPEND(closet->allowed_items, HASH_FIND_STR(default, "jug",a));
	LL_APPEND(closet->allowed_items, HASH_FIND_STR(default, "hat",a));

	//HALLWAY
	roomspec_t *hallway = roomspec_new("hallway", "A well-lit hallway",
		"A sterile, white hallway with no windows",
		NULL, NULL, NULL);
	LL_APPEND(closet->allowed_items, HASH_FIND_STR(default, "door"));
	LL_APPEND(closet->allowed_items, HASH_FIND_STR(default, "nail"));
	LL_APPEND(closet->allowed_items, HASH_FIND_STR(default, "fruit"));
	LL_APPEND(closet->allowed_items, HASH_FIND_STR(default, "tray"));
	LL_APPEND(closet->allowed_items, HASH_FIND_STR(default, "book"));

	//LIBRARY
	roomspec_t *library = roomspec_new("library", "This is a library room with resources",
		"An old, dusty library with skill-boosting resources like books and potions",
		NULL, NULL, NULL);
	LL_APPEND(closet->allowed_items, HASH_FIND_STR(default, "book"));
	LL_APPEND(closet->allowed_items, HASH_FIND_STR(default, "quill"));
	LL_APPEND(closet->allowed_items, HASH_FIND_STR(default, "pencil"));
	LL_APPEND(closet->allowed_items, HASH_FIND_STR(default, "vido"));
	LL_APPEND(closet->allowed_items, HASH_FIND_STR(default, "mirror"));

	assert(bucket != NULL);

	/* I had to calloc the following roomspecs 
	* otherwise I'd be returning a local copy.
	*/
	if (!strcmp(bucket, "school")) {
		roomspec_t **school_rooms = calloc(5, sizeof(roomspec_t*));
		//CLOSET + HALLWAY + LIBRARY
		school_rooms[0] = closet;
		school_rooms[1] = hallway;
		school_rooms[2] = library;

		//CAFETERIA
		school_rooms[3] = roomspec_new("cafeteria", "A grungy cafeteria",
			"A messy high school cafeteria with trays and tables out",
			NULL, NULL, NULL);
		LL_APPEND(school_rooms[0]->allowed_items, HASH_FIND_STR(default, "apple"));
		LL_APPEND(school_rooms[0]->allowed_items, HASH_FIND_STR(default, "fruit"));
		LL_APPEND(school_rooms[0]->allowed_items, HASH_FIND_STR(default, "tray"));
		LL_APPEND(school_rooms[0]->allowed_items, HASH_FIND_STR(default, "ice"));
		LL_APPEND(school_rooms[0]->allowed_items, HASH_FIND_STR(default, "yam"));

		//CLASSROOM
		school_rooms[4] = roomspec_new("classroom",
			"A medium-sized classroom with 30 desks",
			"A geography teacher's classroom with 30 desks",
			NULL, NULL, NULL);
		LL_APPEND(school_rooms[0]->allowed_items, HASH_FIND_STR(default, "book"));
		LL_APPEND(school_rooms[0]->allowed_items, HASH_FIND_STR(default, "door"));
		LL_APPEND(school_rooms[0]->allowed_items, HASH_FIND_STR(default, "pencil"));
		LL_APPEND(school_rooms[0]->allowed_items, HASH_FIND_STR(default, "watercolors"));
		LL_APPEND(school_rooms[0]->allowed_items, HASH_FIND_STR(default, "video"));
		return school_rooms;
	}
	else if (!strcmp(bucket, "farmhouse")) {
		roomspec_t **farm_rooms = calloc(5, sizeof(roomspec_t*));
		//HALLWAY
		farm_rooms[0] = hallway;

		//BARN
		farm_rooms[1] = roomspec_new("barn", "A red barn",
			"A red barn with stables inside",
			NULL, NULL, NULL);
		LL_APPEND(farm_rooms[1]->allowed_items, HASH_FIND_STR(default, "apple"));
		LL_APPEND(farm_rooms[1]->allowed_items, HASH_FIND_STR(default, "cow"));
		LL_APPEND(farm_rooms[1]->allowed_items, HASH_FIND_STR(default, "eagle"));
		LL_APPEND(farm_rooms[1]->allowed_items, HASH_FIND_STR(default, "rabbit"));
		LL_APPEND(farm_rooms[1]->allowed_items, HASH_FIND_STR(default, "yam"));

		//OPEN FIELD
		farm_rooms[2] = roomspec_new("open field",
			"An open field outside",
			"An open field with grass and a clear view",
			NULL, NULL, NULL);
		LL_APPEND(farm_rooms[2]->allowed_items, HASH_FIND_STR(default, "zebra"));
		LL_APPEND(farm_rooms[2]->allowed_items, HASH_FIND_STR(default, "cow"));
		LL_APPEND(farm_rooms[2]->allowed_items, HASH_FIND_STR(default, "eagle"));
		LL_APPEND(farm_rooms[2]->allowed_items, HASH_FIND_STR(default, "rabbit"));
		LL_APPEND(farm_rooms[2]->allowed_items, HASH_FIND_STR(default, "apple"));

		//KITCHEN
		farm_rooms[3] = roomspec_new("kitchen", "A 60s era (outdated) kitchen",
			"An outdated kitchen with obvious wear-and-tear",
			NULL, NULL, NULL);
		LL_APPEND(farm_rooms[3]->allowed_items, HASH_FIND_STR(default, "olive"));
		LL_APPEND(farm_rooms[3]->allowed_items, HASH_FIND_STR(default, "ice"));
		LL_APPEND(farm_rooms[3]->allowed_items, HASH_FIND_STR(default, "jug"));
		LL_APPEND(farm_rooms[3]->allowed_items, HASH_FIND_STR(default, "yam"));
		LL_APPEND(farm_rooms[3]->allowed_items, HASH_FIND_STR(default, "tray"));

		//LIVING ROOM
		farm_rooms[4] = roomspec_new("living room", "A living room with basic items",
			"A plain, unremarkable living room",
			NULL, NULL, NULL);
		LL_APPEND(farm_rooms[4]->allowed_items, HASH_FIND_STR(default, "watercolors"));
		LL_APPEND(farm_rooms[4]->allowed_items, HASH_FIND_STR(default, "video"));
		LL_APPEND(farm_rooms[4]->allowed_items, HASH_FIND_STR(default, "xylophone"));
		LL_APPEND(farm_rooms[4]->allowed_items, HASH_FIND_STR(default, "hat"));
		LL_APPEND(farm_rooms[4]->allowed_items, HASH_FIND_STR(default, "mirror"));

		return farm_rooms;
	} else if(!strcmp(bucket, "castle")) {	
		roomspec_t **castle_rooms = calloc(5, sizeof(roomspec_t*));
		//CLOSET + HALLWAY + LIBRARY
		castle_rooms[0] = closet;
		castle_rooms[1] = library;
		castle_rooms[2] = hallway;

		//DUNGEON
		castle_rooms[3] = roomspec_new("dungeon", "A dark dungeon",
			"A dank, dark dungeon with traps and enemies to battle",
			NULL, NULL, NULL);
		LL_APPEND(castle_rooms[3]->allowed_items, HASH_FIND_STR(default, "nail"));
		LL_APPEND(castle_rooms[3]->allowed_items, HASH_FIND_STR(default, "ladder"));
		LL_APPEND(castle_rooms[3]->allowed_items, HASH_FIND_STR(default, "book"));
		LL_APPEND(castle_rooms[3]->allowed_items, HASH_FIND_STR(default, "gold"));
		LL_APPEND(castle_rooms[3]->allowed_items, HASH_FIND_STR(default, "yam"));

		//THRONE ROOM
		castle_rooms[4] = roomspec_new("throne room", "This is a throne room",
			"A regal throne room decked out with lavish items",
			NULL, NULL, NULL);
		LL_APPEND(castle_rooms[4]->allowed_items, HASH_FIND_STR(default, "gold"));
		LL_APPEND(castle_rooms[4]->allowed_items, HASH_FIND_STR(default, "door"));
		LL_APPEND(castle_rooms[4]->allowed_items, HASH_FIND_STR(default, "mirror"));
		LL_APPEND(castle_rooms[4]->allowed_items, HASH_FIND_STR(default, "jug"));
		LL_APPEND(castle_rooms[4]->allowed_items, HASH_FIND_STR(default, "hat", a));

		return castle_rooms;
	} else{
		roomspec_t **rooms = calloc(1, sizeof(roomspec_t*));
		rooms[0] = roomspec_new(bucket, sh_desc, l_desc,
			NULL, NULL, NULL);
		return rooms;
	}
}

/* see default_rooms.h */
roomspec_t *make_default_room(char *bucket, char *sh_desc, char *l_desc) {

	roomspec_t *hash = NULL;
	//get allowed rooms and defined descriptions
	roomspec_t **rooms = get_allowed_rooms(bucket, sh_desc, l_desc);

	int i = 0;
	while (rooms[i] != NULL) {
		//already adding allowed items when I initialize rooms
		HASH_ADD_STR(hash, room_name, rooms[i]);
		i++;
	}
	return hash;
}

