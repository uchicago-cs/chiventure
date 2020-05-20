/* Implementations of the item struct */
#include <string.h>

#include "../../../include/openworld/sample_rooms.h" 
#include "../../../include/openworld/sample_items.h"


// BASIC ITEM FUNCTIONS -------------------------------------------------------
/* see sample_items.h*/
int item_init(item_t *new_item, item_tag_t item_tag)
{
	int rc;
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
	case EAGLE:
		new_item->item_tag = EAGLE;
		new_item->item_id = "eagle";
		new_item->short_desc = "a bald eagle";
		new_item->long_desc = "A bald eagle calmly perched on a ledge nearby";
		break;
	case FRUIT:
		new_item->item_tag = FRUIT;
		new_item->item_id = "fruit";
		new_item->short_desc = "a bowl of fruit";
		new_item->long_desc = "A bowl of fruit resting on a surface";
		break;
	case GOLD:
		new_item->item_tag = DOOR;
		new_item->item_id = "gold";
		new_item->short_desc = "three gold coins";
		new_item->long_desc = "Three shiny gold coins the size of your eye";
		break;
	case HAT:
		new_item->item_tag = HAT;
		new_item->item_id = "hat";
		new_item->short_desc = "a top hat";
		new_item->long_desc = "A black top hat with a monogrammed A.L.";
		break;
	case ICE:
		new_item->item_tag = ICE;
		new_item->item_id = "ice";
		new_item->short_desc = "a bag of ice";
		new_item->long_desc = "A bag of crunchy ice";
		break;
	case JUG:
		new_item->item_tag = JUG;
		new_item->item_id = "jug";
		new_item->short_desc = "a brown jug";
		new_item->long_desc = "A brown jug with something inside";
		break;
	case KETTLE:
		new_item->item_tag = KETTLE;
		new_item->item_id = "kettle";
		new_item->short_desc = "a black kettle";
		new_item->long_desc = "A black kettle on a stove";
		break;
	case LADDER:
		new_item->item_tag = LADDER;
		new_item->item_id = "ladder";
		new_item->short_desc = "a wood ladder";
		new_item->long_desc = "A woooden ladder with 5 rungs resting against a door";
		break;
	case MIRROR:
		new_item->item_tag = MIRROR;
		new_item->item_id = "mirror";
		new_item->short_desc = "an oval mirror";
		new_item->long_desc = "A dusty oval mirror with one big crack";
		break;
	case NAIL:
		new_item->item_tag = NAIL;
		new_item->item_id = "nail";
		new_item->short_desc = "a normal nail";
		new_item->long_desc = "A regular metail nail";
		break;
	case OLIVE:
		new_item->item_tag = OLIVE;
		new_item->item_id = "olive";
		new_item->short_desc = "a black olive";
		new_item->long_desc = "A singular, unrefrigerated black olive";
		break;
	case PENCIL:
		new_item->item_tag = PENCIL;
		new_item->item_id = "pencil";
		new_item->short_desc = "a no.2 pencil";
		new_item->long_desc = "A sharpened no.2 yellow pencil";
		break;
	case QUILL:
		new_item->item_tag = QUILL;
		new_item->item_id = "quill";
		new_item->short_desc = "a quail quill";
		new_item->long_desc = "A quail quill in a pot of black ink";
		break;
	case RABBIT:
		new_item->item_tag = RABBIT;
		new_item->item_id = "rabbit";
		new_item->short_desc = "a white rabbit";
		new_item->long_desc = "A live, fluffy white rabbit hiding in the corner";
		break;
	case SCISSORS:
		new_item->item_tag = SCISSORS;
		new_item->item_id = "scissors";
		new_item->short_desc = "a pair of scissors";
		new_item->long_desc = "A pair of blue left-handed scissors";
		break;
	case TRAY:
		new_item->item_tag = TRAY;
		new_item->item_id = "tray";
		new_item->short_desc = "a red plastic tray";
		new_item->long_desc = "A red plastic tray with some dried ketchup stains";
		break;
	case UMBRELLA:
		new_item->item_tag = UMBRELLA;
		new_item->item_id = "umbrella";
		new_item->short_desc = "a black umbrella";
		new_item->long_desc = "A black polyester umbrella with M.P. initials";
		break;
	case VIDEO:
		new_item->item_tag = VIDEO;
		new_item->item_id = "video";
		new_item->short_desc = "a dvd video";
		new_item->long_desc = "A DVD video with an illegible label";
		break;
	case WATERCOLORS:
		new_item->item_tag = WATERCOLORS;
		new_item->item_id = "watercolors";
		new_item->short_desc = "a set of watercolors with brush";
		new_item->long_desc = "A set of used watercolors and dusty brush";
		break;
	case XYLOPHONE:
		new_item->item_tag = XYLOPHONE;
		new_item->item_id = "xylophone";
		new_item->short_desc = "a colorful xylophone";
		new_item->long_desc = "A children's xylophone with a pair of mallets";
		break;
	case YAM:
		new_item->item_tag = YAM;
		new_item->item_id = "yam";
		new_item->short_desc = "a rotting yam";
		new_item->long_desc = "A singular rotting yam with flies flying around";
		break;
	case ZEBRA:
		new_item->item_tag = ZEBRA;
		new_item->item_id = "zebra";
		new_item->short_desc = "a small zebra";
		new_item->long_desc = "A small zebra calmly munching on some grass";
		break;
	}
	new_item->attributes = set_exit_attr(new_item);
	return SUCCESS;
}

