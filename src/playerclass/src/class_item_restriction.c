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

    if (item->class_restrictions == NULL) {
        item->class_restrictions = create_list_attribute();
    }

    attribute_t* restriction = bool_attr_new(class->name, true);

    if (restriction == NULL) {
        fprintf(stderr, "Failed to allocate memory in add_item_restriction");
        return FAILURE;
    }

    int add_rc = add_attribute_to_list(item->class_restrictions, restriction);
    return add_rc;
}

/* see class_item_restriction.h */
bool is_restricted(item_t* item, class_t* class) {
    if ((item == NULL) | (class == NULL)) {
        fprintf(stderr, "Item or Class provided are NULL in is_restricted");
        return FAILURE;
    }

    for (int i = 0; i < class->parent_class_num; i++){
        if (list_contains_attribute(item->class_restrictions, strndup(class->parent_class_names[i], 100))){
            return true;
        }
    }
    return list_contains_attribute(item->class_restrictions, strndup(class->name, 100));
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

    int remove_rc = remove_attribute_from_list(item->class_restrictions, class->name);
    return remove_rc;
}
