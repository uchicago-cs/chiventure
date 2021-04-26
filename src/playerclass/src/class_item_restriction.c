#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "game-state/item.h"
#include "playerclass/class.h"
#include "playerclass/class_structs.h"

/* see class_item_restriction.h */
int add_item_restriction(item_t* item, class_t* class) {
    if ((item != NULL) && (class != NULL)) {
        if (item->class_restrictions == NULL) {
            item->class_restrictions = create_list_attribute();
        }

        /* Attribute creation will be refactored in game-state/item to allow for streamlined attribute creation */
        attribute_t* restriction = malloc(sizeof(attribute_t));
        restriction->attribute_tag = BOOLE;
        restriction->attribute_value.bool_val = true;
        restriction->attribute_key = strndup(class->name, 100);

        if (restriction == NULL) {
            fprintf(stderr, "Failed to allocate memory");
        }

        int add_rc = add_attribute_to_list(item->class_restrictions, restriction);
        return add_rc;
    } else {
        fprintf(stderr, "Item or Class provided are NULL");
        return FAILURE;
    }
}

/* see class_item_restriction.h */
bool is_restricted(item_t* item, class_t* class) {
    if ((item != NULL) && (class != NULL)) {
        return (list_contains_attribute(item->class_restrictions, strndup(class->name, 100)) == SUCCESS);
    } else {
        fprintf(stderr, "Item or Class provided are NULL");
        return FAILURE;
    }
}

/* see class_item_restriction.h */
int remove_item_restriction(item_t* item, class_t* class) {
    if ((item != NULL) && (class != NULL)) {
        if (!is_restricted(item, class)){
            fprintf(stderr, "Class is not currently restricted from using this item");
            return FAILURE;
        }
        int remove_rc = remove_attribute_from_list(item->class_restrictions, class->name);
        return remove_rc;
    } else {
        fprintf(stderr, "Item or Class provided are NULL");
        return FAILURE;
    }
}
