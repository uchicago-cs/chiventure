/* Implementations of the item struct */
#include <stdio.h>
#include <stdlib.h.h>
#include "item.h"
#include <assert.h>

item_t *item_new(char *item_id, char *short_desc, char *long_desc)
{
  item_t *new_item;
  int check;

  new_item = malloc(sizeof(item_t));
  new_item->item_id = malloc(10*sizeof(char)); // tentative size allocation
  new_item->short_desc = malloc(50*sizeof(char));
  new_item->long_desc = malloc(300*sizeof(char));

  if(new_item == NULL) {
      error("Could not allocate memory!");
      return NULL;
  }

  check = item_init(new_item, short_desc, long_desc);

  if(check != SUCCESS) {
      error("Could not initialize item!");
      return NULL;
  }

  return new_item;

}

int item_init(item_t *new_item, char *item_id, char *short_desc, char *long_desc)
{

  assert(new_item != NULL);
  new_item->item_id = item_id;
  new_item->short_desc = short_desc;
  new_item->long_desc = long_desc;

  return SUCCESS;
}

/* the following functions retrieve specific information from desired item
in anticipation of supporting player demands */

char *get_id(item_t *item)
{
  char *my_item_id = item->item_id;

  return my_item_id;
}


char *get_short_desc(item_t *item)
{
  char *item_shortd = item->short_desc;

  return item_shortd;
}


char *get_long_desc(item_t *item)
{
  char *item_longd = item->long_desc;

  return item_longd;
}


int *get_item_type(enum item_type_t item_t)
{

    /* TO DO */

    return NULL;
}


int take_item(item_t item)
{

    /* TO DO */

    return 0;
}


/* adding item to room inventory hash */
int add_item_to_room(all_items_t all_items, int item_id, item_t *item) {
    item_t *s;
    HASH_FIND_STR(all_items, &item_id, s);
    if (s != NULL) {
        /* WARNING */
        /* SHOULD BE ABLE TO SUPPORT STACKING MULTIPLE itemS */
        printf("FATAL: item_id already used!\n");
        exit(0);
    }
    HASH_ADD_INT(all_items, item_id, s);
    return 1;
}


/* adding item attributes to item attr hash, in progress */
int add_attr_to_item(item_t *item, char *attribute, attribute_value_t item_attr) {
    item_t *s;
    attribute_table_t all_attrs = item->attributes;
    HASH_FIND_STR(all_attrs, attribute, s);
    if (s != NULL) {
        printf("This attribute is already present!\n");
        exit(1);
    }
    HASH_ADD_INT(all_attrs, attribute, s);
    return 1;
}

//do we want to make the attribute union a tagged union?? 
attribute_value_t* create_attribute(void* value, int type)
{
  attribute_value_t* new_attribute = malloc(attribute_value_t)
  if (type == INTEGER)
  {
    new_attribute->int_val = *value;
    return new_attribute;
  }
  else if (type == DOUBLE)
  {
    new_attribute->double_value = *value;
    return new_attribute;
  }
  else if (type == CHARACTER)
  {
    new_attribute->char_val = *value;
    return new_attribute;
  }
  else if (type == STRING)
  {
    new_attribute->str_val = value;
    return new_attribute;
  }
  error("Attribute could not be created");
  return NULL;

}
