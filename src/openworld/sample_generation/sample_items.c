/* Implementations of the item struct */
#include <string.h>

#include "../../../include/openworld/sample_items.h"

/* see sample_items.h */
item_list_t *item_list_new() {
	item_list_t *llist = calloc(1, sizeof(item_list_t));
	llist->item = NULL;
	llist->next = NULL;
	return llist;
}

/* see sample_items.h */
void item_list_free(item_list_t *llist) {
	while (llist->next != NULL) {
		free(llist->item);
		llist = llist->next;
	}
	free(llist);
}

/* see sample_items.h */
item_list_t *add_items_to_llist(item_list_t *llist, item_t **ids, int count) {
	if (llist == NULL) {
		llist = item_list_new();
	}
	item_list_t *tmp = llist;
	//traverse to the end of the list in case
	while (tmp->item != NULL) {
		tmp = tmp->next;
	}
	for (int i = 0; i < count; i++) {
		tmp->item = ids[i];
		tmp->next = item_list_new();
		tmp = tmp->next;
	}
	return llist;
}

/* see sample_items.h */
item_list_t* get_allowed_items(char *name, item_list_t *llist) {
	int rc;

		item_t *apple = item_new("apple", "a red apple",
			"A juicy Red Delicious apple");
		item_t *book = item_new("book", "A big book",
			"A Simulation survival book");
		item_t *cow = item_new("cow", "A black and white cow",
			"A black and white cow called Mavis");
		item_t *door = item_new("door", "a normal door",
			"A wooden door with a worn doorknob");
		item_t *eagle = item_new("eagle", "a bald eagle",
			"A bald eagle calmly perched on a ledge nearby");
		item_t *fruit = item_new("fruit", "a bowl of fruit",
			"A bowl of fruit resting on a surface");
		item_t *gold = item_new("gold", "three gold coins",
			"Three shiny gold coins the size of your eye");
		item_t *hat = item_new("hat", "a top hat",
			"A black top hat with a monogrammed A.L.");
		item_t *ice = item_new("ice", "a bag of ice",
			"A bag of crunchy ice");
		item_t *jug = item_new("jug", "a brown jug",
			"A brown jug with something inside");
		item_t *kettle = item_new("kettle", "a black kettle",
			"A black kettle on a stove");
		item_t *ladder = item_new("ladder", "a wood ladder",
			"A wooden ladder with 5 rungs resting against a door");
		item_t *mirror = item_new("mirror", "an oval mirror",
			"A dusty oval mirror with one big crack");
		item_t *nail = item_new("nail", "a normal nail",
			"A regular metail nail");
		item_t *olive = item_new("olive", "a black olive",
			"A singular, unrefrigerated black olive");
		item_t *pencil = item_new("pencil", "a no.2 pencil",
			"A sharpened no.2 yellow pencil");
		item_t *quill = item_new("quill", "a quail quill",
			"A quail quill in a pot of black ink");
		item_t *rabbit = item_new("rabbit", "a white rabbit",
			"A live, fluffy white rabbit hiding in the corner");
		item_t *scissors = item_new("scissors", "a pair of scissors",
			"A pair of blue left-handed scissors");
		item_t *tray = item_new("tray", "a red plastic tray",
			"A red plastic tray with some dried ketchup stains");
		item_t *umbrella = item_new("umbrella", "a black umbrella",
			"A black polyester umbrella with M.P. initials");
		item_t *video = item_new("video", "a dvd video",
			"A DVD video with an illegible label");
		item_t *watercolors = item_new("watercolors",
			"a set of watercolors with brush",
			"A set of used watercolors and dusty brush");
		item_t *xylophone = item_new("xylophone", "a colorful xylophone",
			"A children's xylophone with a pair of mallets");
		item_t *yam = item_new("yam", "a rotting yam",
			"A singular rotting yam with flies flying around");
		item_t *zebra = item_new("zebra", "a small zebra",
			"A small zebra calmly munching on some grass");

		assert(name != NULL);
		if (!strcmp(name, "barn")) {
			item_t *barn_ids[9] = { apple, cow, door, fruit, ladder,
			nail, rabbit, yam, zebra };
			return add_items_to_llist(llist, barn_ids, 9);
		}
		else if (!strcmp(name, "cafeteria")) {
			item_t *cafe_ids[9] = { apple, door, fruit, ice, jug,
			kettle, olive, tray, yam };
			return add_items_to_llist(llist, cafe_ids, 9);
		}
		else if (!strcmp(name, "classroom")) {
			item_t *class_ids[9] = { book, door, hat, pencil, quill,
			video, scissors, watercolors, xylophone };
			return add_items_to_llist(llist, class_ids, 9);
		}
		else if (!strcmp(name, "closet")) {
			item_t *closet_ids[8] = { gold, hat, ice, jug, ladder,
			nail, tray, umbrella };
			return add_items_to_llist(llist, closet_ids, 8);
		}
		else if (!strcmp(name, "dungeon")) {
			item_t *dungeon_ids[4] = { door, gold, ladder, nail };
			return add_items_to_llist(llist, dungeon_ids, 4);
		}
		else if (!strcmp(name, "field")) {
			item_t *field_ids[7] = { apple, cow, eagle, rabbit, yam, nail, zebra };
			return add_items_to_llist(llist, field_ids, 7);
		}
		else if (!strcmp(name, "hallway")) {
			item_t *hall_ids[4] = { door, mirror, ladder, nail };
			return add_items_to_llist(llist, hall_ids, 4);
		}
		else if (!strcmp(name, "kitchen")) {
			item_t *kitchen_ids[9] = { apple, door, ice, fruit, jub, kettle,
			olive, scissors, tray, yam };
			return add_items_to_llist(llist, kitchen_ids, 10);
		}
		else if (!strcmp(name, "library")) {
			item_t *library_ids[11] = { book, door, gold, ladder, mirror,pencil,
			quill, scissors, video, watercolors, xylophone };
			return add_items_to_llist(llist, library_ids, 11);
		}
		else if (!strcmp(name, "living room")) {
			item_t *living_ids[8] = { book, door, fruit, umbrella,
			mirror, video, watercolors, xylophone };
			return add_items_to_llist(llist, living_ids, 8);
		}
		else if (!strcmp(name, "throne room")) {
			item_t *throne_ids[5] = { door, gold, hat, mirror, quill };
			return add_items_to_llist(llist, {throne_ids, 5);
		}
		else {
			return llist;
		}
}


