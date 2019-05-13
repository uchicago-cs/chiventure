/* Implementations of the item struct */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "item.h"
#include "room.h"
#include "uthash.h"


item_t *item_new(char *item_id, char *short_desc, char *long_desc)
{
  item_t *new_item;
  int check;

  new_item = malloc(sizeof(item_t));
  new_item->item_id = malloc(10*sizeof(char)); // tentative size allocation
  new_item->short_desc = malloc(50*sizeof(char));
  new_item->long_desc = malloc(300*sizeof(char));

  if(new_item == NULL) {
      // error("Could not allocate memory!");
      return NULL;
  }

  check = item_init(new_item, item_id, short_desc, long_desc);

  if(check != 1) {
      // error("Could not initialize item!");
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

  return 1;
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

/*what was this supposed to do?*/
// int *get_obj_type(enum item_type_t obj_t)
// {
//
//     /* TO DO */
//
//     return NULL;
// }


int take_item(item_t *item)
{

    /* TO DO */

    return 0;
}

/* adding item to room inventory hash */
int add_item_to_room(room_t* room, char* item_id, item_t *item) {
    item_t* check;
    item_t* room_items = room->items;
    HASH_FIND_STR(room_items, item_id, check);
    if (check != NULL) {
        /* WARNING */
        /* SHOULD BE ABLE TO SUPPORT STACKING MULTIPLE items */
        fprintf(stderr, "Error: this item id is already in use.\n");
        exit(0);
    }
    HASH_ADD_STR(room_items, item_id, item);
    return 1;
}

/* adding item attributes to item attribute hash */
int add_attr_to_item(item_t *item, char *attribute_key, tagged_attribute_t* new_attribute) {
    tagged_attribute_t* check;
    tagged_attribute_t* all_attributes = item->attributes;
    HASH_FIND_STR(all_attributes, attribute_key, check);
    if (check != NULL) {
        printf("Error: this attribute is already present.\n");
        exit(1);
    }
    HASH_ADD_STR(all_attributes, attribute_key, new_attribute);
    return 1;
}


tagged_attribute_t* create_attribute(void* value, int type)
{
  tagged_attribute_t* new_attribute = (tagged_attribute_t*)malloc(sizeof(tagged_attribute_t));
  if (type == INTEGER)
  {
    new_attribute->int_val = value;
    return new_attribute;
  }
  else if (type == BOOLE)
  {
    new_attribute->boole_val = value;
    return new_attribute;
  }
  else if (type == CHARACTER)
  {
    new_attribute->char_val = value;
    return new_attribute;
  }
  else if (type == STRING)
  {
    new_attribute->str_val = value;
    return new_attribute;
  }
  fprintf(stderr, "Attribute could not be created");
  return NULL;
}

/*in progress*/
int change_attribute(tagged_attribute_t* attribute, void* new_value)
{
  if (attribute->attr_tag == INTEGER)
  {
    attribute->int_val = value;
    return new_attribute;
  }
  else if (type == BOOLE)
  {
    new_attribute->boole_val = value;
    return new_attribute;
  }
  else if (type == CHARACTER)
  {
    new_attribute->char_val = value;
    return new_attribute;
  }
  else if (type == STRING)
  {
    new_attribute->str_val = value;
    return new_attribute;
  }
  fprintf(stderr, "Attribute could not be created");
  return NULL;
}



