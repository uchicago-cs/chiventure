#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "playerclass/class_structs.h"
#include "playerclass/class.h"
#include "game-state/item.h"

int set_item_restriction(item_t* item, class_t* class) {
    if ((item != NULL) && (class != NULL)) {
        set_bool_attr(item, class->name, true);
    return SUCCESS;
    } else {
        fprintf(stderr, "Item or Class provided are NULL");
        return FAILURE;
    }
}

bool get_class_restriction(item_t* item, class_t* class) {
    if (get_bool_attr(item, class->name)) {
        return true;
    }
    return false;
}