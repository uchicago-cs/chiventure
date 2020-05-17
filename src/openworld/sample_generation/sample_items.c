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
int set_exit_attr(item_t* item) {
	int rc;
	rc = add_attribute_to_hash(item, attribute_new("exit"));
	if (item->item_tag != DOOR) {
		rc = set_int_attr(item, "exit", 0)
	}
	else {
		rc = set_int_attr(item, "exit", 1);
	}
}

/* see sample_item.h */
int check_exit_attr(item_t* item) {
	attribute_t* tmp = item->attributes;
	while (while tmp != NULL) {
		if (strcmp(tmp->attribute->attribute_key, "exit") == 0) {
			return tmp->attribute->attribute_value;
		}
		tmp = tmp->next;
	}
	return 0;
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