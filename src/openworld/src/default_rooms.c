#include <stdlib.h>
#include <string.h>

#include "../../../include/common/utlist.h"
#include "../../../include/common/uthash.h"
#include "../../../include/openworld/default_rooms.h" 
#include "../../../include/openworld/default_items.h"

/* helper function solely to initialize an
* item list given an item found in the hash
*/
item_list_t *llist_new(item_t* item){
	item_list_t* llist = calloc(1, sizeof(item_list_t));
	llist->item =item;
	llist->next = NULL;
	return llist;
}

/* see default_rooms.h */
roomspec_t **get_allowed_rooms(char *bucket, char *sh_desc, char *l_desc,
item_list_t *allowed) {

	assert(bucket != NULL);
	item_hash_t *def = get_default_items();

	item_t *door, *nail, *mirror, *jug, *hat,
		*fruit, *tray, *book, *quill, *pencil,
		*video, *mirror;

	//CLOSET
	roomspec_t *closet = roomspec_new("closet", "A broom closet",
		"A small broom closet with supplies",
		allowed, NULL, NULL);
	HASH_FIND_STR(def, "door", door);
	LL_APPEND(closet->allowed_items, llist_new(door));
	HASH_FIND_STR(def, "nail", nail);
	LL_APPEND(closet->allowed_items, llist_new(nail));
	HASH_FIND_STR(def, "mirror", mirror);
	LL_APPEND(closet->allowed_items, llist_new(mirror));
	HASH_FIND_STR(def, "jug", jug);
	LL_APPEND(closet->allowed_items, llist_new(jug));
	HASH_FIND_STR(def, "hat", hat);
	LL_APPEND(closet->allowed_items, llist_new(hat));

	//HALLWAY
	roomspec_t *hallway = roomspec_new("hallway", "A well-lit hallway",
		"A sterile, white hallway with no windows",
		allowed, NULL, NULL);
	LL_APPEND(hallway->allowed_items, llist_new(door));
	LL_APPEND(hallway->allowed_items, llist_new(nail));
	HASH_FIND_STR(def, "fruit", fruit);
	LL_APPEND(hallway->allowed_items, llist_new(fruit));
	HASH_FIND_STR(def, "tray", tray);
	LL_APPEND(hallway->allowed_items, llist_new(tray));
	HASH_FIND_STR(def, "book", book);
	LL_APPEND(hallway->allowed_items, llist_new(book));

	//LIBRARY
	roomspec_t *library = roomspec_new("library", "This is a library room with resources",
		"An old, dusty library with skill-boosting resources like books and potions",
		allowed, NULL, NULL);
	LL_APPEND(library->allowed_items, llist_new(book));
	HASH_FIND_STR(def, "quill", quill);
	LL_APPEND(library->allowed_items, llist_new(quill));
	HASH_FIND_STR(def, "pencil", pencil);
	LL_APPEND(library->allowed_items, llist_new(pencil));
	HASH_FIND_STR(def, "video" video);
	LL_APPEND(library->allowed_items, llist_new(video));
	HASH_FIND_STR(def, "mirror", mirror);
	LL_APPEND(library->allowed_items, llist_new(mirror));

	assert(bucket != NULL);

	/* I had to calloc the following roomspecs 
	* otherwise I'd be returning a local copy.
	*/
	if (!strcmp(bucket, "school")) {
		roomspec_t **school_rooms = calloc(5, sizeof(roomspec_t*));
		item_t *apple, *tray, *ice, *yam, *book, *pencil,
			*watercolors, *video;
		//CLOSET + HALLWAY + LIBRARY (already defined)
		school_rooms[0] = closet;
		school_rooms[1] = hallway;
		school_rooms[2] = library;

		//CAFETERIA
		school_rooms[3] = roomspec_new("cafeteria", "A grungy cafeteria",
			"A messy high school cafeteria with trays and tables out",
			allowed, NULL, NULL);
		HASH_FIND_STR(def, "apple", apple);
		LL_APPEND(school_rooms[3]->allowed_items, apple);
		LL_APPEND(school_rooms[3]->allowed_items, llist_new(fruit));
		HASH_FIND_STR(def, "tray", tray);
		LL_APPEND(school_rooms[3]->allowed_items, llist_new(tray));
		HASH_FIND_STR(def, "ice", ice)
		LL_APPEND(school_rooms[3]->allowed_items, llist_new(ice));
		HASH_FIND_STR(def, "yam", yam);
		LL_APPEND(school_rooms[3]->allowed_items, llist_new(yam));

		//CLASSROOM
		school_rooms[4] = roomspec_new("classroom",
			"A medium-sized classroom with 30 desks",
			"A geography teacher's classroom with 30 desks",
			allowed, NULL, NULL);
		HASH_FIND_STR(def, "book", book);
		LL_APPEND(school_rooms[4]->allowed_items, llist_new(book));
		LL_APPEND(school_rooms[4]->allowed_items, llist_new(door));
		HASH_FIND_STR(def, "pencil", pencil);
		LL_APPEND(school_rooms[4]->allowed_items, llist_new(pencil));
		HASH_FIND_STR(def, "watercolors", watercolors);
		LL_APPEND(school_rooms[4]->allowed_items, llist_new(watercolors));
		HASH_FIND_STR(def, "video", video);
		LL_APPEND(school_rooms[4]->allowed_items, llist_new(videos));
		return school_rooms;
	}
	else if (!strcmp(bucket, "farmhouse")) {
		roomspec_t **farm_rooms = calloc(5, sizeof(roomspec_t*));
		item_t *apple, *cow, *eagle, *rabbit, *yam, *zebra,
			*olive, *ice, *watercolors, *xylophone, *video,
			*hat, *mirror;

		//HALLWAY
		farm_rooms[0] = hallway;

		//BARN
		farm_rooms[1] = roomspec_new("barn", "A red barn",
			"A red barn with stables inside",
			allowed, NULL, NULL);
		HASH_FIND_STR(def, "apple", apple);
		LL_APPEND(farm_rooms[1]->allowed_items, llist_new(apple));
		HASH_FIND_STR(def, "cow", cow);
		LL_APPEND(farm_rooms[1]->allowed_items, llist_new(cow));
		HASH_FIND_STR(def, "eagle", eagle);
		LL_APPEND(farm_rooms[1]->allowed_items, llist_new(eagle));
		HASH_FIND_STR(def, "rabbit", rabbit);
		LL_APPEND(farm_rooms[1]->allowed_items, llist_new(rabbit));
		HASH_FIND_STR(def, "yam", yam);
		LL_APPEND(farm_rooms[1]->allowed_items, llist_new(yam));

		//OPEN FIELD
		farm_rooms[2] = roomspec_new("open field",
			"An open field outside",
			"An open field with grass and a clear view",
			allowed, NULL, NULL);
		HASH_FIND_STR(def, "zebra", zebra);
		LL_APPEND(farm_rooms[2]->allowed_items, llist_new(zebra));
		LL_APPEND(farm_rooms[2]->allowed_items, llist_new(cow));
		LL_APPEND(farm_rooms[2]->allowed_items, llist_new(eagle));
		LL_APPEND(farm_rooms[2]->allowed_items, llist_new(rabbit));
		LL_APPEND(farm_rooms[2]->allowed_items, llist_new(apple));

		//KITCHEN
		farm_rooms[3] = roomspec_new("kitchen", "A 60s era (outdated) kitchen",
			"An outdated kitchen with obvious wear-and-tear",
			allowed, NULL, NULL);
		HASH_FIND_STR(def, "olive", olive);
		LL_APPEND(farm_rooms[3]->allowed_items, llist_new(olive));
		HASH_FIND_STR(def, "ice", ice);
		LL_APPEND(farm_rooms[3]->allowed_items, llist_new(ice));
		LL_APPEND(farm_rooms[3]->allowed_items, llist_new(jug));
		LL_APPEND(farm_rooms[3]->allowed_items, llist_new(yam));
		LL_APPEND(farm_rooms[3]->allowed_items,llist_new(tray));

		//LIVING ROOM
		farm_rooms[4] = roomspec_new("living room", "A living room with basic items",
			"A plain, unremarkable living room",
			allowed, NULL, NULL);
		HASH_FIND_STR(def, "watercolors", watercolors);
		LL_APPEND(farm_rooms[4]->allowed_items, llist_new(watercolors));
		HASH_FIND_STR(def, "video", video);
		LL_APPEND(farm_rooms[4]->allowed_items, llist_new(video));
		HASH_FIND_STR(def, "xylophone", xylophone);
		LL_APPEND(farm_rooms[4]->allowed_items, llist_new(xylophone));
		HASH_FIND_STR(def, "hat", hat);
		LL_APPEND(farm_rooms[4]->allowed_items, llist_new(hat));
		HASH_FIND_STR(def, "mirror", mirror);
		LL_APPEND(farm_rooms[4]->allowed_items, llist_new(mirror));

		return farm_rooms;

	} else if(!strcmp(bucket, "castle")) {	
		roomspec_t **castle_rooms = calloc(5, sizeof(roomspec_t*));
		item_t *ladder, *gold, *yam;
		//CLOSET + HALLWAY + LIBRARY
		castle_rooms[0] = closet;
		castle_rooms[1] = library;
		castle_rooms[2] = hallway;

		//DUNGEON
		castle_rooms[3] = roomspec_new("dungeon", "A dark dungeon",
			"A dank, dark dungeon with traps and enemies to battle",
			allowed, NULL, NULL);
		LL_APPEND(castle_rooms[3]->allowed_items, llist_new(nail));
		HASH_FIND_STR(def, "ladder", ladder);
		LL_APPEND(castle_rooms[3]->allowed_items,llist_new(ladder));
		LL_APPEND(castle_rooms[3]->allowed_items, llist_new(book));
		HASH_FIND_STR(def, "gold" gold);
		LL_APPEND(castle_rooms[3]->allowed_items, llist_new(gold));
		HASH_FIND_STR(def, "yam", yam);
		LL_APPEND(castle_rooms[3]->allowed_items, llist_new(yam));

		//THRONE ROOM
		castle_rooms[4] = roomspec_new("throne room", "This is a throne room",
			"A regal throne room decked out with lavish items",
			allowed, NULL, NULL);
		LL_APPEND(castle_rooms[4]->allowed_items, llist_new(gold));
		LL_APPEND(castle_rooms[4]->allowed_items, llist_new(door));
		LL_APPEND(castle_rooms[4]->allowed_items, llist_new(mirror));
		LL_APPEND(castle_rooms[4]->allowed_items, llist_new(jug));
		LL_APPEND(castle_rooms[4]->allowed_items, llist_new(hat));

		return castle_rooms;

	} else{
		roomspec_t **rooms = calloc(1, sizeof(roomspec_t*));
		rooms[0] = roomspec_new(bucket, sh_desc, l_desc,
			allowed, NULL, NULL);
		return rooms;
	}
}

/* see default_rooms.h */
roomspec_t *make_default_room(char *bucket, char *sh_desc, char *l_desc,
	item_list_t *allowed) {

	roomspec_t *hash = NULL;
	//get allowed rooms and defined descriptions
	roomspec_t **rooms = get_allowed_rooms(bucket, sh_desc, l_desc, allowed);

	int i = 0;
	while (rooms[i] != NULL) {
		//already adding allowed items when I initialize rooms
		HASH_ADD_STR(hash, room_name, rooms[i]);
		i++;
	}
	return hash;
}

