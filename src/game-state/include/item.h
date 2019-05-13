#ifndef _ITEM_H
#define _ITEM_H

#include "game_state_common.h"

// values will be loaded from WDL/provided by action management
typedef union attribute_value {
    double double_val;
    char char_val;
    bool bool_val;
    char* str_val;
    int int_val;
} attribute_value_t;

enum attribute_tag {BOOLE, CHARACTER, STRING, INTEGER, DOUBLE};

typedef struct attribute {
    UT_hash_handle hh;
    char *attribute_key;
    enum attribute_tag attribute_tag;
    attribute_value_t attribute_value;
} attribute_t;

typedef struct attribute* attribute_hash_t;

/* this object struct will include a door object to be used between rooms,
i.e. included in the room struct in its list of exits */
typedef struct item {
    UT_hash_handle hh; //makes thuis struct hashable for the room struct (objects in rooms) and player struct (inventory)
    char *item_id;
    char *short_desc;
    char *long_desc;
    // bool condition; /* reserved for future expansion */
    attribute_hash_t attributes; // a hashtable for all attributes
} item_t;

typedef struct item* item_hash_t;
/* item_new() allocates a space for an item struct in memory
  Parameters:
    a unique item id
    a short description of the item
    a long description of the item
  Returns:
    A pointer to a new item struct.
*/
item_t *item_new(char *item_id, char *short_desc, char *long_desc);


/* get_item_type() retrieves the type of the item
  Parameters:
    the item struct in question
  Returns:

*/
// int *get_item_type(enum item_type_t item);

int take_item(item_t *item);

// attribute_t* create_attribute(void* value, int type);
//attribute_t* create_attribute(attribute_value_t value, enum attribute_tag type);
int create_new_str_attr(item_t* item, char* attr_name, char* value);

int create_new_char_attr(item_t* item, char* attr_name, char value);

int create_new_boole_attr(item_t* item, char* attr_name, bool value);

int create_new_double_attr(item_t* item, char* attr_name, double value);

int create_new_int_attr(item_t* item, char* attr_name, int value);

/* this has to be in interface as room and player modlues use this -- but shoudl it??*/
int add_item_to_hash(item_hash_t item_hash, char *item_id, item_t *item);

int item_free(item_t *item);

int attribute_free(attribute_t *attribute);

/* this has to be in the interace as room and player modules use this */
int delete_all_items(item_hash_t items);

int delete_item_attributes(item_t* item);

/*create a function to add to the attribute table, create a function that returnsd the value of an attribute,
create a function that changes an atttribute,

*/

#endif
