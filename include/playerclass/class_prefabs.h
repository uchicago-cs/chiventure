/*
 * Defines prefabricated classes for use by game devs and in testing.
 */

#ifndef CLASS_PREFABS_H
#define CLASS_PREFABS_H

#include "playerclass/class_structs.h"

/*
 * Allocates and initializes a prefab class, and its non-skill-related fields.
 * To add skill-related fields, see class_prefab_add_skills().
 *
 * Parameters:
 *  - class_name: The name of the prefab class to be generated.  Must match one
 *                of our classes.
 * 
 * Note: class_name is case insensitive, but the name stored is always lowercase.
 * 
 * Returns:
 *  - A pointer to the new class on success, NULL on failure.
 */
class_t* class_prefab_new(char *class_name);

/*
 * Initializes a prefab class's skilltree and active combat and noncombat skill 
 * lists.
 *
 * Parameters:
 *  - class: the class the skilltree and lists should be placed in. The field
 *    initialized here are assumed to be empty.
 *
 * Returns:
 *  - status code
 *  - the structs in the class now contain skills.
 */
int class_prefab_add_skills(class_t* class);

/* Temporary function, target for deletion */
class_t* class_prefab_warrior();

#endif /* CLASS_PREFABS_H */
