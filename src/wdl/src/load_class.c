
#include "wdl/load_class.h"
#include "wdl/validate.h"
#include "playerclass/class_prefabs.h"  
#include "game-state/stats.h"

/*
 * Loads a single class into a game_t
 *
 * Parameters:
 *  - class_obj: The libobj that holds information about the class in question.
 *  - game: The game_t that will hold the initialized class.
 * 
 * Returns:
 *  - SUCCESS if the class loaded successfully.
 *  - FAILURE otherwise.
 */
int load_class(obj_t* class_obj, game_t* game) {
    /* Initialize class to prefab or to new empty class */
    class_t* class = NULL;
    if (obj_get_type(class_obj, "prefab") == TYPE_BOOL && obj_get_bool(class_obj, "prefab")) {
        class = class_prefab_new(game, class_obj->id);
        class_prefab_add_skills(class);
    }
    else {
        class = class_new(class_obj->id, "", "", NULL, NULL, NULL);
    }

    /* Overwrite short description */
    if (obj_get_type(class_obj, "short_desc") == TYPE_STR) {
        char* short_desc = obj_get_str(class_obj, "short_desc");
        strncpy(class->shortdesc, short_desc, MAX_SHORT_DESC_LEN);
    }

    /* Overwrite long description */
    if (obj_get_type(class_obj, "long_desc") == TYPE_STR) {
        char* long_desc = obj_get_str(class_obj, "long_desc");
        strncpy(class->longdesc, long_desc, MAX_LONG_DESC_LEN);
    }

    /* Overwrite attributes */
    if (obj_get_type(class_obj, "attributes") == TYPE_OBJ) {
        if (class->attributes != NULL)
            obj_free_all(class->attributes); 
        class->attributes = obj_get_attr(class_obj, "attributes", false);;
    }

    /* Overwrite stats (does NOT simply add to an existing stat pool) */
    if (obj_get_type(class_obj, "base_stats") == TYPE_OBJ) {
        if (class->base_stats != NULL)
            free_stats(class->base_stats);
        obj_t* stats_obj = obj_get_attr(class_obj, "base_stats", false);
        class->base_stats = NULL; // TODO
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

