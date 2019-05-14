#ifndef _ITEM_H
#define _ITEM_H

#include "game_state_common.h"

#define ITER_ALL_ITEMS_IN_ROOM(room, curr_item) item_t *ITTMP_ITEMRM; HASH_ITER(hh, (room)->items, (curr_item), ITTMP_ITEMRM)
#define ITER_ALL_ITEMS_IN_INVENTORY(player, curr_item) item_t *ITTMP_ITEMINV; HASH_ITER(hh, (player)->inventory, (curr_item), ITTMP_ITEMINV)
#define ITER_ALL_ATTRIBUTES(item, curr_attr) attribute_t *ITTMP_ATTR; HASH_ITER(hh, (item)->attributes, (curr_attr), ITTMP_ATTR)

// ITEM STRUCTURE DEFINITION --------------------------------------------------
typedef struct attribute* attribute_hash_t;

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
*  Parameters:
*    a unique item id
*  Returns:
*    A pointer to a new item struct.
*/
item_t *item_new(char *item_id, char *short_desc, char *long_desc);


/* item_new() allocates a space for an item struct in memory
*  Parameters:
*    a unique item id
*  Returns:
*    A pointer to a new item struct.
*/
int item_free(item_t *item);


// ATTRIBUTE STUCTURE DEFINITION ----------------------------------------------
// values will be loaded from WDL/provided by action management
typedef union attribute_value {
    double double_val;
    char char_val;
    bool bool_val;
    char* str_val;
    int int_val;
} attribute_value_t;

enum attribute_tag {DOUBLE, BOOLE, CHARACTER, STRING, INTEGER};

typedef struct attribute {
    UT_hash_handle hh;
    char *attribute_key;
    enum attribute_tag attribute_tag;
    attribute_value_t attribute_value;
} attribute_t;

// ATTRIBUTE FUNCTIONS (FOR ITEMS) --------------------------------------------
// attribute_t* create_attribute(void* value, int type);
//attribute_t* create_attribute(attribute_value_t value, enum attribute_tag type);
attribute_t* create_attribute(void* value, enum attribute_tag type);

int attribute_free(attribute_t *attribute);

int attributes_equal(item_t* item_1, item_t* item_2, char* attribute_name);

// ATTRIBUTE ADDITION FUNCTIONS -----------------------------------------------
// the following functions allow their users to add attributes to the given item
// ex. change a door from locked to unlocked

// attribute_t* create_attribute(void* value, int type);
//attribute_t* create_attribute(attribute_value_t value, enum attribute_tag type);
int create_new_str_attr(item_t* item, char* attr_name, char* value);

int create_new_char_attr(item_t* item, char* attr_name, char value);

int create_new_boole_attr(item_t* item, char* attr_name, bool value);

int create_new_double_attr(item_t* item, char* attr_name, double value);

int create_new_int_attr(item_t* item, char* attr_name, int value);

/* this has to be in interface as room and player modlues use this */
int add_item_to_hash(item_hash_t item_hash, char *item_id, item_t *item);



// ATTRIBUTE REPLACEMENT FUNCTIONS --------------------------------------------
// the following functions allow their users to replace (read: change)
// attributes associated

int replace_str_attr(item_t *item, char* attr_name, char *new_value);

int replace_int_attr(item_t *item, char* attr_name, int new_value);

int replace_char_attr(item_t *item, char* attr_name, char new_value);

int replace_double_attr(item_t *item, char* attr_name, double new_value);

int replace_bool_attr(item_t *item, char* attr_name, bool new_value);

// ATTRIBUTE GET FUNCTIONS --------------------------------------------
// the following functions allow their users to get (read: retrieve)
// attributes associated with an item using the name of the attribute

char* get_str_attr(item_t *item, char* attr_name);

int get_int_attr(item_t *item, char* attr_name);

double get_double_attr(item_t *item, char* attr_name);

char get_char_attr(item_t *item, char* attr_name);

bool get_bool_attr(item_t *item, char* attr_name);


// DELETION FUNCTIONS -----------------------------------------------
/* this has to be in the interace as room and player modules use this */
int delete_all_items(item_hash_t items);

int delete_item_attributes(item_t* item);

/*create a function to add to the attribute table, create a function that returnsd the value of an attribute,
create a function that changes an attribute,

*/

#endif