/* see sample_items.h*/
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


/* see sample_items.h*/
char *get_sdesc_item(item_t *item)
{
	if (item == NULL)
	{
		return NULL;
	}
	return item->short_desc;
}

/* see sample_items.h*/
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
	attribute_free(item->attributes);
	free(item->attributes);
	free(item);
	return SUCCESS;
}


// ATTRIBUTE MANIPULATION FUNCTIONS -------------------------------------------

/* see sample_item.h */
int attribute_init(attribute_t* new_attr, char* attr_name, attribute_tag_t* tag) {
	assert(new_attr != NULL);
	new_item->attribute_key = attr_name;
	new_item->attribute_tag = tag;
}

/* see sample_item.h */
attribute_t* attribute_new(char* attr_name, attribute_tag_t* tag) {
	attribute_t *new_attr = (attribute_t*)malloc(sizeof(attribute_t));
	memset(new_attr, 0, sizeof(attribute_t));

	int check = attribute_init(new_attr, tag);

	if (new_attr == NULL)
	{

		return NULL; //item struct not properly malloced

	}

	if (check != SUCCESS)
	{
		return NULL;
	}

	return new_item;
}

/* see sample_item.h */
int add_attribute_to_hash(item_t* item, attribute_t* new_attribute)
{
	attribute_t* check;
	HASH_FIND(hh, item->attributes, new_attribute->attribute_key,
		strlen(new_attribute->attribute_key), check);
	if (check != NULL)
	{
		return FAILURE; //this attribute is already present.
	}
	HASH_ADD_KEYPTR(hh, item->attributes, new_attribute->attribute_key,
		strlen(new_attribute->attribute_key), new_attribute);
	return SUCCESS;
}

/* see sample_item.h */
int set_int_attr(item_t* item, char* attr_name, int value) {

	attribute_t* res = get_attribute(item, attr_name);
	if (res == NULL &&)
	{
		attribute_t* new_attribute = malloc(sizeof(attribute_t));
		new_attribute->attribute_tag = INTEGER;
		new_attribute->attribute_value.int_val = value;
		new_attribute->attribute_key = strndup(attr_name, 100);
		int rv = add_attribute_to_hash(item, new_attribute);
		return rv;
	}
	else if ((res != NULL && res->attribute_tag != INTEGER))
	{
		return FAILURE; // skeleton for not overriding type
	}
	else
	{
		res->attribute_value.int_val = value;
		return SUCCESS;
	}
}

/* see sample_item.h */
int attribute_free(attribute_t* attr)
{
	free(attr->attribute_key);
	free(attr->attribute_tag);
	free(attr->attribute_value);
	free(attr);
	return SUCCESS;
}