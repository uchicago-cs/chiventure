/*
 * Enables players to have more than one class at the same time.
 *
 * For more information see multiclass_prefabs.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "playerclass/class_structs.h"
#include "playerclass/class.h"
#include "playerclass/class_prefabs.h"
#include "playerclass/multiclass_prefabs.h"
#include "skilltrees/skilltree.h"
#include "skilltrees/inventory.h"
#include "common/utlist.h"
#include "playerclass/multiclass.h"


/* Default Multiclasses in alphabetical order. */
const char* const DEFAULT_MULTICLASS_NAMES[] = {
    "hexblade",
    "name1",
    "name2"
};

/* Number of predefined default multiclasses (see above). */
const int DEFAULT_MULTICLASS_COUNT = 3;

/*
 * Determines the index of name in the DEFAULT_MULTICLASS_NAMES array, 
 * for use as an internal id.
 * 
 * Parameters
 *  - name: The name of the class.  Case sensitive.
 * 
 * Returns:
 *  - The index of the name in the DEFAULT_CLASS_NAMES array. Returns -1 if the 
 *    name does not appear or is NULL.
 */
int get_multiclass_name_index(char* name) {
    if (name == NULL)
        return -1;

    char temp_name[MAX_NAME_LEN + 1];
    strncpy(temp_name, name, MAX_NAME_LEN + 1);
    /* make temp_name lowercase */
    for (int i = 0; i < MAX_NAME_LEN + 1; i++) 
        temp_name[i] = tolower(temp_name[i]);

    for (int i = 0; i < DEFAULT_MULTICLASS_COUNT; i++) 
        if (strncmp(temp_name, DEFAULT_MULTICLASS_NAMES[i], MAX_NAME_LEN) == 0) 
            return i;

    return -1;
}

/* See multiclass_prefabs.h */
class_t* multiclass_prefab_new(game_t* game, char* class_name)
{
    /* TODO */
    return NULL;
}

/* See multiclass_prefabs.h */
int multiclass_prefab_add_skills(class_t* multiclass)
{
    /* TODO */
    return 0;
}