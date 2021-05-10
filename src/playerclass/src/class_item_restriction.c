#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "game-state/item.h"
#include "playerclass/class.h"
#include "playerclass/class_structs.h"

/* see class_item_restriction.h */
int add_item_restriction(item_t* item, class_t* class) {
    if ((item == NULL) | (class == NULL)) {
        fprintf(stderr, "Item or Class provided are NULL in add_item_restriction");
        return FAILURE;
    }

    if (item->class_multipliers == NULL) {
        item->class_multipliers = create_list_attribute();
    }
    
    /* 0 represents no proficiency with an item, so it is treated as restricted. */
    attribute_t* restriction = double_attr_new(strndup(class->name, 100), 0.0);

    if (restriction == NULL) {
        fprintf(stderr, "Failed to allocate memory in add_item_restriction");
        return FAILURE;
    }

    int add_rc = add_attribute_to_list(item->class_multipliers, restriction); 
    return add_rc;
}

/* see class_item_restriction.h */
bool is_restricted(item_t* item, class_t* class) {
    if ((item == NULL) | (class == NULL)) {
        fprintf(stderr, "Item or Class provided are NULL in is_restricted");
        return FAILURE;
    }

    if (!list_contains_attribute(item->class_multipliers, strndup(class->name, 100)))
        return false;
    
    return list_get_double_attr(item->class_multipliers, class->name) == 0.0;
}

/* see class_item_restriction.h */
int remove_item_restriction(item_t* item, class_t* class) {
    if ((item == NULL) | (class == NULL)) {
        fprintf(stderr, "Item or Class provided are NULL in remove_item_restriction");
        return FAILURE;
    }

    if (!is_restricted(item, class)){
        fprintf(stderr, "Class is not currently restricted from using this item");
        return FAILURE;
    }

    int remove_rc = remove_attribute_from_list(item->class_multipliers, class->name);
    return remove_rc;
}
