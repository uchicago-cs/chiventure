/* Implementations of the item struct */
#include <string.h>

#include "../../../include/openworld/sample_rooms.h" 
#include "../../../include/openworld/sample_items.h"


// BASIC ITEM FUNCTIONS -------------------------------------------------------
/* see sample_items.h*/
int item_init(item_t *new_item, item_tag_t item_tag)
{
	assert(new_item != NULL);
	switch (item_tag) {
	case APPLE:
		new_item->item_tag = APPLE;
		new_item->item_id = "apple";
		new_item->short_desc = "a red apple";
		new_item->long_desc = "A juicy Red Delicious apple";
		break;
	case BOOK:
		new_item->item_tag = BOOK;
		new_item->item_id = "book";
		new_item->short_desc = "A big book";
		new_item->long_desc = "A Simulation survival book";
		break;
	case COW:
		new_item->item_tag = COW;
		new_item->item_id = "cow";
		new_item->short_desc = "A black and white cow";
		new_item->long_desc ="A black and white cow called Mavis";
		break;
	case DOOR:
		new_item->item_tag = DOOR;
		new_item->item_id = "door";
		new_item->short_desc = "a normal door";
		new_item->long_desc = "A woooden door with a worn doorknob";
		break;
	}
	return SUCCESS;
}

/* see item.h */
item_t *item_new(item_tag_t item_tag)
{
	item_t *new_item = (item_t*) malloc(sizeof(item_t));
	memset(new_item, 0, sizeof(item_t));

	int check = item_init(new_item, item_tag);

	if (new_item == NULL || new_item->item_id == NULL|| 
		new_item->short_desc|| new_item->long_desc == NULL)
	{

		return NULL; //item struct not properly malloced

	}

	if (check != SUCCESS)
	{
		return NULL;
	}

	return new_item;

}


/* see item.h */
char *get_sdesc_item(item_t *item)
{
	if (item == NULL)
	{
		return NULL;
	}
	return item->short_desc;
}

/* see item.h */
char *get_ldesc_item(item_t *item)
{
	if (item == NULL)
	{
		return NULL;
	}
	return item->long_desc;
}


// FREEING AND DELETION FUNCTIONS ---------------------------------------------

/* See sample_items.h */
int item_free(item_t *item)
{
	free(item->item_id);
	free(item->short_desc);
	free(item->long_desc);
	free(item);
	return SUCCESS;
}

