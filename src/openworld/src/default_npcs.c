#include <string.h>
#include "common/uthash.h"
#include "common/utlist.h"
#include "game-state/item.h"
#include "openworld/sample_npc.h"

/* See sample_npc.h */
npc_t *get_hostile_npcs()
{
	// wizard
	item_hash_t *inventory_wizard = NULL;
	item_t *dagger_item = item_new("magical dagger", "a magical dagger", "Sharp, cool, and deadly");
	HASH_ADD_STR(inventory_wizard, item_id, dagger_item);
	item_t *potion_item = item_new("healing potion", "a green potion ", "a healing potion made for you!");

	// assasin
	item_hash_t *inventory_assasin = NULL;
	HASH_ADD_STR(inventory_assasin, item_id, potion_item);
	item_t *rifle_item = item_new("rifle", "sharp rifle", "Level 1 rifle");
	HASH_ADD_STR(inventory_assasin, item_id, rifle_item);
	item_t *knife_item = item_new("knife", "knife", "sharp silver kitchen knife");
	HASH_ADD_STR(inventory_assasin, item_id, knife_item);

	// ninja
	item_hash_t *inventory_ninja = NULL;
	item_t *arrows_item = item_new("arrows", "battle arrows", "red lethal arrows");
	HASH_ADD_STR(inventory_ninja, item_id, arrows_item);
	item_t *grenade_item = item_new("grenades", "lethal grenades", "bombs used to attack you opponent");
	HASH_ADD_STR(inventory_ninja, item_id, grenade_item);

	npc_t *hostile_list = NULL;
	npc_t *wizard = calloc(1, sizeof(npc_t));
	wizard->level = 2;
	wizard->inventory = inventory_wizard;
	wizard->classification = NPC_HOSTILE;
	DL_APPEND(hostile_list, wizard);

	npc_t *assasin = calloc(1, sizeof(npc_t));
	assasin->level = 3;
	assasin->inventory = inventory_assasin;
	assasin->classification = NPC_HOSTILE;
	DL_APPEND(hostile_list, assasin);


	npc_t *ninja = calloc(1, sizeof(npc_t));
	ninja->level = 1;
	ninja->inventory = inventory_ninja;
	ninja->classification = NPC_HOSTILE;
	DL_APPEND(hostile_list, ninja);

	return hostile_list;
}

/* See sample_npc.h */
npc_t *get_friendly_npcs()
{
	// merchant
	item_hash_t *inventory_merchant = NULL;
	item_t *healing_item = item_new("green potion", "healing potion", "lovely healing potion");
	HASH_ADD_STR(inventory_merchant, item_id, healing_item);
	item_t *strength_item = item_new("red potion", "strength potion", "strength potion perfect for battle");
	HASH_ADD_STR(inventory_merchant, item_id, strength_item);

	// farmer
	item_hash_t *inventory_farmer = NULL;
	item_t *peach_item = item_new("peaches", "peaches: fruit", "a sweet savory substance");
	HASH_ADD_STR(inventory_farmer, item_id, peach_item);
	item_t *raspberry_item = item_new("raspberries", "raspberries: fruit", "the most delicious fruit");
	HASH_ADD_STR(inventory_farmer, item_id, raspberry_item);

	// librarian
	item_hash_t *inventory_librarian = NULL;
	item_t *book_item = item_new("book", "a blue book", "a book of knowlege");
	HASH_ADD_STR(inventory_librarian, item_id, book_item);
	item_t *pencil_item = item_new("pencils", "yellow pencil", "Non-lethal weapon");
	HASH_ADD_STR(inventory_librarian, item_id, pencil_item);

	npc_t *friendly_list = NULL;
	npc_t *librarian = calloc(1, sizeof(npc_t));
	librarian->level = 1;
	librarian->inventory = inventory_librarian;
	librarian->classification = NPC_FRIENDLY;
	DL_APPEND(friendly_list, librarian);

	npc_t *merchant = calloc(1, sizeof(npc_t));
	merchant->level = 3;
	merchant->inventory = inventory_merchant;
	merchant->classification = NPC_FRIENDLY;
	DL_APPEND(friendly_list, merchant);

	npc_t *farmer = calloc(1, sizeof(npc_t));
	farmer->level = 1;
	farmer->inventory = inventory_farmer;
	farmer->classification = NPC_FRIENDLY;
	DL_APPEND(friendly_list, farmer);

	return friendly_list;
}

/* See sample_npc.h */
npc_t *get_generic_npcs()
{
	// frenemy1
	item_hash_t *inventory_frenemy1 = NULL;
	item_t *healing_item = item_new("green potion", "healing potion", "use after battle");
	HASH_ADD_STR(inventory_frenemy1, item_id, healing_item);
	item_t *strength_item = item_new("red potion", "strength potion", "use before battle");
	HASH_ADD_STR(inventory_frenemy1, item_id, strength_item);

	// frenemy2
	item_hash_t *inventory_frenemy2 = NULL;
	item_t *peach_item = item_new("peaches", "peaches: fruit", "a sweet savory substance");
	HASH_ADD_STR(inventory_frenemy2, item_id, peach_item);
	item_t *dagger_item = item_new("daggers", "a regular dagger", "Sharp, cool, and deadly");
	HASH_ADD_STR(inventory_frenemy2, item_id, dagger_item);

	// frenemy3
	item_hash_t *inventory_frenemy3 = NULL;
	item_t *book_item = item_new("book", "dark arts book", "perfect to prepare for battle");


	npc_t *generic_list = NULL;
	npc_t *frenemy1 = calloc(1, sizeof(npc_t));
	frenemy1->level = 1;
	frenemy1->inventory = inventory_frenemy1;
	frenemy1->classification = NPC_GENERIC;
	DL_APPEND(generic_list, frenemy1);

	npc_t *frenemy2 = calloc(1, sizeof(npc_t));
	frenemy2->level = 2;
	frenemy2->inventory = inventory_frenemy2;
	frenemy2->classification = NPC_GENERIC;
	DL_APPEND(generic_list, frenemy2);


	npc_t *frenemy3 = calloc(1, sizeof(npc_t));
	frenemy3->level = 3;
	frenemy3->inventory = inventory_frenemy3;
	frenemy3->classification = NPC_GENERIC;
	DL_APPEND(generic_list, frenemy3);

	return generic_list;
}
