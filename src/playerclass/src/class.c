/*
 * Defines a player class struct to store base class information.
 *
 * For more information see class.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "playerclass/class_structs.h"
#include "playerclass/class.h"
#include "playerclass/class_prefabs.h"
#include "common/utlist.h"

/* See class.h */
class_t* class_new(char* name, char* shortdesc, char* longdesc,
                   obj_t* attr, stats_hash_t* stat, effects_hash_t* effect) {
    int rc;
    class_t* c;

    c = (class_t*) calloc(1, sizeof(class_t));

    if(c == NULL) {
        fprintf(stderr, "Could not allocate space for class_new.\n");
        return NULL;
    }

    rc = class_init(c, name, shortdesc, longdesc, attr, stat, effect);

    if (rc == EXIT_FAILURE) {
        fprintf(stderr, "Could not initalize values for class_new.\n");
    }

    return c;
}

/* See class.h */
int class_init(class_t* class, char* name, char* shortdesc, char* longdesc,
               obj_t* attr, stats_hash_t* stat, effects_hash_t* effect) {
    if (class == NULL) {
        fprintf(stderr, "Class to initialize in class_init is NULL.\n");
        return EXIT_FAILURE;
    }

    class->name = (char*) calloc(MAX_NAME_LEN + 1, sizeof(char));
    if (class->name == NULL) {
        fprintf(stderr, "Could not allocate memory for name in class_init.\n");
        return EXIT_FAILURE;
    }
    strncpy(class->name, name, MAX_NAME_LEN);

    class->shortdesc = (char*) calloc(MAX_SHORT_DESC_LEN + 1, sizeof(char));
    if (class->name == NULL) {
        fprintf(stderr, "Could not allocate memory for short description in "
                        "class_init.\n");
        return EXIT_FAILURE;
    }
    strncpy(class->shortdesc, shortdesc, MAX_SHORT_DESC_LEN);

    class->longdesc = (char*) calloc(MAX_LONG_DESC_LEN + 1, sizeof(char));
    if (class->name == NULL) {
        fprintf(stderr, "Could not allocate memory for long description in "
                        "class_init.\n");
        return EXIT_FAILURE;
    }
    strncpy(class->longdesc, longdesc, MAX_LONG_DESC_LEN);

    class->attributes = attr;
    class->base_stats = stat;
    class->effects = effect;

    /* These are initialized by class_init_skills() */
    class->skilltree = NULL;
    class->starting_skills = NULL;

    return EXIT_SUCCESS;
}

/* See class.h */
int class_add_skills(class_t* class, skill_inventory_t* starting_skills, 
                     skill_tree_t* skilltree) {
    class->starting_skills = starting_skills;
    class->skilltree = skilltree;
    return EXIT_SUCCESS;
}

/* See class.h */
int class_free(class_t* class) {
    if (class == NULL) {
        return EXIT_SUCCESS;
    }

    if (class->name != NULL) {
        free(class->name);
    }
    if (class->shortdesc != NULL) {
        free(class->shortdesc);
    }
    if (class->longdesc != NULL) {
        free(class->longdesc);
    }
    if (class->skilltree != NULL) {
        skill_tree_free(class->skilltree);
    }
    if (class->starting_skills != NULL) {
        inventory_free(class->starting_skills);
    }

    free(class);

    return EXIT_SUCCESS;
}

/* Class Hashtable functions */

/* See class.h */
int add_class(class_hash_t** hashtable, class_t* class) {
    if (class == NULL || class->name == NULL)
        return FAILURE;

    if (find_class(hashtable, class->name) != NULL)
        return FAILURE;

    HASH_ADD_STR(*hashtable, name, class); 
    return SUCCESS;
}

/* See class.h */
int set_class(class_hash_t** hashtable, class_t* class) {
    if (class == NULL || class->name == NULL)
        return FAILURE;
    
    class_t* replaced_class = NULL;
    HASH_REPLACE_STR(*hashtable, name, class, replaced_class);

    if (replaced_class != NULL)
        class_free(replaced_class);
    
    return SUCCESS;
}

/* See class.h */
class_t* find_class(class_hash_t** hashtable, char* name) {
    if (hashtable == NULL || name == NULL)
        return NULL;
    class_t* output_ptr = NULL;
    HASH_FIND_STR(*hashtable, name, output_ptr);
    return output_ptr;
}

/* See class.h */
int delete_class(class_hash_t** hashtable, char* name) {
    if (hashtable == NULL || name == NULL)
        return FAILURE; 
    
    class_t* class = find_class(hashtable, name);
    if (class == NULL)
        return FAILURE;

    /* Removes class from hashtable */
    HASH_DEL(*hashtable, class);

    /* Class must still be freed after removal */
    class_free(class);

    return SUCCESS;
}

/* See class.h */
int count_classes(class_hash_t** hashtable) {
    return HASH_COUNT(*hashtable);
}

/* This is an active crime scene!!!!
 * 
 * If you remove this function, running "make" will not work (the linker gets
 * stuck at linking the chiventure executable, and claims: "undefined reference 
 * to `class_prefab_new'").  I have tried and tried to find the problem, but I
 * can't find anything.  This function (originally intended to be facade function for
 * class_prefab_new()) was really just an experiment.  THIS SHOULD NOT WORK
 * 
 * Note that the linker is perfectly fine with grabbing stuff from this file, only
 * class_prefabs.c upsets it.
 * 
 * This function will litterally never be executed.  It is not exposed through
 * any .h files.  It should not have an effect anywhere on my code.
 * 
 * FUN FACT: If you surround the class_prefab_new or class_prefab_add_skills
 * calls with something that prevents it from executing (if (1 == 0)), the code
 * won't compile again.  Yay?
 *  
 * This has to go away before I do a PR.
 */
void please_dont_touch_my_trash() {  
    class_t* my_trash = class_prefab_new(NULL, "");
    class_prefab_add_skills(my_trash);
    return;
}
