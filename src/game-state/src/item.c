/* Implementations of the item struct */
#include "item.h"
#include <string.h>

/* item_init() initializes an item struct with given values
    arguments are taken from WDL
  Parameters:
    a memory allocated new item pointer
    a unique item id
    a short description of the item
    a long description of the item

  Returns:
    FAILURE for failure, SUCCESS for success
*/
int item_init(item_t *new_item, char *item_id, char *short_desc, char *long_desc)
{
    assert(new_item != NULL);

    strcpy(new_item->item_id, item_id);
    strcpy(new_item->short_desc, short_desc);
    strcpy(new_item->long_desc, long_desc);

    return SUCCESS;
}

/* see item.h */
item_t *item_new(char *item_id, char *short_desc, char *long_desc)
{
    item_t *new_item = malloc(sizeof(item_t));
    new_item->item_id = malloc(MAX_ID_LEN * sizeof(char)); // tentative size allocation
    new_item->short_desc = malloc(MAX_SDESC_LEN * sizeof(char));
    new_item->long_desc = malloc(MAX_LDESC_LEN * sizeof(char));

    if(new_item == NULL || new_item->item_id == NULL ||
       new_item->short_desc == NULL || new_item->long_desc == NULL) {
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

/* add_attribute_to_hash() adds an attribute to the item hash table
  Parameters:
    the hash table of an item
    the attribute value to add

  Returns:
    FAILURE for failure, SUCCESS for success
*/
int add_attribute_to_hash(attribute_hash_t attribute_hash, attribute_t* new_attribute) {
    attribute_t* check;
    char* attribute_key = new_attribute->attribute_key;
    HASH_FIND_STR(attribute_hash, attribute_key, check);
    if (check != NULL) {
        fprintf(stderr, "Error: this attribute is already present.\n");
        return FAILURE;
    }
    HASH_ADD_STR(attribute_hash, attribute_key, new_attribute);
    return SUCCESS;
}

attribute_t *get_attribute(item_t *item, char *attr_name) 
{
    attribute_t* return_value;
    attribute_hash_t attribute_hash = item->attributes;
    HASH_FIND_STR(attribute_hash, attr_name, return_value);
    if (return_value != NULL) {
        fprintf(stderr, "Error: this attribute is already present.\n");
        return NULL;
    }
    return return_value;
}

/* see item.h */
int set_str_attr(item_t* item, char* attr_name, char* value)
{
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL) 
    {
        attribute_t* new_attribute = malloc(sizeof(attribute_t));
        new_attribute->attribute_tag = STRING;
        new_attribute->attribute_value.str_val = value;
        new_attribute->attribute_key = attr_name;
        int rv = add_attribute_to_hash(item->attributes, new_attribute);
        return rv;
    }
    else
    {
        res->attribute_value.str_val = value;
        return SUCCESS;
    }    
}


/* see item.h */
int set_int_attr(item_t* item, char* attr_name, int value)
{
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL) 
    {
        attribute_t* new_attribute = malloc(sizeof(attribute_t));
        new_attribute->attribute_tag = INTEGER;
        new_attribute->attribute_value.int_val = value;
        new_attribute->attribute_key = attr_name;
        int rv = add_attribute_to_hash(item->attributes, new_attribute);
        return rv;
    }
    else
    {
        res->attribute_value.int_val = value;
        return SUCCESS;
    }    
}

/* see item.h */
int set_double_attr(item_t* item, char* attr_name, double value)
{
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL) 
    {
        attribute_t* new_attribute = malloc(sizeof(attribute_t));
        new_attribute->attribute_tag = DOUBLE;
        new_attribute->attribute_value.double_val = value;
        new_attribute->attribute_key = attr_name;
        int rv = add_attribute_to_hash(item->attributes, new_attribute);
        return rv;
    }
    else
    {
        res->attribute_value.double_val = value;
        return SUCCESS;
    }    

}

/* see item.h */
int set_char_attr(item_t* item, char* attr_name, char value)
{
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL) 
    {
        attribute_t* new_attribute = malloc(sizeof(attribute_t));
        new_attribute->attribute_tag = CHARACTER;
        new_attribute->attribute_value.char_val = value;
        new_attribute->attribute_key = attr_name;
        int rv = add_attribute_to_hash(item->attributes, new_attribute);
        return rv;
    }
    else
    {
        res->attribute_value.char_val = value;
        return SUCCESS;
    }    
}

