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

/* the following functions retrieve specific information from desired item
in anticipation of supporting player demands */

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

/* see item.h */
attribute_t* create_attribute(void* value, enum attribute_tag type)
{
    attribute_t* new_attribute = malloc(sizeof(attribute_t));

    new_attribute->attribute_tag = type;
    switch(type)
    {
        case(INTEGER):
            new_attribute->attribute_value.int_val = value;
            return new_attribute;
            break;
        case(BOOLE):
            new_attribute->attribute_value.boole_val = value;
            return new_attribute;
            break;
        case(CHARACTER):
            new_attribute->attribute_value.char_val = value;
            return new_attribute;
            break;
        case(STRING):
            new_attribute->attribute_value.str_val = value;
            return new_attribute;
            break;
        default:
            fprintf(stderr, "Attribute could not be created");
            return NULL;
    }
}

/* adding item to room inventory hash */
int add_item_to_hash(item_hash_t item_hash, char *item_id, item_t *item) {
    item_t* check;
    HASH_FIND_STR(item_hash, item_id, check);
    if (check != NULL) {
        /* WARNING */
        /* SHOULD BE ABLE TO SUPPORT STACKING MULTIPLE items */
        fprintf(stderr, "Error: this item id is already in use.\n");
        exit(1);
    }
    HASH_ADD_STR(item_hash, item_id, item);
    return 1;
}

/* adding item attributes to item attribute hash */
int add_attribute_to_hash(attribute_hash_t attribute_hash, char *attribute_key, attribute_t* attribute) {
    attribute_t* check;
    HASH_FIND_STR(attribute_hash, attribute_key, check);
    if (check != NULL) {
        fprintf(stderr, "Error: this attribute is already present.\n");
        return 0;
    }
    HASH_ADD_STR(attribute_hash, attribute_key, attribute);
    return 1;
}

/* see item.h */
int add_attribute_to_item(item_t* item, char *attribute_key, attribute_t* attribute)
{
    int rv = add_attribute_to_hash(item->attributes, attribute_key, attribute);
    return rv;
}

/* see item.h */
void* get_attribute_value(item_t* item, char* attribute_key)
{
    attribute_t* attribute;
    attribute_hash_t attribute_hash = item->attributes;
    HASH_FIND_STR(attribute_hash, attribute_key, attribute);
    if (attribute == NULL)
    {
        printf("Error: this attribute does not exist\n");
        return NULL;
    }
    switch(attribute->attribute_tag)
    {
        case(BOOLE):
            return attribute->attribute_value.boole_val;
            break;
        case(CHARACTER):
            return attribute->attribute_value.char_val;
            break;
        case(INTEGER):
            return attribute->attribute_value.int_val;
            break;
        case(STRING):
            return attribute->attribute_value.int_val;
            break;
    }
    if (attribute == NULL) {
        printf("Error: this attribute does not exist\n");
    }
    return NULL;
}

/* see item.h */
int change_attribute(item_t* item, char* attribute_key, void* new_value)
{
    switch(attribute->attr_tag)
    {
        case(INTEGER):
            attribute->attr_value.int_val = new_value;
            return 1;
        case(BOOLE):

    }

//   if (attribute->attr_tag == INTEGER)
//   {
//     attribute->attr_value.int_val = new_value;
//     return 1;
//   }
//   else if (type == BOOLE)
//   {
//     attribute->attr_value.boole_val = new_value;
//     return 1;
//   }
//   else if (type == CHARACTER)
//   {
//     attribute->attr_value.char_val = new_value;
//     return 1;
//   }
//   else if (type == STRING)
//   {
//     attribute->attr_value.str_val = new_value;
//     return 1;
//   }
//   fprintf(stderr, "Attribute could not be changed");
//   return 0;
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
int attribute_free(attribute_t *attribute) {
    free(attribute->attribute_key);
    free(attribute);
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
int delete_item_attributes(attribute_hash_t attributes) {
    attribute_t *current_attribute, *tmp;
    HASH_ITER(hh, attributes, current_attribute, tmp) {
        HASH_DEL(attributes, current_attribute);  /* delete it (attributes advances to next) */
        attribute_free(current_attribute);             /* free it */
    }
    return 1;
}

int delete_all_attributes(item_t* item)
{
    
}
