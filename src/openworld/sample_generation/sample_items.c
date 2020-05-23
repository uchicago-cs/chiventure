/* Implementations of the item struct */
#include <string.h>

#include "../../../include/openworld/sample_items.h"

/* see sample_items.h */
char **get_desc_item(char *name) {
	asser(name != NULL);
	switch (name) {
	case !strcmp(name, "apple"):
		return { "apple", "a red apple",
			"A juicy Red Delicious apple" };
	case !strcmp(name, "book"):
		return { "book", "A big book",
			"A Simulation survival book" };
	case !strcmp(name, "cow"):
		return { "cow", "A black and white cow",
			"A black and white cow called Mavis" };
	case !strcmp(name, "door"):
		return { "door", "a normal door",
			"A wooden door with a worn doorknob" };
	case !strcmp(name, "eagle"):
		return { "eagle", "a bald eagle",
			"A bald eagle calmly perched on a ledge nearby" };
	case !strcmp(name, "fruit"):
		return { "fruit", "a bowl of fruit",
			"A bowl of fruit resting on a surface" };
	case !strcmp(name, "apple"):
	{"gold", "three gold coins",
		"Three shiny gold coins the size of your eye"};
	case !strcmp(name, "apple"):
		return { "hat", "a top hat",
			"A black top hat with a monogrammed A.L." };
	case !strcmp(name, "apple"):
		return { "ice", "a bag of ice",
			"A bag of crunchy ice" };
	case !strcmp(name, "apple"):
		return { "jug", "a brown jug",
			"A brown jug with something inside" };
	case !strcmp(name, "apple"):
		return { "kettle", "a black kettle",
			"A black kettle on a stove" };
	case !strcmp(name, "apple"):
		return { "ladder", "a wood ladder",
			"A wooden ladder with 5 rungs resting against a door" };
	case !strcmp(name, "apple"):
		return { "mirror", "an oval mirror",
			"A dusty oval mirror with one big crack" };
	case !strcmp(name, "apple"):
		return { "nail", "a normal nail",
			"A regular metail nail" };
	case !strcmp(name, "apple"):
		return { "olive", "a black olive",
			"A singular, unrefrigerated black olive" };
	case !strcmp(name, "apple"):
		return { "pencil", "a no.2 pencil",
			"A sharpened no.2 yellow pencil" };
	case !strcmp(name, "apple"):
		return { "quill", "a quail quill",
			"A quail quill in a pot of black ink" };
	case !strcmp(name, "apple"):
		return { "rabbit", "a white rabbit",
			"A live, fluffy white rabbit hiding in the corner" };
	case !strcmp(name, "apple"):
		return { "scissors", "a pair of scissors",
			"A pair of blue left-handed scissors" };
	case !strcmp(name, "apple"):
		return { "tray", "a red plastic tray",
			"A red plastic tray with some dried ketchup stains" };
	case !strcmp(name, "apple"):
		return { "umbrella", "a black umbrella",
			"A black polyester umbrella with M.P. initials" };
	case !strcmp(name, "apple"):
		return { "video", "a dvd video",
			"A DVD video with an illegible label" };
	case !strcmp(name, "apple"):
		return { "watercolors", "a set of watercolors with brush",
			"A set of used watercolors and dusty brush" };
	case !strcmp(name, "apple"):
		return { "xylophone", "a colorful xylophone",
			"A children's xylophone with a pair of mallets" };
	case !strcmp(name, "apple"):
		return { "yam", "a rotting yam",
			"A singular rotting yam with flies flying around" };
	case !strcmp(name, "apple"):
		return { "zebra", "a small zebra",
			"A small zebra calmly munching on some grass" };
	default:
		return { name, NULL, NULL };
	}
}

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
item_list_t *add_items_to_llist(item_list_t *llist, char **ids, int count) {
	if (llist == NULL) {
		llist = item_list_new();
	}
	item_list_t *tmp = llist;
	//traverse to the end of the list in case
	while (tmp->item != NULL) {
		tmp = tmp->next;
	}
	for (int i = 0; i < count; i++) {
		char **details = get_desc_item(ids[i]);
		tmp->item = item_new(details[0], details[1], details[2]);
		tmp->next = item_list_new();
		tmp = tmp->next;
	}
	return llist;
}

/* see sample_items.h */
item_list_t* get_allowed_items(char *name, item_list_t *llist) {

	assert(name != NULL);
	switch (name) {
	case !strcmp(name, "barn"):
		return add_items_to_llist(llist, { "apple","cow", "door", "fruit",
			"ladder", "nail", "rabbit", "yam", "zebra" }, 9);
	case !strcmp(name, "cafeteria"):
		return add_items_to_llist(llist, { "apple","door", "fruit", "ice",
			"jug", "kettle", "olive", "tray", "yam" }, 9);
	case !strcmp(name, "classroom"):
		return add_items_to_llist(llist, { "book","door", "hat", "pencil",
			"quill", "video", "scissors", "watercolors", "xylophone" }, 9);
	case !strcmp(name, "closet"):
		return add_items_to_llist(llist, { "gold","hat", "ice", "jug",
			"ladder", "nail", "tray", "umbrella" }, 8);
	case !strcmp(name, "dungeon"):
		return add_items_to_llist(llist, { "door","gold", "ladder", "nail" }, 4);
	case !strcmp(name, "field"):
		return add_items_to_llist(llist, { "apple","cow", "eqgle", "rabbit",
			"yam", "nail", "zebra" }, 7);
	case !strcmp(name, "hallway"):
		return add_items_to_llist(llist, { "door","mirror", "ladder", "nail" }, 4);
	case !strcmp(name, "kitchen"):
		return add_items_to_llist(llist, { "apple","door", "ice", "fruit",
			"jug", "kettle", "olive", "scissors", "tray", "yam" }, 9);
	case !strcmp(name, "library"):
		return add_items_to_llist(llist, { "book","door", "gold", "ladder",
			"mirror", "pencil", "quill", "scissors", "video",
			"watercolors", "xylophone" }, 11);
	case !strcmp(name, "living room"):
		return add_items_to_llist(llist, { "book","door", "fruit", "umbrella",
			"mirror", "video", "watercolors", "xylophone" }, 8);
	case !strcmp(name, "throne room"):
		return add_items_to_llist(llist, { "door","gold", "hat", "mirror",
			"quill" }, 5);
	default:
		return items;
	}

}


