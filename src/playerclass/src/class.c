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

/* Default Classes in alphabetical order. */
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

/* Number of predefined default classes (see above). */
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

    char temp_name[MAX_NAME_LEN + 1];
    strncpy(temp_name, name, MAX_NAME_LEN);
    /* make temp_name lowercase */
    for (int i = 0; i < MAX_NAME_LEN + 1; i++) 
        temp_name[i] = tolower(temp_name[i]);

    for (int i = 0; i < DEFAULT_CLASS_COUNT; i++) 
        if (strncmp(temp_name, DEFAULT_CLASS_NAMES[i], MAX_NAME_LEN) == 0) 
            return i;

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

    class->parent_class_num = 0;
    class->parent_class_names = NULL;

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

    class->attributes = attr;
    class->stats = stat;
    class->effects = effect;

    /* These are initialized by class_init_skills() */
    class->skilltree = NULL;
    class->combat = NULL;
    class->noncombat = NULL;

    return EXIT_SUCCESS;
}

/*
 * Creates a shortdesc for a multiclass by simply listing the component classes.
 *
 * Paramaters:
 *  - base_class: the character's base class (their current class).
 *  - new_class: the class being added to the original class.
 *
 * Returns:
 *  - a pointer to a string with the new shortdesc.
 */
char* multiclass_shortdesc (class_t* base_class, class_t* second_class){
    char* new_shortdesc = (char*) malloc(MAX_SHORT_DESC_LEN + 1);
    strcat (new_shortdesc, "Multiclass of ");
    strcat (new_shortdesc, base_class->name);
    strcat (new_shortdesc, ", ");
    strcat (new_shortdesc, second_class->name);
    for (int i = 0; i < base_class->parent_class_num; i++){
        strcat (new_shortdesc, ", ");
        strcat (new_shortdesc, base_class->parent_class_names[i]);
    }
    for (int i = 0; i < second_class->parent_class_num; i++){
        strcat (new_shortdesc, ", ");
        strcat (new_shortdesc, second_class->parent_class_names[i]);
    }
    strcat (new_shortdesc, ".");
    return new_shortdesc;
}

/*
 * Creates a longdesc for a multiclass by concatenating the shortdescs
 * of all the component classes.
 *
 * Paramaters:
 *  - base_class: the character's base class (their current class).
 *  - new_class: the class being added to the original class.
 *
 * Returns:
 *  - a pointer to a string with the new longdesc.
 */
char* multiclass_longdesc (class_t* base_class, class_t* second_class){
    char* new_longdesc = (char*) malloc(MAX_LONG_DESC_LEN + 1);
    strcat (new_longdesc, base_class->shortdesc);
    strcat (new_longdesc, "\n\n");
    strcat (new_longdesc, second_class->shortdesc);
    return new_longdesc;
}

/* See class.h */
class_t* multiclass(class_t* base_class, class_t* second_class, char* name){
    char* new_shortdesc = multiclass_shortdesc(base_class, second_class);
    char* new_longdesc = multiclass_longdesc(base_class, second_class);
    obj_t* combined_attr = NULL; // I dont think this works: int obj_add_attr(base_class->attributes, second_class->attributes->id, second_class->attributes);
    effects_hash_t* combined_effects = NULL; //TODO, will need a new get all function for effects_hash_t
    
    class_t* new_class = class_new(name, new_shortdesc, new_longdesc, combined_attr, base_class->stats, combined_effects);
    if (new_class == NULL) return NULL;
    
    new_class->parent_class_num = 2 + base_class->parent_class_num + second_class->parent_class_num;
    new_class->parent_class_names = (char**) malloc (new_class->parent_class_num * sizeof(char*));
    for (int i = 0; i < new_class->parent_class_num; i++){
        new_class->parent_class_names[i] = (char*) calloc(MAX_NAME_LEN + 1, sizeof(char));
        if (parent_class_names[i] == NULL) return NULL;
    }
    memcpy(new_class->parent_class_names[0], base_class->name, MAX_NAME_LEN + 1)
    memcpy(new_class->parent_class_names[1], second_class->name, MAX_NAME_LEN + 1)
    int i = 0;
    while (i < base_class->parent_class_num){
        memcpy(new_class->parent_class_names[i + 2], base_class->parent_class_names[i], MAX_NAME_LEN + 1)
    }
    while (i < second_class->parent_class_num - base_class->parent_class_num){
        memcpy(new_class->parent_class_names[i + 2], second_class->parent_class_names[i], MAX_NAME_LEN + 1)
    }
    return new_class;
}


/* See class.h */
int class_init_skills(class_t* class, int max_skills_in_tree, 
                      int max_active_skills, int max_passive_skills) 
{
    class->combat = inventory_new(max_active_skills, max_passive_skills);
    class->noncombat = inventory_new(max_active_skills, max_passive_skills);
    
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
    class->skilltree = skill_tree_new(tid, class->name, max_skills_in_tree);

    if (class->skilltree == NULL)
    {
        fprintf(stderr, "Could not allocate memory for skill trees "
                        "in class_init\n");
        return EXIT_FAILURE;
    }
    if (class->combat == NULL || class->noncombat == NULL)
    {
        fprintf(stderr, "Could not allocate memory for skill inventories"
                        "in class_init\n");
        return EXIT_FAILURE;
    }
    if (class_add_skills(class) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }

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
    if (class->parent_class_names != NULL){
        for (int i = 0; i < class->parent_class_num){
            free (class->parent_class_names[i]);
            i++;
        }
        free (class->parent_class_names)
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
