#ifndef _CONDITION_H
#define _CONDITION_H

#include "game_state_common.h"
#include "player.h"
#include "item.h"


typedef struct attribute_condition{
    item_t *item;
    attribute_t *attribute_to_check; //pointer to attribute
    attribute_value_t expected_value;
} attribute_condition_t;

typedef struct inventory_condition{
    player_t *player_to_check;
    item_t *expected_item;
} inventory_condition_t;

typedef union condition_type{
    attribute_condition_t* attr_type;
    inventory_condition_t* inven_type;
} condition_type_t;

enum condition_tag {ATTRIBUTE,INVENTORY};

typedef struct condition{
    condition_type_t type;
    enum condition_tag condition_tag;
    struct condition *next;
} condition_t;

/* This typedef is to distinguish between condition_t
* pointers which are used to point to the condition_t structs
* in the traditional sense, and those which are used to enable UTLIST functionality
* on the ondition_t structs as specified in src/common/include
*/
typedef struct condition condition_list_t;

#endif