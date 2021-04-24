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
#include "class_skills.h"
#include "common/utlist.h"

/* Rudimentary id system for prefab classes (internal) */

// Default Classes in alphabetical order.
const char* const DEFAULT_CLASS_NAMES[] = {
    "bard",
    "druid",
    "elementalist",
    "knight",
    "monk",
    "ranger",
    "rogue",
    "sorcerer",
    "warrior",
    "wizard",
};

// Number of predefined default classes (see above).
const int DEFAULT_CLASS_COUNT = 10;

/*
 * Determines the index of name in the DEFAULT_CLASS_NAMES array, for use as an
 * internal id.
 * 
 * Parameters
 * - name: The name of the class.  Case sensitive.
 * 
 * Returns:
 * - The index of the name in the DEFAULT_CLASS_NAMES array. Returns -1 if the 
 *   name does not appear or is NULL.
 */
int get_class_name_index(char* name) {
    if (name == NULL)
        return -1;

    char* temp_name = (char *) calloc(MAX_NAME_LEN + 1, sizeof(char));
    strncpy(temp_name, name, MAX_NAME_LEN);
    // make temp_name lowercase
    for (char* ch_p = temp_name; *ch_p != '\0'; ch_p += sizeof(char)) 
        *ch_p = tolower(*ch_p);

    for (int i = 0; i < DEFAULT_CLASS_COUNT; i++) 
        if (strcmp(temp_name, DEFAULT_CLASS_NAMES[i]) == 0) {
            free(temp_name);
            return i;
        }
    
    free(temp_name);
    return -1;
}

/* See class.h */
class_t* class_new(char* name, char* shortdesc, char* longdesc,
                   obj_t* attr, stats_hash_t* stat, effects_hash_t* effect)
{
    int rc;
    class_t* c;

    c = (class_t*) calloc(1, sizeof(class_t));

    if(c == NULL)
    {
        fprintf(stderr, "Could not allocate space for class_new.\n");
        return NULL;
    }

    rc = class_init(c, name, shortdesc, longdesc, attr, stat, effect);

    if (rc == EXIT_FAILURE){
        fprintf(stderr, "Could not initalize values for class_new.\n");
    }

    return c;
}

/* See class.h */
int class_init(class_t* class, char* name, char* shortdesc, char* longdesc,
               obj_t* attr, stats_hash_t* stat, effects_hash_t* effect)
{
    if (class == NULL)
    {
        fprintf(stderr, "Class to initialize in class_init is NULL.\n");
        return EXIT_FAILURE;
    }

    class->name = (char*) calloc(MAX_NAME_LEN + 1, sizeof(char));
    if (class->name == NULL)
    {
        fprintf(stderr, "Could not allocate memory for name in class_init.\n");
        return EXIT_FAILURE;
    }
    strncpy(class->name, name, MAX_NAME_LEN);

    class->shortdesc = (char*) calloc(MAX_SHORT_DESC_LEN + 1, sizeof(char));
    if (class->name == NULL)
    {
        fprintf(stderr, "Could not allocate memory for short description in "
                        "class_init.\n");
        return EXIT_FAILURE;
    }
    strncpy(class->shortdesc, shortdesc, MAX_SHORT_DESC_LEN);

    class->longdesc = (char*) calloc(MAX_LONG_DESC_LEN + 1, sizeof(char));
    if (class->name == NULL)
    {
        fprintf(stderr, "Could not allocate memory for long description in "
                        "class_init.\n");
        return EXIT_FAILURE;
    }
    strncpy(class->longdesc, longdesc, MAX_LONG_DESC_LEN);

    // Skill Related Allocations
    class->combat = inventory_new(MAX_ACTIVE_SKILLS, MAX_PASSIVE_SKILLS);
    class->noncombat = inventory_new(MAX_ACTIVE_SKILLS, MAX_PASSIVE_SKILLS);
    
    /* tree ID needs to be unique across all chiventure code.  Our team has been
     * assigned the range 3000-3999.  Default classes start at 3000. There is
     * currently no support for non-prefab classes. */
    int class_id = get_class_name_index(class->name);
    if (class_id == -1)
    {
        fprintf(stderr, "Could not find class name: \"%s\" "
                        "in class_init\n", class->name);
        return EXIT_FAILURE;
    }
    int tid = 3000 + class_id;
    class->skilltree = skill_tree_new(tid, class->name, MAX_SKILLS_IN_TREE);

    if (class->skilltree == NULL)
    {
        fprintf(stderr, "Could not allocate memory for skill trees "
                        "class_init\n");
        return EXIT_FAILURE;
    }
    if (class->combat == NULL || class->noncombat == NULL)
    {
        fprintf(stderr, "Could not allocate memory for skill inventories"
                        "class_init\n");
    }

    if (class_skills_init(class) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }

    class->attributes = attr;
    class->stats = stat;
    class->effects = effect;
    return EXIT_SUCCESS;
}

/* See class.h */
int class_free(class_t* class)
{
    if (class == NULL)
    {
        return EXIT_SUCCESS;
    }

    if (class->name != NULL)
    {
        free(class->name);
    }
    if (class->shortdesc != NULL)
    {
        free(class->shortdesc);
    }
    if (class->longdesc != NULL)
    {
        free(class->longdesc);
    }
    if (class->skilltree != NULL)
    {
        skill_tree_free(class->skilltree);
    }
    if (class->combat != NULL)
    {
        inventory_free(class->combat);
    }
    if (class->noncombat != NULL)
    {
        inventory_free(class->noncombat);
    }

    free(class);

    return EXIT_SUCCESS;
}