/* see item.h */
int set_bool_attr(item_t* item, char* attr_name, bool value)
{
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL) 
    {
        attribute_t* new_attribute = malloc(sizeof(attribute_t));
        new_attribute->attribute_tag = BOOLE;
        new_attribute->attribute_value.bool_val = value;
        new_attribute->attribute_key = attr_name;
        int rv = add_attribute_to_hash(item->attributes, new_attribute);
        return rv;
    }
    else
    {
        res->attribute_value.bool_val = value;
        return SUCCESS;
    }    
}

char* get_str_attr(item_t *item, char* attr_name) {

  attribute_t* res = get_attribute(item, attr_name);
  if (res == NULL) {
    fprintf(stderr, "Error: attribute get failed.\n");
  }
  return res->attribute_value.str_val;
}

int get_int_attr(item_t *item, char* attr_name) {

  attribute_t* res = get_attribute(item, attr_name);
  if (res == NULL) {
    fprintf(stderr, "Error: attribute get failed.\n");
  }

  return res->attribute_value.int_val;
}

double get_double_attr(item_t *item, char* attr_name) {

  attribute_t* res = get_attribute(item, attr_name);
  if (res == NULL) {
    fprintf(stderr, "Error: attribute get failed.\n");
  }

  return res->attribute_value.double_val;
}

char get_char_attr(item_t *item, char* attr_name) {

  attribute_t* res = get_attribute(item, attr_name);
  if (res == NULL) {
    fprintf(stderr, "Error: attribute get failed.\n");
  }

  return res->attribute_value.char_val;
}

bool get_bool_attr(item_t *item, char* attr_name) {

  attribute_t* res = get_attribute(item, attr_name);
  if (res == NULL) {
    fprintf(stderr, "Error: attribute get failed.\n");
  }

  return res->attribute_value.bool_val;
}

int attributes_equal(item_t* item_1, item_t* item_2, char* attribute_name)
{
    attribute_t* attribute_1 = get_attribute(item_1, attribute_name);
    attribute_t* attribute_2 = get_attribute(item_2, attribute_name);
    if(attribute_1==NULL || attribute_2==NULL)
    {
        fprintf(stderr, "Error: attribute does not exist for one or more items\n");
        return -1;
    }
    if (attribute_1->attribute_tag != attribute_2->attribute_tag)
    {
        fprintf(stderr, "Error: could not compare attributes as they are of different types\n");
        return -1;
    }
    int comparison = 0;
    switch(attribute_1->attribute_tag)
    {
        case(DOUBLE):
            if (attribute_1->attribute_value.double_val == attribute_2->attribute_value.double_val)
            {
                comparison = 1;
            }
            break;
        case(BOOLE):
            if (attribute_1->attribute_value.bool_val == attribute_2->attribute_value.bool_val)
            {
                comparison = 1;
            }
            break;
        case(CHARACTER):
            if (attribute_1->attribute_value.char_val == attribute_2->attribute_value.char_val)
            {
                comparison = 1;
            }
            break;
        case(STRING):
            if (!strcmp(attribute_1->attribute_value.str_val,attribute_2->attribute_value.str_val))
            {
                comparison = 1;
            }
            break;
        case(INTEGER):
            if (attribute_1->attribute_value.int_val == attribute_2->attribute_value.int_val)
            {
                comparison = 1;
            }
            break;
    }
    return comparison;
}

int delete_all_attributes(attribute_hash_t attributes)
{
    attribute_t *current_attribute, *tmp;
    HASH_ITER(hh, attributes, current_attribute, tmp) {
        HASH_DEL(attributes, current_attribute);  /* delete it (attributes advances to next) */
        attribute_free(current_attribute);             /* free it */
    }
    return SUCCESS;
}

/* See item.h */
int delete_item_attributes(item_t* item)
{
    return delete_all_attributes(item->attributes);
}

/* See item.h */
int attribute_free(attribute_t *attribute) {
    free(attribute->attribute_key);
    free(attribute);
    return SUCCESS;
}

/* See item.h */
int item_free(item_t *item) {
    free(item->item_id);
    free(item->short_desc);
    free(item->long_desc);
    delete_all_attributes(item->attributes);
    free(item);
    return SUCCESS;
}

/* See item.h */
int delete_all_items(item_hash_t items) {
    item_t *current_item, *tmp;
    HASH_ITER(hh, items, current_item, tmp) {
        HASH_DEL(items, current_item);  /* delete it (items advances to next) */
        item_free(current_item);             /* free it */
    }
    return SUCCESS;
}
