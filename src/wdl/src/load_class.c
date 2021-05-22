
#include "wdl/load_class.h"
#include "wdl/validate.h"

/* See load_class.h */
/* TODO: Remove [LOAD CLASSES] debug print statements */
int load_classes(obj_t* obj_store, game_t* game) {
    printf("[LOAD CLASSES] Trying to load classes.\n");
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
    

    return SUCCESS;
}

