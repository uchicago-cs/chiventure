#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "game-state/item.h"
#include "playerclass/class.h"
#include "playerclass/class_structs.h"

/* see class_item.h */
int add_item_multiplier(item_t* item, class_t* class, double multiplier) {
    if ((item == NULL) || (class == NULL)) {
        fprintf(stderr, "Item or Class provided are NULL in add_item_multiplier.\n");
        return FAILURE;
    }

    if (multiplier < 0) {
        fprintf(stderr, "Negative multiplier provided in add_item_multiplier.\n");
        return FAILURE;
    }

    if (item->class_multipliers == NULL)
        item->class_multipliers = create_list_attribute();
    
    attribute_t *attr = list_get_attribute(item->class_multipliers, class->name);

    /* If the item already has a multiplier attribute for this class, overwrite it. */
    if (attr != NULL) {
        if (attr->attribute_tag == DOUBLE) {
            attr->attribute_value.double_val = multiplier;
            return SUCCESS;
        }
        else {
            fprintf(stderr, "Class multiplier attribute already exists with wrong type "
                            "in add_item_multiplier.\n");
            return FAILURE;
        }
    }
    
    attr = double_attr_new(strndup(class->name, 100), multiplier);

    if (attr == NULL) {
        fprintf(stderr, "Failed to allocate memory in add_item_multiplier.\n");
        return FAILURE;
    }

    int add_rc = add_attribute_to_list(item->class_multipliers, attr); 
    return add_rc;
}


/* see class_item.h */
double get_class_item_multiplier(item_t* item, class_t* class) {
    if ((item == NULL) || (class == NULL)) {
        fprintf(stderr, "Item or Class provided are NULL in get_class_item_multiplier.\n");
        return FAILURE;
    }

    /* A multiplier of 1.0 is returned in the case where it has not been set */
    char buffer[101];
    if (!list_contains_attribute(item->class_multipliers, strncpy(buffer, class->name, 100)))
        return 1.0;

    return list_get_double_attr(item->class_multipliers, class->name);
}


/* see class_item.h */
int remove_item_multiplier(item_t* item, class_t* class) {
    if ((item == NULL) || (class == NULL)) {
        fprintf(stderr, "Item or Class provided are NULL in remove_item_restriction.\n");
        return FAILURE;
    }

    char buffer[101];
    /* If the item multiplier does not exist, removing the multiplier is considered a success. */
    if (!list_contains_attribute(item->class_multipliers, strncpy(buffer, class->name, 100)))
        return SUCCESS;

    int remove_rc = remove_attribute_from_list(item->class_multipliers, class->name);
    return remove_rc;
}


/* see class_item.h */
int add_item_restriction(item_t* item, class_t* class) {
    if ((item == NULL) || (class == NULL)) {
        fprintf(stderr, "Item or Class provided are NULL in add_item_restriction.\n");
        return FAILURE;
    }
    
    /* 0 represents no proficiency with an item, so it is treated as restricted. */
    int add_rc = add_item_multiplier(item, class, 0.0); 
    return add_rc;
}


/* see class_item.h */
bool is_restricted(item_t* item, class_t* class) {
    if ((item == NULL) || (class == NULL)) {
        fprintf(stderr, "Item or Class provided are NULL in is_restricted.\n");
        return FAILURE;
    }
    
    return list_get_double_attr(item->class_multipliers, class->name) == 0.0;
}


/* see class_item.h */
int remove_item_restriction(item_t* item, class_t* class) {
    if ((item == NULL) || (class == NULL)) {
        fprintf(stderr, "Item or Class provided are NULL in remove_item_restriction.\n");
        return FAILURE;
    }

    if (!is_restricted(item, class)) {
        fprintf(stderr, "Class is not currently restricted from using this item.\n");
        return FAILURE;
    }

    int remove_rc = remove_item_multiplier(item, class);
    return remove_rc;
}
