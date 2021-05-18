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
    class->stats = stat;
    class->effects = effect;

    /* These are initialized by class_init_skills() */
    class->skilltree = NULL;
    class->combat = NULL;
    class->noncombat = NULL;

    return EXIT_SUCCESS;
}

/* See class.h */
int class_add_skills(class_t* class, skill_inventory_t* combat, 
                     skill_inventory_t *noncombat, skill_tree_t* skilltree) {
    class->combat = combat;
    class->noncombat = noncombat;
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
    if (class->combat != NULL) {
        inventory_free(class->combat);
    }
    if (class->noncombat != NULL) {
        inventory_free(class->noncombat);
    }

    free(class);

    return EXIT_SUCCESS;
}

/* 
 * Functions for manipulating a class hash table. These more or less wrap the 
 * UTHASH macros into a safer and more convenient form. 
 *
 * These functions take in a class_hash_t**, since UTHASH macros may modify the
 * pointer to the actual hashtable (ie, the class_hash_t*). I recommend simply
 * using the reference operator (&) in calls to these functions.
 */

/*
 * Add a class_t to a (possibly NULL) class_hash_t. Fails if the class already
 * exists (ie: Same Name). Returns an error code.
 * (Call find_class internally)
 */
int add_class(class_hash_t** hashtable, class_t* class);

/*
 * Adds or replaces a class in the hashtable. Unlike add_class, this does not
 * fail if a class of the same name already exists. Instead, that class is 
 * replaced (freeing the old class),
 */
void add_or_replace_class(class_hash_t** hashtable, class_t* class);

/*
 * Returns a pointer to a class in the class hashtable. If no class is found,
 * returns NULL.
 */
class_t find_class(class_hash_t** hashtable, char* name);

/*
 * Finds and frees a class in a class hashtable.  Returns a failure if no such
 * class is found 
 */
int delete_class(class_hash_t** hashtable, char* name);

/* 
 * Returns the number of classes in a class hashtable.
 */
int count_classes(class_hash_t** hashtable);

/* 
 * It is infeasible to provide a function for iterating over a hashtable. 
 * If iteration is needed, one should UTHASH's HASH_ITER macro, or the 
 * class->hh.next and class->hh.prev fields. See our tests for how this might
 * be done. 
 */
