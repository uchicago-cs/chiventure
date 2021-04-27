/*
 * Defines prefabricated classes for use by game devs and in testing.
 */

#ifndef CLASS_PREFABS_H
#define CLASS_PREFABS_H

#include "playerclass/class_structs.h"

/*
 * initializes a prefab class's skilltree and active combat and noncombat skill 
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

class_t* class_prefab_warrior();

#endif /* CLASS_PREFABS_H */
