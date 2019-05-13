/* Implementations of the item struct */
#include "item.h"

/* see item.h */
item_t *item_new(char *item_id, char *short_desc, char *long_desc)
{
    item_t *new_item = malloc(sizeof(item_t));
    new_item->item_id = malloc(MAX_ID_LEN * sizeof(char)); // tentative size allocation
    new_item->short_desc = malloc(MAX_SDESC_LEN * sizeof(char));
    new_item->long_desc = malloc(MAX_LDESC_LEN * sizeof(char));

    if(new_item == NULL || new_item->item_id == NULL || new_item->short_desc == NULL || new_item->long_desc == NULL) {
        // error("Could not allocate memory!");
        exit(1);
    }

    int check = item_init(new_item, item_id, short_desc, long_desc);

    if(check != 1) {
        // error("Could not initialize item!");
        exit(1);
    }

    return new_item;

}

/* item_init() initializes an item struct with given values
    arguments are taken from WDL
  Parameters:
    a memory allocated new item pointer
    a unique item id
    a short description of the item
    a long description of the item

  Returns:
    0 for failure, 1 for success
*/
int item_init(item_t *new_item, char *item_id, char *short_desc, char *long_desc)
{
    assert(new_item != NULL);

    strcpy(new_item->item_id, item_id);
    strcpy(new_item->short_desc, short_desc);
    strcpy(new_item->long_desc, long_desc);

    return 1;
}

/* add_attribute_to_hash() adds an attribute to the item hash table
  Parameters:
    the hash table of an item
    the attribute value to add

  Returns:
    0 for failure, 1 for success
*/
int add_attribute_to_hash(attribute_hash_t attribute_hash, attribute_t* new_attribute) {
    attribute_t* check;
    char* attribute_key = new_attribute->attribute_key;
    HASH_FIND_STR(attribute_hash, attribute_key, check);
    if (check != NULL) {
        fprintf(stderr, "Error: this attribute is already present.\n");
        return 0;
    }
    HASH_ADD_STR(attribute_hash, attribute_key, new_attribute);
    return 1;
}

attribute_t *replace_attribute(item_t *item, char *attribute_name) {
    attribute_t* return_value;
    attribute_hash_t attribute_hash = item->attributes;
    char *attr_key = attribute->attribute_key;
    HASH_FIND_STR(attribute_hash, attribute_key, return_value);
    if (check != NULL) {
        fprintf(stderr, "Error: this attribute is already present.\n");
        return NULL;
    }
    HASH_REPLACE_STR(attribute_hash, attribute_key, attribute);
    return return_value;
}

int replace_str_attr(item_t *item, char* attr_name, attribute_value_t *new_value) {

  int res = replace_attribute(item, attr_name);
  if (res == 0) {
    fprintf(stderr, "Error: attribute replacement failed.\n");
  }

  res.str_val = new_value;
  attr->attribute_value = new_value;

  return 1;
}

int replace_int_attr(item_t *item, attribute_t* attr) {

  int res = replace_attribute(item, attr);
  if (res == 0) {
    fprintf(stderr, "Error: attribute replacement failed.\n");
  }

  res.int_val = new_value;
  attr->attribute_value = new_value;

  return 1;
}

int replace_double_attr(item_t *item, attribute_t* attr) {

  int res = replace_attribute(item, attr);
  if (res == 0) {
    fprintf(stderr, "Error: attribute replacement failed.\n");
  }

  res.double_val = new_value;
  attr->attribute_value = new_value;

  return 1;
}

int replace_char_attr(item_t *item, attribute_t* attr) {

  int res = replace_attribute(item, attr);
  if (res == 0) {
    fprintf(stderr, "Error: attribute replacement failed.\n");
  }

  res.char_val = new_value;
  attr->attribute_value = new_value;

  return 1;
}

int replace_bool_attr(item_t *item, attribute_t* attr) {

  int res = replace_attribute(item, attr);
  if (res == 0) {
    fprintf(stderr, "Error: attribute replacement failed.\n");
  }

  res.bool_val = new_value;
  attr->attribute_value = new_value;

  return 1;
}

/* see item.h */
int add_attribute_to_item(item_t* item, char *attribute_key, attribute_t* attribute)
{
    int rv = add_attribute_to_hash(item->attributes, attribute_key, attribute);
/* see item.h */
int create_new_str_attr(item_t* item, char* attr_name, char* value)
{
    attribute_t* new_attribute = malloc(sizeof(attribute_t));
    new_attribute->attribute_tag = STRING;
    new_attribute->attribute_value.str_val = value;
    new_attribute->attribute_key = attr_name;
    int rv = add_attribute_to_hash(item->attributes, new_attribute);
    return rv;
}

/* see item.h */
int create_new_char_attr(item_t* item, char* attr_name, char value)
{
    attribute_t* new_attribute = malloc(sizeof(attribute_t));
    new_attribute->attribute_tag = CHARACTER;
    new_attribute->attribute_value.char_val = value;
    new_attribute->attribute_key = attr_name;
    int rv = add_attribute_to_hash(item->attributes, new_attribute);
    return rv;
}

/* see item.h */
int create_new_bool_attr(item_t* item, char* attr_name, bool value)
{
    attribute_t* new_attribute = malloc(sizeof(attribute_t));
    new_attribute->attribute_tag = BOOLE;
    new_attribute->attribute_value.bool_val = value;
    new_attribute->attribute_key = attr_name;
    int rv = add_attribute_to_hash(item->attributes, new_attribute);
    return rv;
}

/* see item.h */
int create_new_double_attr(item_t* item, char* attr_name, double value)
{
    attribute_t* new_attribute = malloc(sizeof(attribute_t));
    new_attribute->attribute_tag = DOUBLE;
    new_attribute->attribute_value.double_val = value;
    new_attribute->attribute_key = attr_name;
    int rv = add_attribute_to_hash(item->attributes, new_attribute);
    return rv;
}

/* see item.h */
int create_new_int_attr(item_t* item, char* attr_name, int value)
{
    attribute_t* new_attribute = malloc(sizeof(attribute_t));
    new_attribute->attribute_tag = INTEGER;
    new_attribute->attribute_value.int_val = value;
    new_attribute->attribute_key = attr_name;
    int rv = add_attribute_to_hash(item->attributes, new_attribute);
    return rv;
}


/* Need a function that checks if two attribute_value_ts are equal
* TBD: Is this game-state or action management task?
*/

/* See item.h */
int item_free(item_t *item) {
    free(item->item_id);
    free(item->short_desc);
    free(item->long_desc);
    delete_all_attributes(item->attributes);
    free(item);
    return 1;
}


/* See item.h */
int delete_all_items(item_hash_t items) {
    item_t *current_item, *tmp;
    HASH_ITER(hh, items, current_item, tmp) {
        HASH_DEL(items, current_item);  /* delete it (items advances to next) */
        item_free(current_item);             /* free it */
    }
    return 1;
}

/* See item.h */
int attribute_free(attribute_t *attribute) {
    free(attribute->attribute_key);
    free(attribute);
    return 1;
}

int delete_all_attributes(attribute_hash_t attributes)
{
    attribute_t *current_attribute, *tmp;
    HASH_ITER(hh, attributes, current_attribute, tmp) {
        HASH_DEL(attributes, current_attribute);  /* delete it (attributes advances to next) */
        attribute_free(current_attribute);             /* free it */
    }
    return 1;
}

/* See item.h */
int delete_item_attributes(item_t* item)
{
<<<<<<< HEAD

}
=======
    return delete_all_attributes(item->attributes);
}
>>>>>>> a0f0ef90518c25ce555a18865fe7774e9b4ac4ae
