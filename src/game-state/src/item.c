/* Implementations of the item struct */
#include "item.h"


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


attribute_t* create_attribute(attribute_value_t value, enum attribute_tag type)
{
    attribute_t* new_attribute = malloc(sizeof(attribute_t));

    new_attribute->attribute_tag = type;
    new_attribute->attribute_value = value;

    return new_attribute;

    // if (type == INTEGER)
    // {
    //     new_attribute->int_val = value;
    //     return new_attribute;
    // }
    // else if (type == BOOLE)
    // {
    //     new_attribute->boole_val = value;
    //     return new_attribute;
    // }
    // else if (type == CHARACTER)
    // {
    //     new_attribute->char_val = value;
    //     return new_attribute;
    // }
    // else if (type == STRING)
    // {
    //     new_attribute->str_val = value;
    //     return new_attribute;
    // }
    // fprintf(stderr, "Attribute could not be created");
    // return NULL;
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
        printf("Error: this attribute is already present.\n");
        exit(1);
    }
    HASH_ADD_STR(attribute_hash, attribute_key, attribute);
    return 1;
}

void* get_attribute(item_t* item)
{
    /*to do*/
    return NULL;
}


/*in progress*/
int change_attribute(attribute_t* attribute, attribute_value_t value)
{
    attribute->attribute_value = value;
    return 1;
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