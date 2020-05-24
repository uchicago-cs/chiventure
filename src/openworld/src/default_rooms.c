#include <stdlib.h>
#include <string.h>

#include "../../../include/common/utlist.h"
#include "../../../include/common/uthash.h"
#include "../../../include/openworld/default_rooms.h" 
#include "../../../include/openworld/default_items.h"

/* Mini-helper function solely to initialize an
* item list given an item found in the hash
*/
item_list_t *llist_new(item_t* item){
	item_list_t* llist = calloc(1, sizeof(item_list_t));
	llist->item =item;
	llist->next = NULL;
	return llist;
}

/* see default_rooms.h */
roomspec_t *make_default_room(char *bucket, char *sh_desc, char *l_desc,
item_list_t *allowed) {

	roomspec_t *hash = NULL;

	assert(bucket != NULL);
	item_hash_t *def = get_default_items();

	item_t *door, *nail, *mirror, *jug, *hat,
		*fruit, *tray, *book, *quill, *pencil,
		*video;

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
	roomspec_t *library = roomspec_new("library", 
		"This is a library room with resources",
		"An old, dusty library with skill-boosting resources like books and potions",
		allowed, NULL, NULL);
	LL_APPEND(library->allowed_items, llist_new(book));
	HASH_FIND_STR(def, "quill", quill);
	LL_APPEND(library->allowed_items, llist_new(quill));
	HASH_FIND_STR(def, "pencil", pencil);
	LL_APPEND(library->allowed_items, llist_new(pencil));
	HASH_FIND_STR(def, "video", video);
	LL_APPEND(library->allowed_items, llist_new(video));
	HASH_FIND_STR(def, "mirror", mirror);
	LL_APPEND(library->allowed_items, llist_new(mirror));

	if (!strcmp(bucket, "school")) {
		item_t *apple, *tray, *ice, *yam, *book, *pencil,
			*watercolors, *video;

		//CAFETERIA
		roomspec_t *cafeteria = roomspec_new("cafeteria", "A grungy cafeteria",
			"A messy high school cafeteria with trays and tables out",
			allowed, NULL, NULL);
		HASH_FIND_STR(def, "apple", apple);
		LL_APPEND(cafeteria->allowed_items, llist_new(apple));
		LL_APPEND(cafeteria->allowed_items, llist_new(fruit));
		HASH_FIND_STR(def, "tray", tray);
		LL_APPEND(cafeteria->allowed_items, llist_new(tray));
		HASH_FIND_STR(def, "ice", ice);
		LL_APPEND(cafeteria->allowed_items, llist_new(ice));
		HASH_FIND_STR(def, "yam", yam);
		LL_APPEND(cafeteria->allowed_items, llist_new(yam));

		//CLASSROOM
		roomspec_t *classroom = roomspec_new("classroom",
			"A medium-sized classroom with 30 desks",
			"A geography teacher's classroom with 30 desks",
			allowed, NULL, NULL);
		HASH_FIND_STR(def, "book", book);
		LL_APPEND(classroom->allowed_items, llist_new(book));
		LL_APPEND(classroom->allowed_items, llist_new(door));
		HASH_FIND_STR(def, "pencil", pencil);
		LL_APPEND(classroom->allowed_items, llist_new(pencil));
		HASH_FIND_STR(def, "watercolors", watercolors);
		LL_APPEND(classroom->allowed_items, llist_new(watercolors));
		HASH_FIND_STR(def, "video", video);
		LL_APPEND(classroom->allowed_items, llist_new(video));
		
		//now add all the roomspecs to the hash
		HASH_ADD_STR(hash, room_name, closet);
		HASH_ADD_STR(hash, room_name, library);
		HASH_ADD_STR(hash, room_name, hallway);
		HASH_ADD_STR(hash, room_name, cafeteria);
		HASH_ADD_STR(hash, room_name, classroom);
	}
	else if (!strcmp(bucket, "farmhouse")) {
		item_t *apple, *cow, *eagle, *rabbit, *yam, *zebra,
			*olive, *ice, *watercolors, *xylophone, *video,
			*hat, *mirror;

		//BARN
		roomspec_t *barn = roomspec_new("barn", "A red barn",
			"A red barn with stables inside",
			allowed, NULL, NULL);
		HASH_FIND_STR(def, "apple", apple);
		LL_APPEND(barn->allowed_items, llist_new(apple));
		HASH_FIND_STR(def, "cow", cow);
		LL_APPEND(barn->allowed_items, llist_new(cow));
		HASH_FIND_STR(def, "eagle", eagle);
		LL_APPEND(barn->allowed_items, llist_new(eagle));
		HASH_FIND_STR(def, "rabbit", rabbit);
		LL_APPEND(barn->allowed_items, llist_new(rabbit));
		HASH_FIND_STR(def, "yam", yam);
		LL_APPEND(barn->allowed_items, llist_new(yam));

		//OPEN FIELD
		roomspec_t *field = roomspec_new("open field",
			"An open field outside",
			"An open field with grass and a clear view",
			allowed, NULL, NULL);
		HASH_FIND_STR(def, "zebra", zebra);
		LL_APPEND(field->allowed_items, llist_new(zebra));
		LL_APPEND(field->allowed_items, llist_new(cow));
		LL_APPEND(field->allowed_items, llist_new(eagle));
		LL_APPEND(field->allowed_items, llist_new(rabbit));
		LL_APPEND(field->allowed_items, llist_new(apple));

		//KITCHEN
		roomspec_t *kitchen = roomspec_new("kitchen", "A 60s era (outdated) kitchen",
			"An outdated kitchen with obvious wear-and-tear",
			allowed, NULL, NULL);
		HASH_FIND_STR(def, "olive", olive);
		LL_APPEND(kitchen->allowed_items, llist_new(olive));
		HASH_FIND_STR(def, "ice", ice);
		LL_APPEND(kitchen->allowed_items, llist_new(ice));
		LL_APPEND(kitchen->allowed_items, llist_new(jug));
		LL_APPEND(kitchen->allowed_items, llist_new(yam));
		LL_APPEND(kitchen->allowed_items,llist_new(tray));

		//LIVING ROOM
		roomspec_t *living = roomspec_new("living room", 
			"A living room with basic items",
			"A plain, unremarkable living room",
			allowed, NULL, NULL);
		HASH_FIND_STR(def, "watercolors", watercolors);
		LL_APPEND(living->allowed_items, llist_new(watercolors));
		HASH_FIND_STR(def, "video", video);
		LL_APPEND(living->allowed_items, llist_new(video));
		HASH_FIND_STR(def, "xylophone", xylophone);
		LL_APPEND(living->allowed_items, llist_new(xylophone));
		HASH_FIND_STR(def, "hat", hat);
		LL_APPEND(living->allowed_items, llist_new(hat));
		HASH_FIND_STR(def, "mirror", mirror);
		LL_APPEND(living->allowed_items, llist_new(mirror));

		//now add to hash
		HASH_ADD_STR(hash, room_name, closet);
		HASH_ADD_STR(hash, room_name, barn);
		HASH_ADD_STR(hash, room_name, field);
		HASH_ADD_STR(hash, room_name, kitchen);
		HASH_ADD_STR(hash, room_name, living);

	} else if(!strcmp(bucket, "castle")) {	
		item_t *ladder, *gold, *yam;

		//DUNGEON
		roomspec_t *dungeon = roomspec_new("dungeon", "A dark dungeon",
			"A dank, dark dungeon with traps and enemies to battle",
			allowed, NULL, NULL);
		LL_APPEND(dungeon->allowed_items, llist_new(nail));
		HASH_FIND_STR(def, "ladder", ladder);
		LL_APPEND(dungeon->allowed_items,llist_new(ladder));
		LL_APPEND(dungeon->allowed_items, llist_new(book));
		HASH_FIND_STR(def, "gold", gold);
		LL_APPEND(dungeon->allowed_items, llist_new(gold));
		HASH_FIND_STR(def, "yam", yam);
		LL_APPEND(dungeon->allowed_items, llist_new(yam));

		//THRONE ROOM
		roomspec_t *throne = roomspec_new("throne room", 
			"This is a throne room",
			"A regal throne room decked out with lavish items",
			allowed, NULL, NULL);
		LL_APPEND(throne->allowed_items, llist_new(gold));
		LL_APPEND(throne->allowed_items, llist_new(door));
		LL_APPEND(throne->allowed_items, llist_new(mirror));
		LL_APPEND(throne->allowed_items, llist_new(jug));
		LL_APPEND(throne->allowed_items, llist_new(hat));

		//Now add to hash
		HASH_ADD_STR(hash, room_name, closet);
		HASH_ADD_STR(hash, room_name, hallway);
		HASH_ADD_STR(hash, room_name, library);
		HASH_ADD_STR(hash, room_name, dungeon);
		HASH_ADD_STR(hash, room_name, throne);

	} else{
		roomspec_t *room = roomspec_new(bucket, sh_desc, l_desc,
			allowed, NULL, NULL);
		
		//now add to hash
		HASH_ADD_STR(hash, room_name, room);
		
	}
	return hash;
}

