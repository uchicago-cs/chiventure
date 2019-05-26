/* Implementations of the item struct */
#include "item.h"
#include <string.h>

int item_init(item_t *new_item, char *item_id, char *short_desc, char *long_desc)
{
    assert(new_item != NULL);

    strncpy(new_item->item_id, item_id, strlen(item_id));
    strncpy(new_item->short_desc, short_desc, strlen(short_desc));
    strncpy(new_item->long_desc, long_desc, strlen(long_desc));

    // init. to NULL according to Troy Hanson's documentation?
    // item_new->attributes = NULL;


    return SUCCESS;
}

/* see item.h */
// item_t *item_new(char *item_id, char *short_desc, char *long_desc)
item_t *item_new()
{
    item_t *new_item = malloc(sizeof(item_t));
    new_item->item_id = malloc(MAX_ID_LEN * sizeof(char)); // tentative size allocation
    new_item->short_desc = malloc(MAX_SDESC_LEN * sizeof(char));
    new_item->long_desc = malloc(MAX_LDESC_LEN * sizeof(char));

    new_item->attributes = NULL; //used to be uthash_malloc(NULL) THIS IS WHAT WAS CAUSING THE BUGS

    return new_item;

}

/* See common-item.h */
// int add_item_to_hash(item_t *item, char *item_id, item_t *item_toadd) {
//     item_t* check;
//     HASH_FIND_STR(item_hash, item_id, check);
//     if (check != NULL) {
//         /* WARNING */
//         /* SHOULD BE ABLE TO SUPPORT STACKING MULTIPLE items */
//         fprintf(stderr, "Error: this item id is already in use.\n");
//         exit(1);
//     }
//     HASH_ADD_STR(item_hash, item_id, item_toadd);
//     return SUCCESS;
// }
//


/* see common-item.h */
int add_attribute_to_hash(item_t* item, attribute_t* new_attribute) {
    attribute_t* check;
    HASH_FIND(hh, item->attributes, new_attribute->attribute_key, strlen(new_attribute->attribute_key), check);
    if (check != NULL) {
        fprintf(stderr, "Error: this attribute is already present.\n");
        return FAILURE;
    }
    HASH_ADD_KEYPTR(hh, item->attributes, new_attribute->attribute_key, strlen(new_attribute->attribute_key), new_attribute);
    return SUCCESS;
}
/* see common-item.h */
attribute_t *get_attribute(item_t *item, char* attr_name)
{
    attribute_t* return_value;
    HASH_FIND(hh, item->attributes, attr_name, strlen(attr_name), return_value);
    if (return_value == NULL) {
        return NULL;
    }
    return return_value;
}

/* we need to write a part to the following 5 functions
 * where if the attr alr exists we do not override its type
 */

/* see item.h */
int set_str_attr(item_t* item, char* attr_name, char* value)
{
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        attribute_t* new_attribute = malloc(sizeof(attribute_t));
        new_attribute->attribute_key = (char*)malloc(100);
        new_attribute->attribute_tag = STRING;
        new_attribute->attribute_value.str_val = value;
        strcpy(new_attribute->attribute_key, attr_name);
        int rv = add_attribute_to_hash(item, new_attribute);
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
        new_attribute->attribute_key = (char*)malloc(100);
        new_attribute->attribute_tag = INTEGER;
        new_attribute->attribute_value.int_val = value;
        strcpy(new_attribute->attribute_key, attr_name);
        int rv = add_attribute_to_hash(item, new_attribute);
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
        new_attribute->attribute_key = (char*)malloc(100);
        new_attribute->attribute_tag = DOUBLE;
        new_attribute->attribute_value.double_val = value;
        strcpy(new_attribute->attribute_key, attr_name);
        int rv = add_attribute_to_hash(item, new_attribute);
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
        new_attribute->attribute_key = (char*)malloc(100);
        new_attribute->attribute_tag = CHARACTER;
        new_attribute->attribute_value.char_val = value;
        strcpy(new_attribute->attribute_key, attr_name);
        int rv = add_attribute_to_hash(item, new_attribute);
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
        new_attribute->attribute_key = (char*)malloc(100);
        new_attribute->attribute_tag = BOOLE;
        new_attribute->attribute_value.bool_val = value;
        strcpy(new_attribute->attribute_key, attr_name);
        int rv = add_attribute_to_hash(item, new_attribute);
        return rv;
    }
    else
    {
        res->attribute_value.bool_val = value;
        return SUCCESS;
    }
}

/* see item.h */
char* get_str_attr(item_t *item, char* attr_name)
{
  attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        fprintf(stderr, "Error: attribute get failed.\n");
        exit(1);
    }
    if(res->attribute_tag != STRING)
    {
        fprintf(stderr, "Error: attribute is not type string.\n");
        exit(1);
    }
    return res->attribute_value.str_val;
}

/* see item.h */
int get_int_attr(item_t *item, char* attr_name) {

    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        fprintf(stderr, "Error: attribute get failed.\n");
        exit(1);
    }
    if(res->attribute_tag != INTEGER)
    {
        fprintf(stderr, "Error: attribute is not type integer.\n");
        exit(1);
    }
    return res->attribute_value.int_val;
}

/* see item.h */
double get_double_attr(item_t *item, char* attr_name) {

  attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        fprintf(stderr, "Error: attribute get failed.\n");
        exit(1);
    }
    if (res->attribute_tag != DOUBLE)
    {
        fprintf(stderr, "Error: attribute is not type double.\n");
        exit(1);
    }
    return res->attribute_value.double_val;
}
//rename first error mesg to attribute does not exist

/* see item.h */
char get_char_attr(item_t *item, char* attr_name) {

    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        fprintf(stderr, "Error: attribute get failed.\n");
        exit(1);
    }
    if (res->attribute_tag != CHARACTER)
    {
        fprintf(stderr, "Error: attribute is not type character.\n");
        exit(1);
    }
    return res->attribute_value.char_val;
}

/* see item.h */
bool get_bool_attr(item_t *item, char* attr_name) {
    attribute_t* res = get_attribute(item, attr_name);
    if (res == NULL)
    {
        fprintf(stderr, "Error: attribute get failed.\n");
    }
    if (res->attribute_tag != BOOLE)
    {
        fprintf(stderr, "Error: attribute is not type boolean.\n");
        exit(1);
    }
    return res->attribute_value.bool_val;
}

/* see item.h */
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

/* add_attribute_free() frees an attribute
  Parameters:
    the attribute

  Returns:
    always returns SUCCESS
*/
int attribute_free(attribute_t *attribute) {
    free(attribute->attribute_key);
    free(attribute);
    return SUCCESS;
}

/* delete_all_attributes() deletes all attributes in a hashtable of attributes
  Parameters:
    a hash table of attributes

  Returns:
    Always returns SUCCESS
*/
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
int item_free(item_t *item) {
    free(item->item_id);
    free(item->short_desc);
    free(item->long_desc);
    delete_all_attributes(item->attributes);
    // uthash_free(item->attributes, HASH_SIZE);
    free(item);
    return SUCCESS;
}

/* See common.h*/
int delete_all_items(item_hash_t items) {
    item_t *current_item, *tmp;
    HASH_ITER(hh, items, current_item, tmp) {
        HASH_DEL(items, current_item);  /* delete it (items advances to next) */
        item_free(current_item);             /* free it */
    }
    return SUCCESS;
}
