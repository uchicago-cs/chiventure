#ifndef _ITEM_H
#define _ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"
#include "player.h"
#include "room.h"
#include "game.h"

enum attribute_tag {INTEGER, DOUBLE, CHARACTER, STRING}

// values will be loaded from WDL/provided by action management
typedef union attribute_value {
    bool b;
    char char_val;
    char *str_val;
    int int_val;
} attribute_value_t;


/* this item struct will include a door item to be used between rooms,
i.e. included in the room struct in its list of exits */
typedef struct item {
    UT_hash_handle hh; //makes thuis struct hashable for the room struct (items in rooms) and player struct (inventory)
    char *item_id;
    char *short_desc;
    char *long_desc;
    bool condition; /* reserved for future expansion */
    attribute_table_t attributes;
} item_t;

typedef struct item* all_items_t;

typedef struct attribute_table{
    UT_hash_handle hh; //makes this struct hashable for the item struct
    char* attribute_name;
    union attribute_value_t val;
} attribute_table_t;

item_t *item_new();

// arguments are taken from WDL
int item_init(char *item_id, char *short_desc, char *long_desc);
//
char *get_id(item_t item);

char *get_short_desc(item_t item);

char *get_long_desc(item_t item);

int *get_item_type(enum item_type_t item_t);

int take_item(item_t item);

attribute_value_t *create_attribute(void* value, int type);

/*create a function to add to the attribute table, create a function that returnsd the value of an attribute,
create a function that changes an atttribute,

*/

#endif
