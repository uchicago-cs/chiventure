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
 * 
 * Note: class_name is case insensitive, but the name stored is always lowercase.
 * 
 * Returns:
 *  - A pointer to the new class on success, NULL on failure.
 */
class_t* multiclass_prefab_new(game_t* game, char* class_name);


#endif MULTICLASS_PREFABS_H