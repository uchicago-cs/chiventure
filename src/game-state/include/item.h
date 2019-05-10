#ifndef _OBJECT_H
#define _OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"
#include "player.h"
#include "room.h"
#include "game.h"

enum attribute_tag {INTEGER, DOUBLE, CHARACTER, STRING}

//actual values left up to action management
typedef union attribute_value {
    char* str_val;
    int int_val;
    double double_val;
    char char_val;
} attribute_value_t;

/* this object struct will include a door object to be used between rooms,
i.e. included in the room struct in its list of exits */
typedef struct object {
    UT_hash_handle hh; //makes thuis struct hashable for the room struct (objects in rooms) and player struct (inventory)
    char *object_id;
    char *short_desc;
    char *long_desc;
    bool condition; /* reserved for future expansion */
    attribute_table_t attributes;
} object_t;

typedef struct attribute_table{
    UT_hash_handle hh; //makes this struct hashable for the object struct
    char* attribute_name;
    union attribute_value_t val;
} attribute_table_t;

object_t *object_new();

// arguments are taken from WDL
int object_init(char *object_id, char *short_desc, char *long_desc);
//
char *get_id(object_t obj);

char *get_short_desc(object_t obj);

char *get_long_desc(object_t obj);

int *get_obj_type(enum object_type_t obj_t);

int take_object(object_t obj);

attribute_value_t* create_attribute(void* value, int type);

/*create a function to add to the attribute table, create a function that returnsd the value of an attribute, 
create a function that changes an atttribute, 

*/

#endif