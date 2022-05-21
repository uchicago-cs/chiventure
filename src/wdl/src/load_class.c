
#include "wdl/load_class.h"
#include "wdl/validate.h"
#include "playerclass/class_prefabs.h"  
#include "game-state/stats.h"

/*
 * Loads a stats_hash_t struct from an object.
 *
 * Parameters:
 *  - stat_block_obj: The object that holds information about the stat block in question.
 *  - game: The current chiventure game struct (holds relevant context).
 * 
 * Returns:
 *  - a pointer to a successfully generated stats_hash_t struct.
 *  - NULL if the stat block failed to load.
 */
stats_hash_t* load_stat_hashtable(obj_t* stat_block_obj, game_t* game) {
    stats_hash_t* stat_block = NULL;
    obj_t *stat_obj, *tmp;
    HASH_ITER(hh, stat_block_obj->data.obj.attr, stat_obj, tmp) {
        /* Currently no TYPE_DOUBLE is supported by libobj */
        if (obj_get_type(stat_obj, "max") != TYPE_INT || obj_get_type(stat_obj, "current") != TYPE_INT) {
            fprintf(stderr, "Failed to load stat.\n");
            return NULL;
        }

        /* Update global stat hashtable if this stat has not yet been declared */
        stats_global_t* global_stat;
        HASH_FIND_STR(game->curr_stats, stat_obj->id, global_stat);
        if (global_stat == NULL) {
            global_stat = stats_global_new(stat_obj->id, obj_get_int(stat_obj, "max"));
            HASH_ADD_STR(game->curr_stats, name, global_stat);
        }
        else if (global_stat->max != obj_get_int(stat_obj, "max")) {
            fprintf(stderr, "Stats have inconsistent max.\n");
            return NULL;
        }

        /* Update output stat hashtable */
        stats_t* stat = stats_new(global_stat, obj_get_int(stat_obj, "current"));
        add_stat(&stat_block, stat);
    }

    return stat_block;
}

/*
 * Loads a single class_t struct from an object.
 *
 * Parameters:
 *  - class_obj: The object that holds information about the class in question.
 *  - game: The current chiventure game struct (holds relevant context).
 * 
 * Returns:
 *  - a pointer to a successfully generated class_t struct.
 *  - NULL if the class failed to load.
 */
class_t* load_class(obj_t* class_obj, game_t* game) {
    /* Initialize class to prefab or to new empty class */
    class_t* class = NULL;
    if (obj_get_type(class_obj, "prefab") == TYPE_BOOL && obj_get_bool(class_obj, "prefab")) {
        class = class_prefab_new(game, class_obj->id);
        if (class == NULL) {
            fprintf(stderr, "Failed to load prefab class with non-matching name.\n");
            return NULL;
        }
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
        obj_t* class_stats_obj = obj_get_attr(class_obj, "base_stats", false); 
        class->base_stats = load_stat_hashtable(class_stats_obj, game);
        if (class->base_stats == NULL) {
            fprintf(stderr, "Failed to load class stats.\n");
            return NULL;
        }
    }

    /* Overwrite effects */
    if (obj_get_type(class_obj, "effects") == TYPE_OBJ) {
        /* Currently, it is unclear how effects and classes work together. 
         * Effects are temporary; there is no way to declare an infinite effect,
         * and temporary effects do not make sense on classes. As such, I am
         * leaving this section blank, until we decide if and how to use effects. */
    }

    /* Overwrite effects */
    if (obj_get_type(class_obj, "skill_tree") == TYPE_OBJ) {
        /* Skill effects are currently undergoing change, so it is best to wait
         * on defining the structure of skills and skill effects in JSON. */
    }

    /* Overwrite effects */
    if (obj_get_type(class_obj, "starting_skills") == TYPE_OBJ) {
        /* See above. It is best to wait on the skilltrees team to determine how
         *  they want to store skill information. */
    }
 
    return class;
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
        class_t* class = load_class(class_obj, game);
        if (class == NULL) {
            fprintf(stderr, "Failed to load class with name %s.\n", class_obj->id);
            return FAILURE;
        }

        /* Add class to global class hashtable */
        if (add_class(&(game->all_classes), class) == FAILURE) {
            fprintf(stderr, "Could not add class to global class hashtable.\n");
            return FAILURE;
        }
    }

    return SUCCESS;
}

