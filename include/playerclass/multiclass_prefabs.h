/*
 * Multiclasss prefabs for demo
 */


#ifndef MULTICLASS_PREFABS_H
#define MULTICLASS_PREFABS_H

#include "libobj/obj.h"
#include "common/utlist.h"
#include "playerclass/class_structs.h"
#include "game-state/stats.h"

/*
 * Allocates and initializes a prefab multiclass, and the following fields:
 *  - Short description
 *  - Long description
 *  - Stats
 * To add skill-related fields, see class_prefab_add_skills().
 *
 * Parameters:
 *  - game: The current game struct (contains the global stat hashtable, which 
 *         can be NULL).
 *  - class_name: The name of the prefab multiclass to be generated. 
 *               Must match one of the multiclasses.
 *  - base_class: first class. helps with the descriptions
 *  - second_class: second class for the multiclass. helps with the descriptions
 * 
 * Note: class_name is case insensitive, but the name stored is always lowercase.
 * 
 * Returns:
 *  - A pointer to the new class on success, NULL on failure.
 */
class_t* multiclass_prefab_new(game_t* game, class_t* base_class, 
                            class_t* second_class, char* multiclass_name);

/*
 * Initializes a prefab multiclass's skilltree and active combat and noncombat skill 
 * lists.
 *
 * Parameters:
 *  -multiclass: the multiclass skilltree and lists should be placed in. The field
 *    initialized here are assumed to be empty.
 *
 * Returns:
 *  - status code (FAILURE if the given class or skill is NULL, SUCCESS otherwise.)
 *  - the structs in the class now contain skills.
 * 
 * Notes:
 *  - This function is not fully implemented, as we are waiting for the skill
 *    effects to be more fully developed. However, the warrior class does work,
 *    as a proof of concept.
 */
int multiclass_prefab_add_skills(class_t* multiclass);


#endif /* MULTICLASS_PREFABS_H */