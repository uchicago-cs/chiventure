#ifndef _OBJECT_H
#define _OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include "uthash.h"
// #include "player.h"
// #include "room.h"
// #include "game.h"

//where does this belong?? 
/* Forward declaration of linked list */
typedef struct all_items {
    /* fields used for linked list */
    struct exit *next, *prev;

    /* add necessary item info here */

} all_items_t;

enum attribute_tag {BOOLE, CHARACTER, STRING, INTEGER};

// values will be loaded from WDL/provided by action management
typedef union attribute_value {
    bool *boole_val;
    char *char_val;
    char *str_val;
    int *int_val;
} attribute_value_t;

typedef struct tagged_attributes {
  UT_hash_handle hh;
  char* attribute_name;
  enum attribute_tag attr_tag;
  attribute_value_t attr_value;
} tagged_attributes_t;

/*
typedef struct attribute_table {
    UT_hash_handle hh; //makes this struct hashable for the object struct
    char* attribute_name;
    tagged_attrs_t tagged_values;
} attribute_table_t;
*/

/* this object struct will include a door object to be used between rooms,
i.e. included in the room struct in its list of exits */
typedef struct item {
    UT_hash_handle hh; //makes thuis struct hashable for the room struct (objects in rooms) and player struct (inventory)
    char *item_id;
    char *short_desc;
    char *long_desc;
    bool condition; /* reserved for future expansion */
    tagged_attributes_t* attributes;
} item_t;

/* item_new() allocates a space for an item struct in memory
  Parameters: 
    a unique item id
    a short description of the item
    a long description of the item
  Returns:
    A pointer to a new item struct.
*/
item_t *item_new(char *item_id, char *short_desc, char *long_desc);

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
int item_init(item_t *new_item, char *item_id, char *short_desc, char *long_desc);

/* get_id() retrieves the unique id of the item
  Parameters:
    the item struct in question
  Returns:
    a string representing the item id
*/
char *get_id(item_t *item);

/* get_short_desc() retrieves the short description of the item
  Parameters:
    the item struct in question
  Returns:
    a string representing a brief description of the item
*/
char *get_short_desc(item_t *item);

/* get_long_desc() retrieves the long description of the item
  Parameters:
    the item struct in question
  Returns:
    a string representing a longer, more detailed description of the item
*/
char *get_long_desc(item_t *item);

/* get_item_type() retrieves the type of the item
  Parameters:
    the item struct in question
  Returns:

*/
// int *get_item_type(enum item_type_t item);

int take_item(item_t *item);

attribute_value_t* create_attribute(void* value, int type);

/*create a function to add to the attribute table, create a function that returnsd the value of an attribute,
create a function that changes an atttribute,

*/

#endif
