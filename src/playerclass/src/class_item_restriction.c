#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "game-state/item.h"
#include "playerclass/class.h"
#include "playerclass/class_structs.h"

/* see class_item_restriction.h */
int set_item_restriction(item_t* item, class_t* class) {
    if ((item != NULL) && (class != NULL)) {
        set_bool_attr(item, class->name, true);
        return SUCCESS;
    } else {
        fprintf(stderr, "Item or Class provided are NULL");
        return FAILURE;
    }
}

/* see class_item_restriction.h */
bool get_class_restriction(item_t* item, class_t* class) {
    if (get_bool_attr(item, class->name) == false) return false;
    for (int i = 0; i < class->parent_class_num; i++){
        if (get_bool_attr(item, parent_class_names[i]->name) == false)
    }
    return true;
}
