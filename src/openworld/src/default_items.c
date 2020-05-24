/* Implementations of the item struct */
#include <string.h>

#include "../../../include/openworld/default_items.h"
#include "../../../include/common/uthash.h"
#include "../../../include/common/room.h"
#include "../../../include/game-state/room.h"

/* see default_items.h */
item_hash_t *get_default_items() {
	item_hash_t *hash = NULL;

	HASH_ADD_STR(hash, item_id, item_new("apple", "a red apple",
		"A juicy Red Delicious apple"));
	HASH_ADD_STR(hash, item_id, item_new("cow", "A black and white cow",
		"A black and white cow called Mavis"));
	HASH_ADD_STR(hash, item_id, item_new("fruit", "a bowl of fruit",
		"A bowl of fruit resting on a surface"));
	HASH_ADD_STR(hash, item_id, item_new("ladder", "a wood ladder",
		"A wooden ladder with 5 rungs resting against a door"));
	HASH_ADD_STR(hash, item_id, item_new("yam", "a rotting yam",
		"A singular rotting yam with flies flying around"));
	HASH_ADD_STR(hash, item_id, item_new("ice", "a bag of ice", 
		"A bag of crunchy ice"));
	HASH_ADD_STR(hash, item_id, item_new("jug", "a brown jug", 
		"A brown jug with something inside"));
	HASH_ADD_STR(hash, item_id, item_new("tray", "a red plastic tray",
		"A red plastic tray with some dried ketchup stains"));
	HASH_ADD_STR(hash, item_id, item_new("book", "A big book",
		"A Simulation survival book"));
	HASH_ADD_STR(hash, item_id, item_new("door", "a normal door",
		"A wooden door with a worn doorknob"));
	HASH_ADD_STR(hash, item_id, item_new("pencil", "a no.2 pencil",
		"A sharpened no.2 yellow pencil"));
	HASH_ADD_STR(hash, item_id, item_new("quill", "a quail quill",
		"A quail quill in a pot of black ink"));
	HASH_ADD_STR(hash, item_id, item_new("watercolors",
		"a set of watercolors with brush",
		"A set of used watercolors and dusty brush"));
	item_t *hat = item_new("hat", "a top hat", "A black top hat with monogrammed A. L.");

	HASH_ADD_STR(hash, item_id, hat);
	HASH_ADD_STR(hash, item_id, item_new("nail", "a normal nail",
		"A regular metail nail"));
	HASH_ADD_STR(hash, item_id, item_new("gold", "three gold coins",
		"Three shiny gold coins the size of your eye"));
	HASH_ADD_STR(hash, item_id, item_new("eagle", "a bald eagle",
		"A bald eagle calmly perched on a ledge nearby"));
	HASH_ADD_STR(hash, item_id, item_new("umbrella", "a black umbrella",
		"A black polyester umbrella with M.P. initials"));
	HASH_ADD_STR(hash, item_id, item_new("rabbit", "a white rabbit",
		"A live, fluffy white rabbit hiding in the corner"));
	HASH_ADD_STR(hash, item_id, item_new("zebra", "a small zebra",
		"A small zebra calmly munching on some grass"));
	HASH_ADD_STR(hash, item_id, item_new("mirror", "an oval mirror",
		"A dusty oval mirror with one big crack"));
	HASH_ADD_STR(hash, item_id, item_new("kettle", "a black kettle",
		"A black kettle on a stove"));
	HASH_ADD_STR(hash, item_id, item_new("olive", "a black olive",
		"A singular, unrefrigerated black olive"));
	HASH_ADD_STR(hash, item_id, item_new("quill", "a quail quill",
		"A quail quill in a pot of black ink"));
	HASH_ADD_STR(hash, item_id, item_new("video", "a dvd video",
		"A DVD video with an illegible label"));
	HASH_ADD_STR(hash, item_id, item_new("xylophone", "a colorful xylophone",
		"A children's xylophone with a pair of mallets"));
	HASH_ADD_STR(hash, item_id, item_new("video", "a dvd video",
		"A DVD video with an illegible label"));
	return hash;
}
