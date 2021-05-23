
#include "wdl/load_class.h"
#include "wdl/validate.h"
#include "playerclass/class_prefabs.h"  

// RETURNS ERROR CODE
int load_class(obj_t* class_obj, game_t* game) {
    class_t* class = NULL;
    if (obj_get_type(class_obj, "prefab") == TYPE_BOOL && obj_get_bool(class_obj, "prefab")) {
        class = class_prefab_new(game, "monk"); // Still messing around
    }
    else {
        class = class_new(class_obj->id, "", "", NULL, NULL, NULL);
    }

    /* Add class to global class hashtable */
    if (add_class(&(game->all_classes), class) == FAILURE) {
        fprintf(stderr, "Could not add class to global class hashtable.\n");
        return FAILURE;
    }
    
    return SUCCESS;
}

/* See load_class.h */
int load_classes(obj_t* obj_store, game_t* game) {
    obj_t *classes_obj = obj_get_attr(obj_store, "CLASSES", false);

    /* Failing to find a CLASSES object is OK, as many games will not define classes */
    if (classes_obj == NULL)
        return SUCCESS;
    
    /* Validate objects in CLASS */
    if (list_type_check(classes_obj, class_type_check) == FAILURE)
    {
        fprintf(stderr, "One or more classes fail type checking.\n");
        return FAILURE;
    }

    /* Iterate over attributes of CLASSES and add them to game */
    obj_t *class_obj, *tmp;
    HASH_ITER(hh, classes_obj->data.obj.attr, class_obj, tmp) {
        if (load_class(class_obj, game) == FAILURE) {
            fprintf(stderr, "Failed to load class with name %s.\n", class_obj->id);
            return FAILURE;
        }
    }

    return SUCCESS;
}

