#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "game-state/item.h"
#include "playerclass/class.h"
#include "playerclass/class_structs.h"

/* see class_item_restriction.h */
int set_item_restriction(item_t* item, class_t* class) {
    if ((item != NULL) && (class != NULL)) {
        if (item->class_restrictions == NULL) {
            item->class_restrictions = create_list_attribute();
        }

        attribute_t* restriction = malloc(sizeof(attribute_t));
        restriction->attribute_tag = BOOLE;
        restriction->attribute_value.bool_val = true;
        restriction->attribute_key = strndup(class->name, 100);

        if (restriction == NULL) {
            fprintf(stderr, "Failed to allocate memory");
        }

        add_attribute_to_list(item->class_restrictions, restriction);
        return SUCCESS;
    } else {
        fprintf(stderr, "Item or Class provided are NULL");
        return FAILURE;
    }
}

/* see class_item_restriction.h */
bool get_class_restriction(item_t* item, class_t* class) {
    return !list_contains_attribute(item->class_restrictions, class->name);
}
