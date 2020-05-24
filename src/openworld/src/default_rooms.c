#include <stdlib.h>
#include <string.h>

#include "../../../include/common/utlist.h"
#include "../../../include/common/uthash.h"
#include "../../../include/openworld/default_rooms.h" 
#include "../../../include/openworld/default_items.h"

/* see default_rooms.h */
roomspec_t **get_allowed_rooms(char *bucket, char *sh_desc, char *l_desc) {

	//these types of rooms are shared by more than one themed room group
	roomspec_t *closet = roomspec_new("closet", "A broom closet",
		"A small broom closet with supplies",
		make_default_items("closet"), NULL, NULL);
	roomspec_t *hallway = roomspec_new("hallway", "A well-lit hallway",
		"A sterile, white hallway with no windows",
		make_default_items("hallway"), NULL, NULL);
	roomspec_t *library = roomspec_new("library", "This is a library room with resources",
		"An old, dusty library with skill-boosting resources like books and potions",
		make_default_items("library"), NULL, NULL);

	assert(bucket != NULL);

	/* I had to calloc the following roomspecs 
	* otherwise I'd be returning a local copy.
	*/
	if (!strcmp(bucket, "school")) {
		roomspec_t **school_rooms = calloc(5, sizeof(roomspec_t*));
		school_rooms[0] = roomspec_new("cafeteria", "A grungy cafeteria",
			"A messy high school cafeteria with trays and tables out",
			make_default_items("cafeteria"), NULL, NULL);
		school_rooms[1] = roomspec_new("classroom",
			"A medium-sized classroom with 30 desks",
			"A geography teacher's classroom with 30 desks",
			make_default_items("classroom"), NULL, NULL);
		school_rooms[2] = closet;
		school_rooms[3] = hallway;
		school_rooms[4] = library;
		return school_rooms;
	}
	else if (!strcmp(bucket, "farmhouse")) {
		roomspec_t **farm_rooms = calloc(5, sizeof(roomspec_t*));
		farm_rooms[0] = roomspec_new("barn", "A red barn",
			"A red barn with stables inside",
			make_default_items("barn"), NULL, NULL);
		farm_rooms[1] = roomspec_new("open field",
			"An open field outside",
			"An open field with grass and a clear view",
			make_default_items("open field"), NULL, NULL);
		farm_rooms[2] = roomspec_new("kitchen", "A 60s era (outdated) kitchen",
			"An outdated kitchen with obvious wear-and-tear",
			make_default_items("kitchen"), NULL, NULL);
		farm_rooms[3] = hallway;
		farm_rooms[4] = roomspec_new("living room", "A living room with basic items",
			"A plain, unremarkable living room",
			make_default_items("living room"), NULL, NULL);
		return farm_rooms;
	} else if(!strcmp(bucket, "castle")) {	
		roomspec_t **castle_rooms = calloc(5, sizeof(roomspec_t*));
		castle_rooms[0] = closet;
		castle_rooms[1] = roomspec_new("dungeon", "A dark dungeon",
			"A dank, dark dungeon with traps and enemies to battle",
			make_default_items("dungeon"), NULL, NULL);
		castle_rooms[2] = library;
		castle_rooms[3] = hallway;
		castle_rooms[4] = roomspec_new("throne room", "This is a throne room",
			"A regal throne room decked out with lavish items",
			make_default_items("throne room"), NULL, NULL);
		return castle_rooms;
	} else{
		roomspec_t **rooms = calloc(1, sizeof(roomspec_t*));
		rooms[0] = roomspec_new(bucket, sh_desc, l_desc,
			make_default_items(bucket), NULL, NULL);
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
		rooms[i]->allowed_items = make_default_items(rooms[i]->room_name);
		HASH_ADD_STR(hash, room_name, rooms[i]);
		i++;
	}
	return hash;
}

